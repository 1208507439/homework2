#include<opencv2/opencv.hpp>
#include<cv.h>
#include<iostream>
using namespace cv;
using namespace std;
#define MY_OK 1
#define MY_FAIL 0
#define MAX_VALUE 100000
int x_0[MAX_VALUE] = { 0 }, y_0[MAX_VALUE] = { 0 }, radius_0[MAX_VALUE] = { 0 };

//功能说明：找到图像中所有圆心在图像内的圆，得到中心点和半径
//colorImg：用来搜索圆形目标的彩色图像
//min_radius：需要搜索的圆的最小半径
//max_radius：需要搜索的圆的最大半径
//min_center_dist：找到的圆心之间的最小距离
//min_radius_dist：同心圆半径之间的最小差距
//max_circle_diff：阈值，圆周差分值低于此阈值，不是圆
//x：数组，存储所有的圆的中心点x坐标
//y：数组，存储所有的圆的中心点y坐标
//radius：数组，存储所有的圆的半径值
//circle_cnt：图像中找到的圆的数目
//max_circle：外部传入参数，圆的数目上限。如果图像中圆的数目超过此参数，根据差分值由大到小进行排序
//返回值：MY_OK或者MY_FAIL
int ustc_Find_Circles_By_Difference
(Mat colorImg,
	int min_radius,
	int max_radius,
	int min_center_dist,
	int min_radius_dist,
	int max_circle_diff,
	int* x,
	int* y,
	int *radius,
	int *circle_cnt,
	int max_circle
)
{
	memset(x, 0, sizeof(int)*max_circle);
	memset(y, 0, sizeof(int)*max_circle);
	memset(radius, 0, sizeof(int)*max_circle);

	
	int center2 = min_center_dist*min_center_dist;
	(*circle_cnt) = 0;

	if (NULL == colorImg.data)
	{
		cout << "image is NULL." << endl;
		return MY_FAIL;
	}


	if (colorImg.channels() != 3)
	{
		cout << "channels not match." << endl;
		return MY_FAIL;
	}


	float factor = CV_PI / 180;
	int height = colorImg.rows;
	int width = colorImg.cols;

	if (2 * max_radius > height)
	{
		max_radius = height / 2;
	}

	if (2 * max_radius > width)
	{
		max_radius = width / 2;
	}

	Mat grayImg(height, width, CV_8UC1);
	Mat grad_x(height, width, CV_32FC1);
	Mat grad_y(height, width, CV_32FC1);
	Mat binaryImg(height, width, CV_8UC1);


	//分离三个通道
	Mat bImg(height, width, CV_8UC1);
	Mat gImg(height, width, CV_8UC1);
	Mat rImg(height, width, CV_8UC1);

	for (int ii = 0; ii < height; ii++)
	{
		int temp = ii*width;
		for (int jj = 0; jj < width; jj++)
		{
			bImg.data[temp + jj] = colorImg.data[3 * (temp + jj)];
			gImg.data[temp + jj] = colorImg.data[3 * (temp + jj) + 1];
			rImg.data[temp + jj] = colorImg.data[3 * (temp + jj) + 2];
		}
	}


	//打表优化
	int* r_sin_list = new int[(max_radius + 6) * 360];
	int* r_cos_list = new int[(max_radius + 6) * 360];
	int* r_tri_list = new int[(max_radius + 6) * 360];
	for (int rr = min_radius - 5; rr <= max_radius + 5; rr++)
	{
		int temp_rr = 360 * rr;
		for (int angle = 0; angle < 360; angle++)
		{
			r_sin_list[temp_rr + angle] = ((int)(sin(angle*factor)*rr));
			r_cos_list[temp_rr + angle] = ((int)(cos(angle*factor)*rr));
			r_tri_list[temp_rr + angle] = ((int)(sin(angle*factor)*rr)) + ((int)(cos(angle*factor)*rr))*width;
		}
	}


	//在外部定义变量优化速度
	int* sum_light_b = new int[height*width];
	int* sum_light_g = new int[height*width];
	int* sum_light_r = new int[height*width];
	int* max_diff = new int[height*width*max_radius];
	memset(max_diff, 0, sizeof(int)*height*width*max_radius);

	int r1 = max_radius > 57 ? 57 : max_radius;
	for (int r = min_radius; r < r1; r++)
	{
		int dif_rmax = r + 5;
		int dif_rmin = r - 5;
		int temp_tri_r = r * 360;
		int temp_tri_rmax = dif_rmax * 360;
		int temp_tri_rmin = dif_rmin * 360;
		//清空数组
		memset(sum_light_b, 0, sizeof(int)*height*width);
		memset(sum_light_g, 0, sizeof(int)*height*width);
		memset(sum_light_r, 0, sizeof(int)*height*width);

		//以固定大小的圆去每个去遍历像素，计算每个点的亮度差值情况存入数组

		for (int angle = 0; angle < 360; angle += 2)
		{
			int temp_r_max = temp_tri_rmax + angle;
			int temp_r_min = temp_tri_rmin + angle;
			int temp_r = temp_tri_r + angle;
			for (int row_x = r; row_x < height - r; row_x++)
			{
				int temp0 = row_x + r_cos_list[temp_r_max];

				if (temp0<0 || temp0 >= height)
				{
					continue;
				}

				int temp_row = row_x*width;
				int temp_row_r_max = temp_row + r_tri_list[temp_r_max];
				int temp_row_r_min = temp_row + r_tri_list[temp_r_min];
				int temp_row_r = temp_row + r_tri_list[temp_r];


				for (int col_y = r; col_y < width - r; col_y++)
				{
					int temp1 = col_y + r_sin_list[temp_r_max];
					if (temp1<0 || temp1 >= width)
					{
						continue;
					}
					sum_light_b[temp_row + col_y] += (bImg.data[temp_row_r_max + col_y] - bImg.data[temp_row_r_min + col_y]);
					sum_light_g[temp_row + col_y] += (gImg.data[temp_row_r_max + col_y] - gImg.data[temp_row_r_min + col_y]);
					sum_light_r[temp_row + col_y] += (rImg.data[temp_row_r_max + col_y] - rImg.data[temp_row_r_min + col_y]);
				}
			}
		}


		//遍历数组，判断是否为圆
		for (int row_x = 0; row_x < height; row_x++)
		{
			int temp = row_x*width;

			for (int col_y = 0; col_y < width; col_y++)
			{
				sum_light_b[temp + col_y] = sum_light_b[temp + col_y] > 0 ? (sum_light_b[temp + col_y] / 180) : (-sum_light_b[temp + col_y] / 180);
				sum_light_g[temp + col_y] = sum_light_g[temp + col_y] > 0 ? (sum_light_g[temp + col_y] / 180) : (-sum_light_g[temp + col_y] / 180);
				sum_light_r[temp + col_y] = sum_light_r[temp + col_y] > 0 ? (sum_light_r[temp + col_y] / 180) : (-sum_light_r[temp + col_y] / 180);

				int max = sum_light_b[temp + col_y];
				if (sum_light_g[temp + col_y] > max) max = sum_light_g[temp + col_y];
				if (sum_light_r[temp + col_y] > max) max = sum_light_r[temp + col_y];

				if (max >= max_circle_diff)
				{
					x_0[(*circle_cnt)] = row_x;
					y_0[(*circle_cnt)] = col_y;
					radius_0[(*circle_cnt)] = r;
					max_diff[(*circle_cnt)] = max;
					(*circle_cnt)++;
					if (*circle_cnt >= MAX_VALUE)
					{
						cout << "threshold is too low" << endl;
						return MY_FAIL;
					}
				}
			}
		}	
	}

	int r2 = max_radius > 57 ? max_radius : 57;
	for (int r = 57; r < r2; r++)
	{
		int dif_rmax = r + 5;
		int dif_rmin = r - 5;
		int temp_tri_r = r * 360;
		int temp_tri_rmax = dif_rmax * 360;
		int temp_tri_rmin = dif_rmin * 360;
		//清空数组

		memset(sum_light_b, 0, sizeof(int)*height*width);
		memset(sum_light_g, 0, sizeof(int)*height*width);
		memset(sum_light_r, 0, sizeof(int)*height*width);

		//以固定大小的圆去每个去遍历像素，计算每个点的亮度差值情况存入数组
		for (int angle = 0; angle < 360; angle++)
		{
			int temp_r_max = temp_tri_rmax + angle;
			int temp_r_min = temp_tri_rmin + angle;
			int temp_r = temp_tri_r + angle;
			for (int row_x = r; row_x < height - r; row_x++)
			{
				int temp0 = row_x + r_cos_list[temp_r_max];

				if (temp0<0 || temp0 >= height)
				{
					continue;
				}
				int temp_row = row_x*width;
				int temp_row_r_max = temp_row + r_tri_list[temp_r_max];
				int temp_row_r_min = temp_row + r_tri_list[temp_r_min];
				int temp_row_r = temp_row + r_tri_list[temp_r];

				for (int col_y = r; col_y < width - r; col_y++)
				{
					int temp1 = col_y + r_sin_list[temp_r_max];
					if (temp1<0 || temp1 >= width)
					{
						continue;
					}

					sum_light_b[temp_row + col_y] += (bImg.data[temp_row_r_max + col_y] - bImg.data[temp_row_r_min + col_y]);
					sum_light_g[temp_row + col_y] += (gImg.data[temp_row_r_max + col_y] - gImg.data[temp_row_r_min + col_y]);
					sum_light_r[temp_row + col_y] += (rImg.data[temp_row_r_max + col_y] - rImg.data[temp_row_r_min + col_y]);
				}
			}
		}


		//遍历数组，判断是否为圆
		for (int row_x = 0; row_x < height; row_x++)
		{
			int temp = row_x*width;

			for (int col_y = 0; col_y < width; col_y++)
			{
				
				sum_light_b[temp + col_y] = sum_light_b[temp + col_y] > 0 ? (sum_light_b[temp + col_y] / 360) : (-sum_light_b[temp + col_y] / 360);
				sum_light_g[temp + col_y] = sum_light_g[temp + col_y] > 0 ? (sum_light_g[temp + col_y] / 360) : (-sum_light_g[temp + col_y] / 360);
				sum_light_r[temp + col_y] = sum_light_r[temp + col_y] > 0 ? (sum_light_r[temp + col_y] / 360) : (-sum_light_r[temp + col_y] / 360);
				int max = sum_light_b[temp + col_y];
				if (sum_light_g[temp + col_y] > max) max = sum_light_g[temp + col_y];
				if (sum_light_r[temp + col_y] > max) max = sum_light_r[temp + col_y];

				if (max >= max_circle_diff)
				{
					x_0[*circle_cnt] = row_x;
					y_0[*circle_cnt] = col_y;
					radius_0[*circle_cnt] = r;
					max_diff[*circle_cnt] = max;
					(*circle_cnt)++;
					if (*circle_cnt >= MAX_VALUE)
					{
						cout << "threshold is too low" << endl;
						return MY_FAIL;
					}
				}
			}
		}


		//排除同圆
		int len = *circle_cnt;
		for (int ii = 0; ii < len; ii++)
		{
			if (max_diff[ii] == 0) continue;
			for (int jj = ii + 1; jj < len; jj++)
			{
				int dif_r = radius_0[ii] - radius_0[jj];
				int dif_x = x_0[ii] - x_0[jj];
				int dif_y = y_0[ii] - y_0[jj];
				dif_r = dif_r > 0 ? dif_r : -dif_r;
				if (((dif_x*dif_x + dif_y*dif_y) <= center2) && (dif_r <= min_radius_dist))
				{
					(*circle_cnt)--;
					if (max_diff[ii] >= max_diff[jj])
					{
						x_0[jj] = 0;
						y_0[jj] = 0;
						radius_0[jj] = 0;
						max_diff[jj] = 0;
					}

					else
					{
						//消灭ii处的值，把jj的值放到前面来
						x_0[ii] = x_0[jj];
						y_0[ii] = y_0[jj];
						radius_0[ii] = radius_0[jj];
						max_diff[ii] = max_diff[jj];

						x_0[jj] = 0;
						y_0[jj] = 0;
						radius_0[jj] = 0;
						max_diff[jj] = 0;
					}
				}
			}
		}
		//降序排列
		int temp = 0;
		for (int ii = 0; ii < len; ii++)
		{
			int max = max_diff[ii];
			int pos = ii;
			for (int jj = ii + 1; jj < len; jj++)
			{
				if (max_diff[jj] > max)
				{
					max = max_diff[jj];
					pos = jj;
				}
			}
			temp = x_0[pos]; x_0[pos] = x_0[ii]; x_0[ii] = temp;
			temp = y_0[pos]; y_0[pos] = y_0[ii]; y_0[ii] = temp;
			temp = radius_0[pos]; radius_0[pos] = radius_0[ii]; radius_0[ii] = temp;
			temp = max_diff[pos]; max_diff[pos] = max_diff[ii]; max_diff[ii] = temp;
		}
	}
	
	//把x0,y0,radius0的值输入到x,y,radius里
	max_circle = max_circle > (*circle_cnt) ?  (*circle_cnt) : max_circle;
	for (int ii = 0; ii < max_circle; ii++)
	{
		x[ii] = x_0[ii];
		y[ii] = y_0[ii];
		radius[ii] = radius_0[ii];
	}

	return MY_OK;
}
