#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define MyOK 1
#define MyFail 0
#define pi 3.1415
using namespace std;
using namespace cv;
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
	if (colorImg.data == NULL)
	{
		cout << "no image!" << endl;
		return MyFail;
	}
	if ((NULL == x) | (NULL == y) | (NULL == radius) | (NULL == circle_cnt))
	{
		printf("x,y,radius or len is NULL!\n");
		return MyFail;
	}
	int mlf_min_radius = min_radius;
	int mlf_max_radius = max_radius;
	int rows = colorImg.rows;
	int cols = colorImg.cols;
	int rc_min = (((rows - cols) >> 31) & 1)*rows + (((cols - rows) >> 31) & 1)*cols;
	if (max_radius >= rc_min / 2)
	{
		mlf_max_radius = rc_min / 2;
	}
	Mat bgrImg[3], originImg[3];
	split(colorImg, originImg); 
	originImg[0].convertTo(bgrImg[0], CV_16UC1);
	originImg[1].convertTo(bgrImg[1], CV_16UC1);
	originImg[2].convertTo(bgrImg[2], CV_16UC1);
	bgrImg[0] = bgrImg[0] * 0.7;
	bgrImg[1] = bgrImg[1] * 0.7;
	bgrImg[2] = bgrImg[2] * 0.7;

	float COS[360] = { 0 }, SIN[360] = { 0 };
	int row_cter = 0, col_cter = 0;
	int cir_rads = 0, cir_angle = 0;
	int fx[3000] = { 0 }, fy[3000] = { 0 }, fr[3000] = { 0 }, fdiff[3000] = { 0 };
	Mat rad_mean_b[400], rad_mean_g[400], rad_mean_r[400], valid_num[400];
	Mat rad_diff_b[400], rad_diff_g[400], rad_diff_r[400];
	uchar *pgray = colorImg.data;

	for (int i = 359; i >= 0; i--)
	{
		double angle = i*pi / 180;
		COS[i] = cos(angle);
		SIN[i] = sin(angle);
	}
	Mat dotImg(colorImg.size(), CV_16UC1);
	dotImg.setTo(1);



	int flag = 0;
	int diff_rad_r[500] = { 0 }, diff_rad_g[500] = { 0 }, diff_rad_b[500] = { 0 };
	//store the sum and the means of 3 channel's pixel
	for (cir_rads = min_radius - 5; cir_rads <= mlf_max_radius + 5; cir_rads++)
	{
		Mat sumImg_b = Mat::zeros(colorImg.size(), CV_16UC1);
		Mat sumImg_g = Mat::zeros(colorImg.size(), CV_16UC1);
		Mat sumImg_r = Mat::zeros(colorImg.size(), CV_16UC1);
		Mat numImg(colorImg.size(), CV_16UC1);
		numImg.setTo(0);

		for (cir_angle = 0; cir_angle < 360; cir_angle++)
		{
			int r_cos = cir_rads*COS[cir_angle];//rcos(theta)
			int r_sin = cir_rads*SIN[cir_angle];//rsin(theta)
			int row_begin = ((-r_sin >> 31) & 1)*r_sin;
			int row_end = rows + ((r_sin >> 31) & 1)*r_sin;
			int col_begin = -((r_cos >> 31) & 1)*r_cos;
			int col_end = cols - ((-r_cos >> 31) & 1)*r_cos;

			Mat img_b = sumImg_b(Range(row_begin, row_end), Range(col_begin, col_end));
			Mat img_g = sumImg_g(Range(row_begin, row_end), Range(col_begin, col_end));
			Mat img_r = sumImg_r(Range(row_begin, row_end), Range(col_begin, col_end));
			Mat source_b = bgrImg[0](Range(rows - row_end, rows - row_begin), Range(cols - col_end, cols - col_begin));
			Mat source_g = bgrImg[1](Range(rows - row_end, rows - row_begin), Range(cols - col_end, cols - col_begin));
			Mat source_r = bgrImg[2](Range(rows - row_end, rows - row_begin), Range(cols - col_end, cols - col_begin));
			img_b = img_b + source_b;
			img_g = img_g + source_g;
			img_r = img_r + source_r;

			Mat img_num = numImg(Range(row_begin, row_end), Range(col_begin, col_end));
			Mat source_num = dotImg(Range(rows - row_end, rows - row_begin), Range(cols - col_end, cols - col_begin));
			img_num = img_num + source_num;
		}
		rad_mean_b[cir_rads] = sumImg_b / numImg*1.4;
		rad_mean_g[cir_rads] = sumImg_g / numImg*1.4;
		rad_mean_r[cir_rads] = sumImg_r / numImg*1.4;
		if (cir_rads >= min_radius + 5)
		{
			rad_diff_b[cir_rads - 5] = (rad_mean_b[cir_rads - 10] - rad_mean_b[cir_rads]) + (rad_mean_b[cir_rads] - rad_mean_b[cir_rads - 10]);
			rad_diff_g[cir_rads - 5] = (rad_mean_g[cir_rads - 10] - rad_mean_g[cir_rads]) + (rad_mean_g[cir_rads] - rad_mean_g[cir_rads - 10]);
			rad_diff_r[cir_rads - 5] = (rad_mean_r[cir_rads - 10] - rad_mean_r[cir_rads]) + (rad_mean_r[cir_rads] - rad_mean_r[cir_rads - 10]);
		}
	}
  for (cir_rads = min_radius; cir_rads <= max_radius; cir_rads++)
		{
			uint16_t *data_b_s = (uint16_t*)rad_mean_b[cir_rads-5].data, *data_b_l = (uint16_t*)rad_mean_b[cir_rads + 5].data;
			uint16_t *data_g_s = (uint16_t*)rad_mean_g[cir_rads-5].data, *data_g_l = (uint16_t*)rad_mean_g[cir_rads + 5].data;
			uint16_t *data_r_s = (uint16_t*)rad_mean_r[cir_rads-5].data, *data_r_l = (uint16_t*)rad_mean_r[cir_rads + 5].data;
			for (row_cter = 0; row_cter < rows; row_cter++)
			{
				for (col_cter = 0; col_cter <= cols; col_cter++)
				{
					int position_cter = row_cter*cols + col_cter;
					int diff_b = data_b_s[position_cter] - data_b_l[position_cter];
					diff_b = -((diff_b >> 31) & 1)*(diff_b << 1) + diff_b;
					int diff_g = data_g_s[position_cter] - data_g_l[position_cter];
					diff_g = -((diff_g >> 31) & 1)*(diff_g << 1) + diff_g;
					int diff_r = data_r_s[position_cter] - data_r_l[position_cter];
					diff_r = -((diff_r >> 31) & 1)*(diff_r << 1) + diff_r;
					if (diff_b > max_circle_diff | diff_g > max_circle_diff | diff_r > max_circle_diff)
					{
						fx[flag] = col_cter;
						number++;
						int m = (((diff_b - diff_g) >> 31) & 1)*diff_g + (((diff_g - diff_b) >> 31) & 1)*diff_b;//calculate the maximum difference
						m = (((diff_r - m) >> 31) & 1)*m + (((m - diff_r) >> 31) & 1)*diff_r;
						fy[flag] = row_cter;
						fr[flag] = cir_rads;
						fdiff[flag] = m;
						flag++;
						int ff = flag - 1;
						for (int i = 0; i < ff; i++)
						{
							int distance_x = abs(fx[ff] - fx[i]);
							int distance_y = abs(fy[ff] - fy[i]);
							if ((distance_x <= min_center_dist) && (distance_y <= min_center_dist) && (fr[i] - fr[ff] <= min_radius_dist) && (fr[ff] - fr[i] <= min_radius_dist))
							{
								fx[i] = (fx[i] + fx[ff]) / 2;
								fy[i] = (fy[i] + fy[ff]) / 2;
								fr[i] = (fr[i] + fr[ff]) / 2;
								fdiff[i] = (((fdiff[i] - fdiff[ff]) >> 31) & 1)*fdiff[ff] + (((fdiff[ff] - fdiff[i]) >> 31) & 1)*fdiff[i];
								fx[ff] = 0;
								fy[ff] = 0;
								fr[ff] = 0;
								fdiff[ff] = 0;
								flag--;
								number--;
								break;
							}

						}
					}
				}
			}
		}
		int temp_number = number;
		for (int i = 1; i <temp_number; i++)
		{
			for (int j = 0; j < i; j++)
			{
				int distance_x = abs(fx[j] - fx[i]);
				int distance_y = abs(fy[j] - fy[i]);
				if ((distance_x <= min_center_dist) && (distance_y <= min_center_dist) && (fr[i] - fr[j] <= min_radius_dist) && (fr[j] - fr[i] <= min_radius_dist))
				{

					fx[i] = 0; 
					fy[i] = 0;
					fr[i] = 0;
					fdiff[i] = 0;
					fdiff[j] = (((fdiff[i] - fdiff[j]) >> 31) & 1)*fdiff[j] + (((fdiff[j] - fdiff[i]) >> 31) & 1)*fdiff[i];
					number--;
					break;
				}
			}
		}
			for (int i = 1; i < temp_number; i++)
			{
				for (int j = 0; j < i; j++)
				{
					if (fdiff[i] > fdiff[j])
					{
						int temp = fdiff[j];
						fdiff[j] = fdiff[i];
						fdiff[i] = temp;

						temp = fx[j];
						fx[j] = fx[i];
						fx[i] = temp;

						temp = fy[j];
						fy[j] = fy[i];
						fy[i] = temp;

						temp = fr[j];
						fr[j] = fr[i];
						fr[i] = temp;

					}
				}
			}
		
		temp_number = (((number - max_circle) >> 31) & 1)*number + (((max_circle - number) >> 31) & 1)*max_circle;
		number = 0;
		int* px = x;	
		int* py = y;
		int* pr = radius;
		for (int i = 0; i < temp_number; i++)
		{
			if (fx[i] != 0 && fy[i] != 0 && fr[i] != 0)
			{
				*px = fx[i]; px++;
				*py = fy[i]-(min_center_dist>>2); py++;
				*pr = fr[i]; pr++;
				number++;
			}
		}		
		*circle_cnt = number;
		return MyOK;
}
