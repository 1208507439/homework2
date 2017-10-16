//#define IMG_SHOW
#define MY_OK 1
#define MY_FAIL -1
#define pi 3.1415926
//#include"hw2.h"
#include "opencv2/opencv.hpp"
using namespace cv;
#include <iostream>
using namespace std;
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
//len：圆的数目
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
	int* len,
	int max_circle)
{
	if (!colorImg.data)
	{
		cout << "image is NULL." << endl;
		return MY_FAIL;
	}
	if (colorImg.channels() != 3) {
		cout << "bgrImg channels wrong!" << endl;
		return MY_FAIL;
	}
	if (colorImg.depth() != 0) {
		cout << "bgrImg depth wrong!" << endl;
		return MY_FAIL;
	}
	if (max_radius > 300 || min_radius<30)
	{
		cout << "radius range error" << endl;
		return MY_FAIL;
	}
	int i = colorImg.rows*colorImg.cols;
	//int _3i = 0;
	//Mat bImg(colorImg.rows, colorImg.cols, CV_8UC1);
	//Mat gImg(colorImg.rows, colorImg.cols, CV_8UC1);
	//Mat rImg(colorImg.rows, colorImg.cols, CV_8UC1);
	int width = colorImg.cols, height = colorImg.rows;
	//for (int j = 0; j < i; )
	//{
	//	bImg.data[j] =colorImg.data[_3i++];
	//	gImg.data[j] =colorImg.data[_3i++];
	//	rImg.data[j++] =colorImg.data[_3i++];
	//}
	//imshow("colorImg", colorImg);
	//waitKey(1);
	//imshow("bImg", bImg);
	//waitKey(1);
	//imshow("gImg", gImg);
	//waitKey(1);
	//imshow("rImg", rImg);
	//waitKey(1);
	int diffb = 0, diffg = 0, diffr = 0;
	int sum1b, sum2b;   //bgr图像素值计数器
	int sum1g, sum2g;   //bgr图像素值计数器
	int sum1r, sum2r;   //bgr图像素值计数器
	short count1b, count1g, count1r;
	short count2b, count2g, count2r;
	short x1 = 0, y1 = 0, x2 = 0, y2 = 0;
	int trim = 1;
	short m, n, r, theta;
	int _x[10000], _y[10000], _radius[10000], _count[10000], _diff[10000];    //距离相近点累加器
	short _cos[360], _sin[360];
	//short temp;
	for (theta = 0; theta < 360; theta++)
	{
		_cos[theta] = 1024 * cos(theta / 180.0 * 3.1415926);
		_sin[theta] = 1024 * sin(theta / 180.0 * 3.1415926);
	}
	for (m = 0; m < height; m++)
	{
		for (n = 0; n < width; n++)
		{
			for (r = min_radius; r <= max_radius; r++)
			{
				count1b = count2b = sum1b = sum2b = 0;   //bgr图像素值计数器
				count1g = count2g = sum1g = sum2g = 0;   //bgr图像素值计数器
				count1r = count2r = sum1r = sum2r = 0;   //bgr图像素值计数器
				for (theta = 0; theta < 360; theta++)
				{
					x1 = n + (((r + trim)*_cos[theta]) >> 10);
					x2 = n + (((r - trim)*_cos[theta]) >> 10);
					y1 = m + (((r + trim)*_sin[theta]) >> 10);
					y2 = m + (((r - trim)*_sin[theta]) >> 10);
					if (y2 >= 0 && y2 < height && x2 >= 0 && x2 < width)    //计算内圈的和
					{
						int index = 3 * (y2*width + x2);
						sum2b = sum2b + colorImg.data[index];
						count2b++;
						sum2g = sum2g + colorImg.data[index + 1];
						count2g++;
						sum2r = sum2r + colorImg.data[index + 2];
						count2r++;
						if (y1 >= 0 && y1 < height && x1 >= 0 && x1 < width)     //外圆
						{
							index = 3 * (y1*width + x1);
							sum1b = sum1b + colorImg.data[index];
							count1b++;
							sum1g = sum1g + colorImg.data[index + 1];
							count1g++;
							sum1r = sum1r + colorImg.data[index + 2];
							count1r++;
						}
					}
				}
				if (count1b > 90)diffb = abs((sum1b / count1b) - (sum2b / count2b));
				if (count1g > 90)diffg = abs((sum1g / count1g) - (sum2g / count2g));
				if (count1r > 90)diffr = abs((sum1r / count1r) - (sum2r / count2r));
				if (diffb >= max_circle_diff)           //平均值的差大于最大值
				{
					for (i = 0; i < (*len); i++)     //在列表里搜索重叠的圆
					{
						if (((n - x[i])*(n - x[i]) + (m - y[i])*(m - y[i])) < (4 * min_center_dist*min_center_dist) && abs(r - radius[i]) < 2 * min_radius_dist)
						{
							_x[i] += n;
							_y[i] += m;
							_radius[i] += r;
							_count[i] += 1;
							_diff[i] += diffb;
							break;
						}
					}
					if (i == (*len))
					{
						x[*len] = n;
						y[*len] = m;
						radius[*len] = r;
						_x[*len] = n;
						_y[*len] = m;
						_radius[*len] = r;
						_count[i] = 1;
						_diff[i] = diffb;
						(*len) = (*len) + 1;
					}
				}
				if (diffg >= max_circle_diff)           //平均值的差大于最大值
				{
					for (i = 0; i < (*len); i++)     //在列表里搜索重叠的圆
					{
						if (((n - x[i])*(n - x[i]) + (m - y[i])*(m - y[i])) < (4 * min_center_dist*min_center_dist) && abs(r - radius[i]) < 2 * min_radius_dist)
						{
							_x[i] += n;
							_y[i] += m;
							_radius[i] += r;
							_count[i] += 1;
							_diff[i] += diffg;
							break;
						}
					}
					if (i == (*len))
					{
						x[*len] = n;
						y[*len] = m;
						radius[*len] = r;
						_x[*len] = n;
						_y[*len] = m;
						_radius[*len] = r;
						_count[i] = 1;
						_diff[i] = diffg;
						(*len) = (*len) + 1;
					}
				}
				if (diffr >= max_circle_diff)           //平均值的差大于最大值
				{
					for (i = 0; i < (*len); i++)     //在列表里搜索重叠的圆
					{
						if (((n - x[i])*(n - x[i]) + (m - y[i])*(m - y[i])) < (4 * min_center_dist*min_center_dist) && abs(r - radius[i]) < 2 * min_radius_dist)
						{
							_x[i] += n;
							_y[i] += m;
							_radius[i] += r;
							_count[i] += 1;
							_diff[i] += diffr;
							break;
						}
					}
					if (i == (*len))
					{
						x[*len] = n;
						y[*len] = m;
						radius[*len] = r;
						_x[*len] = n;
						_y[*len] = m;
						_radius[*len] = r;
						_count[i] = 1;
						_diff[i] = diffr;
						(*len) = (*len) + 1;
					}
				}
			}
		}
	}
	for (i = 0; i < (*len); i++)
	{
		_x[i] = _x[i] / _count[i];
		_y[i] = _y[i] / _count[i];
		_radius[i] = _radius[i] / _count[i];
		_diff[i] = _diff[i] / _count[i];
		circle(colorImg, Point(x[i], y[i]), radius[i], Scalar(255, 255, 255), 1, 8, 0);
	}
	if ((*len) > max_circle)
	{
		for (i = 0; i < (*len); i++)
		{
			for (int j = i; j < (*len); j++)
			{
				if (_diff[i] < _diff[j])
				{
					int temp;
					temp = _diff[i];
					_diff[i] = _diff[j];
					_diff[j] = temp;
					temp = _x[i];
					_x[i] = _x[j];
					_x[j] = temp;
					temp = _y[i];
					_y[i] = _y[j];
					_y[j] = temp;
					temp = _radius[i];
					_radius[i] = _radius[j];
					_radius[j] = temp;
				}
			}
		}
	}
	for (i = 0; i < (*len); i++)
	{
		x[i] = _x[i];
		y[i] = _y[i];
		radius[i] = _radius[i];
	}
	//for (i = 0; i < (*len); i++)
	//{
	//	printf("%d     x:%d  y:%d  radius:%d  diff:%d\n", i + 1, x[i], y[i], radius[i],_diff[i]);
	//	//circle(img, Point(x[i], y[i]), radius[i], Scalar(0, 0, 255), 1, 8, 0);
	//}
	//imshow("circles", colorImg);
	//waitKey(1);
	return MY_OK;

}
