#define _CRT_NONSTDC_NO_WARNINGS 
#define PI 3.1415926f
#include "opencv.hpp"
#include "math.h"
#include <cv.h>
#include <iostream>
using namespace cv;
using namespace std;
#define IN
#define OUT
#define MY_OK 1
#define MY_FAIL -1

// the threshold of converting gradient map  into a binary map; 
#define g2b_threshold 225


//#define test_guan

// this is the value when the gradient map pixels beyond the g2b_threshold will be assigned.
#define G_binaryvalue 1
//cos sin list
float cos_list[360] = { 1,0.999848,0.999391,0.99863,0.997564,0.996195,0.994522,0.992546,0.990268,0.987688,0.984808,0.981627,0.978148,0.97437,0.970296,0.965926,0.961262,0.956305,0.951057,0.945519,0.939693,0.93358,0.927184,0.920505,0.913545,0.906308,0.898794,0.891007,0.882948,0.87462,0.866025,0.857167,0.848048,0.838671,0.829038,0.819152,0.809017,0.798636,0.788011,0.777146,0.766044,0.75471,0.743145,0.731354,0.71934,0.707107,0.694658,0.681998,0.669131,0.656059,0.642788,0.62932,0.615662,0.601815,0.587785,0.573577,0.559193,0.544639,0.529919,0.515038,0.5,0.48481,0.469472,0.453991,0.438371,0.422618,0.406737,0.390731,0.374607,0.358368,0.34202,0.325568,0.309017,0.292372,0.275637,0.258819,0.241922,0.224951,0.207912,0.190809,0.173648,0.156435,0.139173,0.121869,0.104529,0.0871558,0.0697565,0.0523361,0.0348996,0.0174525,7.54979e-08,-0.0174524,-0.0348995,-0.0523358,-0.0697564,-0.0871556,-0.104529,-0.121869,-0.139173,-0.156434,-0.173648,-0.190809,-0.207912,-0.224951,-0.241922,-0.258819,-0.275637,-0.292372,-0.309017,-0.325568,-0.34202,-0.358368,-0.374607,-0.390731,-0.406737,-0.422618,-0.438371,-0.45399,-0.469471,-0.48481,-0.5,-0.515038,-0.529919,-0.544639,-0.559193,-0.573576,-0.587785,-0.601815,-0.615661,-0.62932,-0.642787,-0.656059,-0.669131,-0.681998,-0.694658,-0.707107,-0.71934,-0.731354,-0.743145,-0.754709,-0.766044,-0.777146,-0.788011,-0.798635,-0.809017,-0.819152,-0.829037,-0.83867,-0.848048,-0.857167,-0.866025,-0.87462,-0.882948,-0.891006,-0.898794,-0.906308,-0.913545,-0.920505,-0.927184,-0.93358,-0.939693,-0.945518,-0.951056,-0.956305,-0.961262,-0.965926,-0.970296,-0.97437,-0.978148,-0.981627,-0.984808,-0.987688,-0.990268,-0.992546,-0.994522,-0.996195,-0.997564,-0.99863,-0.999391,-0.999848,-1,-0.999848,-0.999391,-0.99863,-0.997564,-0.996195,-0.994522,-0.992546,-0.990268,-0.987688,-0.984808,-0.981627,-0.978148,-0.97437,-0.970296,-0.965926,-0.961262,-0.956305,-0.951057,-0.945519,-0.939693,-0.93358,-0.927184,-0.920505,-0.913545,-0.906308,-0.898794,-0.891007,-0.882948,-0.87462,-0.866026,-0.857167,-0.848048,-0.838671,-0.829038,-0.819152,-0.809017,-0.798636,-0.788011,-0.777146,-0.766045,-0.75471,-0.743145,-0.731354,-0.71934,-0.707107,-0.694659,-0.681998,-0.669131,-0.656059,-0.642788,-0.629321,-0.615662,-0.601815,-0.587785,-0.573577,-0.559193,-0.544639,-0.529919,-0.515038,-0.5,-0.48481,-0.469472,-0.453991,-0.438371,-0.422618,-0.406737,-0.390731,-0.374607,-0.358368,-0.342021,-0.325568,-0.309017,-0.292372,-0.275638,-0.258819,-0.241922,-0.224951,-0.207912,-0.190809,-0.173649,-0.156435,-0.139173,-0.12187,-0.104529,-0.0871562,-0.069757,-0.0523361,-0.0348998,-0.0174523,1.19249e-08,0.0174518,0.0348993,0.0523357,0.0697566,0.0871557,0.104528,0.121869,0.139173,0.156434,0.173648,0.190809,0.207911,0.224951,0.241921,0.258819,0.275637,0.292371,0.309017,0.325568,0.34202,0.358368,0.374606,0.390731,0.406736,0.422618,0.438371,0.45399,0.469472,0.484809,0.499999,0.515038,0.529919,0.544639,0.559193,0.573576,0.587785,0.601815,0.615661,0.62932,0.642788,0.656059,0.66913,0.681998,0.694658,0.707107,0.71934,0.731353,0.743145,0.75471,0.766044,0.777146,0.788011,0.798635,0.809017,0.819152,0.829037,0.838671,0.848048,0.857167,0.866025,0.87462,0.882947,0.891007,0.898794,0.906308,0.913545,0.920505,0.927184,0.93358,0.939693,0.945518,0.951056,0.956305,0.961262,0.965926,0.970296,0.97437,0.978148,0.981627,0.984808,0.987688,0.990268,0.992546,0.994522,0.996195,0.997564,0.99863,0.999391,0.999848 };
float sin_list[360] = { 0,0.0174524,0.0348995,0.052336,0.0697565,0.0871557,0.104528,0.121869,0.139173,0.156434,0.173648,0.190809,0.207912,0.224951,0.241922,0.258819,0.275637,0.292372,0.309017,0.325568,0.34202,0.358368,0.374607,0.390731,0.406737,0.422618,0.438371,0.453991,0.469472,0.48481,0.5,0.515038,0.529919,0.544639,0.559193,0.573576,0.587785,0.601815,0.615662,0.62932,0.642788,0.656059,0.669131,0.681998,0.694658,0.707107,0.71934,0.731354,0.743145,0.75471,0.766044,0.777146,0.788011,0.798635,0.809017,0.819152,0.829038,0.838671,0.848048,0.857167,0.866025,0.87462,0.882948,0.891007,0.898794,0.906308,0.913545,0.920505,0.927184,0.93358,0.939693,0.945519,0.951057,0.956305,0.961262,0.965926,0.970296,0.97437,0.978148,0.981627,0.984808,0.987688,0.990268,0.992546,0.994522,0.996195,0.997564,0.99863,0.999391,0.999848,1,0.999848,0.999391,0.99863,0.997564,0.996195,0.994522,0.992546,0.990268,0.987688,0.984808,0.981627,0.978148,0.97437,0.970296,0.965926,0.961262,0.956305,0.951056,0.945519,0.939693,0.93358,0.927184,0.920505,0.913545,0.906308,0.898794,0.891007,0.882948,0.87462,0.866025,0.857167,0.848048,0.838671,0.829038,0.819152,0.809017,0.798636,0.788011,0.777146,0.766044,0.75471,0.743145,0.731354,0.71934,0.707107,0.694658,0.681998,0.669131,0.656059,0.642788,0.62932,0.615662,0.601815,0.587785,0.573576,0.559193,0.544639,0.529919,0.515038,0.5,0.48481,0.469472,0.45399,0.438371,0.422618,0.406737,0.390731,0.374607,0.358368,0.34202,0.325568,0.309017,0.292372,0.275637,0.258819,0.241922,0.224951,0.207912,0.190809,0.173648,0.156435,0.139173,0.121869,0.104529,0.0871558,0.0697565,0.052336,0.0348996,0.0174525,5.35898e-08,-0.0174522,-0.0348995,-0.0523359,-0.0697566,-0.0871557,-0.104528,-0.121869,-0.139173,-0.156434,-0.173648,-0.190809,-0.207912,-0.224951,-0.241922,-0.258819,-0.275637,-0.292372,-0.309017,-0.325568,-0.34202,-0.358368,-0.374606,-0.390731,-0.406737,-0.422618,-0.438371,-0.45399,-0.469472,-0.48481,-0.5,-0.515038,-0.529919,-0.544639,-0.559193,-0.573576,-0.587785,-0.601815,-0.615661,-0.62932,-0.642788,-0.656059,-0.669131,-0.681998,-0.694658,-0.707107,-0.71934,-0.731354,-0.743145,-0.75471,-0.766044,-0.777146,-0.788011,-0.798635,-0.809017,-0.819152,-0.829037,-0.838671,-0.848048,-0.857167,-0.866025,-0.87462,-0.882948,-0.891007,-0.898794,-0.906308,-0.913545,-0.920505,-0.927184,-0.93358,-0.939693,-0.945519,-0.951056,-0.956305,-0.961262,-0.965926,-0.970296,-0.97437,-0.978148,-0.981627,-0.984808,-0.987688,-0.990268,-0.992546,-0.994522,-0.996195,-0.997564,-0.99863,-0.999391,-0.999848,-1,-0.999848,-0.999391,-0.99863,-0.997564,-0.996195,-0.994522,-0.992546,-0.990268,-0.987688,-0.984808,-0.981627,-0.978148,-0.97437,-0.970296,-0.965926,-0.961262,-0.956305,-0.951057,-0.945519,-0.939693,-0.93358,-0.927184,-0.920505,-0.913545,-0.906308,-0.898794,-0.891007,-0.882948,-0.87462,-0.866026,-0.857167,-0.848048,-0.838671,-0.829038,-0.819152,-0.809017,-0.798636,-0.788011,-0.777146,-0.766045,-0.75471,-0.743145,-0.731354,-0.71934,-0.707107,-0.694659,-0.681998,-0.669131,-0.656059,-0.642788,-0.629321,-0.615661,-0.601815,-0.587785,-0.573576,-0.559193,-0.544639,-0.529919,-0.515038,-0.5,-0.48481,-0.469472,-0.453991,-0.438371,-0.422618,-0.406737,-0.390731,-0.374607,-0.358368,-0.34202,-0.325568,-0.309017,-0.292372,-0.275637,-0.258819,-0.241922,-0.224951,-0.207912,-0.190809,-0.173648,-0.156434,-0.139173,-0.12187,-0.104528,-0.0871559,-0.0697568,-0.052336,-0.0348997,-0.0174524 };


/*
int cos_sin_list()
{
for (int i = 0;i < 360;i++)
{
if (abs(float(cos(float(i) / 180 * PI)) - cos_list[i] )> 0.01) {
cout << float(cos(float(i) / 180 * PI))<<" "<<cos_list[i] << " cos "<<endl;
}

}
for (int i = 0;i < 360;i++)
{
if (abs((float)(sin(float(i)/ 180 * PI)) - sin_list[i])> 0.01) {
cout << (float)(sin(float(i)) / 180 * PI) <<"  "<<sin_list[i]<<" sin " <<i<<endl;
}

}
cout << "end" << endl;
return 0;
}

int is_near(//判断是否需要跳过这次圆心-半径对
IN int min_radius_dist,
IN int min_center_dist,
IN int *x,
IN int *y,
IN int *radius,
IN int row_i,
IN int col_j,
IN int r,
IN int len
)
{
int tresh = min_center_dist*min_center_dist;
for (int i = len-1;i >=0;  i--)
{
if (x[i] == row_i && y[i] == col_j) {
if (r - radius[i] < min_radius_dist)
return 1;
}
int a = x[i] - row_i;
int b = y[i] - col_j;
if (a*a + b*b < min_radius_dist)
return 1;
}
return 0;
}
*/

struct circle_centre
{
	int x;
	int y;
	int radius;
	float value;
	struct circle_centre *next;
};
int ustc_ConvertBgr2Gray(Mat bgrImg, Mat& grayImg)
{
	if (NULL == bgrImg.data)
	{
		cout << "image input failed" << '\n';
		return -1;
	}
	int width = bgrImg.cols;
	int height = bgrImg.rows;
	int k1, k2, k3, t;
	for (int row_i = 0; row_i < height; row_i++)
	{
		k1 = row_i*width;
		for (int col_j = 0; col_j < width; col_j++)
		{
			k2 = k1 + col_j;
			k3 = k2 * 3;
			t = bgrImg.data[k3] * 114 + bgrImg.data[k3 + 1] * 587 + bgrImg.data[k3 + 2] * 299;
			grayImg.data[k2] = t / 1000;
		}
	}
	return 1;
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
	int max_circle)
{
	int height = colorImg.rows;
	int width = colorImg.cols;
	*circle_cnt = 0;
	int thresh;
	struct circle_centre head_circ;
	Mat grayImg(height, width, CV_8UC1);
	int dx_in, dx_out, dy_in, dy_out;
	int indx_in, indx_out, idx;
	uchar *p_img = grayImg.data;
	int sum_in, sum_out;
	float average;
	*circle_cnt = 0;
	ustc_ConvertBgr2Gray(colorImg, grayImg);

	head_circ.next = NULL;

	for (int row_i = 0;row_i < height;row_i++)
	{
		for (int col_j = 0;col_j < width;col_j++)
		{
			for (int r = min_radius;r <= max_radius;r++)
			{
				if (r > row_i || row_i + r > height || r > col_j || col_j + r > width)
				{
					continue;
				}
				int r_in = r - 5;
				int r_out = r + 5;
				sum_in = 0;
				sum_out = 0;
				for (int theta = 0;theta < 360;theta++)
				{
					dx_in = r_in	*	cos_list[theta];
					dx_out = r_out	*	cos_list[theta];
					dy_in = r_in	*	sin_list[theta];
					dy_out = r_out	*	sin_list[theta];
					sum_in += p_img[(row_i + dx_in)*width + col_j + dy_in];
					sum_out += p_img[(row_i + dx_out)*width + col_j + dy_out];
				}
				average = fabs(sum_in - sum_out) / 360;
				if (average>max_circle_diff)
				{
					struct circle_centre * circle = &head_circ;
					int flag = 1;
					while (circle->next != NULL)
					{
						//半径差小于要求 以及 距离小于要求的只允许有一个圆
						if (abs(circle->next->radius - r) < min_radius  && abs(circle->next->x - row_i) + abs(circle->next->y - col_j) < min_center_dist)
						{
							//现存已有更大差值者
							if (circle->next->value > average)
							{
								flag = 0;
								break;
							}
							else
							{
								struct circle_centre * delete_circle = circle->next;
								circle->next = circle->next->next;
								free(delete_circle);
								*circle_cnt -= 1;
								continue;
							}
						}
						circle = circle->next;
					}
					if (flag) {
						if (*circle_cnt >= max_circle)
						{
							continue;
						}
						*circle_cnt += 1;
						struct circle_centre * new_circle = new circle_centre;
						circle = &head_circ;
						while (circle->next != NULL && circle->next->value > average)
						{
							circle = circle->next;
						}
						new_circle->x = row_i;
						new_circle->y = col_j;
						new_circle->radius = r;
						new_circle->value = average;
						new_circle->next = circle->next;
						circle->next = new_circle;
					}
				}
			}
		}
	}


	/*//create a Mat array to store the total sum of a circle
	Mat sum_in(height, width, CV_32SC3);
	Mat sum_out(height, width, CV_32SC3);
	Mat gradient(height, width, CV_8UC3);
	Mat anglecalc(height, width, CV_8UC3);

	int total_siz = height*width * sizeof(int)*3;
	int total_length = height*width * 3;

	head_circ.next = NULL;
	ustc_CalcGrad(colorImg, gradient, g2b_threshold);



	// basic algorithm is to each certain r,theta , to each circle center
	// add the pixel's value of the inner circle and of outer circle to the average array.
	// after theta loops from 0-359, the whole picture's circle's average have already been calculated
	// then we can calculate the thresh hold and decide whether there is circle centre with the certain radius r.
	int dx_in, dx_out, dy_in, dy_out,xdx_in,xdx_out,idx_x;
	int indx_in, indx_out, idx;
	for (int r = min_radius;r <= max_radius;r++)
	{
	int r_in = r - 5;
	int r_out = r + 5;
	memset(sum_in.data, 0, total_siz);
	memset(sum_out.data, 0, total_siz);
	memset(anglecalc.data , 0, total_length);
	for (int theta = 0;theta < 360;theta++)
	{
	dx_in	= r_in	*	cos_list[theta];
	dx_out	= r_out	*	cos_list[theta];
	dy_in	= r_in	*	sin_list[theta];
	dy_out	= r_out	*	sin_list[theta];
	uchar *p_img=colorImg.data;
	int *p_sum_in = (int *)sum_in.data;
	int *p_sum_out = (int *)sum_out.data;
	uchar *p_grad = gradient.data;
	uchar *p_calc = anglecalc.data;
	for (int row_i = 0;row_i < height;row_i++)
	{
	if (row_i + dx_out < 0 || row_i + dx_out >= height)
	{
	continue;
	}
	// inner circle's x-coordinate index
	xdx_in	= (row_i +	dx_in)*width;
	//outer circle's y-coordinate index
	xdx_out	= (row_i + dx_out)*width;
	// the circle's centre point x_index
	idx_x	= row_i*width;
	for (int col_j = 0;col_j < width;col_j++)
	{
	if (col_j + dy_out < 0 || col_j + dy_out >= width)
	{
	continue;
	}
	indx_in = xdx_in + col_j + dy_in;
	indx_out = xdx_out + col_j + dy_out;
	idx = idx_x + col_j;
	// 3 channel
	indx_in = indx_in+ indx_in+ indx_in;
	indx_out = indx_out+ indx_out+ indx_out;
	idx = idx+ idx+ idx;
	// if the outer cirle's pixel overstep the ranges of array then continue;

	p_sum_in[idx] += (p_img[indx_in])* (p_grad[idx]);
	p_sum_in[idx+1] += (p_img[indx_in+1])* (p_grad[idx+1]);
	p_sum_in[idx+2] += (p_img[indx_in+2])* (p_grad[idx+2]);

	p_sum_out[idx] += (p_img[indx_out]) * (p_grad[idx]);
	p_sum_out[idx + 1] += (p_img[indx_out + 1]) * (p_grad[idx+1]);
	p_sum_out[idx + 2] += (p_img[indx_out + 2]) * (p_grad[idx+2]);

	p_calc[idx] += p_grad[idx];
	idx++;

	p_calc[idx] += p_grad[idx];
	idx++;

	p_calc[idx] += p_grad[idx];

	}
	}

	}
	int *p_sum_in = (int *)sum_in.data;
	int *p_sum_out = (int *)sum_out.data;
	uchar *p_anglecalc = anglecalc.data;
	for (int row_i = 0;row_i < height;row_i++)
	{
	int k0 = row_i*width;
	for (int col_j = 0;col_j < width;col_j++)
	{
	int k1 = k0 +col_j;
	//3 channel
	k1 = k1 + k1 + k1;
	// if the proportion of circle less than one fouth then continue;
	if (p_anglecalc[k1] < 90)
	{
	continue;
	}
	float average = abs(p_sum_in[k1] - p_sum_out[k1])*1.0f / p_anglecalc[k1];

	struct circle_centre * circle = &head_circ;

	#ifdef test_guan
	cout << average << '\t';
	#endif
	if (average > max_circle_diff)
	{
	while (circle->next != NULL)
	{
	//半径差小于要求 以及 距离小于要求的只允许有一个圆
	if (abs(circle->next->radius - r) < min_radius  && abs(circle->next->x - row_i) + abs(circle->next->y - col_j) < min_center_dist)
	{
	//现存已有更大差值者
	if (circle->next->value > average)
	{
	break;
	}
	else
	{
	struct circle_centre * delete_circle = circle->next;
	circle->next = circle->next->next;
	free(delete_circle);
	continue;
	}
	}
	circle = circle->next;

	//头插法插入合格元素

	}
	if (NULL == circle)
	{
	int cnt = 0;
	struct circle_centre * new_circle = (struct circle_centre *) malloc(sizeof(struct circle_centre));
	circle = &head_circ;
	while (circle->next != NULL && circle->next->value > average)
	{
	cnt++;
	circle = circle->next;
	}

	if (cnt >= max_circle)
	continue;

	new_circle->x = row_i;
	new_circle->y = col_j;
	new_circle->radius = r;
	new_circle->value = average;
	new_circle->next = circle->next;
	circle->next = new_circle;
	}
	}
	else
	{
	;
	}

	k1 += 1;
	if (p_anglecalc[k1] < 90)
	{
	continue;
	}
	average = abs(p_sum_in[k1] - p_sum_out[k1])*1.0f / p_anglecalc[k1];
	circle = &head_circ;
	if (average > max_circle_diff)
	{
	while (circle->next != NULL)
	{
	if (abs(circle->next->radius - r) < min_radius  && abs(circle->next->x - row_i) + abs(circle->next->y - col_j) < min_center_dist)
	{
	if (circle->next->value > average)
	{
	break;
	}
	else
	{
	struct circle_centre * delete_circle = circle->next;
	circle->next = circle->next->next;
	free(delete_circle);
	continue;
	}
	}
	circle = circle->next;
	}
	if (NULL == circle)
	{
	int cnt = 0;
	struct circle_centre * new_circle = (struct circle_centre *) malloc(sizeof(struct circle_centre));
	circle = &head_circ;
	while (circle->next != NULL && circle->next->value > average)
	{
	cnt++;
	circle = circle->next;
	}

	if (cnt >= max_circle)
	continue;

	new_circle->x = row_i;
	new_circle->y = col_j;
	new_circle->radius = r;
	new_circle->value = average;
	new_circle->next = circle->next;
	circle->next = new_circle;
	}
	}
	else
	{
	;
	}


	k1 += 1;
	if (p_anglecalc[k1] < 90)
	{
	continue;
	}
	average = abs(p_sum_in[k1] - p_sum_out[k1])*1.0f / p_anglecalc[k1];
	circle = &head_circ;
	if (average > max_circle_diff)
	{
	while (circle->next != NULL)
	{
	if (abs(circle->next->radius - r) < min_radius  && abs(circle->next->x - row_i) + abs(circle->next->y - col_j) < min_center_dist)
	{
	if (circle->next->value > average)
	{
	break;
	}
	else
	{
	struct circle_centre * delete_circle = circle->next;
	circle->next = circle->next->next;
	free(delete_circle);
	continue;
	}
	}
	circle = circle->next;
	}
	if (NULL == circle)
	{
	int cnt = 0;
	struct circle_centre * new_circle = (struct circle_centre *) malloc(sizeof(struct circle_centre));
	circle = &head_circ;
	while (circle->next != NULL && circle->next->value > average)
	{
	cnt++;
	circle = circle->next;
	}

	if (cnt >= max_circle)
	continue;

	new_circle->x = row_i;
	new_circle->y = col_j;
	new_circle->radius = r;
	new_circle->value = average;
	new_circle->next = circle->next;
	circle->next = new_circle;
	}
	}
	else
	{
	;
	}
	}
	}
	}*/

	*circle_cnt = 0;
	struct circle_centre *circle = head_circ.next;
	while (circle != NULL)
	{
		x[*circle_cnt] = circle->x;
		y[*circle_cnt] = circle->y;
		radius[*circle_cnt] = circle->radius;
		*circle_cnt += 1;
		circle = circle->next;
	}
	return MY_OK;
}

