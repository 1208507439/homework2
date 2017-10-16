#include"FindCircle.h"
#define MY_OK 1
#define MY_FAIL -1

float sin_value[360] = {0.000000,0.017452,0.034899,0.052336,0.069756,0.087156,0.104528,0.121869,0.139173,0.156434,0.173648,0.190809,0.207912,0.224951,0.241922,0.258819,0.275637,0.292372,0.309017,0.325568,0.342020,0.358368,0.374607,0.390731,0.406737,0.422618,0.438371,0.453990,0.469472,0.484810,0.500000,0.515038,0.529919,0.544639,0.559193,0.573576,0.587785,0.601815,0.615661,0.629320,0.642788,0.656059,0.669131,0.681998,0.694658,0.707107,0.719340,0.731354,0.743145,0.754710,0.766044,0.777146,0.788011,0.798636,0.809017,0.819152,0.829038,0.838671,0.848048,0.857167,
0.866025,0.874620,0.882948,0.891007,0.898794,0.906308,0.913545,0.920505,0.927184,0.933580,0.939693,0.945519,0.951057,0.956305,0.961262,0.965926,0.970296,0.974370,0.978148,0.981627,0.984808,0.987688,0.990268,0.992546,0.994522,0.996195,0.997564,0.998630,0.999391,0.999848,1.000000,0.999848,0.999391,0.998630,0.997564,0.996195,0.994522,0.992546,0.990268,0.987688,0.984808,0.981627,0.978148,0.974370,0.970296,0.965926,0.961262,0.956305,0.951057,0.945519,0.939693,0.933580,0.927184,0.920505,0.913545,0.906308,0.898794,0.891007,0.882948,0.874620,
0.866025,0.857167,0.848048,0.838671,0.829038,0.819152,0.809017,0.798636,0.788011,0.777146,0.766044,0.754710,0.743145,0.731354,0.719340,0.707107,0.694658,0.681998,0.669131,0.656059,0.642788,0.629320,0.615661,0.601815,0.587785,0.573576,0.559193,0.544639,0.529919,0.515038,0.500000,0.484810,0.469472,0.453990,0.438371,0.422618,0.406737,0.390731,0.374607,0.358368,0.342020,0.325568,0.309017,0.292372,0.275637,0.258819,0.241922,0.224951,0.207912,0.190809,0.173648,0.156434,0.139173,0.121869,0.104528,0.087156,0.069756,0.052336,0.034899,0.017452,
0.000000,-0.017452,-0.034899,-0.052336,-0.069756,-0.087156,-0.104528,-0.121869,-0.139173,-0.156434,-0.173648,-0.190809,-0.207912,-0.224951,-0.241922,-0.258819,-0.275637,-0.292372,-0.309017,-0.325568,-0.342020,-0.358368,-0.374607,-0.390731,-0.406737,-0.422618,-0.438371,-0.453990,-0.469472,-0.484810,-0.500000,-0.515038,-0.529919,-0.544639,-0.559193,-0.573576,-0.587785,-0.601815,-0.615661,-0.629320,-0.642788,-0.656059,-0.669131,-0.681998,-0.694658,-0.707107,-0.719340,-0.731354,-0.743145,-0.754710,-0.766044,-0.777146,-0.788011,-0.798636,-0.809017,-0.819152,-0.829038,-0.838671,-0.848048,-0.857167,
-0.866025,-0.874620,-0.882948,-0.891007,-0.898794,-0.906308,-0.913545,-0.920505,-0.927184,-0.933580,-0.939693,-0.945519,-0.951057,-0.956305,-0.961262,-0.965926,-0.970296,-0.974370,-0.978148,-0.981627,-0.984808,-0.987688,-0.990268,-0.992546,-0.994522,-0.996195,-0.997564,-0.998630,-0.999391,-0.999848,-1.000000,-0.999848,-0.999391,-0.998630,-0.997564,-0.996195,-0.994522,-0.992546,-0.990268,-0.987688,-0.984808,-0.981627,-0.978148,-0.974370,-0.970296,-0.965926,-0.961262,-0.956305,-0.951057,-0.945519,-0.939693,-0.933580,-0.927184,-0.920505,-0.913545,-0.906308,-0.898794,-0.891007,-0.882948,-0.874620,
-0.866025,-0.857167,-0.848048,-0.838671,-0.829038,-0.819152,-0.809017,-0.798636,-0.788011,-0.777146,-0.766044,-0.754710,-0.743145,-0.731354,-0.719340,-0.707107,-0.694658,-0.681998,-0.669131,-0.656059,-0.642788,-0.629320,-0.615661,-0.601815,-0.587785,-0.573576,-0.559193,-0.544639,-0.529919,-0.515038,-0.500000,-0.484810,-0.469472,-0.453990,-0.438371,-0.422618,-0.406737,-0.390731,-0.374607,-0.358368,-0.342020,-0.325568,-0.309017,-0.292372,-0.275637,-0.258819,-0.241922,-0.224951,-0.207912,-0.190809,-0.173648,-0.156434,-0.139173,-0.121869,-0.104528,-0.087156,-0.069756,-0.052336,-0.034899,-0.017452};

float cos_value[360] = {1.000000,0.999848,0.999391,0.998630,0.997564,0.996195,0.994522,0.992546,0.990268,0.987688,0.984808,0.981627,0.978148,0.974370,0.970296,0.965926,0.961262,0.956305,0.951057,0.945519,0.939693,0.933580,0.927184,0.920505,0.913545,0.906308,0.898794,0.891007,0.882948,0.874620,0.866025,0.857167,0.848048,0.838671,0.829038,0.819152,0.809017,0.798636,0.788011,0.777146,0.766044,0.754710,0.743145,0.731354,0.719340,0.707107,0.694658,0.681998,0.669131,0.656059,0.642788,0.629320,0.615661,0.601815,0.587785,0.573576,0.559193,0.544639,0.529919,0.515038,
0.500000,0.484810,0.469472,0.453990,0.438371,0.422618,0.406737,0.390731,0.374607,0.358368,0.342020,0.325568,0.309017,0.292372,0.275637,0.258819,0.241922,0.224951,0.207912,0.190809,0.173648,0.156434,0.139173,0.121869,0.104528,0.087156,0.069756,0.052336,0.034899,0.017452,0.000000,-0.017452,-0.034899,-0.052336,-0.069756,-0.087156,-0.104528,-0.121869,-0.139173,-0.156434,-0.173648,-0.190809,-0.207912,-0.224951,-0.241922,-0.258819,-0.275637,-0.292372,-0.309017,-0.325568,-0.342020,-0.358368,-0.374607,-0.390731,-0.406737,-0.422618,-0.438371,-0.453990,-0.469472,-0.484810,
-0.500000,-0.515038,-0.529919,-0.544639,-0.559193,-0.573576,-0.587785,-0.601815,-0.615661,-0.629320,-0.642788,-0.656059,-0.669131,-0.681998,-0.694658,-0.707107,-0.719340,-0.731354,-0.743145,-0.754710,-0.766044,-0.777146,-0.788011,-0.798636,-0.809017,-0.819152,-0.829038,-0.838671,-0.848048,-0.857167,-0.866025,-0.874620,-0.882948,-0.891007,-0.898794,-0.906308,-0.913545,-0.920505,-0.927184,-0.933580,-0.939693,-0.945519,-0.951057,-0.956305,-0.961262,-0.965926,-0.970296,-0.974370,-0.978148,-0.981627,-0.984808,-0.987688,-0.990268,-0.992546,-0.994522,-0.996195,-0.997564,-0.998630,-0.999391,-0.999848,
-1.000000,-0.999848,-0.999391,-0.998630,-0.997564,-0.996195,-0.994522,-0.992546,-0.990268,-0.987688,-0.984808,-0.981627,-0.978148,-0.974370,-0.970296,-0.965926,-0.961262,-0.956305,-0.951057,-0.945519,-0.939693,-0.933580,-0.927184,-0.920505,-0.913545,-0.906308,-0.898794,-0.891007,-0.882948,-0.874620,-0.866025,-0.857167,-0.848048,-0.838671,-0.829038,-0.819152,-0.809017,-0.798636,-0.788011,-0.777146,-0.766044,-0.754710,-0.743145,-0.731354,-0.719340,-0.707107,-0.694658,-0.681998,-0.669131,-0.656059,-0.642788,-0.629320,-0.615661,-0.601815,-0.587785,-0.573576,-0.559193,-0.544639,-0.529919,-0.515038,
-0.500000,-0.484810,-0.469472,-0.453990,-0.438371,-0.422618,-0.406737,-0.390731,-0.374607,-0.358368,-0.342020,-0.325568,-0.309017,-0.292372,-0.275637,-0.258819,-0.241922,-0.224951,-0.207912,-0.190809,-0.173648,-0.156434,-0.139173,-0.121869,-0.104528,-0.087156,-0.069756,-0.052336,-0.034899,-0.017452,-0.000000,0.017452,0.034899,0.052336,0.069756,0.087156,0.104528,0.121869,0.139173,0.156434,0.173648,0.190809,0.207912,0.224951,0.241922,0.258819,0.275637,0.292372,0.309017,0.325568,0.342020,0.358368,0.374607,0.390731,0.406737,0.422618,0.438371,0.453990,0.469472,0.484810,
0.500000,0.515038,0.529919,0.544639,0.559193,0.573576,0.587785,0.601815,0.615661,0.629320,0.642788,0.656059,0.669131,0.681998,0.694658,0.707107,0.719340,0.731354,0.743145,0.754710,0.766044,0.777146,0.788011,0.798636,0.809017,0.819152,0.829038,0.838671,0.848048,0.857167,0.866025,0.874620,0.882948,0.891007,0.898794,0.906308,0.913545,0.920505,0.927184,0.933580,0.939693,0.945519,0.951057,0.956305,0.961262,0.965926,0.970296,0.974370,0.978148,0.981627,0.984808,0.987688,0.990268,0.992546,0.994522,0.996195,0.997564,0.998630,0.999391,0.999848};

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
	if (NULL == colorImg.data)
	{
		printf("ColorImage is NULL!\n");
		return MY_FAIL;
	}

	if (min_radius <= 5)
	{
		printf("min_radius is no larger than 5!\n");
		return MY_FAIL;
	}

	if (min_radius > max_radius)
	{
		printf("min_radius is larger than max_radius!\n");
		return MY_FAIL;
	}

	if ((NULL == x) | (NULL == y) | (NULL == radius) | (NULL == circle_cnt))
	{
		printf("x,y,radius or len is NULL!\n");
		return MY_FAIL;
	}

	if (max_circle < 0)
	{
		printf("max_circle is less than 0!\n");
		return MY_FAIL;
	}

	if (max_circle_diff < 80)
	{
		printf("max_circle_diff is too small,please input a larger one!\n");
		return MY_FAIL;
	}

	Mat dx(max_radius + 6, 360, CV_32SC1, Scalar(0));	//dx = 3*(int)(r*cos(theta)),rows = max_r + 6
	Mat dy(max_radius + 6, 360, CV_32SC1, Scalar(0));	//dy = (int)(r*sin(theta))
	int init_r = min_radius - 5;
	int final_r = max_radius + 5;
	int *pr_dx,*pr_dy;
	for (int r = init_r; r <= final_r; r++)
	{
		pr_dx = dx.ptr<int>(r);
		pr_dy = dy.ptr<int>(r);
		for (int theta = 0; theta < 360; theta++)
		{
			pr_dx[theta] = 3 * (int)(r * cos_value[theta]);
			pr_dy[theta] = (int)(r * sin_value[theta]);
		}
	}

	int local_center_x[3000] = { 0 };	//local array, to save center or radius
	int local_center_y[3000] = { 0 };
	int local_radius[3000] = { 0 };
	int max_bgr_diff[3000] = { 0 };	//save the max difference among 3 channels
	int local_len = 0;

	int* temp_x = local_center_x;
	int* temp_y = local_center_y;
	int* temp_radius = local_radius;
	int* temp_diff = max_bgr_diff;
	int temp_len = 0;	//save the number of circles
	
	uchar *data = colorImg.data;
	int num_rows = colorImg.rows;
	int num_cols = 3 * colorImg.cols;

	int max_row = num_rows - min_radius;
	int max_col = num_cols - 3 * min_radius;

	int *data_dx = (int*)dx.data;
	int *data_dy = (int*)dy.data;

	for (int i = min_radius; i < max_row; i++)
	{
		for (int j = min_radius; j < max_col; j += 3)
		{
			int circle_value[3][10] = { 0 };	//save 10 large circle(r+5) mean BGR value 
			int circle_value_index = 0;	//range(0,9)
			int init_radius = min_radius;	//initial radius，add min_radius_dist after finding a circle

			for (int current_r = init_radius; current_r <= max_radius; current_r++)
			{
				int b_mean[2] = { 0 };	//index 0--> b_mean of inner circle, index 1--> b_mean of outer circle
				int g_mean[2] = { 0 };
				int r_mean[2] = { 0 };
				int r_small,r_large;	//r = current_r-5 || current_r+5
				int row_index;
				int col_index;
				int data_index;

				//calc mean value of inner circle
				int valid_pixel_num_in = 0;
				int valid_pixel_num_out = 0;
				r_large = current_r + 5;

				if (current_r < init_radius + 10)
				{
					r_small = current_r - 5;
					for (int theta = 0; theta < 360; theta++)
					{
						//sum BGR value of pixels on inner circle
						row_index = i - data_dy[r_small * 360 + theta];
						col_index = j + data_dx[r_small * 360 + theta];

						if (row_index >= 0 && row_index < num_rows && col_index >= 0 && col_index < num_cols)
						{
							data_index = row_index * num_cols + col_index;
							b_mean[0] += data[data_index];
							g_mean[0] += data[data_index + 1];
							r_mean[0] += data[data_index + 2];
							valid_pixel_num_in++;
						}

						//sum BGR value of pixels on outer circle
						row_index = i - data_dy[r_large * 360 + theta];
						col_index = j + data_dx[r_large * 360 + theta];
						
						if (row_index >= 0 && row_index < num_rows && col_index >= 0 && col_index < num_cols)
						{
							data_index = row_index * num_cols + col_index;
							b_mean[1] += data[data_index];
							g_mean[1] += data[data_index + 1];
							r_mean[1] += data[data_index + 2];
							valid_pixel_num_out++;
						}
					}

					valid_pixel_num_in -= (valid_pixel_num_in - 1)*(((valid_pixel_num_in - 1) >> 31) & 1);	//prevent denominator being 0
					b_mean[0] = b_mean[0] / valid_pixel_num_in;
					g_mean[0] = g_mean[0] / valid_pixel_num_in;
					r_mean[0] = r_mean[0] / valid_pixel_num_in;

					valid_pixel_num_out -= (valid_pixel_num_out - 1)*(((valid_pixel_num_out - 1) >> 31) & 1);
					b_mean[1] = b_mean[1] / valid_pixel_num_out;
					g_mean[1] = g_mean[1] / valid_pixel_num_out;
					r_mean[1] = r_mean[1] / valid_pixel_num_out;

					//put mean value of outer circle into circle_value
					circle_value[0][circle_value_index] = b_mean[1];
					circle_value[1][circle_value_index] = g_mean[1];
					circle_value[2][circle_value_index] = r_mean[1];
					circle_value_index = (circle_value_index + 1) % 10;
				}
				//after moving 10 radius, there is no need to calc mmean value of inner circle
				else
				{
					//inner circle
					b_mean[0] = circle_value[0][circle_value_index];
					g_mean[0] = circle_value[1][circle_value_index];
					r_mean[0] = circle_value[2][circle_value_index];

					//outer circle
					for (int theta = 0; theta < 360; theta++)
					{
						row_index = i - data_dy[r_large * 360 + theta];
						col_index = j + data_dx[r_large * 360 + theta];
						
						if (row_index >= 0 && row_index < num_rows && col_index >= 0 && col_index < num_cols)
						{
							b_mean[1] += data[row_index * num_cols + col_index];
							g_mean[1] += data[row_index * num_cols + col_index + 1];
							r_mean[1] += data[row_index * num_cols + col_index + 2];
							valid_pixel_num_out++;
						}
						//unfold loop for 3 times
						theta++;
						row_index = i - data_dy[r_large * 360 + theta];
						col_index = j + data_dx[r_large * 360 + theta];

						if (row_index >= 0 && row_index < num_rows && col_index >= 0 && col_index < num_cols)
						{
							b_mean[1] += data[row_index * num_cols + col_index];
							g_mean[1] += data[row_index * num_cols + col_index + 1];
							r_mean[1] += data[row_index * num_cols + col_index + 2];
							valid_pixel_num_out++;
						}

						theta++;
						row_index = i - data_dy[r_large * 360 + theta];
						col_index = j + data_dx[r_large * 360 + theta];

						if (row_index >= 0 && row_index < num_rows && col_index >= 0 && col_index < num_cols)
						{
							b_mean[1] += data[row_index * num_cols + col_index];
							g_mean[1] += data[row_index * num_cols + col_index + 1];
							r_mean[1] += data[row_index * num_cols + col_index + 2];
							valid_pixel_num_out++;
						}

						theta++;
						row_index = i - data_dy[r_large * 360 + theta];
						col_index = j + data_dx[r_large * 360 + theta];

						if (row_index >= 0 && row_index < num_rows && col_index >= 0 && col_index < num_cols)
						{
							b_mean[1] += data[row_index * num_cols + col_index];
							g_mean[1] += data[row_index * num_cols + col_index + 1];
							r_mean[1] += data[row_index * num_cols + col_index + 2];
							valid_pixel_num_out++;
						}
					}
					valid_pixel_num_out -= (valid_pixel_num_out - 1)*(((valid_pixel_num_out - 1) >> 31) & 1);
					b_mean[1] = b_mean[1] / valid_pixel_num_out;
					g_mean[1] = g_mean[1] / valid_pixel_num_out;
					r_mean[1] = r_mean[1] / valid_pixel_num_out;

					//put mean value of outer circle into circle_value
					circle_value[0][circle_value_index] = b_mean[1];
					circle_value[1][circle_value_index] = g_mean[1];
					circle_value[2][circle_value_index] = r_mean[1];
					circle_value_index = (circle_value_index + 1) % 10;
				}

				//calc circle_diff
				int b_circle_diff = b_mean[0] - b_mean[1];
				b_circle_diff *= (1 - 2 * ((b_circle_diff >> 31) & 1));
				int g_circle_diff = g_mean[0] - g_mean[1];
				g_circle_diff *= (1 - 2 * ((g_circle_diff >> 31) & 1));
				int r_circle_diff = r_mean[0] - r_mean[1];
				r_circle_diff *= (1 - 2 * ((r_circle_diff >> 31) & 1));

				if ((b_circle_diff >= max_circle_diff) | (g_circle_diff >= max_circle_diff) | (r_circle_diff >= max_circle_diff))
				{
					
					*temp_x = j / 3;
					*temp_y = i;
					*temp_radius = current_r;
					temp_len++;
					//put the largest difference value among 3 channels into the array that is pointed by temp_diff
					*temp_diff = (((b_circle_diff - g_circle_diff) >> 31) & 1) * (g_circle_diff - b_circle_diff) + b_circle_diff;
					*temp_diff = (((r_circle_diff - *temp_diff) >> 31) & 1) * (*temp_diff - r_circle_diff) + r_circle_diff;
					
					
					int* px = local_center_x;
					int* py = local_center_y;
					int* pr = local_radius;
					int* pm = max_bgr_diff;
					while (px < temp_x)
					{
						if ((*temp_x - *px <= min_center_dist) && (*px - *temp_x <= min_center_dist) && (*temp_y - *py <= min_center_dist) && (*temp_radius - *pr <= min_radius_dist) && (*pr - *temp_radius <= min_radius_dist))
						{
							*px = (*px + *temp_x) >> 1;
							*py = (*py + *temp_y) >> 1;
							*pr = (*pr + *temp_radius) >> 1;
							*pm = (*pm + *temp_diff) >> 1;

							temp_x--;
							temp_y--;
							temp_radius--;
							temp_len--;
							temp_diff--;
							break;
						}
						px++;
						py++;
						pr++;
						pm++;
					}
					
					temp_x++;
					temp_y++;
					temp_radius++;
					temp_diff++;

					init_radius = current_r + min_radius_dist + 1;
					current_r = init_radius - 1;
				}
			}
		}
	}
	
	
	for (int i = 0; i < temp_len; i++)
	{
		local_center_x[local_len] = local_center_x[i];
		local_center_y[local_len] = local_center_y[i] - (min_center_dist >> 1);
		local_radius[local_len] = local_radius[i];
		max_bgr_diff[local_len] = max_bgr_diff[i];

		for (int j = 0; j < local_len; j++)
		{
			int x_diff = local_center_x[i] - local_center_x[j];
			x_diff = x_diff*(1 - 2 * ((x_diff >> 31) & 1));	//abs()
			int y_diff = local_center_y[i] - local_center_y[j];
			y_diff = y_diff*(1 - 2 * ((y_diff >> 31) & 1));
			int r_diff = local_radius[i] - local_radius[j];
			r_diff = r_diff*(1 - 2 * ((r_diff >> 31) & 1));

			if ((x_diff <= min_center_dist) && (y_diff <= min_center_dist) && (r_diff <= min_radius_dist))
			{
				local_len--;
				break;
			}
		}
		local_len++;
	}
	*circle_cnt = local_len;

	if (local_len <= max_circle)
	{
		int* px = x;
		int* py = y;
		int* pr = radius;
		for (int i = 0; i < local_len; i++)
		{
			*px = local_center_x[i];
			*py = local_center_y[i];
			*pr = local_radius[i];

			px++;
			py++;
			pr++;
		}
	}
	else
	{
		*circle_cnt = max_circle;
		int* px = x;
		int* py = y;
		int* pr = radius;
		for (int i = 0; i < max_circle; i++)	//sort
		{
			int max_diff_index = 0;
			for (int j = 1; j < local_len; j++)
			{
				if (max_bgr_diff[j] > max_bgr_diff[max_diff_index])
				{
					max_diff_index = j;
				}
			}
			//printf("%d   ", max_bgr_diff[max_diff_index]);
			*px = local_center_x[max_diff_index];
			*py = local_center_y[max_diff_index];
			*pr = local_radius[max_diff_index];
			px++;
			py++;
			pr++;

			max_bgr_diff[max_diff_index] = 0;
		}
	}

	return MY_OK;
}
