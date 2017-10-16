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
	
	int size = height*width;
	for (int i = 0; i < size; i++) {
		bImg.data[i] = colorImg.data[i * 3];
		gImg.data[i] = colorImg.data[i * 3 + 1];
		rImg.data[i] = colorImg.data[i * 3 + 2];
	}
	
	
	max_circle_diff /= 2;
	rImg.convertTo(rImg, CV_16UC1);
	rImg = rImg / 2;
	gImg.convertTo(gImg, CV_16UC1);
	gImg = gImg / 2;
	bImg.convertTo(bImg, CV_16UC1);
	bImg = bImg / 2;
	Mat cir_sum_diff_r = Mat::zeros(height, width, CV_16UC1);
	Mat cir_sum_diff_g = Mat::zeros(height, width, CV_16UC1);
	Mat cir_sum_diff_b = Mat::zeros(height, width, CV_16UC1);

	int* cir_point_count_buff = new int[max_cnt];

	Mat one = Mat::ones(height, width, CV_16UC1);

	Mat cir_sum_cnt = Mat::zeros(height, width, CV_16UC1);

	for (int cl = 0; cl < 2; cl++) {
		Mat cir_sum_p_r = Mat::zeros(height, width, CV_16UC1);
		Mat cir_sum_p_g = Mat::zeros(height, width, CV_16UC1);
		Mat cir_sum_p_b = Mat::zeros(height, width, CV_16UC1);

		cir_sum_cnt = Mat::zeros(height, width, CV_16UC1);
		for (int theta = 0; theta < 360; theta++) {
			int x_vary = (min_radius + cl - 1)*ustc_ydc_cos[theta];
			int y_vary = (min_radius + cl - 1)*ustc_ydc_sin[theta];

			int x_start = 0, x_end = width, y_start = 0, y_end = height;

			if (x_vary > 0)x_end = width - x_vary;
			if (x_vary < 0)x_start = -x_vary;
			if (y_vary > 0)y_end = height - y_vary;
			if (y_vary < 0)y_start = -y_vary;
			int cir_x_p_start = x_vary + x_start, cir_x_p_end = x_vary + x_end;
			int cir_y_p_start = y_vary + y_start, cir_y_p_end = y_vary + y_end;
			int cir_point_count = 0;
			Mat addi_img_r = rImg(Range(cir_y_p_start, cir_y_p_end), Range(cir_x_p_start, cir_x_p_end));
			Mat to_be_added_r = cir_sum_p_r(Range(y_start, y_end), Range(x_start, x_end));
			to_be_added_r = to_be_added_r + addi_img_r;

			addi_img_r = gImg(Range(cir_y_p_start, cir_y_p_end), Range(cir_x_p_start, cir_x_p_end));
			to_be_added_r = cir_sum_p_g(Range(y_start, y_end), Range(x_start, x_end));
			to_be_added_r = to_be_added_r + addi_img_r;

			addi_img_r = bImg(Range(cir_y_p_start, cir_y_p_end), Range(cir_x_p_start, cir_x_p_end));
			to_be_added_r = cir_sum_p_b(Range(y_start, y_end), Range(x_start, x_end));
			to_be_added_r = to_be_added_r + addi_img_r;

			addi_img_r = one(Range(cir_y_p_start, cir_y_p_end), Range(cir_x_p_start, cir_x_p_end));
			to_be_added_r = cir_sum_cnt(Range(y_start, y_end), Range(x_start, x_end));
			to_be_added_r = to_be_added_r + addi_img_r;

		}
		cir_sum_p_r = cir_sum_p_r / cir_sum_cnt;
		cir_sum_p_g = cir_sum_p_g / cir_sum_cnt;
		cir_sum_p_b = cir_sum_p_b / cir_sum_cnt;
		for (int rr = min_radius + cl; rr <= max_radius; rr += 2) {
			Mat cir_sum_m_r = cir_sum_p_r.clone();
			Mat cir_sum_m_g = cir_sum_p_g.clone();
			Mat cir_sum_m_b = cir_sum_p_b.clone();

			unsigned short * p_r = (unsigned short *)cir_sum_diff_r.data;
			for (int i = 0; i < size; i++) {
				p_r[i] = 0;
			}
			unsigned short * p_g = (unsigned short *)cir_sum_diff_g.data;
			for (int i = 0; i < size; i++) {
				p_g[i] = 0;
			}
			unsigned short * p_b = (unsigned short *)cir_sum_diff_b.data;
			for (int i = 0; i < size; i++) {
				p_b[i] = 0;
			}
			cir_sum_cnt = Mat::zeros(height, width, CV_16UC1);
			cir_sum_p_r = Mat::zeros(height, width, CV_16UC1);
			cir_sum_p_g = Mat::zeros(height, width, CV_16UC1);
			cir_sum_p_b = Mat::zeros(height, width, CV_16UC1);
			

			for (int theta = 0; theta < 360; theta++) {
				int x_vary = (rr + 1)*ustc_ydc_cos[theta];
				int y_vary = (rr + 1)*ustc_ydc_sin[theta];

				int x_start = 0, x_end = width, y_start = 0, y_end = height;

				if (x_vary > 0)x_end = width - x_vary;
				if (x_vary < 0)x_start = -x_vary;
				if (y_vary > 0)y_end = height - y_vary;
				if (y_vary < 0)y_start = -y_vary;
				int cir_x_p_start = x_vary + x_start, cir_x_p_end = x_vary + x_end;
				int cir_y_p_start = y_vary + y_start, cir_y_p_end = y_vary + y_end;
				int cir_point_count = 0;
				Mat addi_img_r = rImg(Range(cir_y_p_start, cir_y_p_end), Range(cir_x_p_start, cir_x_p_end));
				Mat to_be_added_r = cir_sum_p_r(Range(y_start, y_end), Range(x_start, x_end));
				to_be_added_r = to_be_added_r + addi_img_r;

				addi_img_r = gImg(Range(cir_y_p_start, cir_y_p_end), Range(cir_x_p_start, cir_x_p_end));
				to_be_added_r = cir_sum_p_g(Range(y_start, y_end), Range(x_start, x_end));
				to_be_added_r = to_be_added_r + addi_img_r;

				addi_img_r = bImg(Range(cir_y_p_start, cir_y_p_end), Range(cir_x_p_start, cir_x_p_end));
				to_be_added_r = cir_sum_p_b(Range(y_start, y_end), Range(x_start, x_end));
				to_be_added_r = to_be_added_r + addi_img_r;

				addi_img_r = one(Range(cir_y_p_start, cir_y_p_end), Range(cir_x_p_start, cir_x_p_end));
				to_be_added_r = cir_sum_cnt(Range(y_start, y_end), Range(x_start, x_end));
				to_be_added_r = to_be_added_r + addi_img_r;
				if (*len >= max_cnt)break;
			}
			
			cir_sum_p_r = cir_sum_p_r / cir_sum_cnt;
			cir_sum_p_g = cir_sum_p_g / cir_sum_cnt;
			cir_sum_p_b = cir_sum_p_b / cir_sum_cnt;
			cir_sum_diff_r = abs(cir_sum_p_r - cir_sum_m_r);
			cir_sum_diff_g = abs(cir_sum_p_g - cir_sum_m_g);
			cir_sum_diff_b = abs(cir_sum_p_b - cir_sum_m_b);
			

			for (int yy = 0; yy < height; yy++) {
				for (int xx = 0; xx < width; xx++) {
					int cir_point_count = *(p_r + xx + yy*width);
					if (cir_point_count < *(p_g + xx + yy*width))
						cir_point_count= *(p_g + xx + yy*width);
					if (cir_point_count < *(p_b + xx + yy*width))
						cir_point_count = *(p_b + xx + yy*width);
					if (cir_point_count > max_circle_diff) {

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
	
	
	
	return MY_OK;
}

