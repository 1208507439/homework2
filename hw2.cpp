//
//  main.cpp
//  homework1
//
//  Created by 丁煜航 on 2017/9/15.
//  Copyright © 2017年 丁煜航. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>

using namespace cv;
using namespace std;

#define channel 3
#define diff_circle_interval 5

#define MY_OK 1
#define MY_FAIL 0

int ustc_Find_Circles_By_Differece(Mat colorImg, int min_radius, int max_radius, int min_center_dist, int min_radius_dist, int max_circle_diff, int *x, int *y, int *radius, int *circle_cnt, int max_circle)
{
	if (NULL == colorImg.data)
	{
		cout << "the image is empty" << endl;
		return MY_FAIL;
	}
	double sin_array[360] = { 0 };
	double cos_array[360] = { 0 };
	for (int array_num = 0; array_num < 360; array_num++)
	{
		float angle = array_num*CV_PI / 180;
		sin_array[array_num] = sin(angle);
		cos_array[array_num] = cos(angle);
	}
	int row = colorImg.rows;
	int col = colorImg.cols;
	int x_array[10000] = { 0 };
	int*p1 = x_array;
	int y_array[10000] = { 0 };
	int*p2 = y_array;
	int radius_array[10000] = { 0 };
	int*p3 = radius_array;
	float diffe[10000] = { 0 };
	float*p4 = diffe;
	int circle_num = 0;
	uchar* data1 = colorImg.data;
	for (int point_x = 0; point_x < row; point_x++)
	{
		for (int point_y = 0; point_y < col; point_y++)
		{
			float sum_circle[2 * diff_circle_interval][3] = { 0 };
			int k2 = 0;
			for (int i = 0; i < 2 * diff_circle_interval; i++)
			{
				float sum_a_circle[3] = { 0 };
				int count_num = 360;
				for (int angle = 0; angle < 360; angle++)
				{
					int circle_point_x = point_x + (i + min_radius - diff_circle_interval)*cos_array[angle];
					int circle_point_y = point_y + (i + min_radius - diff_circle_interval)*sin_array[angle];
					if (circle_point_x >= 0 && circle_point_x < row&&circle_point_y >= 0 && circle_point_y < col)
					{
						int save_point = 3 * (circle_point_x*col + circle_point_y);
						for (int chan = 0; chan < channel; chan++)
						{
							sum_a_circle[chan] += data1[save_point + chan];
						}
					}
					else
					{
						k2 = 1;
						break;
					}
				}
				if (k2 == 1)
				{
					break;
				}
				for (int j = 0; j < 3; j++)
				{
					sum_circle[i][j] = sum_a_circle[j] / count_num;
				}
			}
			if (k2 == 1)
			{
				continue;
			}
			for (int radius1 = min_radius + diff_circle_interval; radius1 <= max_radius + diff_circle_interval; radius1++)
			{
				float sum_a_circle[3] = { 0 };
				int count_num = 360;
				for (int angle = 0; angle < 360; angle++)
				{
					int circle_point_x = point_x + radius1*cos_array[angle];
					int circle_point_y = point_y + radius1*sin_array[angle];
					if (circle_point_x >= 0 && circle_point_x < row&&circle_point_y >= 0 && circle_point_y < col)
					{
						int save_point = 3 * (circle_point_x*col + circle_point_y);
						for (int chan = 0; chan < channel; chan++)
						{
							sum_a_circle[chan] += data1[save_point + chan];
						}
					}
					else
					{
						k2 = 1;
						break;
					}
				}
				if (k2 == 1)
				{
					break;
				}
				for (int j = 0; j < 3; j++)
				{
					sum_a_circle[j] = sum_a_circle[j] / count_num;
				}
				float difference0 = fabs(sum_a_circle[0] - sum_circle[0][0]);
				float difference1 = fabs(sum_a_circle[1] - sum_circle[0][1]);
				float difference2 = fabs(sum_a_circle[2] - sum_circle[0][2]);
				float max = difference0;
				if (max < difference1)
				{
					max = difference1;
				}
				if (max < difference2)
				{
					max = difference2;
				}
				if (max >= max_circle_diff)
				{
					*p1 = point_x;
					p1++;
					*p2 = point_y;
					p2++;
					*p3 = radius1 - diff_circle_interval;
					p3++;
					*p4 = max;
					p4++;
					circle_num++;
				}
				for (int i = 0; i < 9; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						sum_circle[i][j] = sum_circle[i + 1][j];
					}
				}
				sum_circle[9][0] = sum_a_circle[0];
				sum_circle[9][1] = sum_a_circle[1];
				sum_circle[9][2] = sum_a_circle[2];
				if (circle_num > 10000)
				{
					cout << "the max_circle_diff is too small,please change it." << endl;
					return MY_FAIL;

				}
			}
		}
	}
  
	for (int i = 0; i < circle_num; i++)
	{
		for (int j = i + 1; j < circle_num; j++)
		{
			if (diffe[i] >= diffe[j])
			{

			}
			else
			{
				int temp1;
				float temp2;
				temp1 = x_array[i];
				x_array[i] = x_array[j];
				x_array[j] = temp1;
				temp1 = y_array[i];
				y_array[i] = y_array[j];
				y_array[j] = temp1;
				temp1 = radius_array[i];
				radius_array[i] = radius_array[j];
				radius_array[j] = temp1;
				temp2 = diffe[i];
				diffe[i] = diffe[j];
				diffe[j] = temp2;
			}
		}
	}
	int circle_new_num = circle_num;
	for (int i = 0; i < circle_num; i++)
	{
		if (diffe[i] != 0)
		{
			for (int j = i + 1; j < circle_num; j++)
			{
				if (diffe[j] != 0)
				{
					if (x_array[i] <= x_array[j] + min_center_dist&&x_array[i] >= x_array[j] - min_center_dist)
					{
						if (y_array[i] <= y_array[j] + min_center_dist&&y_array[i] >= y_array[j] - min_center_dist)
						{
							if (radius_array[i] <= radius_array[j] + min_radius_dist&&radius_array[i] >= radius_array[j] - min_radius_dist)
							{
								if (x_array[i] == x_array[j] && y_array[i] == y_array[j] && fabs(diffe[i] - diffe[j]) < 0.1)
								{

								}
								else
								{
									diffe[j] = 0;
									circle_new_num--;
								}
							}
						}
					}
				}
			}
		}
	}
	for (int i = 0; i < circle_num; i++)
	{
		for (int j = i + 1; j < circle_num; j++)
		{
			if (diffe[i] >= diffe[j])
			{

			}
			else
			{
				int temp1;
				float temp2;
				temp1 = x_array[i];
				x_array[i] = x_array[j];
				x_array[j] = temp1;
				temp1 = y_array[i];
				y_array[i] = y_array[j];
				y_array[j] = temp1;
				temp1 = radius_array[i];
				radius_array[i] = radius_array[j];
				radius_array[j] = temp1;
				temp2 = diffe[i];
				diffe[i] = diffe[j];
				diffe[j] = temp2;
			}
		}
	}
	circle_num = circle_new_num;
	float radius_array1[100] = { 0 };
	int number[100] = { 0 };
	for (int i = 0; i < circle_num; i++)
	{
		if (diffe[i] != 0)
		{
			int k = 0;
			radius_array1[k] = diffe[i];
			number[k] = i;
			for (int j = i + 1; j < circle_num; j++)
			{
				if (diffe[j] != 0)
				{
					if (fabs(diffe[i] - diffe[j]) < 0.5)
					{
						if (x_array[i] == x_array[j] && y_array[i] == y_array[j])
						{
							if (radius_array[i] <= radius_array[j] + min_radius_dist&&radius_array[i] >= min_radius_dist)
							{
								k++;
								radius_array1[k] = radius_array[j];
								number[k] = j;
							}
						}
					}
				}
			}
			for (int i1 = 0; i1 <= k; i1++)
			{
				for (int j1 = i + 1; j1 <= k; j1++)
				{
					if (radius_array1[i1] >= radius_array1[j1])
					{
						int temp1;
						float temp2;
						temp1 = number[i1];
						number[i1] = number[j1];
						number[j1] = temp1;
						temp2 = radius_array1[i1];
						radius_array1[i1] = radius_array1[j1];
						radius_array1[j1] = temp2;
					}
				}
			}
			for (int i2 = 0; i2 <= k; i2++)
			{
				if (i2 != (int)((k - 1) / 2))
				{
					diffe[number[i2]] = 0;
				}
			}
			circle_new_num -= (k);
		}
	}
	for (int i = 0; i < circle_num; i++)
	{
		for (int j = i + 1; j < circle_num; j++)
		{
			if (diffe[i] >= diffe[j])
			{

			}
			else
			{
				int temp1;
				float temp2;
				temp1 = x_array[i];
				x_array[i] = x_array[j];
				x_array[j] = temp1;
				temp1 = y_array[i];
				y_array[i] = y_array[j];
				y_array[j] = temp1;
				temp1 = radius_array[i];
				radius_array[i] = radius_array[j];
				radius_array[j] = temp1;
				temp2 = diffe[i];
				diffe[i] = diffe[j];
				diffe[j] = temp2;
			}
		}
	}
	if (circle_new_num > max_circle)
	{
		circle_new_num = max_circle;
	}
	for (int i = 0; i < circle_new_num; i++)
	{
		*x = x_array[i];
		x++;
		*y = y_array[i];
		y++;
		*radius = radius_array[i];
		radius++;
	}
	*circle_cnt = circle_new_num;
	return MY_OK;
}
