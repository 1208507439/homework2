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

	int num[1000];
	*circle_cnt = 0;

	Find_Circles_SingleChannel(redImg,  min_radius, max_radius, min_center_dist, min_radius_dist, max_circle_diff, x, y, radius, circle_cnt,num, max_circle);
	Find_Circles_SingleChannel(greenImg,  min_radius, max_radius, min_center_dist, min_radius_dist, max_circle_diff, x, y, radius, circle_cnt,num, max_circle);
	Find_Circles_SingleChannel(blueImg,  min_radius, max_radius, min_center_dist, min_radius_dist, max_circle_diff, x, y, radius, circle_cnt,num, max_circle);


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
	int max_circle) {

	if (*len >= max_circle) {
		return;
	}

	int width = Img.cols;
	int height = Img.rows;
	uchar *Imgptr = Img.data;

	Mat alloneimg(height, width, CV_16UC1);
	alloneimg.setTo(1);
	Mat convertimg(height, width, CV_16UC1);
	Img /= 2;
	max_circle_diff /= 2;
	Img.convertTo(convertimg, CV_16UC1);
	for (int i = 0; i <2; i++){
		Mat numImg = Mat::zeros(height, width, CV_16UC1);
		Mat ave_in = Mat::zeros(height, width, CV_16UC1);
		for (int degree = 0; degree < 360; degree++) {
			int dx = (min_radius+ i - 1)*cosvalue[degree];
			int dy = (min_radius + i - 1)*sinvalue[degree];
			if (dx >= 0 && dy >= 0) {
				Mat subimg = ave_in(Range(dy, height), Range(0, width - dx));
				subimg = subimg + convertimg(Range(0, height - dy), Range(dx, width));
				Mat numsubimg = numImg(Range(dy, height), Range(0, width - dx));
				numsubimg = numsubimg + alloneimg(Range(0, height - dy), Range(dx, width));
			}
			if (dx < 0 && dy >= 0) {
				Mat subimg = ave_in(Range(dy, height), Range(-dx, width));
				subimg = subimg + convertimg(Range(0, height - dy), Range(0, width + dx));
				Mat numsubimg = numImg(Range(dy, height), Range(-dx, width));
				numsubimg = numsubimg + alloneimg(Range(0, height - dy), Range(0, width + dx));
			}
			if (dx < 0 && dy < 0) {
				Mat subimg = ave_in(Range(0, height + dy), Range(-dx, width));
				subimg = subimg + convertimg(Range(-dy, height), Range(0, width + dx));
				Mat numsubimg = numImg(Range(0, height + dy), Range(-dx, width));
				numsubimg = numsubimg + alloneimg(Range(-dy, height), Range(0, width + dx));
			}
			if (dx >= 0 && dy < 0) {
				Mat subimg = ave_in(Range(0, height + dy), Range(0, width - dx));
				subimg = subimg + convertimg(Range(-dy, height), Range(dx, width));
				Mat numsubimg = numImg(Range(0, height + dy), Range(0, width - dx));
				numsubimg = numsubimg + alloneimg(Range(-dy, height), Range(dx, width));
			}
		}
		for (int r = min_radius; r <= max_radius; r+=2) {
			Mat numImg2 = Mat::zeros(height, width, CV_16UC1);
			Mat ave_out = Mat::zeros(height, width, CV_16UC1);
			Mat ave_del = Mat::zeros(height, width, CV_16UC1);
			uint16_t* ave_inptr = (uint16_t*)ave_in.data;
			uint16_t* ave_outptr = (uint16_t*)ave_out.data;
			uint16_t* numptr = (uint16_t*)numImg.data;
			uint16_t* numptr2 = (uint16_t*)numImg2.data;
			uint16_t* ave_delptr = (uint16_t*)ave_del.data;

			for (int degree = 0; degree < 360; degree++) {
				int dx = (r + 1)*cosvalue[degree];
				int dy = (r + 1)*sinvalue[degree];
				if (dx >= 0 && dy >= 0) {
					Mat subimg = ave_out(Range(dy, height), Range(0, width - dx));
					subimg = subimg + convertimg(Range(0, height - dy), Range(dx, width));
					Mat numsubimg = numImg2(Range(dy, height), Range(0, width - dx));
					numsubimg = numsubimg + alloneimg(Range(0, height - dy), Range(dx, width));
				}
				if (dx < 0 && dy >= 0) {
					Mat subimg = ave_out(Range(dy, height), Range(-dx, width));
					subimg = subimg + convertimg(Range(0, height - dy), Range(0, width + dx));
					Mat numsubimg = numImg2(Range(dy, height), Range(-dx, width));
					numsubimg = numsubimg + alloneimg(Range(0, height - dy), Range(0, width + dx));
				}
				if (dx < 0 && dy < 0) {
					Mat subimg = ave_out(Range(0, height + dy), Range(-dx, width));
					subimg = subimg + convertimg(Range(-dy, height), Range(0, width + dx));
					Mat numsubimg = numImg2(Range(0, height + dy), Range(-dx, width));
					numsubimg = numsubimg + alloneimg(Range(-dy, height), Range(0, width + dx));
				}
				if (dx >= 0 && dy < 0) {
					Mat subimg = ave_out(Range(0, height + dy), Range(0, width - dx));
					subimg = subimg + convertimg(Range(-dy, height), Range(dx, width));
					Mat numsubimg = numImg2(Range(0, height + dy), Range(0, width - dx));
					numsubimg = numsubimg + alloneimg(Range(-dy, height), Range(dx, width));
				}
			}

			ave_del = abs(ave_in / numImg - ave_out / numImg2);

			for (int row_i = 0; row_i < height; row_i++)
				for (int col_j = 0; col_j < width; col_j++) {
					int pos = row_i*width + col_j;
					int number = ave_delptr[pos];
					if (number > max_circle_diff) {
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
										}
									}
									else if (flag == 1) {
										if (number > num[i]) {
											for (int j = i; j < *len - 1; j++) {
												x[j] = x[j + 1];
												y[j] = y[j + 1];
												radius[j] = radius[j + 1];
												num[j] = num[j + 1];
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
							(*len)++;
						}
					}
				}
			ave_in = ave_out;
			numImg = numImg2;
		}
	}
}
