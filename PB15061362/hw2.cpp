
#include "opencv2/opencv.hpp"
using namespace cv;
#include<iostream>
using namespace std;
#define IMG_SHOW
#define MY_OK 1
#define MY_FAIL -1
#define PI 3.14159


void calculate(int* cos_a, int *sin_a, int min_radius, int max_radius)
{
	float convert = 2 * PI / 360;
	for (int rad = min_radius - 5; rad < max_radius + 6; rad++)
	{
		int cos_value = rad;
		int sin_value = 0;
		int pre_sign = 0;
		for (int angle = 0; angle < 360; angle++)
		{
			float radian = angle * convert;
			int position = rad * 720 + angle * 2;
			cos_a[position] = rad * cos(radian);
			sin_a[position] = rad * sin(radian);
			if ((cos_value != cos_a[position]) || (sin_value != sin_a[position]))
			{
				for (int next = pre_sign; next < angle; next++)
				{
					cos_a[rad * 720 + next * 2 + 1] = angle;
				}
				cos_value = cos_a[position];
				sin_value = sin_a[position];
				pre_sign = angle;
			}
		}
		for (int next = pre_sign; next < 360; next++)
		{
			cos_a[rad * 720 + next * 2 + 1] = 360;
		}
	}
}

int ustc_Find_Circles_By_Difference(Mat colorImg, int min_radius, int max_radius, int min_center_dist, int min_radius_dist, int max_circle_diff, int* x, int* y, int* radius, int* circle_cnt, int max_cycle)
{
	//建立500的数组存放圆，所以如果圆的个数大于500则越界
	int* x_test = new int[500];
	int* y_test = new int[500];
	int* r_test = new int[500];
	int* differ_val = new int[500];
	//用于存放 r * cos 和 r * sin 的值而建立的数组 ， 最后 * 2 的原因是对于每个半径每个角度，第一个空间存放就是的值，
	//第二个空间存放下一个不同的位置对应的角度， 从而防止在圆周差分循环中对某个像素点重复求和
	int* cos_a = new int[(max_radius + 6) * 360 * 2];
	int* sin_a = new int[(max_radius + 6) * 360 * 2];
	//存放圆的个数
	int total_num = 0;
	if ((NULL == colorImg.data) || (NULL == x) || (NULL == y) || (NULL == radius))
	{
		cout << "image is NULL." << endl;
		return MY_FAIL;
	}
	//计算 r * cos 和 r * sin 的值
	calculate(cos_a, sin_a, min_radius, max_radius);

	int height = colorImg.rows;
	int width = colorImg.cols;
	int total_size = height * width * max_radius;
	//用于存放某坐标半径值时是否是个圆， 0 表示该坐标半径下不是圆 ， 1表示是圆
	int *sign_xyr = (int *)malloc(sizeof(int) * total_size);
	memset(sign_xyr, 0, sizeof(int) * total_size);
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			for (int r = min_radius; r < max_radius; ++r)
			{
				int min_rad = r - 5;
				int max_rad = r + 5;
				int min_angle = 0;
				int max_angle = 0;
				int min_num = 0;
				int max_num = 0;
				int min_total_r = 0;
				int min_total_g = 0;
				int min_total_b = 0;
				int max_total_r = 0;
				int max_total_g = 0;
				int max_total_b = 0;

				while (min_angle < 360)
				{
					int row_i = i + sin_a[min_rad * 720 + min_angle * 2];
					int col_j = j + cos_a[min_rad * 720 + min_angle * 2];
					if (row_i < 0 || row_i >= height || col_j < 0 || col_j >= width)
					{
						//防止重复取像素点
						min_angle = cos_a[min_rad * 720 + min_angle * 2 + 1];
						continue;
					}
					else
					{
						int z = (row_i * width + col_j) * 3;
						min_total_b += colorImg.data[z];
						min_total_g += colorImg.data[z + 1];
						min_total_r += colorImg.data[z + 2];
						min_angle = cos_a[min_rad * 720 + min_angle * 2 + 1];
						min_num++;
					}
				}
				while (max_angle < 360)
				{
					int row_i = i + sin_a[max_rad * 720 + max_angle * 2];
					int col_j = j + cos_a[max_rad * 720 + max_angle * 2];
					if (row_i < 0 || row_i >= height || col_j < 0 || col_j >= width)
					{
						max_angle = cos_a[max_rad * 720 + max_angle * 2 + 1];
						continue;
					}
					else
					{
						int z = (row_i * width + col_j) * 3;
						max_total_b += colorImg.data[z];
						max_total_g += colorImg.data[z + 1];
						max_total_r += colorImg.data[z + 2];
						max_angle = cos_a[max_rad * 720 + max_angle * 2 + 1];
						max_num++;
					}
				}
				int min_ave_r = min_total_r / min_num;
				int min_ave_b = min_total_b / min_num;
				int min_ave_g = min_total_g / min_num;
				int max_ave_r = max_total_r / max_num;
				int max_ave_b = max_total_b / max_num;
				int max_ave_g = max_total_g / max_num;
				int diff_r = min_ave_r - max_ave_r;
				int diff_g = min_ave_g - max_ave_g;
				int diff_b = min_ave_b - max_ave_b;
				//将RGB三通道的差值取绝对值
				int temp = 0; 
				temp = diff_r >> 31;
				diff_r = diff_r ^ temp;
				diff_r = diff_r - temp;
				temp = diff_g >> 31;
				diff_g = diff_g ^ temp;
				diff_g = diff_g - temp;
				temp = diff_b >> 31;
				diff_b = diff_b ^ temp;
				diff_b = diff_b - temp;
				//找出RGB三通道中最大值
				int largest = diff_r;
				temp = diff_r - diff_g;
				largest -= temp & (temp >> 31);
				temp = largest - diff_b;
				largest -= temp & (temp >> 31);
				//当大于阈值时，需要判断，若之前计算过的横坐标差min_center_dist，纵坐标差min_center_dist，同时半径差 min_radius_dist的
				//所有位置是否有以及储存的圆，若有则此圆跳过
				if ( largest > max_circle_diff) 
				{
					int result = 0;
					for (int col_j = j - 1; (col_j >= 0) && (col_j >(j - min_center_dist)); col_j--)
					{
						int x = i * width * max_radius + col_j * max_radius;
						for (int cal_r = r; (cal_r > min_radius) && (cal_r > r - min_radius_dist); cal_r--)
						{
							result += sign_xyr[x + cal_r];
						}
						for (int cal_r = r + 1; (cal_r < max_radius) && (cal_r < r + min_radius_dist); cal_r++)
						{
							result += sign_xyr[x + cal_r];
						}
					}
					for (int row_i = i - 1; (row_i >= 0) && (row_i >(i - min_center_dist)); row_i--)
					{

						for (int col_j = j; (col_j >= 0) && (col_j >(j - min_center_dist)); col_j--)
						{
							int x = row_i * width * max_radius + col_j * max_radius;
							for (int cal_r = r; (cal_r > min_radius) && (cal_r > r - min_radius_dist); cal_r--)
							{
								result += sign_xyr[x + cal_r];
							}
							for (int cal_r = r + 1; (cal_r < max_radius) && (cal_r < r + min_radius_dist); cal_r++)
							{
								result += sign_xyr[x + cal_r];
							}
						}
						for (int col_j = j + 1; (col_j < width) && (col_j < (j + min_center_dist)); col_j++)
						{
							int x = row_i * width * max_radius + col_j * max_radius;
							for (int cal_r = r; (cal_r > min_radius) && (cal_r > r - min_radius_dist); cal_r--)
							{
								result += sign_xyr[x + cal_r];
							}
							for (int cal_r = r + 1; (cal_r < max_radius) && (cal_r < r + min_radius_dist); cal_r++)
							{
								result += sign_xyr[x + cal_r];
							}
						}
					}
					if (result == 0)
					{
						sign_xyr[(i * width + j) * max_radius + r] = 1;
						r += min_radius_dist;
						x_test[total_num] = i;
						y_test[total_num] = j;
						r_test[total_num] = r;
						differ_val[total_num] = largest;
						total_num++;
					}
				}
			}
		}
	}
	//当找到圆的个数小于max_cycle，直接将子程序中建立的数组中的值复制给主程序
	if (total_num <= max_cycle)
	{
		for (int i = 0; i < total_num; i++)
		{
			x[i] = x_test[i];
			y[i] = y_test[i];
			radius[i] = r_test[i];
		}
		free(sign_xyr);
		*circle_cnt = total_num;
		return 1;
	}
	//若找到的圆的个数大于max_cycle，采用选择排序法找其中前max_cycle个 
	else
	{
		for (int i = 0; i < max_cycle; i++)
		{
			int max_num = i;
			for (int j = i; j < total_num; ++j)
			{
				int value = differ_val[max_num] - differ_val[j];
				int temp = max_num - j;
				max_num -= temp & (value >> 31);
			}
			x[i] = x_test[max_num];
			y[i] = y_test[max_num];
			radius[i] = r_test[max_num];
			x_test[max_num] = x_test[i];
			y_test[max_num] = y_test[i];
			r_test[max_num] = r_test[i];
			differ_val[max_num] = differ_val[max_num];
		}
		free(sign_xyr);
		*circle_cnt = max_cycle;
		return 1;
	}

}

