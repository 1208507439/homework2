#include<opencv2/opencv.hpp>
#include<cv.h>
using namespace cv;
using namespace std;
#include <iostream>
#include <math.h>
#include<stdio.h>
#include<time.h>
#define MY_OK 1
#define MY_FAIL 0
#define N  20000
int c_x[N] = { 0 };
int c_y[N] = { 0 };
float c_diff[N] = { 0 };
#define N0 3000
#define N1 9998
int ustc_Find_Circles_By_Difference(Mat colorImg, int min_radius, int max_radius, int min_center_dist, int min_radius_dist, int max_circle_diff, int *x, int *y, int *radius, int *cirlce_cnt, int max_circle)
{
	if (NULL == colorImg.data)
	{
		cout << "image is NULL." << endl;
		return MY_FAIL;
	}

	memset(x, 0, max_circle);
	memset(y, 0, max_circle);
	memset(radius, 0, max_circle);
	float cal_sin[360] = { 0.000000,0.017452,0.034899,0.052336,0.069756,0.087156,0.104528,0.121869,0.139173,0.156434,0.173648,0.190809,0.207912,0.224951,0.241922,0.258819,0.275637,0.292372,0.309017,0.325568,0.342020,0.358368,0.374607,0.390731,0.406737,0.422618,0.438371,0.453991,0.469472,0.484810,0.500000,0.515038,0.529919,0.544639,0.559193,0.573576,0.587785,0.601815,0.615661,0.629320,0.642788,0.656059,0.669131,0.681998,0.694658,0.707107,0.719340,0.731354,0.743145,0.754710,0.766044,0.777146,0.788011,0.798636,0.809017,0.819152,0.829038,0.838671,0.848048,0.857167,0.866025,0.874620,0.882948,0.891007,0.898794,0.906308,0.913545,0.920505,0.927184,0.933580,0.939693,0.945519,0.951057,0.956305,0.961262,0.965926,0.970296,0.974370,0.978148,0.981627,0.984808,0.987688,0.990268,0.992546,0.994522,0.996195,0.997564,0.998630,0.999391,0.999848,1.000000,0.999848,0.999391,0.998630,0.997564,0.996195,0.994522,0.992546,0.990268,0.987688,0.984808,0.981627,0.978148,0.974370,0.970296,0.965926,0.961262,0.956305,0.951057,0.945519,0.939693,0.933580,0.927184,0.920505,0.913545,0.906308,0.898794,0.891007,0.882948,0.874620,0.866025,0.857167,0.848048,0.838671,0.829037,0.819152,0.809017,0.798635,0.788011,0.777146,0.766044,0.754710,0.743145,0.731354,0.719340,0.707107,0.694658,0.681998,0.669131,0.656059,0.642788,0.629320,0.615661,0.601815,0.587785,0.573576,0.559193,0.544639,0.529919,0.515038,0.500000,0.484810,0.469472,0.453990,0.438371,0.422618,0.406737,0.390731,0.374607,0.358368,0.342020,0.325568,0.309017,0.292372,0.275637,0.258819,0.241922,0.224951,0.207912,0.190809,0.173648,0.156434,0.139173,0.121869,0.104528,0.087156,0.069756,0.052336,0.034900,0.017452,-0.000000,-0.017452,-0.034900,-0.052336,-0.069757,-0.087156,-0.104528,-0.121869,-0.139173,-0.156434,-0.173648,-0.190809,-0.207912,-0.224951,-0.241922,-0.258819,-0.275637,-0.292372,-0.309017,-0.325568,-0.342020,-0.358368,-0.374606,-0.390731,-0.406737,-0.422618,-0.438371,-0.453991,-0.469472,-0.484810,-0.500000,-0.515038,-0.529919,-0.544639,-0.559193,-0.573576,-0.587785,-0.601815,-0.615661,-0.629320,-0.642788,-0.656059,-0.669131,-0.681998,-0.694658,-0.707107,-0.719340,-0.731354,-0.743145,-0.754710,-0.766045,-0.777146,-0.788011,-0.798635,-0.809017,-0.819152,-0.829038,-0.838671,-0.848048,-0.857167,-0.866025,-0.874620,-0.882948,-0.891007,-0.898794,-0.906308,-0.913545,-0.920505,-0.927184,-0.933580,-0.939692,-0.945519,-0.951056,-0.956305,-0.961262,-0.965926,-0.970296,-0.974370,-0.978148,-0.981627,-0.984808,-0.987688,-0.990268,-0.992546,-0.994522,-0.996195,-0.997564,-0.998630,-0.999391,-0.999848,-1.000000,-0.999848,-0.999391,-0.998630,-0.997564,-0.996195,-0.994522,-0.992546,-0.990268,-0.987688,-0.984808,-0.981627,-0.978148,-0.974370,-0.970296,-0.965926,-0.961262,-0.956305,-0.951056,-0.945519,-0.939693,-0.933580,-0.927184,-0.920505,-0.913545,-0.906308,-0.898794,-0.891007,-0.882948,-0.874620,-0.866025,-0.857167,-0.848048,-0.838671,-0.829038,-0.819152,-0.809017,-0.798635,-0.788011,-0.777146,-0.766045,-0.754710,-0.743145,-0.731354,-0.719340,-0.707107,-0.694659,-0.681998,-0.669131,-0.656059,-0.642788,-0.629321,-0.615661,-0.601815,-0.587785,-0.573576,-0.559193,-0.544639,-0.529919,-0.515038,-0.500000,-0.484809,-0.469472,-0.453991,-0.438371,-0.422618,-0.406736,-0.390731,-0.374607,-0.358368,-0.342020,-0.325568,-0.309017,-0.292372,-0.275638,-0.258819,-0.241922,-0.224951,-0.207912,-0.190809,-0.173648,-0.156434,-0.139173,-0.121869,-0.104528,-0.087156,-0.069757,-0.052336,-0.034900 };
	float cal_cos[360] = { 1.000000,0.999848,0.999391,0.998630,0.997564,0.996195,0.994522,0.992546,0.990268,0.987688,0.984808,0.981627,0.978148,0.974370,0.970296,0.965926,0.961262,0.956305,0.951057,0.945519,0.939693,0.933580,0.927184,0.920505,0.913545,0.906308,0.898794,0.891007,0.882948,0.874620,0.866025,0.857167,0.848048,0.838671,0.829038,0.819152,0.809017,0.798635,0.788011,0.777146,0.766044,0.754710,0.743145,0.731354,0.719340,0.707107,0.694658,0.681998,0.669131,0.656059,0.642788,0.629320,0.615661,0.601815,0.587785,0.573576,0.559193,0.544639,0.529919,0.515038,0.500000,0.484810,0.469472,0.453991,0.438371,0.422618,0.406737,0.390731,0.374607,0.358368,0.342020,0.325568,0.309017,0.292372,0.275637,0.258819,0.241922,0.224951,0.207912,0.190809,0.173648,0.156434,0.139173,0.121869,0.104528,0.087156,0.069757,0.052336,0.034899,0.017453,-0.000000,-0.017452,-0.034900,-0.052336,-0.069756,-0.087156,-0.104529,-0.121869,-0.139173,-0.156434,-0.173648,-0.190809,-0.207912,-0.224951,-0.241922,-0.258819,-0.275637,-0.292372,-0.309017,-0.325568,-0.342020,-0.358368,-0.374607,-0.390731,-0.406737,-0.422618,-0.438371,-0.453990,-0.469472,-0.484810,-0.500000,-0.515038,-0.529919,-0.544639,-0.559193,-0.573576,-0.587785,-0.601815,-0.615661,-0.629320,-0.642788,-0.656059,-0.669131,-0.681998,-0.694658,-0.707107,-0.719340,-0.731354,-0.743145,-0.754710,-0.766044,-0.777146,-0.788011,-0.798635,-0.809017,-0.819152,-0.829038,-0.838671,-0.848048,-0.857167,-0.866025,-0.874620,-0.882948,-0.891007,-0.898794,-0.906308,-0.913545,-0.920505,-0.927184,-0.933580,-0.939693,-0.945519,-0.951057,-0.956305,-0.961262,-0.965926,-0.970296,-0.974370,-0.978148,-0.981627,-0.984808,-0.987688,-0.990268,-0.992546,-0.994522,-0.996195,-0.997564,-0.998630,-0.999391,-0.999848,-1.000000,-0.999848,-0.999391,-0.998630,-0.997564,-0.996195,-0.994522,-0.992546,-0.990268,-0.987688,-0.984808,-0.981627,-0.978148,-0.974370,-0.970296,-0.965926,-0.961262,-0.956305,-0.951057,-0.945519,-0.939693,-0.933580,-0.927184,-0.920505,-0.913546,-0.906308,-0.898794,-0.891007,-0.882948,-0.874620,-0.866025,-0.857167,-0.848048,-0.838671,-0.829038,-0.819152,-0.809017,-0.798636,-0.788011,-0.777146,-0.766044,-0.754710,-0.743145,-0.731354,-0.719340,-0.707107,-0.694658,-0.681998,-0.669131,-0.656059,-0.642787,-0.629320,-0.615662,-0.601815,-0.587785,-0.573576,-0.559193,-0.544639,-0.529919,-0.515038,-0.500000,-0.484810,-0.469472,-0.453990,-0.438371,-0.422618,-0.406737,-0.390731,-0.374606,-0.358368,-0.342021,-0.325568,-0.309017,-0.292371,-0.275637,-0.258819,-0.241922,-0.224951,-0.207912,-0.190809,-0.173648,-0.156435,-0.139173,-0.121870,-0.104528,-0.087156,-0.069757,-0.052336,-0.034900,-0.017452,0.000000,0.017452,0.034900,0.052336,0.069757,0.087156,0.104528,0.121870,0.139173,0.156435,0.173648,0.190809,0.207912,0.224951,0.241922,0.258819,0.275637,0.292371,0.309017,0.325568,0.342020,0.358368,0.374606,0.390731,0.406737,0.422618,0.438371,0.453990,0.469472,0.484810,0.500000,0.515038,0.529919,0.544639,0.559193,0.573576,0.587785,0.601815,0.615662,0.629320,0.642788,0.656059,0.669131,0.681998,0.694658,0.707107,0.719340,0.731354,0.743145,0.754710,0.766044,0.777146,0.788011,0.798636,0.809017,0.819152,0.829037,0.838671,0.848048,0.857167,0.866026,0.874620,0.882947,0.891007,0.898794,0.906308,0.913546,0.920505,0.927184,0.933580,0.939693,0.945519,0.951057,0.956305,0.961262,0.965926,0.970296,0.974370,0.978148,0.981627,0.984808,0.987688,0.990268,0.992546,0.994522,0.996195,0.997564,0.998630,0.999391 };
	
	int *c_px = c_x;
	
	int *c_py = c_y;
	int c_r[N] = { 0 };
	int *c_pr = c_r;
	
	float *c_pdiff = c_diff;
	int width = colorImg.cols;
	int height = colorImg.rows;
	int dis_x_y = min_center_dist*min_center_dist;
	int dis_r_r = min_radius_dist;
	float radius_aver[N0] = { 0 };
	int width_1 = width - 1;
	int height_1 = height - 1;
	int range0 = max_radius + 5;
	int range1 = min_radius - 5;
	int range = 2 * range0;
	int panduan_height_minradius1 = height - min_radius;
	int panduan_width_minradius2 = width - min_radius;
	int range_1 = min_radius + 5;
	int range_2 = max_radius - 5;
	int range_n_1 = height - range0;
	int range_n_2 = width - range0;

	if (width <= range || height <= range)
	{
		for (int cir_y = min_radius; cir_y < panduan_height_minradius1; cir_y++)
		{
			if ((c_px - c_x) ==N1)

			{
				break;
				printf("the diff should be larger");
			}
			for (int cir_x = min_radius; cir_x < panduan_width_minradius2; cir_x++)
			{
				if ((c_px - c_x)==N1)

				{
					break;
					printf("the diff should be larger");
				}
				for (int cir_r = range1; cir_r < range0; cir_r++)
				{
					if ((c_px - c_x) ==N1)

					{
						break;
						printf("the diff should be larger");
					}
					int count = 0;

					float blue_aver = 0, green_aver = 0, red_aver = 0;

					for (int theta = 0; theta < 360; theta++)
					{

						int cir_x1 = cir_x + cir_r*cal_cos[theta];
						int cir_y1 = cir_y + cir_r*cal_sin[theta];
						int loc_in = 3 * (cir_x1 + cir_y1*width);

						if (cir_x1<0 || cir_x1>width_1 || cir_y1<0 || cir_y1>height_1)
						{
							continue;
						}
						else
						{
							count++;
							blue_aver += colorImg.data[loc_in + 0];
							green_aver += colorImg.data[loc_in + 1];
							red_aver += colorImg.data[loc_in + 2];

						}

					}
					if (count < 180)
						continue;

					else
					{
						float max = blue_aver;
						if (green_aver > max)
						{
							max = green_aver;
						}
						if (red_aver > max)
						{
							max = green_aver;
						}

						*(radius_aver + cir_r) = max / float(count);
					}
				}
				for (int flag_radius = min_radius; flag_radius <max_radius; flag_radius++)
				{
					if (flag_radius > cir_x || flag_radius > cir_y)
						break;
					float diff_at_r = fabs(*(radius_aver + flag_radius - 5) - *(radius_aver + flag_radius + 5));
					if (diff_at_r > max_circle_diff)
					{
						if (c_px == c_x)
						{
							*c_px = cir_x;
							c_px++;
							*c_py = cir_y;
							c_py++;
							*c_pr = flag_radius;
							c_pr++;
							*c_pdiff = diff_at_r;
							c_pdiff++;
						}
						if (c_px > c_x)
						{
							int c_x_0 = *(c_px - 1);
							int c_y_0 = *(c_py - 1);
							int c_r_0 = *(c_pr - 1);

							float c_diff_0 = *(c_pdiff - 1);
							int dis_x = c_x_0 - cir_x;
							int dis_y = c_y_0 - cir_y;
							int dis_r = abs(c_r_0 - flag_radius);
							if ((dis_x*dis_x + dis_y*dis_y) > dis_x_y || dis_r > dis_r_r)
							{
								*c_px = cir_x;
								c_px++;
								*c_py = cir_y;
								c_py++;
								*c_pr = flag_radius;
								c_pr++;
								*c_pdiff = diff_at_r;
								c_pdiff++;

							}

							else

							{
								if (diff_at_r > *(c_pdiff - 1))
								{
									*(c_px - 1) = cir_x;

									*(c_py - 1) = cir_y;

									*(c_pr - 1) = flag_radius;


									*(c_pdiff - 1) = diff_at_r;

								}





							}

						}

					}
				}
			}
		}

	}
	else
	{
		for (int cir_y = min_radius; cir_y < range0; cir_y++)
		{
			if ((c_px - c_x) ==N1)

			{
				break;
				printf("the diff should be larger");
			}
			for (int cir_x = min_radius; cir_x < panduan_width_minradius2; cir_x++)
			{
				if ((c_px - c_x) ==N1)

				{
					break;
					printf("the diff should be larger");
				}
				for (int cir_r = range1; cir_r < range0; cir_r++)
				{
					if ((c_px - c_x) ==N1)

					{
						break;
						printf("the diff should be larger");
					}
					int count = 0;

					float blue_aver = 0, green_aver = 0, red_aver = 0;

					for (int theta = 0; theta < 360; theta++)
					{

						int cir_x1 = cir_x + cir_r*cal_cos[theta];
						int cir_y1 = cir_y + cir_r*cal_sin[theta];
						int loc_in = 3 * (cir_x1 + cir_y1*width);

						if (cir_x1<0 || cir_x1>width_1 || cir_y1<0 || cir_y1>height_1)
						{
							continue;
						}
						else
						{
							count++;
							blue_aver += colorImg.data[loc_in + 0];
							green_aver += colorImg.data[loc_in + 1];
							red_aver += colorImg.data[loc_in + 2];

						}

					}
					if (count < 180)
						continue;

					else
					{
						float max = blue_aver;
						if (green_aver > max)
						{
							max = green_aver;
						}
						if (red_aver > max)
						{
							max = green_aver;
						}

						*(radius_aver + cir_r) = max / float(count);
					}
				}
				for (int flag_radius =min_radius; flag_radius < max_radius; flag_radius++)
				{
					if (flag_radius > cir_x || flag_radius > cir_y)
						break;
					float diff_at_r = fabs(*(radius_aver + flag_radius - 5) - *(radius_aver + flag_radius + 5));
					if (diff_at_r > max_circle_diff)
					{
						if (c_px == c_x)
						{
							*c_px = cir_x;
							c_px++;
							*c_py = cir_y;
							c_py++;
							*c_pr = flag_radius;
							c_pr++;
							*c_pdiff = diff_at_r;
							c_pdiff++;
						}
						if (c_px > c_x)
						{
							int c_x_0 = *(c_px - 1);
							int c_y_0 = *(c_py - 1);
							int c_r_0 = *(c_pr - 1);

							float c_diff_0 = *(c_pdiff - 1);
							int dis_x = c_x_0 - cir_x;
							int dis_y = c_y_0 - cir_y;
							int dis_r = abs(c_r_0 - flag_radius);
							if ((dis_x*dis_x + dis_y*dis_y) > dis_x_y || dis_r > dis_r_r)
							{
								*c_px = cir_x;
								c_px++;
								*c_py = cir_y;
								c_py++;
								*c_pr = flag_radius;
								c_pr++;
								*c_pdiff = diff_at_r;
								c_pdiff++;

							}

							else

							{
								if (diff_at_r > *(c_pdiff - 1))
								{
									*(c_px - 1) = cir_x;

									*(c_py - 1) = cir_y;

									*(c_pr - 1) = flag_radius;


									*(c_pdiff - 1) = diff_at_r;

								}





							}

						}

					}
				}
			}
		}
		
		for (int cir_y = range0; cir_y < range_n_1; cir_y++)
		{
			if ((c_px - c_x) ==N1)

			{
				break;
				printf("the diff should be larger");
			}
			for (int cir_x = min_radius; cir_x < range0; cir_x++)
			{
				if ((c_px - c_x) == N1)

				{
					break;
					printf("the diff should be larger");
				}
				for (int cir_r = range1; cir_r < range0; cir_r++)
				{
					if ((c_px - c_x) == N1)

					{
						break;
						printf("the diff should be larger");
					}
					int count = 0;

					float blue_aver = 0, green_aver = 0, red_aver = 0;

					for (int theta = 0; theta < 360; theta++)
					{

						int cir_x1 = cir_x + cir_r*cal_cos[theta];
						int cir_y1 = cir_y + cir_r*cal_sin[theta];
						int loc_in = 3 * (cir_x1 + cir_y1*width);

						if (cir_x1<0 || cir_x1>width_1 || cir_y1<0 || cir_y1>height_1)
						{
							continue;
						}
						else
						{
							count++;
							blue_aver += colorImg.data[loc_in + 0];
							green_aver += colorImg.data[loc_in + 1];
							red_aver += colorImg.data[loc_in + 2];

						}

					}
					if (count < 180)
						continue;

					else
					{
						float max = blue_aver;
						if (green_aver > max)
						{
							max = green_aver;
						}
						if (red_aver > max)
						{
							max = green_aver;
						}

						*(radius_aver + cir_r) = max / float(count);
					}
				}
				for (int flag_radius = min_radius; flag_radius <max_radius; flag_radius++)
				{
					if (flag_radius > cir_x || flag_radius > cir_y)
						break;
					float diff_at_r = fabs(*(radius_aver + flag_radius - 5) - *(radius_aver + flag_radius + 5));
					if (diff_at_r > max_circle_diff)
					{
						if (c_px == c_x)
						{
							*c_px = cir_x;
							c_px++;
							*c_py = cir_y;
							c_py++;
							*c_pr = flag_radius;
							c_pr++;
							*c_pdiff = diff_at_r;
							c_pdiff++;
						}
						if (c_px > c_x)
						{
							int c_x_0 = *(c_px - 1);
							int c_y_0 = *(c_py - 1);
							int c_r_0 = *(c_pr - 1);

							float c_diff_0 = *(c_pdiff - 1);
							int dis_x = c_x_0 - cir_x;
							int dis_y = c_y_0 - cir_y;
							int dis_r = abs(c_r_0 - flag_radius);
							if ((dis_x*dis_x + dis_y*dis_y) > dis_x_y || dis_r > dis_r_r)
							{
								*c_px = cir_x;
								c_px++;
								*c_py = cir_y;
								c_py++;
								*c_pr = flag_radius;
								c_pr++;
								*c_pdiff = diff_at_r;
								c_pdiff++;

							}

							else

							{
								if (diff_at_r > *(c_pdiff - 1))
								{
									*(c_px - 1) = cir_x;

									*(c_py - 1) = cir_y;

									*(c_pr - 1) = flag_radius;


									*(c_pdiff - 1) = diff_at_r;

								}





							}

						}

					}
				}
			}
			for (int cir_x = range0; cir_x < range_n_2; cir_x++)
			{
				if ((c_px - c_x) == N1)

				{
					break;
					printf("the diff should be larger");
				}
				for (int cir_r = range1; cir_r < range0; cir_r++)
				{
					if ((c_px - c_x) == N1)

					{
						break;
						printf("the diff should be larger");
					}
					int count = 0;

					float blue_aver = 0, green_aver = 0, red_aver = 0;

					for (int theta = 0; theta < 360; theta++)
					{

						int cir_x1 = cir_x + cir_r*cal_cos[theta];
						int cir_y1 = cir_y + cir_r*cal_sin[theta];
						int loc_in = 3 * (cir_x1 + cir_y1*width);




						float max = blue_aver;
						if (green_aver > max)
						{
							max = green_aver;
						}
						if (red_aver > max)
						{
							max = green_aver;
						}

						*(radius_aver + cir_r) = max / 360.0;

					}
				}
				for (int flag_radius = min_radius; flag_radius <max_radius; flag_radius++)
				{
					if (flag_radius > cir_x || flag_radius > cir_y)
						break;
					float diff_at_r = fabs(*(radius_aver + flag_radius - 5) - *(radius_aver + flag_radius + 5));
					if (diff_at_r > max_circle_diff)
					{
						if (c_px == c_x)
						{
							*c_px = cir_x;
							c_px++;
							*c_py = cir_y;
							c_py++;
							*c_pr = flag_radius;
							c_pr++;
							*c_pdiff = diff_at_r;
							c_pdiff++;
						}
						if (c_px > c_x)
						{
							int c_x_0 = *(c_px - 1);
							int c_y_0 = *(c_py - 1);
							int c_r_0 = *(c_pr - 1);

							float c_diff_0 = *(c_pdiff - 1);
							int dis_x = c_x_0 - cir_x;
							int dis_y = c_y_0 - cir_y;
							int dis_r = abs(c_r_0 - flag_radius);
							if ((dis_x*dis_x + dis_y*dis_y) > dis_x_y || dis_r > dis_r_r)
							{
								*c_px = cir_x;
								c_px++;
								*c_py = cir_y;
								c_py++;
								*c_pr = flag_radius;
								c_pr++;
								*c_pdiff = diff_at_r;
								c_pdiff++;

							}

							else

							{
								if (diff_at_r > *(c_pdiff - 1))
								{
									*(c_px - 1) = cir_x;

									*(c_py - 1) = cir_y;

									*(c_pr - 1) = flag_radius;


									*(c_pdiff - 1) = diff_at_r;

								}





							}

						}

					}
				}
			}
			for (int cir_x = range_n_2; cir_x < panduan_width_minradius2; cir_x++)
			{
				if ((c_px - c_x) == N1)

				{
					break;
					printf("the diff should be larger");
				}
				for (int cir_r = range1; cir_r < range0; cir_r++)
				{
					if ((c_px - c_x) == N1)

					{
						break;
						printf("the diff should be larger");
					}
					int count = 0;

					float blue_aver = 0, green_aver = 0, red_aver = 0;

					for (int theta = 0; theta < 360; theta++)
					{

						int cir_x1 = cir_x + cir_r*cal_cos[theta];
						int cir_y1 = cir_y + cir_r*cal_sin[theta];
						int loc_in = 3 * (cir_x1 + cir_y1*width);

						if (cir_x1<0 || cir_x1>width_1 || cir_y1<0 || cir_y1>height_1)
						{
							continue;
						}
						else
						{
							count++;
							blue_aver += colorImg.data[loc_in + 0];
							green_aver += colorImg.data[loc_in + 1];
							red_aver += colorImg.data[loc_in + 2];

						}

					}
					if (count < 180)
						continue;

					else
					{
						float max = blue_aver;
						if (green_aver > max)
						{
							max = green_aver;
						}
						if (red_aver > max)
						{
							max = green_aver;
						}

						*(radius_aver + cir_r) = max / float(count);
					}
				}
				for (int flag_radius =min_radius; flag_radius < max_radius; flag_radius++)
				{
					if (flag_radius > cir_x || flag_radius > cir_y)
						break;
					float diff_at_r = fabs(*(radius_aver + flag_radius - 5) - *(radius_aver + flag_radius + 5));
					if (diff_at_r > max_circle_diff)
					{
						if (c_px == c_x)
						{
							*c_px = cir_x;
							c_px++;
							*c_py = cir_y;
							c_py++;
							*c_pr = flag_radius;
							c_pr++;
							*c_pdiff = diff_at_r;
							c_pdiff++;
						}
						if (c_px > c_x)
						{
							int c_x_0 = *(c_px - 1);
							int c_y_0 = *(c_py - 1);
							int c_r_0 = *(c_pr - 1);

							float c_diff_0 = *(c_pdiff - 1);
							int dis_x = c_x_0 - cir_x;
							int dis_y = c_y_0 - cir_y;
							int dis_r = abs(c_r_0 - flag_radius);
							if ((dis_x*dis_x + dis_y*dis_y) > dis_x_y || dis_r > dis_r_r)
							{
								*c_px = cir_x;
								c_px++;
								*c_py = cir_y;
								c_py++;
								*c_pr = flag_radius;
								c_pr++;
								*c_pdiff = diff_at_r;
								c_pdiff++;

							}

							else

							{
								if (diff_at_r > *(c_pdiff - 1))
								{
									*(c_px - 1) = cir_x;

									*(c_py - 1) = cir_y;

									*(c_pr - 1) = flag_radius;


									*(c_pdiff - 1) = diff_at_r;

								}





							}

						}

					}
				}
			}
			
		}
			for (int cir_y = range_n_1; cir_y <panduan_height_minradius1; cir_y++)
			{
				if ((c_px - c_x) ==N1)

				{
					break;
					printf("the diff should be larger");
				}
				for (int cir_x = min_radius; cir_x <panduan_width_minradius2; cir_x++)
				{
					if ((c_px - c_x) ==N1)

					{
						break;
						printf("the diff should be larger");
					}
					for (int cir_r = range1; cir_r < range0; cir_r++)
					{
						if ((c_px - c_x) ==N1)

						{
							break;
							printf("the diff should be larger");
						}
						int count = 0;

						float blue_aver = 0, green_aver = 0, red_aver = 0;

						for (int theta = 0; theta < 360; theta++)
						{

							int cir_x1 = cir_x + cir_r*cal_cos[theta];
							int cir_y1 = cir_y + cir_r*cal_sin[theta];
							int loc_in = 3 * (cir_x1 + cir_y1*width);

							if (cir_x1<0 || cir_x1>width_1 || cir_y1<0 || cir_y1>height_1)
							{
								continue;
							}
							else
							{
								count++;
								blue_aver += colorImg.data[loc_in + 0];
								green_aver += colorImg.data[loc_in + 1];
								red_aver += colorImg.data[loc_in + 2];

							}

						}
						if (count < 180)
							continue;

						else
						{
							float max = blue_aver;
							if (green_aver > max)
							{
								max = green_aver;
							}
							if (red_aver > max)
							{
								max = green_aver;
							}

							*(radius_aver + cir_r) = max / float(count);
						}
					}
					for (int flag_radius = range_1; flag_radius < range_2; flag_radius++)
					{
						if (flag_radius > cir_x || flag_radius > cir_y)
							break;
						float diff_at_r = fabs(*(radius_aver + flag_radius - 5) - *(radius_aver + flag_radius + 5));
						if (diff_at_r > max_circle_diff)
						{
							if (c_px == c_x)
							{
								*c_px = cir_x;
								c_px++;
								*c_py = cir_y;
								c_py++;
								*c_pr = flag_radius;
								c_pr++;
								*c_pdiff = diff_at_r;
								c_pdiff++;
							}
							if (c_px > c_x)
							{
								int c_x_0 = *(c_px - 1);
								int c_y_0 = *(c_py - 1);
								int c_r_0 = *(c_pr - 1);

								float c_diff_0 = *(c_pdiff - 1);
								int dis_x = c_x_0 - cir_x;
								int dis_y = c_y_0 - cir_y;
								int dis_r = abs(c_r_0 - flag_radius);
								if ((dis_x*dis_x + dis_y*dis_y) > dis_x_y || dis_r > dis_r_r)
								{
									*c_px = cir_x;
									c_px++;
									*c_py = cir_y;
									c_py++;
									*c_pr = flag_radius;
									c_pr++;
									*c_pdiff = diff_at_r;
									c_pdiff++;

								}

								else

								{
									if (diff_at_r > *(c_pdiff - 1))
									{
										*(c_px - 1) = cir_x;

										*(c_py - 1) = cir_y;

										*(c_pr - 1) = flag_radius;


										*(c_pdiff - 1) = diff_at_r;

									}





								}

							}

						}
					}
				}
			}

		
	}





		int circle_x[N] = { 0 };
		int *circle_px = circle_x;
		int circle_y[N] = { 0 };
		int *circle_py = circle_y;
		int circle_r[N] = { 0 };
		int *circle_pr = circle_r;

		int n = c_px - c_x;

		for (int i = 0; i < n; i++)
		{

			float c_diff_0 = *(c_diff + i);
			if (c_diff_0 < 1)
				continue;
			int flag[N] = { 0 };
			int *p_f = flag;
			int c_x_0 = *(c_x + i);
			int c_y_0 = *(c_y + i);
			int c_r_0 = *(c_r + i);

			int max_x = c_x_0, max_y = c_y_0, max_r = c_r_0;
			float max_diff = c_diff_0;
			int max_flag = i;
			for (int j = 0; j < n; j++)
			{
				int c_x_1 = *(c_x + j);
				int c_y_1 = *(c_y + j);
				int c_r_1 = *(c_r + j);
				int c_diff_1 = *(c_diff + j);
				int disx = c_x_1 - c_x_0;
				int disy = c_y_1 - c_y_0;
				int disr = abs(c_r_1 - c_r_0);
				if ((disx*disx + disy*disy)<dis_x_y && disr <dis_r_r)
				{
					*p_f = j;
					p_f++;
					if (c_diff_1 > max_diff)
					{

						max_diff = c_diff_1;
						max_flag = j;


					}

				}



			}



			int num = p_f - flag;
			for (int k = 0; k < num; k++)
			{
				int temp_diff = *(flag + k);
				*(c_diff + temp_diff) = 0;


			}
			*(c_diff + max_flag) = max_diff;



		}
		for (int i_j = 0; i_j < n; i_j++)
		{
			if (*(c_diff + i_j))
			{
				*circle_px = *(c_x + i_j);
				circle_px++;
				*circle_py = *(c_y + i_j);
				circle_py++;
				*circle_pr = *(c_r + i_j);
				circle_pr++;

			}
		}
		int num_of_circle = circle_px - circle_x;
		if (num_of_circle < 2)
		{
			printf("the diff may be too big,please adjust it ");
		}


		if (num_of_circle <= max_circle)
		{
			for (int i_k = 0; i_k < num_of_circle; i_k++)
			{
				*(x + i_k) = *(circle_x + i_k);
				*(y + i_k) = *(circle_y + i_k);
				*(radius + i_k) = *(circle_r + i_k);

			}
			*cirlce_cnt = num_of_circle;
		}
		if (num_of_circle > max_circle)
		{
			for (int i_k = 0; i_k < max_circle; i_k++)
			{
				*(x + i_k) = *(circle_x + i_k);
				*(y + i_k) = *(circle_y + i_k);
				*(radius + i_k) = *(circle_r + i_k);

			}
			*cirlce_cnt = max_circle;
		}
	}
