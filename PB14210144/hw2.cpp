#include "opencv.hpp"
using namespace cv;
#include <iostream>
using namespace std;
#include <time.h>
#include <math.h>

#define pi 3.141592653f
//#define my_round(temp) (int)((temp > 0.0f) ? (temp + 0.5) : (temp - 0.5))
#define my_round(temp) temp
#define my_min(a, b) (((a) > (b)) ? (b) : (a))
#define my_max(a, b) (((a) < (b)) ? (b) : (a))
#define exchange(a, b, temp) {temp = a; a = b; b = temp;}

#define IMG_SHOW
#define MY_OK 1
#define MY_FAIL -1

#define block_num 15
#define circle_dist 4
#define same_diff 75

const static float my_sin[361] = { 0.000000, 0.017452, 0.034899, 0.052336, 0.069756, 0.087156, 0.104528, 0.121869, 0.139173, 0.156434, 0.173648, 0.190809, 0.207912, 0.224951, 0.241922, 0.258819, 0.275637, 0.292372, 0.309017, 0.325568, 0.342020, 0.358368, 0.374607, 0.390731, 0.406737, 0.422618, 0.438371, 0.453991, 0.469472, 0.484810, 0.500000, 0.515038, 0.529919, 0.544639, 0.559193, 0.573576, 0.587785, 0.601815, 0.615661, 0.629320, 0.642788, 0.656059, 0.669131, 0.681998, 0.694658, 0.707107, 0.719340, 0.731354, 0.743145, 0.754710, 0.766044, 0.777146, 0.788011, 0.798636, 0.809017, 0.819152, 0.829038, 0.838671, 0.848048, 0.857167, 0.866025, 0.874620, 0.882948, 0.891007, 0.898794, 0.906308, 0.913545, 0.920505, 0.927184, 0.933580, 0.939693, 0.945519, 0.951057, 0.956305, 0.961262, 0.965926, 0.970296, 0.974370, 0.978148, 0.981627, 0.984808, 0.987688, 0.990268, 0.992546, 0.994522, 0.996195, 0.997564, 0.998630, 0.999391, 0.999848, 1.000000, 0.999848, 0.999391, 0.998630, 0.997564, 0.996195, 0.994522, 0.992546, 0.990268, 0.987688, 0.984808, 0.981627, 0.978148, 0.974370, 0.970296, 0.965926, 0.961262, 0.956305, 0.951057, 0.945519, 0.939693, 0.933580, 0.927184, 0.920505, 0.913545, 0.906308, 0.898794, 0.891006, 0.882948, 0.874620, 0.866025, 0.857167, 0.848048, 0.838671, 0.829037, 0.819152, 0.809017, 0.798635, 0.788011, 0.777146, 0.766044, 0.754710, 0.743145, 0.731354, 0.719340, 0.707107, 0.694658, 0.681998, 0.669131, 0.656059, 0.642787, 0.629320, 0.615661, 0.601815, 0.587785, 0.573576, 0.559193, 0.544639, 0.529919, 0.515038, 0.500000, 0.484810, 0.469472, 0.453990, 0.438371, 0.422618, 0.406737, 0.390731, 0.374606, 0.358368, 0.342020, 0.325568, 0.309017, 0.292372, 0.275637, 0.258819, 0.241922, 0.224951, 0.207912, 0.190809, 0.173648, 0.156434, 0.139173, 0.121869, 0.104528, 0.087156, 0.069756, 0.052336, 0.034899, 0.017452, -0.000000, -0.017453, -0.034900, -0.052336, -0.069756, -0.087156, -0.104528, -0.121869, -0.139173, -0.156435, -0.173648, -0.190809, -0.207912, -0.224951, -0.241922, -0.258819, -0.275638, -0.292372, -0.309017, -0.325568, -0.342020, -0.358368, -0.374607, -0.390731, -0.406737, -0.422618, -0.438371, -0.453991, -0.469472, -0.484810, -0.500000, -0.515038, -0.529919, -0.544639, -0.559193, -0.573577, -0.587785, -0.601815, -0.615661, -0.629320, -0.642788, -0.656059, -0.669131, -0.681998, -0.694659, -0.707107, -0.719340, -0.731354, -0.743145, -0.754710, -0.766045, -0.777146, -0.788011, -0.798635, -0.809017, -0.819152, -0.829038, -0.838671, -0.848048, -0.857167, -0.866025, -0.874620, -0.882948, -0.891007, -0.898794, -0.906308, -0.913545, -0.920505, -0.927184, -0.933580, -0.939693, -0.945519, -0.951057, -0.956305, -0.961262, -0.965926, -0.970296, -0.974370, -0.978148, -0.981627, -0.984808, -0.987688, -0.990268, -0.992546, -0.994522, -0.996195, -0.997564, -0.998630, -0.999391, -0.999848, -1.000000, -0.999848, -0.999391, -0.998630, -0.997564, -0.996195, -0.994522, -0.992546, -0.990268, -0.987688, -0.984808, -0.981627, -0.978148, -0.974370, -0.970296, -0.965926, -0.961262, -0.956305, -0.951056, -0.945519, -0.939693, -0.933580, -0.927184, -0.920505, -0.913545, -0.906308, -0.898794, -0.891006, -0.882948, -0.874620, -0.866025, -0.857167, -0.848048, -0.838671, -0.829038, -0.819152, -0.809017, -0.798635, -0.788011, -0.777146, -0.766045, -0.754709, -0.743145, -0.731354, -0.719340, -0.707107, -0.694658, -0.681998, -0.669131, -0.656059, -0.642787, -0.629320, -0.615661, -0.601815, -0.587785, -0.573576, -0.559193, -0.544639, -0.529919, -0.515038, -0.500000, -0.484809, -0.469471, -0.453991, -0.438371, -0.422618, -0.406736, -0.390731, -0.374606, -0.358368, -0.342020, -0.325568, -0.309017, -0.292372, -0.275638, -0.258819, -0.241922, -0.224951, -0.207911, -0.190809, -0.173648, -0.156434, -0.139173, -0.121869, -0.104529, -0.087156, -0.069756, -0.052336, -0.034900, -0.017452, 0.000000 };
const static float my_cos[361] = { 1.000000, 0.999848, 0.999391, 0.998630, 0.997564, 0.996195, 0.994522, 0.992546, 0.990268, 0.987688, 0.984808, 0.981627, 0.978148, 0.974370, 0.970296, 0.965926, 0.961262, 0.956305, 0.951057, 0.945519, 0.939693, 0.933580, 0.927184, 0.920505, 0.913545, 0.906308, 0.898794, 0.891007, 0.882948, 0.874620, 0.866025, 0.857167, 0.848048, 0.838671, 0.829038, 0.819152, 0.809017, 0.798635, 0.788011, 0.777146, 0.766044, 0.754710, 0.743145, 0.731354, 0.719340, 0.707107, 0.694658, 0.681998, 0.669131, 0.656059, 0.642788, 0.629320, 0.615661, 0.601815, 0.587785, 0.573576, 0.559193, 0.544639, 0.529919, 0.515038, 0.500000, 0.484810, 0.469472, 0.453990, 0.438371, 0.422618, 0.406737, 0.390731, 0.374607, 0.358368, 0.342020, 0.325568, 0.309017, 0.292372, 0.275637, 0.258819, 0.241922, 0.224951, 0.207912, 0.190809, 0.173648, 0.156434, 0.139173, 0.121869, 0.104528, 0.087156, 0.069757, 0.052336, 0.034899, 0.017452, -0.000000, -0.017452, -0.034899, -0.052336, -0.069757, -0.087156, -0.104529, -0.121869, -0.139173, -0.156434, -0.173648, -0.190809, -0.207912, -0.224951, -0.241922, -0.258819, -0.275637, -0.292372, -0.309017, -0.325568, -0.342020, -0.358368, -0.374607, -0.390731, -0.406737, -0.422618, -0.438371, -0.453991, -0.469472, -0.484810, -0.500000, -0.515038, -0.529919, -0.544639, -0.559193, -0.573576, -0.587785, -0.601815, -0.615661, -0.629320, -0.642788, -0.656059, -0.669131, -0.681999, -0.694658, -0.707107, -0.719340, -0.731354, -0.743145, -0.754710, -0.766045, -0.777146, -0.788011, -0.798636, -0.809017, -0.819152, -0.829038, -0.838671, -0.848048, -0.857167, -0.866025, -0.874620, -0.882948, -0.891007, -0.898794, -0.906308, -0.913545, -0.920505, -0.927184, -0.933580, -0.939693, -0.945519, -0.951057, -0.956305, -0.961262, -0.965926, -0.970296, -0.974370, -0.978148, -0.981627, -0.984808, -0.987688, -0.990268, -0.992546, -0.994522, -0.996195, -0.997564, -0.998630, -0.999391, -0.999848, -1.000000, -0.999848, -0.999391, -0.998630, -0.997564, -0.996195, -0.994522, -0.992546, -0.990268, -0.987688, -0.984808, -0.981627, -0.978148, -0.974370, -0.970296, -0.965926, -0.961262, -0.956305, -0.951057, -0.945519, -0.939693, -0.933580, -0.927184, -0.920505, -0.913545, -0.906308, -0.898794, -0.891007, -0.882948, -0.874620, -0.866025, -0.857167, -0.848048, -0.838671, -0.829038, -0.819152, -0.809017, -0.798635, -0.788011, -0.777146, -0.766044, -0.754710, -0.743145, -0.731354, -0.719340, -0.707107, -0.694658, -0.681998, -0.669131, -0.656059, -0.642787, -0.629320, -0.615662, -0.601815, -0.587785, -0.573576, -0.559193, -0.544639, -0.529919, -0.515038, -0.500000, -0.484810, -0.469472, -0.453990, -0.438371, -0.422618, -0.406737, -0.390731, -0.374606, -0.358368, -0.342020, -0.325568, -0.309017, -0.292372, -0.275637, -0.258819, -0.241922, -0.224951, -0.207911, -0.190809, -0.173648, -0.156435, -0.139173, -0.121869, -0.104528, -0.087156, -0.069756, -0.052336, -0.034899, -0.017452, 0.000000, 0.017453, 0.034900, 0.052336, 0.069757, 0.087156, 0.104528, 0.121870, 0.139173, 0.156435, 0.173649, 0.190809, 0.207912, 0.224951, 0.241922, 0.258819, 0.275638, 0.292372, 0.309017, 0.325568, 0.342020, 0.358368, 0.374607, 0.390731, 0.406737, 0.422618, 0.438371, 0.453991, 0.469472, 0.484810, 0.500000, 0.515038, 0.529919, 0.544639, 0.559193, 0.573577, 0.587785, 0.601815, 0.615662, 0.629320, 0.642788, 0.656059, 0.669131, 0.681998, 0.694659, 0.707107, 0.719340, 0.731354, 0.743145, 0.754710, 0.766045, 0.777146, 0.788011, 0.798636, 0.809017, 0.819152, 0.829037, 0.838671, 0.848048, 0.857167, 0.866026, 0.874620, 0.882948, 0.891007, 0.898794, 0.906308, 0.913546, 0.920505, 0.927184, 0.933581, 0.939693, 0.945519, 0.951057, 0.956305, 0.961262, 0.965926, 0.970296, 0.974370, 0.978148, 0.981627, 0.984808, 0.987688, 0.990268, 0.992546, 0.994522, 0.996195, 0.997564, 0.998630, 0.999391, 0.999848, 1.000000 };
int original_r[200];
int all_sub_sum[200];
bool center_area[300000000] = { 0 };

inline void set_center_area(bool * center_area, int & x, int & y, int & min_center_dist, int & height, int & width, int & r, int & min_radius_dist, int & r_range, int & min_radius){
	int end_x = my_min(x + min_center_dist, width) / 5;
	int end_y = my_min(y + min_center_dist, height) / 5;
	int i, j, k, bottom, top, center_index;
	bottom = my_max(0, r - min_radius - min_radius_dist + 1) / 5;
	top = my_min(r_range, r - min_radius + min_radius_dist) / 5;
	for (i = my_max(x - min_center_dist, 0) / 5; i <= end_x; i++)
		for (j = my_max(y - min_center_dist, 0) / 5; j <= end_y; j++)
			for (k = bottom, center_index = (r_range / 5) * (j * (width / 5) + i) + bottom; k < top; k++, center_index++)
				center_area[center_index] = true;
		

	
}

//功能说明：找到图像中所有圆心在图像内的圆，得到中心点和半径
//colorImg：用来搜索圆形目标的彩色图像
//min_radius：需要搜索的圆的最小半径
//max_radius：需要搜索的圆的最大半径
//min_center_dist：找到的圆心之间的最小距离
//min_radius_dist：同心圆半径之间的最小差距
//max_circle_diff：阈值，圆周差分值低于此阈值，不是圆
//x：数组，存储所有的圆的中心点x坐标
//y：数组，存储所有的圆的中心点y坐标
//radius：数组，存储所有的圆的半径值
//circle_cnt：图像中找到的圆的数目
//max_circle：外部传入参数，圆的数目上限。如果图像中圆的数目超过此参数，根据差分值由大到小进行排序
//返回值：MY_OK或者MY_FAIL
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

	if (NULL == colorImg.data)
	{
		cout << "image is NULL." << endl;
		return MY_FAIL;
	}

	int width = colorImg.cols;
	int height = colorImg.rows;
	int size = width * height;
	int min_dist = (min_center_dist > 1) ? (min_center_dist * 0.707107f) : 1;
	int max_image_r = (width > height) ? height : width;
	if (max_image_r > max_radius + 1)
		max_image_r = max_radius + 1;
	if (min_radius < 4)
		min_radius = 4;

	int i, j, r, theta, k, circle_x, circle_y, max_circle_r, temp1, temp2, sub_sum, channel, sub_sum2, cnt = 0;
	int block_l, block_r, angle_l, angle_r, center_index, bottom, top, index;
	int r_range = max_radius - min_radius + 1;
	int max_diff = max_circle_diff * 5;
	float temp;
	int add_i = 0, add_j = 0, add_r = 0, set_num;
	bool flag_l, flag_r, fail_l, fail_r;

	temp1 = sizeof(bool) * (width / 5) * (height / 5) * (r_range / 5);
	if (temp1 > 300000000)
		temp1 = 300000000;
		
	memset(center_area, 0, temp1);
			


	for (i = 0; i < width; i++){
		for (j = 0; j < height; j++){
			temp1 = (i + 1) > (width - i) ? (width - i) : (i + 1);
			temp2 = (j + 1) > (height - j) ? (height - j) : (j + 1);
			max_circle_r = ((temp1 > temp2) ? temp2 : temp1) - circle_dist;
			if (max_circle_r > max_radius + 1)
				max_circle_r = max_radius + 1;
			center_index = (r_range / 5) * (j / 5 * (width / 5) + i / 5);
			
			for (r = max_circle_r - 1; r >= min_radius; r--){
				if (center_area[center_index + (r - min_radius) / 5])
					continue;
				block_l = block_r = 0;
				angle_l = angle_r = 0;
				fail_l = fail_r = false;
				flag_r = false;
				flag_l = false;
				for (theta = 355; theta >= 0; theta -= 5){
					
					for (channel = 2; channel >= 0; channel--){
						k = theta;
						sub_sum = 0;
						sub_sum2 = 0;

						temp = my_cos[k] * r;
						circle_x = i + my_round(temp);
						temp = my_sin[k] * r;
						circle_y = j + my_round(temp);
						index = 3 * (circle_y * width + circle_x) + channel;
						sub_sum += colorImg.data[index];
						sub_sum2 += colorImg.data[index];
						temp = my_cos[k] * (r + circle_dist);
						circle_x = i + my_round(temp);
						temp = my_sin[k] * (r + circle_dist);
						circle_y = j + my_round(temp);
						index = 3 * (circle_y * width + circle_x) + channel;
						sub_sum -= colorImg.data[index];
						temp = my_cos[k] * (r - circle_dist);
						circle_x = i + my_round(temp);
						temp = my_sin[k] * (r - circle_dist);
						circle_y = j + my_round(temp);
						index = 3 * (circle_y * width + circle_x) + channel;
						sub_sum2 -= colorImg.data[index];
						k++;

						temp = my_cos[k] * r;
						circle_x = i + my_round(temp);
						temp = my_sin[k] * r;
						circle_y = j + my_round(temp);
						index = 3 * (circle_y * width + circle_x) + channel;
						sub_sum += colorImg.data[index];
						sub_sum2 += colorImg.data[index];
						temp = my_cos[k] * (r + circle_dist);
						circle_x = i + my_round(temp);
						temp = my_sin[k] * (r + circle_dist);
						circle_y = j + my_round(temp);
						index = 3 * (circle_y * width + circle_x) + channel;
						sub_sum -= colorImg.data[index];
						temp = my_cos[k] * (r - circle_dist);
						circle_x = i + my_round(temp);
						temp = my_sin[k] * (r - circle_dist);
						circle_y = j + my_round(temp);
						index = 3 * (circle_y * width + circle_x) + channel;
						sub_sum2 -= colorImg.data[index];
						k++;

						temp = my_cos[k] * r;
						circle_x = i + my_round(temp);
						temp = my_sin[k] * r;
						circle_y = j + my_round(temp);
						index = 3 * (circle_y * width + circle_x) + channel;
						sub_sum += colorImg.data[index];
						sub_sum2 += colorImg.data[index];
						temp = my_cos[k] * (r + circle_dist);
						circle_x = i + my_round(temp);
						temp = my_sin[k] * (r + circle_dist);
						circle_y = j + my_round(temp);
						index = 3 * (circle_y * width + circle_x) + channel;
						sub_sum -= colorImg.data[index];
						temp = my_cos[k] * (r - circle_dist);
						circle_x = i + my_round(temp);
						temp = my_sin[k] * (r - circle_dist);
						circle_y = j + my_round(temp);
						index = 3 * (circle_y * width + circle_x) + channel;
						sub_sum2 -= colorImg.data[index];
						k++;

						temp = my_cos[k] * r;
						circle_x = i + my_round(temp);
						temp = my_sin[k] * r;
						circle_y = j + my_round(temp);
						index = 3 * (circle_y * width + circle_x) + channel;
						sub_sum += colorImg.data[index];
						sub_sum2 += colorImg.data[index];
						temp = my_cos[k] * (r + circle_dist);
						circle_x = i + my_round(temp);
						temp = my_sin[k] * (r + circle_dist);
						circle_y = j + my_round(temp);
						index = 3 * (circle_y * width + circle_x) + channel;
						sub_sum -= colorImg.data[index];
						temp = my_cos[k] * (r - circle_dist);
						circle_x = i + my_round(temp);
						temp = my_sin[k] * (r - circle_dist);
						circle_y = j + my_round(temp);
						index = 3 * (circle_y * width + circle_x) + channel;
						sub_sum2 -= colorImg.data[index];
						k++;

						temp = my_cos[k] * r;
						circle_x = i + my_round(temp);
						temp = my_sin[k] * r;
						circle_y = j + my_round(temp);
						index = 3 * (circle_y * width + circle_x) + channel;
						sub_sum += colorImg.data[index];
						sub_sum2 += colorImg.data[index];
						temp = my_cos[k] * (r + circle_dist);
						circle_x = i + my_round(temp);
						temp = my_sin[k] * (r + circle_dist);
						circle_y = j + my_round(temp);
						index = 3 * (circle_y * width + circle_x) + channel;
						sub_sum -= colorImg.data[index];
						temp = my_cos[k] * (r - circle_dist);
						circle_x = i + my_round(temp);
						temp = my_sin[k] * (r - circle_dist);
						circle_y = j + my_round(temp);
						index = 3 * (circle_y * width + circle_x) + channel;
						sub_sum2 -= colorImg.data[index];

						if (sub_sum < 0)
							sub_sum = 0 - sub_sum;
						if (sub_sum2 < 0)
							sub_sum2 = 0 - sub_sum2;
						if (sub_sum > max_diff && sub_sum2 < same_diff)
							flag_l = true;
						if (sub_sum2 > max_diff && sub_sum < same_diff)
							flag_r = true;
						if (flag_l && flag_r)
							break;
					}
					if (!fail_l){
						if (flag_l){
							flag_l = false;
							block_l = 0;
							angle_l += 5;
							if (theta == 0 && angle_l >= 180){
								x[cnt] = i + 1;
								y[cnt] = j;
								radius[cnt] = r + 2;
								original_r[cnt] = r;
								add_r = min_radius_dist - 1;
								//set_num = radius[cnt] - min_radius_dist;
								set_center_area(center_area, i, j, min_dist, height, width, radius[cnt], min_radius_dist, r_range, min_radius);
								cnt++;
								break;
							}
						}
						else{
							block_l += 5;
							if (block_l >= block_num)
								fail_l = true;
						}
					}

					if (!fail_r){
						if (flag_r){
							flag_r = false;
							block_r = 0;
							angle_r += 5;
							if (theta == 0 && angle_r >= 180){
								x[cnt] = i + 1;
								y[cnt] = j;
								radius[cnt] = r - 2;
								original_r[cnt] = r - 4;
								add_r = min_radius_dist - 1;
								//set_num = radius[cnt] - min_radius_dist;
								set_center_area(center_area, i, j, min_dist, height, width, radius[cnt], min_radius_dist, r_range, min_radius);
								cnt++;
								break;
							}
						}
						else{
							block_r += 5;
							if (block_r >= block_num)
								fail_r = true;
						}
					}
					
					if (fail_r && fail_l)
						break;
				}
				r -= add_r;
				center_index -= add_r;
				add_r = 0;
			}
		}
	}

	if (cnt > max_circle){
		for (k = cnt - 1; k >= 0; k--){
			all_sub_sum[k] = 0;
			i = x[k];
			j = y[k];
			r = original_r[k];
			for (theta = 0; theta < 360; theta += 5){
				
				for (channel = 0; channel < 3; channel++){
					temp = my_cos[theta] * r;
					circle_x = i + my_round(temp);
					temp = my_sin[theta] * r;
					circle_y = j + my_round(temp);
					index = 3 * (circle_y * width + circle_x) + channel;
					sub_sum += colorImg.data[index];
					temp = my_cos[theta] * (r + circle_dist);
					circle_x = i + my_round(temp);
					temp = my_sin[theta] * (r + circle_dist);
					circle_y = j + my_round(temp);
					index = 3 * (circle_y * width + circle_x) + channel;
					sub_sum -= colorImg.data[index];
					if (sub_sum < 0)
						all_sub_sum[k] -= sub_sum;
					else
						all_sub_sum[k] += sub_sum;
				}
				
			}
		}
		for (i = 0; i < max_circle; i++){
			for (j = cnt - 1; j > i; j--){
				if (all_sub_sum[j] > all_sub_sum[j - 1]){
					exchange(all_sub_sum[j], all_sub_sum[j - 1], temp);
					exchange(x[j], x[j - 1], temp);
					exchange(y[j], y[j - 1], temp);
					exchange(radius[j], radius[j - 1], temp);
				}
			}
		}
		*circle_cnt = max_circle;
	}
	else
		*circle_cnt = cnt;

	return MY_OK;

};
