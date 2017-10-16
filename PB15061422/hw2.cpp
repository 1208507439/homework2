#include <math.h>
#include <opencv2/opencv.hpp> 
#include <emmintrin.h>
#include "iostream"

#define MY_OK 1
#define MY_FAIL 0
#define PI 3.14159
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
	int width_x = colorImg.cols;
	int height_y = colorImg.rows;
	int my_min_radius = min_radius;
	int my_max_radius = max_radius;
	if (max_radius > 300)
	{
		cout << "max_radius should be smaller than 300" << endl;
		return(MY_FAIL);
	}
	if (width_x / 2 < max_radius || height_y / 2 < max_radius)
	{
		cout << "the size of image is smaller than  2*max_radius ,can only find the circle whose radius is lower than the image size,wait.... " << endl;
		my_max_radius = height_y / 2;
		if (width_x < height_y)
			my_max_radius = width_x / 2;

	}
	if (width_x < min_radius + 10 || height_y < min_radius + 10)
	{
		cout << "error" << endl;
		return(MY_FAIL);
	}

	int count_r = 0;
	int count_theta = 0;
	int count_x = 0;
	int count_y = 0;
	const int SIZE = max_radius + 10;
	Mat sourceImg;
	colorImg.convertTo(sourceImg, CV_16UC3);
	sourceImg *= 0.7;

	Mat  perr_ave[310];
	Mat  perr_diff[310];
	Mat  flag_num[310];

	float my_sin[360];
	float my_cos[360];
	for (int i = 0; i < 360; i++)
	{
		my_sin[i] = sin(i*PI / 180);
		my_cos[i] = cos(i*PI / 180);
	}
	for (count_r = my_min_radius - 5; count_r <= my_max_radius + 5; count_r++)
	{
		//cout << count_r << endl;
		Mat SUM_around;
		SUM_around.create(height_y, width_x, CV_16UC3);
		SUM_around.setTo(0);

		Mat SUM_num;
		SUM_num.create(height_y, width_x, CV_16UC3);
		SUM_num.setTo(0);

		Mat num_tool;
		num_tool.create(height_y, width_x, CV_16UC3);
		num_tool.setTo(1);

		Mat sub_source;
		Mat sub_around;
		Mat sub_numtool;
		Mat sub_numsource;

		for (count_theta = 0; count_theta < 360; count_theta++)
		{
			int start_x = 0;
			int end_x = 0;
			int start_y = 0;
			int end_y = 0;
			if (my_sin[count_theta] > 0)
			{
				start_y = count_r*my_sin[count_theta];
				end_y = height_y;
			}
			else
			{
				start_y = 0;
				end_y = height_y + count_r*my_sin[count_theta];
			}

			if (my_cos[count_theta] > 0)
			{
				start_x = 0;
				end_x = width_x - count_r*my_cos[count_theta];
			}
			else
			{
				start_x = -count_r*my_cos[count_theta];
				end_x = width_x;
			}

			sub_around = SUM_around(Range(start_y, end_y), Range(start_x, end_x));
			sub_source = sourceImg(Range(height_y - end_y, height_y - start_y), Range(width_x - end_x, width_x - start_x));
			sub_numtool = num_tool(Range(start_y, end_y), Range(start_x, end_x));
			sub_numsource = SUM_num(Range(start_y, end_y), Range(start_x, end_x));

			sub_around = sub_around + sub_source;
			sub_numsource = sub_numsource + sub_numtool;
		}
		perr_ave[count_r] = SUM_around / SUM_num*1.43;

		if (count_r >= min_radius + 5)
		{
			int temp_r = count_r - 5;
			//the abs of diff value
			perr_diff[temp_r] = (perr_ave[temp_r + 5] - perr_ave[temp_r - 5]) + (perr_ave[temp_r - 5] - perr_ave[temp_r + 5]);
		}

	}
	int _circle_cnt = 0;
	int* diff = new int[max_circle];

	//Remove Same Ciecle
	for (int count_diff = 255; count_diff >= max_circle_diff; count_diff--)
	{
		for (int r = my_min_radius; r < my_max_radius; r++)
		{
			for (int i_y = min_center_dist; i_y < height_y - min_center_dist; i_y++)
			{
				for (int j_x = min_center_dist; j_x < width_x - min_center_dist; j_x++)
				{

					int axis_ = i_y*width_x + j_x;
					uint16_t* point = (uint16_t*)perr_diff[r].data;
					if (*(point + 3 * axis_ + 0) != count_diff&& *(point + 3 * axis_ + 1) != count_diff&& *(point + 3 * axis_ + 2) != count_diff)
						continue;

					int start_r, end_r;
					if (r - min_radius_dist >= min_radius) start_r = r - min_radius_dist;
					else start_r = min_radius;
					if (r + min_radius_dist <= my_max_radius) end_r = r + min_radius_dist;
					else end_r = my_max_radius;

					int diff_flag = 0;
					for (int sub_r = start_r; sub_r < end_r; sub_r++)
					{
						for (int sub_i = i_y - min_center_dist; sub_i < i_y + min_center_dist; sub_i++)
						{
							for (int sub_j = j_x - min_center_dist; sub_j < j_x + min_center_dist; sub_j++)
							{
								uint16_t sub_value_b = *((uint16_t*)perr_diff[sub_r].data + 3 * (sub_i*width_x + sub_j));
								uint16_t sub_value_g = *((uint16_t*)perr_diff[sub_r].data + 3 * (sub_i*width_x + sub_j) + 1);
								uint16_t sub_value_r = *((uint16_t*)perr_diff[sub_r].data + 3 * (sub_i*width_x + sub_j) + 2);
								if (sub_value_b > count_diff || sub_value_g > count_diff || sub_value_r > count_diff)
								{
									diff_flag = 1;
									sub_r = end_r;
									sub_i = i_y + min_center_dist;
									break;
								}

							}
						}
					}

					for (int p = 0; p < _circle_cnt; p++)
					{
						if (((j_x - x[p])*(j_x - x[p]) + (i_y - y[p])*(i_y - y[p])) < min_center_dist*min_center_dist && abs(radius[p] - r) < min_radius_dist)
						{

							diff_flag = 1;
							continue;
						}
					}

					if (0 == diff_flag)
					{
						x[_circle_cnt] = j_x;
						y[_circle_cnt] = i_y;
						radius[_circle_cnt] = r;
						_circle_cnt++;
					}
					if (_circle_cnt >= max_circle)
					{
						*circle_cnt = _circle_cnt;
						return(MY_OK);
					}


				}
			}
		}
	}
	*circle_cnt = _circle_cnt;
	return MY_OK;

}
