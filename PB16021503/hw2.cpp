#include <opencv.hpp>
using namespace cv;
#include <iostream>
using namespace std;
#include <time.h>

#define MY_OK 1
#define MY_FAIL -1 



int ustc_Circles_By_Difference(Mat colorImg, int min_radius, int max_radius, int min_center_dist, int min_radius_dist, int max_circle_diff, int *x, int *y, int *radius, int *circle_cnt, int max_circle)
{
	//检测指针是否正常传入
	if (NULL == colorImg.data || NULL == x || NULL == y || NULL == radius || NULL == circle_cnt)
	{
		cout << "inpoint is NULL." << endl;
		return MY_FAIL;
	}

	int width = colorImg.cols;
	int height = colorImg.rows;
	int area = width * height;
	
	int circle_x[10000] = { 0 };
	int circle_y[10000] = { 0 };
	int circle_radius[10000] = { 0 };
	int circle_diff[10000] = { 0 };
	int num = 0;
	
	//检测空间是否正确分配
	if (NULL == circle_x || NULL == circle_y || NULL == circle_radius )
	{
		cout << "point erro" << endl;
		return MY_FAIL;
	}

	int *pcircle_x = circle_x;
	int *pcircle_y = circle_y;
	int *pcircle_radius = circle_radius;
	int *pcircle_diff = circle_diff;


	
	//将图片分为三个通道灰度图分开储存
	Mat blueImg(height, width, CV_8UC1);
	Mat greenImg(height, width, CV_8UC1);
	Mat redImg(height, width, CV_8UC1);

	uchar* data_color = colorImg.data;
	uchar* data_blue = blueImg.data;
	uchar* data_green = greenImg.data;
	uchar* data_red = redImg.data;

	for (int i = 0;i < height;i++)
		for (int j = 0;j < width;j++)
		{
			int loc = i*width + j;
			int loc3 = 3 * loc;
			data_blue[loc] = data_color[loc3];
			data_green[loc] = data_color[loc3 + 1];
			data_red[loc] = data_color[loc3 + 2];
		}


#ifdef IMG_SHOW
	namedWindow("blueImg", 0);
	imshow("blueImg", blueImg);
	namedWindow("greenImg", 0);
	imshow("greenImg", greenImg);
	namedWindow("redImg", 0);
	imshow("redImg", redImg);
#endif


	Mat cannyImg_blue(height, width, CV_8UC1);
	Canny(blueImg, cannyImg_blue, 60, 300, 3);
	uchar* canny_blue = cannyImg_blue.data;
	Mat cannyImg_green(height, width, CV_8UC1);
	Canny(greenImg, cannyImg_green, 60, 300, 3);
	uchar* canny_green = cannyImg_green.data;
	Mat cannyImg_red(height, width, CV_8UC1);
	Canny(redImg, cannyImg_red, 60, 300, 3);
	uchar* canny_red = cannyImg_red.data;


#ifdef IMG_SHOW
	namedWindow("cannyImg_blue", 0);
	imshow("cannyImg_blue", cannyImg_blue);
	namedWindow("cannyImg_green", 0);
	imshow("cannyImg_green", cannyImg_green);
	namedWindow("cannyImg_red", 0);
	imshow("cannyImg_red", cannyImg_red);
	//waitKey(0);

#endif

	float cos_theta[360] = { 1, 0.999848, 0.999391, 0.99863, 0.997564, 0.996195, 0.994522, 0.992546, 0.990268, 0.987688, 0.984808, 0.981627, 0.978148, 0.97437, 0.970296, 0.965926, 0.961262, 0.956305, 0.951057, 0.945519, 0.939693, 0.93358, 0.927184, 0.920505, 0.913545, 0.906308, 0.898794, 0.891007, 0.882948, 0.87462, 0.866025, 0.857167, 0.848048, 0.838671, 0.829038, 0.819152, 0.809017, 0.798636, 0.788011, 0.777146, 0.766044, 0.75471, 0.743145, 0.731354, 0.71934, 0.707107, 0.694658, 0.681998, 0.669131, 0.656059, 0.642788, 0.62932, 0.615662, 0.601815, 0.587785, 0.573576, 0.559193, 0.544639, 0.529919, 0.515038, 0.5, 0.48481, 0.469472, 0.453991, 0.438371, 0.422618, 0.406737, 0.390731, 0.374607, 0.358368, 0.34202, 0.325568, 0.309017, 0.292372, 0.275637, 0.258819, 0.241922, 0.224951, 0.207912, 0.190809, 0.173648, 0.156434, 0.139173, 0.121869, 0.104528, 0.0871558, 0.0697565, 0.052336, 0.0348995, 0.0174524, -4.37114e-08, -0.0174524, -0.0348995, -0.0523359, -0.0697565, -0.0871558, -0.104529, -0.121869, -0.139173, -0.156434, -0.173648, -0.190809, -0.207912, -0.224951, -0.241922, -0.258819, -0.275637, -0.292372, -0.309017, -0.325568, -0.34202, -0.358368, -0.374607, -0.390731, -0.406737, -0.422618, -0.438371, -0.453991, -0.469472, -0.48481, -0.5, -0.515038, -0.529919, -0.544639, -0.559193, -0.573576, -0.587785, -0.601815, -0.615661, -0.62932, -0.642788, -0.656059, -0.669131, -0.681998, -0.694658, -0.707107, -0.71934, -0.731354, -0.743145, -0.75471, -0.766044, -0.777146, -0.788011, -0.798635, -0.809017, -0.819152, -0.829038, -0.838671, -0.848048, -0.857167, -0.866025, -0.87462, -0.882948, -0.891006, -0.898794, -0.906308, -0.913545, -0.920505, -0.927184, -0.93358, -0.939693, -0.945519, -0.951056, -0.956305, -0.961262, -0.965926, -0.970296, -0.97437, -0.978148, -0.981627, -0.984808, -0.987688, -0.990268, -0.992546, -0.994522, -0.996195, -0.997564, -0.99863, -0.999391, -0.999848, -1, -0.999848, -0.999391, -0.99863, -0.997564, -0.996195, -0.994522, -0.992546, -0.990268, -0.987688, -0.984808, -0.981627, -0.978148, -0.97437, -0.970296, -0.965926, -0.961262, -0.956305, -0.951057, -0.945519, -0.939693, -0.93358, -0.927184, -0.920505, -0.913545, -0.906308, -0.898794, -0.891007, -0.882948, -0.87462, -0.866025, -0.857167, -0.848048, -0.838671, -0.829038, -0.819152, -0.809017, -0.798635, -0.788011, -0.777146, -0.766044, -0.75471, -0.743145, -0.731354, -0.71934, -0.707107, -0.694658, -0.681998, -0.669131, -0.656059, -0.642788, -0.62932, -0.615662, -0.601815, -0.587785, -0.573576, -0.559193, -0.544639, -0.529919, -0.515038, -0.5, -0.48481, -0.469472, -0.453991, -0.438371, -0.422618, -0.406737, -0.390731, -0.374607, -0.358368, -0.34202, -0.325568, -0.309017, -0.292372, -0.275637, -0.258819, -0.241922, -0.224951, -0.207912, -0.190809, -0.173648, -0.156435, -0.139173, -0.121869, -0.104528, -0.0871557, -0.0697565, -0.0523361, -0.0348993, -0.0174523, 1.19249e-08, 0.0174523, 0.0348993, 0.0523361, 0.0697566, 0.0871557, 0.104528, 0.121869, 0.139173, 0.156435, 0.173648, 0.190809, 0.207911, 0.224951, 0.241922, 0.258819, 0.275637, 0.292371, 0.309017, 0.325568, 0.34202, 0.358368, 0.374607, 0.390731, 0.406737, 0.422618, 0.438371, 0.453991, 0.469472, 0.48481, 0.5, 0.515038, 0.529919, 0.544639, 0.559193, 0.573576, 0.587785, 0.601815, 0.615662, 0.62932, 0.642788, 0.656059, 0.669131, 0.681998, 0.694658, 0.707107, 0.71934, 0.731354, 0.743145, 0.75471, 0.766044, 0.777146, 0.788011, 0.798636, 0.809017, 0.819152, 0.829038, 0.838671, 0.848048, 0.857167, 0.866025, 0.87462, 0.882948, 0.891007, 0.898794, 0.906308, 0.913546, 0.920505, 0.927184, 0.93358, 0.939693, 0.945519, 0.951057, 0.956305, 0.961262, 0.965926, 0.970296, 0.97437, 0.978148, 0.981627, 0.984808, 0.987688, 0.990268, 0.992546, 0.994522, 0.996195, 0.997564, 0.99863, 0.999391, 0.999848 };
	float sin_theta[360] = { 0, 0.0174524, 0.0348995, 0.052336, 0.0697565, 0.0871557, 0.104528, 0.121869, 0.139173, 0.156434, 0.173648, 0.190809, 0.207912, 0.224951, 0.241922, 0.258819, 0.275637, 0.292372, 0.309017, 0.325568, 0.34202, 0.358368, 0.374607, 0.390731, 0.406737, 0.422618, 0.438371, 0.453991, 0.469472, 0.48481, 0.5, 0.515038, 0.529919, 0.544639, 0.559193, 0.573576, 0.587785, 0.601815, 0.615662, 0.62932, 0.642788, 0.656059, 0.669131, 0.681998, 0.694658, 0.707107, 0.71934, 0.731354, 0.743145, 0.75471, 0.766044, 0.777146, 0.788011, 0.798636, 0.809017, 0.819152, 0.829038, 0.838671, 0.848048, 0.857167, 0.866025, 0.87462, 0.882948, 0.891007, 0.898794, 0.906308, 0.913545, 0.920505, 0.927184, 0.93358, 0.939693, 0.945519, 0.951057, 0.956305, 0.961262, 0.965926, 0.970296, 0.97437, 0.978148, 0.981627, 0.984808, 0.987688, 0.990268, 0.992546, 0.994522, 0.996195, 0.997564, 0.99863, 0.999391, 0.999848, 1, 0.999848, 0.999391, 0.99863, 0.997564, 0.996195, 0.994522, 0.992546, 0.990268, 0.987688, 0.984808, 0.981627, 0.978148, 0.97437, 0.970296, 0.965926, 0.961262, 0.956305, 0.951056, 0.945519, 0.939693, 0.93358, 0.927184, 0.920505, 0.913545, 0.906308, 0.898794, 0.891006, 0.882948, 0.87462, 0.866025, 0.857167, 0.848048, 0.838671, 0.829038, 0.819152, 0.809017, 0.798635, 0.788011, 0.777146, 0.766044, 0.75471, 0.743145, 0.731354, 0.71934, 0.707107, 0.694658, 0.681998, 0.669131, 0.656059, 0.642788, 0.629321, 0.615661, 0.601815, 0.587785, 0.573576, 0.559193, 0.544639, 0.529919, 0.515038, 0.5, 0.48481, 0.469472, 0.453991, 0.438371, 0.422618, 0.406737, 0.390731, 0.374606, 0.358368, 0.34202, 0.325568, 0.309017, 0.292372, 0.275637, 0.258819, 0.241922, 0.224951, 0.207912, 0.190809, 0.173648, 0.156434, 0.139173, 0.121869, 0.104528, 0.0871556, 0.0697565, 0.052336, 0.0348995, 0.0174525, -8.74228e-08, -0.0174524, -0.0348994, -0.052336, -0.0697564, -0.0871558, -0.104528, -0.121869, -0.139173, -0.156434, -0.173648, -0.190809, -0.207912, -0.224951, -0.241922, -0.258819, -0.275637, -0.292372, -0.309017, -0.325568, -0.34202, -0.358368, -0.374607, -0.390731, -0.406737, -0.422618, -0.438371, -0.453991, -0.469472, -0.48481, -0.5, -0.515038, -0.529919, -0.544639, -0.559193, -0.573576, -0.587785, -0.601815, -0.615661, -0.62932, -0.642788, -0.656059, -0.669131, -0.681998, -0.694658, -0.707107, -0.71934, -0.731354, -0.743145, -0.75471, -0.766045, -0.777146, -0.788011, -0.798635, -0.809017, -0.819152, -0.829038, -0.838671, -0.848048, -0.857167, -0.866025, -0.87462, -0.882948, -0.891006, -0.898794, -0.906308, -0.913545, -0.920505, -0.927184, -0.933581, -0.939693, -0.945519, -0.951056, -0.956305, -0.961262, -0.965926, -0.970296, -0.97437, -0.978148, -0.981627, -0.984808, -0.987688, -0.990268, -0.992546, -0.994522, -0.996195, -0.997564, -0.99863, -0.999391, -0.999848, -1, -0.999848, -0.999391, -0.99863, -0.997564, -0.996195, -0.994522, -0.992546, -0.990268, -0.987688, -0.984808, -0.981627, -0.978148, -0.97437, -0.970296, -0.965926, -0.961262, -0.956305, -0.951056, -0.945519, -0.939693, -0.93358, -0.927184, -0.920505, -0.913545, -0.906308, -0.898794, -0.891006, -0.882948, -0.87462, -0.866025, -0.857167, -0.848048, -0.83867, -0.829038, -0.819152, -0.809017, -0.798635, -0.788011, -0.777146, -0.766044, -0.75471, -0.743145, -0.731354, -0.71934, -0.707107, -0.694658, -0.681998, -0.669131, -0.656059, -0.642788, -0.62932, -0.615661, -0.601815, -0.587785, -0.573577, -0.559193, -0.544639, -0.529919, -0.515038, -0.5, -0.484809, -0.469471, -0.453991, -0.438371, -0.422618, -0.406736, -0.390731, -0.374607, -0.358368, -0.34202, -0.325568, -0.309017, -0.292372, -0.275638, -0.258819, -0.241922, -0.224951, -0.207912, -0.190809, -0.173648, -0.156434, -0.139173, -0.121869, -0.104529, -0.0871556, -0.0697564, -0.052336, -0.0348996, -0.0174526 };




	Mat key_blueImg(height, width, CV_16UC1);//blue内外圆计数器
	uchar *key_blue = key_blueImg.data;

	Mat avemin_b(height, width, CV_16UC1);//blue内圆平均灰度
	ushort *datamin_b = (ushort *)avemin_b.data;

	Mat avemax_b(height, width, CV_16UC1);//blue外圆平均灰度值
	ushort *datamax_b = (ushort *)avemax_b.data;

	Mat key_greenImg(height, width, CV_16UC1);//green内外圆计数器
	uchar *key_green = key_greenImg.data;

	Mat avemin_g(height, width, CV_16UC1);//green内圆平均灰度
	ushort *datamin_g = (ushort *)avemin_g.data;

	Mat avemax_g(height, width, CV_16UC1);//green外圆平均灰度值
	ushort *datamax_g = (ushort *)avemax_g.data;


	Mat key_redImg(height, width, CV_16UC1);//red内外圆计数器
	uchar *key_red = key_redImg.data;

	Mat avemin_r(height, width, CV_16UC1);//red内圆平均灰度
	ushort *datamin_r = (ushort *)avemin_r.data;

	Mat avemax_r(height, width, CV_16UC1);//red外圆平均灰度值
	ushort *datamax_r = (ushort *)avemax_r.data;

	int key_min1 = 50;
	int key_min = 110;
	//进行圆周差分遍历
	if (min_radius > 60)
	{
		for (int r = max_radius;r > 60;r--)
		{
			key_blueImg.setTo(0);
			avemin_b.setTo(0);
			avemax_b.setTo(0);

			key_greenImg.setTo(0);
			avemin_g.setTo(0);
			avemax_g.setTo(0);

			key_redImg.setTo(0);
			avemin_r.setTo(0);
			avemax_r.setTo(0);


			for (int theta = 0; theta < 360; theta += 1)
			{
				float cos_theta = cos(theta);
				float sin_theta = sin(theta);
				int p_xmid = r * cos_theta;
				int p_ymid = r * sin_theta;
				int ex_rcos = 5 * cos_theta;
				int ex_rsin = 5 * sin_theta;

				for (int picture_y = 0;picture_y < height;picture_y++)
				{
					for (int picture_x = 0;picture_x < width;picture_x++)
					{
						//圆位置计算
						int point_xmid = picture_x + p_xmid;
						int point_ymid = picture_y + p_ymid;

						//内圆位置计算
						int point_xmin = point_xmid - ex_rcos;;
						int point_ymin = point_ymid - ex_rsin;

						//外圆位置计算
						int point_xmax = point_xmid + ex_rcos;
						int point_ymax = point_ymid + ex_rsin;
						int point_max = point_xmax + point_ymax *width;
						//计算内外圆平均灰度
						if (point_max >= 0 && point_max < area) //判断外圆点在图内
						{
							int point = picture_x + picture_y * width;
							int point_mid = point_xmid + point_ymid* width;
							int point_min = point_xmin + point_ymin * width;

							if (canny_blue[point_mid] > 170)
							{
								key_blue[point]++;
								datamin_b[point] += data_blue[point_min];
								datamax_b[point] += data_blue[point_max];
							}

							if (canny_green[point_mid] > 170)
							{
								key_green[point]++;
								datamin_g[point] += data_green[point_min];
								datamax_g[point] += data_green[point_max];
							}

							if (canny_red[point_mid] > 170)
							{
								key_red[point]++;
								datamin_r[point] += data_red[point_min];
								datamax_r[point] += data_red[point_max];
							}

						}
					}
				}
			}
			//对所有半径为r的圆查分进行筛选

			for (int y = 0;y < height;y++)
				for (int x = 0;x < width;x++)
				{
					int loc = x + y * width;
					float key_b = key_blue[loc];
					ushort dtmin_b = datamin_b[loc];
					ushort dtmax_b = datamax_b[loc];
                    int circle_diff_b = (dtmin_b - dtmax_b) /key_b;//差分计算
					circle_diff_b = ((circle_diff_b > 0) * 2 - 1)*circle_diff_b;

					float key_g = key_green[loc];
					ushort dtmin_g = datamin_g[loc];
					ushort dtmax_g = datamax_g[loc];
					int circle_diff_g = (dtmin_g - dtmax_g) / key_g;//差分计算
					circle_diff_g = ((circle_diff_g > 0) * 2 - 1)*circle_diff_g;

                    float key_r = key_red[loc];
					ushort dtmin_r = datamin_r[loc];
					ushort dtmax_r = datamax_r[loc];
                    int circle_diff_r = (dtmin_r - dtmax_r) / key_r;
					circle_diff_r = ((circle_diff_r > 0) * 2 - 1)*circle_diff_r;//差分计算

					if (key_b > key_min)//未遮挡是否超过四分之一
					{

						if (circle_diff_b >= max_circle_diff)//判断是否超过阈值
						{
							*pcircle_x = x; pcircle_x++;
							*pcircle_y = y; pcircle_y++;
							*pcircle_radius = r;pcircle_radius++;
							*pcircle_diff = circle_diff_b + circle_diff_g + circle_diff_r;pcircle_diff++;
							num++;
							x += 4;
							continue;
						}

					}


					if (key_g > key_min)//未遮挡是否超过四分之一
					{
						if (circle_diff_g >= max_circle_diff)//判断是否超过阈值
						{
							*pcircle_x = x; pcircle_x++;
							*pcircle_y = y; pcircle_y++;
							*pcircle_radius = r;pcircle_radius++;
							*pcircle_diff = circle_diff_b + circle_diff_g + circle_diff_r;pcircle_diff++;
							num++;
							x += 4;
							continue;
						}
					}

					

					if (key_r > key_min)//未遮挡是否超过四分之一
					{
						if (circle_diff_r >= max_circle_diff)//判断是否超过阈值
						{
							*pcircle_x = x; pcircle_x++;
							*pcircle_y = y; pcircle_y++;
							*pcircle_radius = r;pcircle_radius++;
							*pcircle_diff = circle_diff_b + circle_diff_g + circle_diff_r;pcircle_diff++;
							num++;
							x += 4;
							continue;
						}
					}
				}
		}
	}

	if (min_radius <= 60)
	{

		for (int r = max_radius;r > min_radius + 30;r--)
		{
			
			key_blueImg.setTo(0);
			avemin_b.setTo(0);
			avemax_b.setTo(0);

			key_greenImg.setTo(0);
			avemin_g.setTo(0);
			avemax_g.setTo(0);

			key_redImg.setTo(0);
			avemin_r.setTo(0);
			avemax_r.setTo(0);


			for (int theta = 0; theta < 360; theta += 1)
			{
				float cos_theta = cos(theta);
				float sin_theta = sin(theta);
				int p_xmid = r * cos_theta;
				int p_ymid = r * sin_theta;
				int ex_rcos = 5 * cos_theta;
				int ex_rsin = 5 * sin_theta;

				for (int picture_y = 0;picture_y < height;picture_y++)
				{
					for (int picture_x = 0;picture_x < width;picture_x++)
					{
						//圆位置计算
						int point_xmid = picture_x + p_xmid;
						int point_ymid = picture_y + p_ymid;

						//内圆位置计算
						int point_xmin = point_xmid - ex_rcos;;
						int point_ymin = point_ymid - ex_rsin;

						//外圆位置计算
						int point_xmax = point_xmid + ex_rcos;
						int point_ymax = point_ymid + ex_rsin;
						int point_max = point_xmax + point_ymax *width;
						//计算内外圆平均灰度
						if (point_max >= 0 && point_max < area) //判断外圆点在图内
						{
							int point = picture_x + picture_y * width;
							int point_mid = point_xmid + point_ymid* width;
							int point_min = point_xmin + point_ymin * width;

							if (canny_blue[point_mid] > 170)
							{
								//key_blue[point]++;
								datamin_b[point] += data_blue[point_min];
								datamax_b[point] += data_blue[point_max];
							}

							if (canny_green[point_mid] > 170)
							{
								//key_green[point]++;
								datamin_g[point] += data_green[point_min];
								datamax_g[point] += data_green[point_max];
							}

							if (canny_red[point_mid] > 170)
							{
								//key_red[point]++;
								datamin_r[point] += data_red[point_min];
								datamax_r[point] += data_red[point_max];
							}

						}
					}
				}
			}
			//对所有半径为r的圆查分进行筛选


			for (int y = 0;y < height;y++)
				for (int x = 0;x < width;x++)
				{
					int loc = x + y * width;
					float key_b = key_blue[loc];
					ushort dtmin_b = datamin_b[loc];
					ushort dtmax_b = datamax_b[loc];
					int flag_b = 0, flag_g = 0, flag_r = 0;
					float circle_diff_b = (dtmin_b - dtmax_b) / key_b;//差分计算
					circle_diff_b = ((circle_diff_b > 0) * 2 - 1)*circle_diff_b;

					float key_g = key_green[loc];
					ushort dtmin_g = datamin_g[loc];
					ushort dtmax_g = datamax_g[loc];
					float circle_diff_g = (dtmin_g - dtmax_g) / key_g;//差分计算
					circle_diff_g = ((circle_diff_g > 0) * 2 - 1)*circle_diff_g;

					float key_r = key_red[loc];
					ushort dtmin_r = datamin_r[loc];
					ushort dtmax_r = datamax_r[loc];
					float circle_diff_r = (dtmin_r - dtmax_r) / key_r;
					circle_diff_r = ((circle_diff_r > 0) * 2 - 1)*circle_diff_r;//差分计算

					if (key_b > key_min)//未遮挡是否超过四分之一
					{

						if (circle_diff_b >= max_circle_diff)//判断是否超过阈值
						{
							*pcircle_x = x; pcircle_x++;
							*pcircle_y = y; pcircle_y++;
							*pcircle_radius = r;pcircle_radius++;
							*pcircle_diff = circle_diff_b + circle_diff_g + circle_diff_r;pcircle_diff++;
							num++;
							x += 4;
							continue;
						}

					}


					if (key_g > key_min)//未遮挡是否超过四分之一
					{
						if (circle_diff_g >= max_circle_diff)//判断是否超过阈值
						{
							*pcircle_x = x; pcircle_x++;
							*pcircle_y = y; pcircle_y++;
							*pcircle_radius = r;pcircle_radius++;
							*pcircle_diff = circle_diff_b + circle_diff_g + circle_diff_r;pcircle_diff++;
							num++;
							x += 4;
							continue;
						}
					}



					if (key_r > key_min)//未遮挡是否超过四分之一
					{
						if (circle_diff_r >= max_circle_diff)//判断是否超过阈值
						{
							*pcircle_x = x; pcircle_x++;
							*pcircle_y = y; pcircle_y++;
							*pcircle_radius = r;pcircle_radius++;
							*pcircle_diff = circle_diff_b + circle_diff_g + circle_diff_r;pcircle_diff++;
							num++;
							x += 4;
							continue;
						}
					}
				}
		}
		for (int r = min_radius + 30;r >= min_radius; r--)
		{			
			key_blueImg.setTo(0);
			avemin_b.setTo(0);
			avemax_b.setTo(0);

			key_greenImg.setTo(0);
			avemin_g.setTo(0);
			avemax_g.setTo(0);

			key_redImg.setTo(0);
			avemin_r.setTo(0);
			avemax_r.setTo(0);


			for (int theta = 0; theta < 360; theta += 3)
			{
				float cos_theta = cos(theta);
				float sin_theta = sin(theta);
				int p_xmid = r * cos_theta;
				int p_ymid = r * sin_theta;
				int ex_rcos = 5 * cos_theta;
				int ex_rsin = 5 * sin_theta;

				for (int picture_y = 0;picture_y < height;picture_y++)
				{
					for (int picture_x = 0;picture_x < width;picture_x++)
					{
						//圆位置计算
						int point_xmid = picture_x + p_xmid;
						int point_ymid = picture_y + p_ymid;

						//内圆位置计算
						int point_xmin = point_xmid - ex_rcos;;
						int point_ymin = point_ymid - ex_rsin;

						//外圆位置计算
						int point_xmax = point_xmid + ex_rcos;
						int point_ymax = point_ymid + ex_rsin;
						int point_max = point_xmax + point_ymax *width;
						//计算内外圆平均灰度
						if (point_max >= 0 && point_max < area) //判断外圆点在图内
						{
							int point = picture_x + picture_y * width;
							int point_mid = point_xmid + point_ymid* width;
							int point_min = point_xmin + point_ymin * width;

							if (canny_blue[point_mid]>170)
							{
								key_blue[point]++;
								datamin_b[point] += data_blue[point_min];
								datamax_b[point] += data_blue[point_max];
							}

							if (canny_green[point_mid]>170)
							{
								key_green[point]++;
								datamin_g[point] += data_green[point_min];
								datamax_g[point] += data_green[point_max];
							}

							if (canny_red[point_mid]>170)
							{
								key_red[point]++;
								datamin_r[point] += data_red[point_min];
								datamax_r[point] += data_red[point_max];
							}

						}
					}
				}
			}
			//对所有半径为r的圆查分进行筛选


			for (int y = 0;y < height;y++)
				for (int x = 0;x < width;x++)
				{
					int loc = x + y * width;
					float key_b = key_blue[loc];
					ushort dtmin_b = datamin_b[loc];
					ushort dtmax_b = datamax_b[loc];
					int flag_b = 0, flag_g = 0, flag_r = 0;
					float circle_diff_b = (dtmin_b - dtmax_b) / key_b;//差分计算
					circle_diff_b = ((circle_diff_b > 0) * 2 - 1)*circle_diff_b;

					float key_g = key_green[loc];
					ushort dtmin_g = datamin_g[loc];
					ushort dtmax_g = datamax_g[loc];
					float circle_diff_g = (dtmin_g - dtmax_g) / key_g;//差分计算
					circle_diff_g = ((circle_diff_g > 0) * 2 - 1)*circle_diff_g;

					float key_r = key_red[loc];
					ushort dtmin_r = datamin_r[loc];
					ushort dtmax_r = datamax_r[loc];
					float circle_diff_r = (dtmin_r - dtmax_r) / key_r;
					circle_diff_r = ((circle_diff_r > 0) * 2 - 1)*circle_diff_r;//差分计算

					if (key_b > key_min1)//未遮挡是否超过四分之一
					{

						if (circle_diff_b >= max_circle_diff)//判断是否超过阈值
						{
							*pcircle_x = x; pcircle_x++;
							*pcircle_y = y; pcircle_y++;
							*pcircle_radius = r;pcircle_radius++;
							*pcircle_diff = circle_diff_b + circle_diff_g + circle_diff_r;pcircle_diff++;
							num++;
							x += 4;
							continue;
						}

					}


					if (key_g > key_min1)//未遮挡是否超过四分之一
					{
						if (circle_diff_g >= max_circle_diff)//判断是否超过阈值
						{
							*pcircle_x = x; pcircle_x++;
							*pcircle_y = y; pcircle_y++;
							*pcircle_radius = r;pcircle_radius++;
							*pcircle_diff = circle_diff_b + circle_diff_g + circle_diff_r;pcircle_diff++;
							num++;
							x += 4;
							continue;
						}
					}



					if (key_r > key_min1)//未遮挡是否超过四分之一
					{
						if (circle_diff_r >= max_circle_diff)//判断是否超过阈值
						{
							*pcircle_x = x; pcircle_x++;
							*pcircle_y = y; pcircle_y++;
							*pcircle_radius = r;pcircle_radius++;
							*pcircle_diff = circle_diff_b + circle_diff_g + circle_diff_r;pcircle_diff++;
							num++;
							x += 4;
							continue;
						}
					}
				}
		}
	}


	
	//融合
	//判断是否重合
	for (int i = 0; i < num;i++)
	{
		int x = circle_x[i];
		int y = circle_y[i];
		int r = circle_radius[i];
		for (int j = i + 1;j<num;j++)
		{
			int x_x = x - circle_x[j];
			int y_y = y - circle_y[j];
			int c_dist = x_x * x_x + y_y * y_y;
			int r_dist = circle_radius[j] - r;
			r_dist = ((r_dist > 0) * 2 - 1)*r_dist;
			if (c_dist < min_center_dist * min_center_dist && r_dist < min_radius_dist)
			{
				//circle_x[j] = 0;
				//circle_y[j] = 0;
				circle_radius[j] = 0;
				//circle_diff[i] = circle_diff[j]>circle_diff[i]? circle_diff[j]: circle_diff[i];
				circle_diff[j] = 0;
			}
		}
	}
	
	int c_x[10000] = { 0 };
	int c_y[10000] = { 0 };
	int c_radius[10000] = { 0 };
	int c_diff[10000] = { 0 };
	int num_c = 0;

	for (int i = 0;i < num;i++)
	{
		if (circle_radius[i])
		{
			c_x[num_c] = circle_x[i];
			c_y[num_c] = circle_y[i];
			c_radius[num_c] = circle_radius[i];
			c_diff[num_c] = circle_diff[i];
			num_c++;
		}
	}

	//输出
	//个数未超出的情况
	if (num_c <= max_circle)
	{
		*circle_cnt = num_c;
	}
	//个数超出max排序
	else if (num_c > max_circle)
	{
		*circle_cnt = max_circle;
		for (int i = 0;i < num_c;i++)
		{
			for (int j = 0;j < num_c - i;j++)
			{
				if (c_diff[j] < c_diff[j + 1])
				{
					int temp_diff = c_diff[j];
					c_diff[j] = c_diff[j + 1];
					c_diff[j + 1] = temp_diff;
					int temp_x = c_x[j];
					c_x[j] = c_x[j + 1];
					c_x[j + 1] = temp_x;
					int temp_y = c_y[j];
					c_y[j] = c_y[j + 1];
					c_y[j + 1] = temp_y;
					int temp_radius = c_radius[j];
					c_radius[j] = c_radius[j + 1];
					c_radius[j + 1] = temp_radius;
				}
			}
		}
	}
	for (int i = 0;i < *circle_cnt;i++)
	{
		x[i] = c_x[i];
		y[i] = c_y[i];
		radius[i] = c_radius[i];i++;
		x[i] = c_x[i];
		y[i] = c_y[i];
		radius[i] = c_radius[i];
	}



#ifdef IMG_SHOW
	Mat roundImg(height, width, CV_8UC1);
	roundImg.setTo(0);
	for (int i = 0;i < *circle_cnt;i++)
	{
		for (int theta = 0; theta < 360; theta++)
		{
			int r = radius[i];
			int p_x = r * cos_theta[theta];
			int p_y = r * sin_theta[theta];
			int point_x = x[i] + p_x;
			int point_y = y[i] + p_y;
			int point = point_x + point_y*width;
			if (point_x >= 0 && point_x < width  && point_y >= 0 && point_y < height && r)
				roundImg.data[point] = 255;
		}
	}
	namedWindow("roundImg", 0);
	imshow("roundImg", roundImg);
	waitKey(0);
#endif

	return MY_OK;
}
