#include <math.h>
#include <opencv2/opencv.hpp>

using namespace cv;

int x_axis[280][360];
int y_axis[280][360];
int my_max(int x, int y, int z);


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
	int i, j, r, an, row, col;
	uchar* data = colorImg.data;
	if (NULL == data)
	{
		cout << "void ptr!" << endl;
		return -1;
	}

	double temp;
	for (i = 25; i < 305; i++)
	{
		for (j = 0; j < 360; j++)
		{
			temp = j*3.1415926 / 180;
			x_axis[i - 25][j] = i*cos(temp);
			y_axis[i - 25][j] = i*sin(temp);
		}
	}

	*circle_cnt = 0;
	row = colorImg.rows;
	col = colorImg.cols;

	int diff1, out_circle1, in_circle1;
	int diff2, out_circle2, in_circle2;
	int diff3, out_circle3, in_circle3;
	int row_col_in, row_col_out;
	int *diff, *temp_x, *temp_y, *temp_radius;
	diff = new int[10000];
	temp_radius = new int[10000];
	temp_x = new int[10000];
	temp_y = new int[10000];

	for (r = min_radius ; r <= max_radius; r++)
	{
		for (i = r + 5; i < row - (r + 5); i++)
		{
			for (j = r + 5; j < col - (r + 5); j++)
			{
				out_circle1 = in_circle1 = out_circle2 = in_circle2 = out_circle3 = in_circle3 = 0;
				for (an = 0; an < 360; an++)
				{
					row_col_out = ((i + x_axis[r - 30][an])*col + j + y_axis[r - 30][an]) * 3;
					row_col_in = ((i + x_axis[r - 20][an])*col + j + y_axis[r - 20][an]) * 3;

					out_circle1 += data[row_col_out];
					in_circle1 += data[row_col_in];
					out_circle2 += data[row_col_out + 1];
					in_circle2 += data[row_col_in + 1];
					out_circle3 += data[row_col_out + 2];
					in_circle3 += data[row_col_in + 2];
				}
				diff1 = abs(out_circle1 - in_circle1);
				diff2 = abs(out_circle2 - in_circle2);
				diff3 = abs(out_circle3 - in_circle3);
				if (diff1 > max_circle_diff || diff2 > max_circle_diff || diff3 > max_circle_diff)
				{
						temp_x[*circle_cnt] = i;
						temp_y[*circle_cnt] = j;
						temp_radius[*circle_cnt] = r;
						(*circle_cnt)++;
						diff[*circle_cnt] = my_max(diff1, diff2, diff3);
				}
			}
		}
	}

	int distance;
	int *circle_flag;
	int min_circle_r= min_center_dist*min_center_dist;
	circle_flag = new int[*circle_cnt];
	for (i = 0; i < *circle_cnt; i++)
	{
		circle_flag[i] = 1;
	}


	for (i = 0; i < *circle_cnt; i++)
	{
		if (0 == circle_flag[i])
		{
			continue;
		}

		for (j = i+1; j < *circle_cnt; j++)
		{
			if (0 == circle_flag[j])
			{
				continue;
			}

			distance = (temp_x[i] - temp_x[j])*(temp_x[i] - temp_x[j]) + (temp_y[i] - temp_y[j])*(temp_y[i] - temp_y[j]);
			if (distance > min_circle_r)
			{
				circle_flag[j] = 1;
			}

			else if ((temp_radius[i] - temp_radius[j]) > min_radius_dist)
			{
				circle_flag[j] = 1;
			}
			else
			{
				circle_flag[j] = 0;
			}
		}
	}

	int circle_num = 0;
	for (i = 0; i < *circle_cnt; i++)
	{
		if (circle_flag[i] == 1)
		{
			temp_x[circle_num] = temp_x[i];
			temp_y[circle_num] = temp_y[i];
			temp_radius[circle_num] = temp_radius[i];
			diff[circle_num] = diff[i];
			circle_num++;
		}
	}
	
	int exchange_temp;
	if (circle_num > max_circle)
	{
		for (i = 0; i < max_circle; i++)
		{
			for (j = circle_num - 1; j > 0; j--)
			{
				if (diff[j] > diff[j - 1])
				{
					exchange_temp = diff[j];
					diff[j] = diff[j - 1];
					diff[j - 1] = exchange_temp;

					exchange_temp = temp_x[j];
					temp_x[j] = temp_x[j - 1];
					temp_x[j - 1] = exchange_temp;

					exchange_temp = temp_y[j];
					temp_y[j] = temp_y[j - 1];
					temp_y[j - 1] = exchange_temp;

					exchange_temp = temp_radius[j];
					temp_radius[j] = temp_radius[j - 1];
					temp_radius[j - 1] = exchange_temp;
				}
			}
		}

		for (i = 0; i < max_circle; i++)
		{
			x[i] = temp_x[i];
			y[i] = temp_y[i];
			radius[i] = temp_radius[i];
		}
		*circle_cnt = max_circle;
	}
	else
	{
		*circle_cnt = circle_num;
		for (i = 0; i < circle_num; i++)
		{
			x[i] = temp_x[i];
			y[i] = temp_y[i];
			radius[i] = temp_radius[i];
		}
	}

	return 0;
}

int my_max(int x, int y, int z)
{
	if (x > y&&x > z)
		return x;
	else if (y > z)
		return y;
	else
		return z;

}
