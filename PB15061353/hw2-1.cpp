#include <iostream>
#include <math.h>
#include "FindCircles.h"

using namespace std;

float sinvalue[360];
int sinflag = 0;
float cosvalue[360];
int cosflag = 0;

void Find_Circles_SingleChannel(
	Mat Img,
	int min_radius,
	int max_radius,
	int min_center_dist,
	int min_radius_dist,
	int max_circle_diff,
	int* x,
	int* y,
	int* radius,
	int* len,
	int* num,
	int* tag,
	int max_circle);

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
		return MY_FAIL;
	}

	if (0 == sinflag) {
		for (int count = 0; count < 360; count++) {
			sinvalue[count] = sin(count*3.14159 / 180);
		}
	}
	if (0 == cosflag) {
		for (int count = 0; count < 360; count++) {
			cosvalue[count] = cos(count*3.14159 / 180);
		}
	}

	int width = colorImg.cols;
	int height = colorImg.rows;
	Mat blueImg(height,width, CV_8UC1);
	Mat greenImg(height, width, CV_8UC1);
	Mat redImg(height, width, CV_8UC1);
	int limit = width * height;
	uchar * imgptr = colorImg.data;
	uchar * blueptr = blueImg.data;
	uchar * greenptr = greenImg.data;
	uchar * redptr = redImg.data;
	for (int i = 0; i < limit; i++) {
		blueptr[i] = imgptr[i * 3];
		greenptr[i] = imgptr[i * 3 + 1];
		redptr[i] = imgptr[i * 3 + 2];
	}

	int* num = new int[2*max_circle];
	int* tag = new int[2 * max_circle];
	*circle_cnt = 0;

	Find_Circles_SingleChannel(redImg,  min_radius, max_radius, min_center_dist, min_radius_dist, max_circle_diff, x, y, radius, circle_cnt ,num,tag,max_circle);
	Find_Circles_SingleChannel(greenImg,  min_radius, max_radius, min_center_dist, min_radius_dist, max_circle_diff, x, y, radius, circle_cnt ,num,tag,max_circle);
	Find_Circles_SingleChannel(blueImg,  min_radius, max_radius, min_center_dist, min_radius_dist, max_circle_diff, x, y, radius, circle_cnt ,num,tag,max_circle);

	for (int i = 0; i < *circle_cnt; i++) {
		if (tag[i] == 0) {
			for (int j = i; j < *circle_cnt; j++) {
				x[j] = x[j + 1];
				y[j] = y[j + 1];
				radius[j] = radius[j + 1];
				num[j] = num[j + 1];
				tag[j] = tag[j + 1];
			}
			*circle_cnt -= 1;
		}
	}
	

	return MY_OK;
}

void Find_Circles_SingleChannel(
	Mat Img,
	int min_radius,
	int max_radius,
	int min_center_dist,
	int min_radius_dist,
	int max_circle_diff,
	int* x,
	int* y,
	int* radius,
	int* len,
	int* num,
	int* tag,
	int max_circle) {

	if (*len >= max_circle) {
		return;
	}

	int width = Img.cols;
	int height = Img.rows;
	Mat binaryImg = Mat::zeros(height, width, CV_8UC1);
	Mat binaryImg2= Mat::zeros(height, width, CV_16UC1);

	IplImage Imgip(Img) ;
	IplImage binaryImgip(binaryImg);
	cvCanny(&Imgip,&binaryImgip, 80, 150, 3);

	uchar *Imgptr = Img.data;
	uchar* binaryptr = binaryImg.data;
	uint16_t* binaryptr2 = (uint16_t *)binaryImg2.data;
	
	//边界归一
	for (int row_i = 0; row_i < height; row_i++) {
		for (int col_j = 0; col_j < width; col_j++) {
			if (binaryptr[row_i*width + col_j]>0) {

				binaryptr2[row_i*width + col_j] = 1;
			}
		}
	}
	

	
	//选出超过90度在边界上的圆
	for (int r = min_radius; r <= max_radius; r++) {
		Mat binarynum = Mat::zeros(height, width, CV_16UC1);
		uint16_t* binarynumptr = (uint16_t*)binarynum.data;
		for (int degree = 0; degree < 360; degree++) {
					int dx = r*cosvalue[degree];
					int dy = r*sinvalue[degree];
					if (dx >= 0 && dy >= 0) {
						Mat subimg = binarynum(Range(dy, height), Range(0, width - dx));
						subimg = subimg + binaryImg2(Range(0, height - dy), Range(dx, width));
					}
					if (dx < 0 && dy >= 0) {
						Mat subimg = binarynum(Range(dy, height), Range(-dx, width));
						subimg = subimg + binaryImg2(Range(0, height - dy), Range(0, width + dx));
					}
					if (dx < 0 && dy < 0) {
						Mat subimg = binarynum(Range(0, height + dy), Range(-dx, width));
						subimg = subimg + binaryImg2(Range(-dy, height), Range(0, width + dx));
					}
					if (dx >= 0 && dy < 0) {
						Mat subimg = binarynum(Range(0, height + dy), Range(0, width - dx));
						subimg = subimg + binaryImg2(Range(-dy, height), Range(dx, width));
					}
		}

		for (int row_i = 0; row_i < height; row_i++)
			for (int col_j = 0; col_j < width; col_j++) {
				uint16_t number = binarynumptr[row_i*width+col_j];
				if (number> 75) {
					int flag = 0;
					for (int i = 0; i < *len; i++) {
						if (abs(x[i] - col_j) < min_center_dist && abs(y[i] - row_i) < min_center_dist) {
							if (abs(radius[i] - r) < min_radius_dist) {
								if (flag == 0) {
									flag = 1;
									if (number > num[i]) {
										x[i] = col_j;
										y[i] = row_i;
										radius[i] = r;
										num[i] = number;
										tag[i] = 0;
									}
								}
								else if (flag == 1) {
									if (number > num[i]) {
										for (int j = i; j < *len - 1; j++) {
											x[j] = x[j + 1];
											y[j] = y[j + 1];
											radius[j] = radius[j + 1];
											num[j] = num[j + 1];
											tag[j] = tag[j+1];
										}
										(*len)--;
									}
								}
							}
						}
					}
					if (flag == 0) {
						if (*len >= max_circle) {
							return;
						}
						x[*len] = col_j;
						y[*len] = row_i;
						radius[*len] = r;
						num[*len] = number;
						tag[*len] = 0;
						(*len)++;
					}
				}
			}
	}

	for (int i = 0; i < *len; i++) {
		int _x = x[i];
		int _y = y[i];
		int _r = radius[i];
		int sum_in = 0;
		int sum_out = 0;
		int num_auto = 0;
		for (int deg = 0; deg < 360; deg++) {
			float dx = cosvalue[deg];
			float dy = sinvalue[deg];
			int pos_xin = _x + (_r - 5)*dx;
			int pos_yin = _y + (_r - 5)*dy;
			int pos_x = _x + _r * dx;
			int pos_y = _y + _r * dy;
			int pos_xout = _x + (_r + 5)*dx;
			int pos_yout = _y + (_r + 5)*dy;
			if (pos_xout<0 || pos_xout>=height) {
					continue;
			}
			if (pos_yout<0 || pos_yout>=width) {
				continue;
			}
			int flag = binaryptr2[pos_x*width + pos_y];
			sum_in += flag*Imgptr[pos_xin*width + pos_yin];
			sum_out += flag*Imgptr[pos_xout*width + pos_yout];
			num_auto += flag;
		}
		if (abs(sum_out - sum_in) / num_auto > max_circle_diff) {
			tag[i] = 1;
		}
	}
}
