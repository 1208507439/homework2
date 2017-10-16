#include"opencv2/opencv.hpp"
#include"cv.h"
#include"find_circles.h"
#include"time.h"
using namespace cv;
using namespace std;

#define MAX_R 300
#define MIN_R 30

#define MY_OK 1
#define MY_FAIL -1
#define CIR_CNT 200
#define DEG2RAD 0.0174532922	//3.1415926/180

float ustc_ydc_sin[360];
float ustc_ydc_cos[360];
int ustc_ydc_abs[512];
uchar sin_cos_flag = 0;
uchar abs_flag = 0;
void ustc_circle_find_single_channel(Mat rImg, Mat rImg_edge, int* cir_point_count_buff,
	int width, int height, int size, int min_radius,
	int max_radius,
	int min_center_dist,
	int min_radius_dist,
	int max_circle_diff,
	int* x,
	int* y,
	int* radius,
	int* len,
	int max_cnt);


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
	int* len,
	int max_cnt) {

	
	int* cir_point_count_buff = new int[max_cnt];

	if (sin_cos_flag == 0) {
		sin_cos_flag = 1;
		for (int i = 0; i < 360; i++) {
			float rad = i*DEG2RAD;
			ustc_ydc_cos[i] = cos(rad);
			ustc_ydc_sin[i] = sin(rad);
		}
	}

	if (abs_flag == 0) {
		abs_flag = 1;
		for (int i = 0; i < 512; i++) {
			ustc_ydc_abs[i] = abs(i - 256);
		}
	}

	int width = colorImg.cols;
	int height = colorImg.rows;
				
	
	Mat rImg = Mat::zeros(height, width, CV_8UC1);
	Mat gImg = Mat::zeros(height, width, CV_8UC1);
	Mat bImg = Mat::zeros(height, width, CV_8UC1);
	Mat rImg_edge = Mat::zeros(height, width, CV_8UC1);
	Mat gImg_edge = Mat::zeros(height, width, CV_8UC1);
	Mat bImg_edge = Mat::zeros(height, width, CV_8UC1);
	int size = height*width;
	for (int i = 0; i < size; i++) {
		bImg.data[i] = colorImg.data[i * 3];
		gImg.data[i] = colorImg.data[i * 3 + 1];
		rImg.data[i] = colorImg.data[i * 3 + 2];
	}
	IplImage imgr(rImg), edger(rImg_edge);
	cvCanny(&imgr, &edger, 100, 100, 3);
	IplImage imgg(gImg), edgeg(gImg_edge);
	cvCanny(&imgg, &edgeg, 100 , 100, 3);
	IplImage imgb(bImg), edgeb(bImg_edge);
	cvCanny(&imgb, &edgeb, 100, 100, 3);
	Mat edge = Mat::zeros(height, width, CV_8UC1);
	for (int i = 0; i < size; i++) {
		if (rImg_edge.data[i] | gImg_edge.data[i] | bImg_edge.data[i]>100)
			edge.data[i] = 1;
		if (rImg_edge.data[i])
			rImg_edge.data[i] = 1;
		if ( gImg_edge.data[i])
			gImg_edge.data[i] = 1;
		if (bImg_edge.data[i])
			bImg_edge.data[i] = 1;
	}
	
	
	ustc_circle_find_single_channel(rImg, rImg_edge, cir_point_count_buff, width, height, size, min_radius, max_radius, min_center_dist, min_radius_dist, max_circle_diff, x, y, radius, len, max_cnt);
	ustc_circle_find_single_channel(gImg, gImg_edge, cir_point_count_buff, width, height, size, min_radius, max_radius, min_center_dist, min_radius_dist, max_circle_diff, x, y, radius, len, max_cnt);
	ustc_circle_find_single_channel(bImg, bImg_edge, cir_point_count_buff, width, height, size, min_radius, max_radius, min_center_dist, min_radius_dist, max_circle_diff, x, y, radius, len, max_cnt);
	
	
	return MY_OK;
}

void ustc_circle_find_single_channel(Mat rImg, Mat rImg_edge, int* cir_point_count_buff,
	int width, int height, int size, int min_radius,
	int max_radius,
	int min_center_dist,
	int min_radius_dist,
	int max_circle_diff,
	int* x,
	int* y,
	int* radius,
	int* len,
	int max_cnt) {
	Mat rImg_edge_loc(rImg_edge);
	rImg_edge_loc.convertTo(rImg_edge_loc, CV_16UC1);
	Mat cir_sum_diff = Mat::zeros(height, width, CV_16UC1);
	int x_vary_m[360] = { 0 };
	int y_vary_m[360] = { 0 };
	int x_vary_p[360] = { 0 };
	int y_vary_p[360] = { 0 };

	int width_is_inside = width + 2 * max_radius + 2;
	Mat is_inside = Mat::zeros(height + 2 * max_radius + 2, width + 2 * max_radius + 2, CV_8UC1);
	for (int i = max_radius + 1; i < height + max_radius + 1; i++) {
		for (int j = max_radius + 1; j < width + max_radius + 1; j++) {
			is_inside.data[i*width_is_inside + j] = 255;
		}
	}
	for (int rr = min_radius; rr <= max_radius; rr++) {
		unsigned short * p = (unsigned short *)cir_sum_diff.data;
		for (int i = 0; i < size; i++) {
			p[i] = 0;
		}

		for (int theta = 0; theta < 360; theta++) {
			x_vary_m[theta] = (rr - 1)*ustc_ydc_cos[theta];
			y_vary_m[theta] = (rr - 1)*ustc_ydc_sin[theta];

			x_vary_p[theta] = (rr + 1)*ustc_ydc_cos[theta];
			y_vary_p[theta] = (rr + 1)*ustc_ydc_sin[theta];
		}
		for (int theta = 0; theta < 360; theta++) {
			int x_vary = (rr - 0)*ustc_ydc_cos[theta];
			int y_vary = (rr - 0)*ustc_ydc_sin[theta];

			int x_start = 0, x_end = width, y_start = 0, y_end = height;
			
			if (x_vary > 0)x_end = width - x_vary;
			if (x_vary < 0)x_start = -x_vary;
			if (y_vary > 0)y_end = height - y_vary;
			if (y_vary < 0)y_start = -y_vary;
			int cir_x_p_start = x_vary + x_start, cir_x_p_end = x_vary + x_end;
			int cir_y_p_start = y_vary + y_start, cir_y_p_end = y_vary + y_end;
			int cir_point_count = 0;
			Mat addi_img = rImg_edge_loc(Range(cir_y_p_start, cir_y_p_end), Range(cir_x_p_start, cir_x_p_end));
			Mat to_be_added = cir_sum_diff(Range(y_start, y_end), Range(x_start, x_end));
			to_be_added = to_be_added + addi_img;
			

			if (*len >= max_cnt)break;
		}
		
		for (int yy = 0; yy < height; yy++) {
			for (int xx = 0; xx < width; xx++) {
				int cir_point_count = *(p + xx + yy*width);
				if (cir_point_count > 89) {
					int cir_x_m;
					int cir_y_m;

					int cir_x_p;
					int cir_y_p;

					int sum_p_r = 0, sum_m_r = 0;
					int cnt = 0;
					int avr_diff_r = 0;
					for (int theta = 0; theta < 360; theta++) {
						cir_x_m = xx + x_vary_m[theta];
						cir_y_m = yy + y_vary_m[theta];

						cir_x_p = xx + x_vary_p[theta];
						cir_y_p = yy + y_vary_p[theta];

						if (!is_inside.data[(cir_y_p + max_radius + 1)*width_is_inside + cir_x_p + max_radius + 1]) {
							continue;
						}
						cnt++;
						sum_p_r += rImg.data[cir_y_p*width + cir_x_p];
						sum_m_r += rImg.data[cir_y_m*width + cir_x_m];
						

					}
					avr_diff_r = sum_p_r - sum_m_r;
					avr_diff_r /= cnt;
					cir_point_count = avr_diff_r;
					if (cir_point_count < max_circle_diff) {
						continue;
					}
					int len1 = *len;
					if (len1 == 0) {
						x[len1] = xx;
						y[len1] = yy;
						radius[len1] = rr;
						cir_point_count_buff[len1] = cir_point_count;
						(*len)++;
					}
					else {
						uchar merged_flag = 0;
						int flag_i = 0;

						for (int i = 0; i < len1; i++) {
							uchar merge_flag = 0;
							merge_flag = (xx - x[i]) < min_center_dist && (xx - x[i]) > -min_center_dist && (yy - y[i]) < min_center_dist && (yy - y[i]) > -min_center_dist && (radius[i] - rr) < min_radius_dist && (radius[i] - rr) > -min_radius_dist;
							if (merge_flag&&merged_flag == 0) {
								merged_flag = 1;

								if (cir_point_count_buff[i] < cir_point_count) {
									x[i] = xx;
									y[i] = yy;
									radius[i] = rr;
									cir_point_count_buff[i] = cir_point_count;
									flag_i = i;
								}
								i++;
							}
							if (merged_flag == 1) {
								merge_flag = (x[flag_i] - x[i]) < min_center_dist && (x[flag_i] - x[i]) > -min_center_dist && (y[flag_i] - y[i]) < min_center_dist && (y[flag_i] - y[i]) > -min_center_dist && (radius[i] - radius[flag_i]) < min_radius_dist && (radius[i] - radius[flag_i]) > -min_radius_dist;
								if (merge_flag) {
									if (cir_point_count_buff[flag_i] < cir_point_count_buff[i]) {
										x[flag_i] = x[i];
										y[flag_i] = y[i];
										radius[flag_i] = radius[i];
										cir_point_count_buff[flag_i] = cir_point_count_buff[i];

									}
									(*len)--;
									len1--;
									for (int j = i; j < len1; j++) {
										x[j] = x[j + 1];
										y[j] = y[j + 1];
										radius[j] = radius[j + 1];
										cir_point_count_buff[j] = cir_point_count_buff[j + 1];
									}
									i--;
								}
							}

						}

						if (merged_flag == 0) {
							x[len1] = xx;
							y[len1] = yy;
							radius[len1] = rr;
							cir_point_count_buff[len1] = cir_point_count;
							(*len)++;
						}

					}
					if (*len >= max_cnt)break;
				}
				if (*len >= max_cnt)break;
			}
			if (*len >= max_cnt)break;
		}

		if (*len >= max_cnt)break;
	}
}
