
#include "FindCircle.h"

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
	int max_circle){


	if (NULL == colorImg.data) {
		cout << "no image" << endl;
		return MY_FAIL;
	}
	if (max_radius < min_radius) {
		cout << "no such circle" << endl;
		return MY_FAIL;
	}
	float ustc_cos[360];
	float ustc_sin[360];

	for (int i = 0; i < 360; i++) {
		ustc_cos[i] = cos(i*3.1415926 / 180);
		ustc_sin[i] = sin(i*3.1415926 / 180);
	}
	int height = colorImg.rows;
	int width = colorImg.cols;
	int num = 0;
	uchar* data = colorImg.data;
	Mat grayImg(height, width, CV_8UC1);
    Mat redImg(height, width, CV_8UC1);
    Mat greenImg(height, width, CV_8UC1);
	Mat blueImg(height, width, CV_8UC1);
	uchar* red = redImg.data;
	uchar* green = greenImg.data;
	uchar* blue = blueImg.data;

	for (int row_i = 0; row_i < height; row_i++)
	{
		for (int col_j = 0; col_j < width; col_j += 1)
		{
			int n =3*( row_i * width + col_j);
			int b =data[n + 0];
			int g = data[n + 1];
			int r =data[n + 2];
			red[row_i * width + col_j] = r;
			green[row_i*width + col_j] = g;
			blue[row_i*width + col_j] = b;
		}
	}


	int x_total[100] = { 0 };

	int y_total[100] = { 0 };

	int radius_total[100] = { 0 };

	int len = 0;
	
	int circle_diff[100];

	Mat place_x(360, max_radius + 6,CV_32SC1);
	Mat place_y(360, max_radius + 6, CV_32SC1);
	place_x.setTo(0);
	place_x.setTo(0);
	int *xd = (int *)place_x.data;
	int *yd = (int *)place_y.data;

	for (int MY_radius = min_radius - 5; MY_radius <= max_radius + 5; MY_radius++) {
		for (int theta = 0; theta < 360; theta++) {
			xd[theta*(max_radius + 6) + MY_radius] = MY_radius*ustc_cos[theta];
			yd[theta*(max_radius + 6) + MY_radius] = MY_radius*ustc_sin[theta];
		}
	}
	for (int row_i = 0; row_i < height; row_i++)
	{
		for (int col_j = 0; col_j < width; col_j += 1)
		{
			int* light_r = new int[max_radius + 6];
			int* light_g = new int[max_radius + 6];
			int* light_b = new int[max_radius + 6];
			memset(light_r, 0, (max_radius + 6) * sizeof(int));
			memset(light_g, 0, (max_radius + 6) * sizeof(int));
			memset(light_b, 0, (max_radius + 6) * sizeof(int));
			int *lgt_r = &light_r[min_radius - 5];
			int *lgt_g = &light_g[min_radius - 5];
			int *lgt_b = &light_b[min_radius - 5];
			for (int MY_radius = min_radius-5; MY_radius <= max_radius+5; MY_radius++) {
				int count_light=0;
				for (int angle = 0; angle < 360; angle++) {
				
					int index_x = col_j + xd[angle*(max_radius + 6) + MY_radius];
					int index_y = row_i + yd[angle*(max_radius + 6) + MY_radius];
					if (index_x < 0 || index_x >= width || index_y < 0 || index_y >= height) {

					}
					else {
						int num = index_y*width + index_x;
						*lgt_r += red[num];
						*lgt_g += green[num];
						*lgt_b += blue[num];
						count_light++;
					}
				}
				count_light++;
				*lgt_r /= count_light;
				*lgt_g /= count_light;
				*lgt_b /= count_light;	
				*lgt_r++;
				*lgt_g++;
				*lgt_b++;
		}
			
			for (int MY_Radius = min_radius; MY_Radius <= max_radius; MY_Radius++) {
				int count_flag = 0;
				int gray_diff_r = abs(light_r[MY_Radius-5]-light_r[MY_Radius+5]);
				if (gray_diff_r > max_circle_diff) {
					int symbal_r = 0;
					for (int i = 0; i < len; i++) {
						if (abs(col_j - x_total[i]) <= min_center_dist && abs(row_i - y_total[i]) <= min_center_dist) {
							if (abs(MY_Radius - radius_total[i]) >= min_radius_dist) {
								symbal_r++;
							}
							else {
								x_total[i] += col_j;
								x_total[i] /= 2;
								y_total[i] += row_i;
								y_total[i] /= 2;
								radius_total[i] += MY_Radius;
								radius_total[i] /= 2;
								break;
							}
						}
						else {
							symbal_r++;
						}

					}
					if (symbal_r == len) {
						x_total[len] = col_j;
						y_total[len] = row_i;
						radius_total[len] = MY_Radius;
						circle_diff[len] = gray_diff_r;
						len++;
					}
					count_flag = 1;
				}
				if (count_flag != 1) {
					int gray_diff_g = abs(light_g[MY_Radius - 5] - light_g[MY_Radius + 5]);
					if (gray_diff_g > max_circle_diff) {
						int symbal_g = 0;
						for (int i = 0; i < len; i++) {
							if (abs(col_j - x_total[i]) <= min_center_dist && abs(row_i - y_total[i]) <= min_center_dist) {
								if (abs(MY_Radius - radius_total[i]) >= min_radius_dist) {
									symbal_g++;
								}
								else {
									x_total[i] += col_j;
									x_total[i] /= 2;
									y_total[i] += row_i;
									y_total[i] /= 2;
									radius_total[i] += MY_Radius;
									radius_total[i] /= 2;
									break;
								}
							}
							else {
								symbal_g++;
							}

						}
						if (symbal_g == len) {
							x_total[len] = col_j;
							y_total[len] = row_i;
							radius_total[len] = MY_Radius;
							circle_diff[len] = gray_diff_g;
							len++;
						}
						count_flag = 1;
					}
					if (count_flag != 1) {
						int gray_diff_b = abs(light_b[MY_Radius - 5] - light_b[MY_Radius + 5]);
						if (gray_diff_b > max_circle_diff) {
							int symbal_b = 0;
							for (int i = 0; i < len; i++) {
								if (abs(col_j - x_total[i]) <= min_center_dist && abs(row_i - y_total[i]) <= min_center_dist) {
									if (abs(MY_Radius - radius_total[i]) >= min_radius_dist) {
										symbal_b++;
									}
									else {
										x_total[i] += col_j;
										x_total[i] /= 2;
										y_total[i] += row_i;
										y_total[i] /= 2;
										radius_total[i] += MY_Radius;
										radius_total[i] /= 2;
										break;
									}
								}
								else {
									symbal_b++;
								}
							}
							if (symbal_b == len) {
								x_total[len] = col_j;
								y_total[len] = row_i;
								radius_total[len] = MY_Radius;
								circle_diff[len] = gray_diff_b;
								len++;
							}

						}
					}
				}
			}

			delete light_r;
			delete light_b;
			delete light_g;
	}
}
int *x_1 = x_total;
int *y_1 = y_total;
int *radius_1 = radius_total;
int num_circle = 0;
int symbol = 0;
for(int i=0;i<len;i++){
	symbol = 0;
	for (int j = 0; j < num_circle; j++) {
		
		if (abs(*x_1 - x_total[j]) <=2* min_center_dist&&abs(*y_1 - y_total[j]) <= 2*min_radius_dist) {
			x_total[j] += *x_1;
			x_total[j] /= 2;
			y_total[j] += *y_1;
			y_total[j] /= 2;
			radius_total[j] += *radius_1;
			radius_total[j] /= 2;
			break;

		}
		else {
			symbol++;
		}
	}
		if (symbol == num_circle ) {
			x_total[num_circle] = *x_1;
			y_total[num_circle] = *y_1;
			radius_total[num_circle] = *radius_1;
			num_circle++;
		}
	
	x_1++;
	y_1++;
	radius_1++;
}
len = num_circle;

if (len > max_circle) {
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len -i-1; j++) {
			if (circle_diff[j] < circle_diff[j + 1]);
			int tmp=0;
			
			tmp = circle_diff[j];
			circle_diff[j] = circle_diff[j + 1];
			circle_diff[j + 1] = tmp;
			
			tmp = x_total[j];
			x_total[j] = x_total[j + 1];
			x_total[j + 1] = tmp;


			tmp = y_total[j];
			y_total[j] = x_total[j + 1];
			y_total[j + 1] = tmp;

			tmp = radius_total[j];
			radius_total[j] = radius_total[j + 1];
			radius_total[j + 1] = tmp;


		}
	}
}
    
*circle_cnt = min(len, max_circle);
for (int i = 0; i < *circle_cnt; i++) {
	x[i] = x_total[i];
	y[i] = y_total[i]-min_center_dist/2;
	radius[i] = radius_total[i];
}

	return MY_OK;
}
