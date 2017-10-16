#include "opencv2/opencv.hpp"
using namespace cv;
#include <iostream>
using namespace std;
#include <math.h>

#define MY_OK 1
#define MY_FAIL -1

#define R_LEN 1000//估计的 max_radius + 6 的大小
#define CIRCLE_NUM 100000//估计第一遍找到的圆的个数

//#define IMG_SHOW

int ustc_Find_Circles_By_Difference(
	Mat colorImg,
	int min_radius,
	int max_radius,
	int min_center_dist,
	int min_radius_dist,
	int max_circle_diff,
	int* x,
	int* y,
	int* radius,
	int* circle_cnt,
    int max_circle)
{
	if (max_radius + 6  > R_LEN)
	{
		cout <<"max_radius is too big." << endl;
		return MY_FAIL;
	}
	if (max_circle_diff < 20)
	{
		cout << "max_circle_diff is too small." << endl;
		return MY_FAIL;
	}
	//分离三个通道
	vector<Mat> channels;
	split(colorImg, channels);

	int width = channels[0].cols;
	int height = channels[0].rows;

	//计算三角函数
	float cosx[90];
	float sinx[90];
	int x_rtheta[R_LEN][90];
	int y_rtheta[R_LEN][90];
	memset(x_rtheta, 0, sizeof(x_rtheta));
	memset(y_rtheta, 0, sizeof(y_rtheta));
	int lowbound_radius = min_radius - 5;
	int upbound_radius  = max_radius + 5;
	for (int i = 0; i < 90; i++)
	{
		cosx[i] = (float)cos((float)i / 180 * 3.1416);
        sinx[i] = (float)sin((float)i / 180 * 3.1416);
        for (int r = lowbound_radius; r <= upbound_radius; r++)
		{
			x_rtheta[r][i] = int(r * cosx[i]);
			y_rtheta[r][i] = int(r * sinx[i]);	
		}
	}
	
	int B_sum_gray[R_LEN] = { 0 };
	int G_sum_gray[R_LEN] = { 0 };
	int R_sum_gray[R_LEN] = { 0 };
	uchar* BImg_data = channels[0].data;
	uchar* GImg_data = channels[1].data;
	uchar* RImg_data = channels[2].data;
	int* BGR_x =      new int[CIRCLE_NUM];
	int* BGR_y =      new int[CIRCLE_NUM];
	int* BGR_radius = new int[CIRCLE_NUM];
	int* BGR_diff =   new int[CIRCLE_NUM];
	int counter = 0;
#ifdef IMG_SHOW
	Mat resultImg(height, width, CV_8UC3, Scalar(255, 255, 255));
#endif

	for (int row_i = 0; row_i < height; row_i++)
	{
		for (int col_j = 0; col_j < width; col_j++)
		{
			//计算不同半径的圆周亮度平均值
			for (int r = lowbound_radius; r <= upbound_radius; r++)
			{
				B_sum_gray[r] = 0;
				G_sum_gray[r] = 0;
				R_sum_gray[r] = 0;
				for (int theta = 0; theta < 90; theta++)
				{
					int temp_x = x_rtheta[r][theta];
					int now_px = col_j + temp_x;
					int now_nx = col_j - temp_x;
					int temp_y = y_rtheta[r][theta];
					int now_py = row_i + temp_y;
					int now_ny = row_i - temp_y;
					
					if (now_nx >= 0)
					{
						if (now_ny >= 0)     
						{ 
							int index_ny_nx = now_ny * width + now_nx;
							B_sum_gray[r] += BImg_data[index_ny_nx];
							G_sum_gray[r] += GImg_data[index_ny_nx];
							R_sum_gray[r] += RImg_data[index_ny_nx];
						}
						if (now_py <= height)
						{
							int index_py_nx = now_py * width + now_nx;
							B_sum_gray[r] += BImg_data[index_py_nx];
							G_sum_gray[r] += GImg_data[index_py_nx];
							R_sum_gray[r] += RImg_data[index_py_nx];
						}
					}
					if (now_px <= width)
					{
						if (now_ny >= 0)     
						{ 
							int index_ny_px = now_ny * width + now_px;
							B_sum_gray[r] += BImg_data[index_ny_px];
							G_sum_gray[r] += GImg_data[index_ny_px];
							R_sum_gray[r] += RImg_data[index_ny_px];
						}
						if (now_py <= height)
						{
							int index_py_px = now_py * width + now_px;
							B_sum_gray[r] += BImg_data[index_py_px];
							G_sum_gray[r] += GImg_data[index_py_px];
							R_sum_gray[r] += RImg_data[index_py_px];
						}
					}
				}
				B_sum_gray[r] = B_sum_gray[r] / 360;
				G_sum_gray[r] = G_sum_gray[r] / 360;
				R_sum_gray[r] = R_sum_gray[r] / 360;
			}
			//算差分
			for (int r = min_radius; r <= max_radius; r++)
			{
				int B_temp_diff = abs(B_sum_gray[r + 5] - B_sum_gray[r - 5]);
				if (B_temp_diff >= max_circle_diff)
				{
					if (abs(r - BGR_radius[counter - 1]) > min_radius_dist || 
				        (abs(col_j - BGR_x[counter - 1]) > min_center_dist || abs(row_i - BGR_y[counter - 1]) > min_center_dist))
					{
						BGR_x[counter] = col_j;
						BGR_y[counter] = row_i;
						BGR_radius[counter] = r;
						BGR_diff[counter] = B_temp_diff;
#ifdef IMG_SHOW
						cout << counter << '\t' << BGR_x[counter] << '\t' << BGR_y[counter] << '\t' << BGR_radius[counter] << '\t' << BGR_diff[counter] << endl;
#endif
						counter++;
						if (counter == CIRCLE_NUM)
						{
							cout << "array index is out of range." << endl;
							return MY_FAIL;
						}
						continue;
					}
				}
				int G_temp_diff = abs(G_sum_gray[r + 5] - G_sum_gray[r - 5]);
				if (G_temp_diff >= max_circle_diff)
				{
					if (abs(r - BGR_radius[counter - 1]) > min_radius_dist ||
						(abs(col_j - BGR_x[counter - 1]) > min_center_dist || abs(row_i - BGR_y[counter - 1]) > min_center_dist))
					{
						BGR_x[counter] = col_j;
						BGR_y[counter] = row_i;
						BGR_radius[counter] = r;
						BGR_diff[counter] = G_temp_diff;
#ifdef IMG_SHOW
						cout << counter << '\t' << BGR_x[counter] << '\t' << BGR_y[counter] << '\t' << BGR_radius[counter] << '\t' << BGR_diff[counter] << endl;
#endif
						counter++;
						if (counter == CIRCLE_NUM)
						{
							cout << "array index is out of range." << endl;
							return MY_FAIL;
						}
						continue;
					}
				}
				int R_temp_diff = abs(R_sum_gray[r + 5] - R_sum_gray[r - 5]);
				if (R_temp_diff >= max_circle_diff)
				{
					if (abs(r - BGR_radius[counter - 1]) > min_radius_dist ||
						(abs(col_j - BGR_x[counter - 1]) > min_center_dist || abs(row_i - BGR_y[counter - 1]) > min_center_dist))
					{
						BGR_x[counter] = col_j;
						BGR_y[counter] = row_i;
						BGR_radius[counter] = r;
						BGR_diff[counter] = R_temp_diff;
#ifdef IMG_SHOW
						cout << counter << '\t' << BGR_x[counter] << '\t' << BGR_y[counter] << '\t' << BGR_radius[counter] << '\t' << BGR_diff[counter] << endl;
#endif
						counter++;
						if (counter == CIRCLE_NUM)
						{
							cout << "array index is out of range." << endl;
							return MY_FAIL;
						}
						continue;
					}
				}
			}
		}
	}

	//融合
	int* tag = new int[counter];
	memset(tag, 0, sizeof(tag));
	for (int now_i = 0; now_i < counter; now_i++)
	{
		//非极大值抑制
		for (int back_i = 0; back_i < now_i; back_i++)
		{
			if (abs(BGR_radius[now_i] - BGR_radius[back_i]) < min_radius_dist &&
				(abs(BGR_x[now_i] - BGR_x[back_i]) < min_center_dist && abs(BGR_y[now_i] - BGR_y[back_i]) < min_center_dist))
			{
				tag[now_i] = 1;
				break;
			}
		}
	}
	//数找到的圆的个数
	int number = 0;
	for (int now_i = 0; now_i < counter; now_i++)
	{
		if (tag[now_i] == 0)
		{
			number++;
		}
	}
	if (number <= max_circle)
	{
		*circle_cnt = number;
		int New_num = 0;
		for (int now_i = 0; now_i < counter; now_i++)
		{
			if (tag[now_i] == 0)
			{
				x[New_num] = BGR_x[now_i];
				y[New_num] = BGR_y[now_i];
				radius[New_num] = BGR_radius[now_i];
#ifdef IMG_SHOW
				cout << New_num << '\t' << x[New_num] << '\t' << y[New_num] << '\t' << radius[New_num] << endl;
				circle(resultImg, Point(BGR_x[now_i], BGR_y[now_i]), BGR_radius[now_i], Scalar(0, 0, 0));
#endif
				New_num++;
			}
		}
	}
	else if (number > max_circle)
	{
		*circle_cnt = max_circle;
		int* all_circle = new int[number];//所有满足要求的圆
		int Alc_i = 0;
		for (int now_i = 0; now_i < counter; now_i++)
		{
			if (tag[now_i] == 0)
			{
				all_circle[Alc_i] = now_i;//记下在原来粗选序列中的序号
				Alc_i++;
			}
		}
		int sortbound = max_circle;
		int New_num = 0;
		int temp, j, i;
		for (j = 0; j < sortbound; j++)
		{
			for (i = 0; i < Alc_i - 1 - j; i++)
			{
				int a = all_circle[i];
				int b = all_circle[i + 1];
				if (BGR_diff[a] > BGR_diff[b])
				{
					temp = all_circle[i];
					all_circle[i] = all_circle[i + 1];
					all_circle[i + 1] = temp;
				}
			}
			int chosen_i = all_circle[i];
			x[New_num] = BGR_x[chosen_i];
			y[New_num] = BGR_y[chosen_i];
			radius[New_num] = BGR_radius[chosen_i];
#ifdef IMG_SHOW
			cout << New_num << '\t' << x[New_num] << '\t' << y[New_num] << '\t' << radius[New_num] << endl;
			circle(resultImg, Point(BGR_x[chosen_i], BGR_y[chosen_i]), BGR_radius[chosen_i], Scalar(0, 0, 0));
#endif
			New_num++;
		}
	}
	
#ifdef IMG_SHOW
	namedWindow("colorImg", 0);
	imshow("colorImg", colorImg);
	namedWindow("result", 0);
	imshow("result", resultImg);
	waitKey();
#endif
	
	return MY_OK;
}
