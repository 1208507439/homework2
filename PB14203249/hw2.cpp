#include "opencv2/opencv.hpp"
#include "cv.h"
#include "math.h"
#include "iostream"
#include "string"

#define MY_OK			1
#define MY_FAIL			-1
#define PER_RAD			0.0174533

#define IMG_SHOW
#define my_function 
#define defense

#define max_radiu_range	310
#define max_row			700
#define max_col			700
int Circle_B[max_radiu_range][max_row][max_col] = {0};
int Circle_G[max_radiu_range][max_row][max_col] = {0};
int Circle_R[max_radiu_range][max_row][max_col]= {0};

using namespace cv;
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
//circle_cnt：图像中找到的圆的数目
//max_circle：外部传入参数，圆的数目上限。如果图像中圆的数目超过此参数，根据差分值由大到小进行排序
//返回值：MY_OK或者MY_FAIL
int ustc_Find_Circles_By_Difference_new(
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
#ifdef defense
	if (NULL == colorImg.data)
	{
		cout << "image is NULL" << endl;
		return MY_FAIL;
	}
	if (int(colorImg.channels()) != 3)
	{
		cout << "image is not color" << endl;
		return MY_FAIL;
	}
	if (min_radius > max_radius || min_radius < 30 || max_radius > 300)
	{
		cout << "there are some error in min_radius or max_radius" << endl;
		return MY_FAIL;
	}
	if (max_circle <= 0)
	{
		cout << "max_circle shoule larger than zero" << endl;
		*circle_cnt = 0;
		return MY_FAIL;
	}
	if (colorImg.rows > 700 || colorImg.cols > 700 )
	{
		cout << " I am very sorry.Because of the This program only can find circle in 700*700 or smaller than it. \n\n " << endl;
		return MY_FAIL;
	}
	if (NULL == x || NULL == y || NULL == radius || NULL == circle_cnt)
	{
		cout << "there have an empty pointer" << endl;
		return MY_FAIL;
	}
	if (min_center_dist != 5 || min_radius_dist != 5)
	{
		cout << "min_center_dist and min_radius_dist should = 5" << endl;
		return MY_FAIL;
	}
	if (max_circle_diff > 360 || max_circle_diff < 0)
	{
		cout << "0 should < max_circle_diff should < 360" << endl;
		return MY_FAIL;
	}
#endif // defense

#ifdef my_function
	float my_sin[360];
	float my_cos[360];
	float rad = 0;
	//生成sin和cos数组，降低运算时间
	for (int theta = 0; theta < 360; ++theta)
	{
		my_sin[theta] = sin(rad);
		my_cos[theta] = cos(rad);
		rad += PER_RAD;
	}
	int my_abs[513];
	//生成abs数组，降低运算时间
	for (int abs_value = 0; abs_value < 513; abs_value++)
	{
		my_abs[abs_value] = abs(abs_value - 256);
	}
#endif my_function

	int height = colorImg.rows;
	int width = colorImg.cols;
	cout << "原图高度和宽度分别为" << height << "\t" << width << endl;

	uchar* ImgData = colorImg.data;

	for (int radiu = min_radius - 5; radiu < max_radius + 5; radiu++)
	{
		cout << "radiu = " << radiu ;

		for (int theta = 0; theta < 360; theta++)
		{
			int circle_row_i = - radiu * my_sin[theta];
			int row_i = 0;
			if (circle_row_i < 0)
			{
				row_i -= circle_row_i;
				circle_row_i = 0;//按理来说遍历少于360度的话，max_circle_diff是应该做一些改变的
			}
			for ( ; (circle_row_i - height < 0)&&(row_i < height); row_i++)
			{


				int circle_col_j = radiu * my_cos[theta];
				int col_j = 0;
				if (circle_col_j < 0)
				{
					col_j -= circle_col_j;
					circle_col_j = 0;
				}
				int location = 3 * (circle_row_i * width + circle_col_j);

				for ( ; (circle_col_j - width < 0)&&(col_j <width); col_j++)
				{
					Circle_B[radiu][row_i][col_j] += ImgData[location++];
					Circle_G[radiu][row_i][col_j] += ImgData[location++];
					Circle_R[radiu][row_i][col_j] += ImgData[location++];
					circle_col_j++;
				}
				circle_row_i++;
			}
		}
	}

	int diff[1000];
	int circle_center_num = 0;
	for (int row_i = 0; row_i < height; row_i++)
	{
		for (int col_j = 0; col_j < width; col_j++)
		{
			for (int radiu = min_radius; radiu < max_radius; radiu++)
			{
				int diff_B = abs(Circle_B[radiu + 5][row_i][col_j] - Circle_B[radiu - 5][row_i][col_j]);
				int diff_G = abs(Circle_G[radiu + 5][row_i][col_j] - Circle_G[radiu - 5][row_i][col_j]);
				int diff_R = abs(Circle_R[radiu + 5][row_i][col_j] - Circle_R[radiu - 5][row_i][col_j]);
				int max_diff = (diff_B > diff_G) ? diff_B : diff_G;
				max_diff = (max_diff > diff_R) ? max_diff : diff_R;
				if (max_diff > max_circle_diff * 360)
				{
					//相邻的两个圆心之间的距离应该大于min_center_dist
					int skip = 0;
					for (int temp_num = 0; temp_num < circle_center_num; temp_num++)
					{
						int derta_distance = sqrt((row_i - y[temp_num])*(row_i - y[temp_num]) + (col_j - x[temp_num])*(col_j - x[temp_num]));
						if (derta_distance<min_center_dist && abs(radiu-radius[temp_num]) < min_radius_dist)
						{
							//如果该位置与已知圆的距离小于min_center_dist
							//则快速移动col_j
							//此时有越界风险
							skip = 1;
							break;
						}

					}
					//越界风险解除
					if (skip == 0)
					{
						if (circle_center_num > max_circle - 1)
						{
							int i = 0;
							while (diff[i] > max_diff)
							{
								i++;
							}
							if (i < max_circle)
							{
								x[i] = col_j;
								y[i] = row_i;
								radius[i] = radiu;
								diff[i] = max_diff;
								//cout << 1 << "\t" << i << endl;
							}
						}
						else
						{
							x[circle_center_num] = col_j;
							y[circle_center_num] = row_i;
							radius[circle_center_num] = radiu;
							diff[circle_center_num] = max_diff;
							circle_center_num++;
							//相邻的两个圆心相同的圆的半径应该大于min_radius_dist
							radiu += min_radius_dist;
							//cout << 2  <<"\t" << circle_center_num << endl;
						}
					}
				}
			}
		}
	}

	*circle_cnt = circle_center_num;

#ifdef IMG_SHOW
	for (int i = 0; i < circle_center_num; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			for (int theta = 0; theta < 360; ++theta)
			{
				//以当前位置为圆心，从x轴正半轴逆时针旋转
				int circle_row_i = y[i] - (radius[i] + j) * my_sin[theta];
				int circle_col_j = x[i] + (radius[i] + j) * my_cos[theta];
				if (((circle_row_i >> 31) + 1) * ((circle_col_j >> 31) + 1) * (((height - circle_row_i - 1) >> 31) + 1) * (((width - circle_col_j - 1) >> 31) + 1))
				{
					colorImg.data[3 * (circle_row_i * width + circle_col_j)] = 0;
					colorImg.data[3 * (circle_row_i * width + circle_col_j) + 1] = 0;
					colorImg.data[3 * (circle_row_i * width + circle_col_j) + 2] = 0;
				}
			}

		}
		cout << "第" <<i<<"个"<< "\t" << y[i] << "\t" << x[i] << "\t" << "radius = " << radius[i] << "\tdiff = " << diff[i] << endl;
	}

	namedWindow("FindCircle", 1);
	imshow("FindCircle", colorImg);
	waitKey(0);
#endif
	return MY_FAIL;
}
