#define CIRCLE_RANGE 360
#define MIN_RADIUS 30
#define MAX_RADIUS 310
#define DIFF_RANGE 5 
#define COFF_TRANS 180
#define CIR_SUCCESS 1
#define CIR_FAIL -2
#define MY_OK 1
#define MY_FAIL -1
#define TH 200
#define CIR_DIFF_TH 5
#define Grad_TH 150
#define CIR_MIN(X,Y) ( Y ^ (( X ^ Y ) & - ( X < Y )))
#define CIR_MAX(X,Y) ( X ^ (( X ^ Y ) & - ( X < Y )))
#define ABS(X) (X + ((( X >> INT_LENGTH ) * X) << 1))

int SIN_DISTANCE[MAX_RADIUS + DIFF_RANGE + 1][CIRCLE_RANGE][2];
int COS_DISTANCE[MAX_RADIUS + DIFF_RANGE + 1][CIRCLE_RANGE][2];
bool first_flag = true;
static int INT_LENGTH = sizeof(int) * 8 - 1;

int ustc_Find_Circles_By_Difference(Mat colorImg, int min_radius, int max_radius, int min_center_dist, int max_circle_diff, int * x, int * y, int * radius, int * cir_cnt, int max_circle)
{
	// to prevent something unexpected
	if (NULL == colorImg.data || NULL == x || NULL == y || NULL == radius || NULL == cir_cnt || max_circle <= 0 || max_radius < min_radius)
	{
		return MY_FAIL;
	}

	if (first_flag)
	{
		first_flag = false;
		int Max_Radius_Range = MAX_RADIUS + DIFF_RANGE;
		int Min_Radius_Range = MIN_RADIUS - DIFF_RANGE;
		float Temp4Distance;
		int count = 0;
		int temp_theta;
		int temp_sin_val;
		int temp_cos_val;
		bool temp_flag = true;

		for (int temp_i = Min_Radius_Range - 2; temp_i < Max_Radius_Range + 3; ++temp_i)
		{
			if (false == temp_flag)
			{
				while (temp_theta < 360)
				{
					COS_DISTANCE[temp_i - 1][temp_theta++][1] = 360;
				}
				temp_flag = true;
			}

			for (int temp_j = 0; temp_j < CIRCLE_RANGE; ++temp_j)
			{
				Temp4Distance = temp_j * CV_PI / COFF_TRANS;
				SIN_DISTANCE[temp_i][temp_j][0] = temp_i * sin(Temp4Distance);
				COS_DISTANCE[temp_i][temp_j][0] = temp_i * cos(Temp4Distance);
				if (temp_flag)
				{
					temp_cos_val = COS_DISTANCE[temp_i][temp_j][0];
					temp_sin_val = SIN_DISTANCE[temp_i][temp_j][0];
					temp_theta = temp_j;
					temp_flag = false;
				}
				else
				{
					if (temp_cos_val != COS_DISTANCE[temp_i][temp_j][0] || temp_sin_val != SIN_DISTANCE[temp_i][temp_j][0])
					{
						while (temp_theta < temp_j)
						{
							COS_DISTANCE[temp_i][temp_theta++][1] = temp_j;
						}
						temp_cos_val = COS_DISTANCE[temp_i][temp_j][0];
						temp_sin_val = SIN_DISTANCE[temp_i][temp_j][0];
					}
				}

			}
		}
	}
	const int Cols = colorImg.cols;
	const int Rows = colorImg.rows;

	Mat redImg(Rows, Cols, CV_8UC1);
	Mat blueImg(Rows, Cols, CV_8UC1);
	Mat greenImg(Rows, Cols, CV_8UC1);

	Mat ValueImg_r(Rows, Cols, CV_32SC1);
	Mat ValueImg_g(Rows, Cols, CV_32SC1);
	Mat ValueImg_b(Rows, Cols, CV_32SC1);
	Mat NumImg(Rows, Cols, CV_32SC1);
	Mat Value_IN_r(Rows, Cols, CV_32SC1);
	Mat Value_IN_b(Rows, Cols, CV_32SC1);
	Mat Value_IN_g(Rows, Cols, CV_32SC1);
	Mat Value_OUT_r(Rows, Cols, CV_32SC1);
	Mat Value_OUT_b(Rows, Cols, CV_32SC1);
	Mat Value_OUT_g(Rows, Cols, CV_32SC1);

	ValueImg_r.setTo(0);
	ValueImg_g.setTo(0);
	ValueImg_b.setTo(0);
	NumImg.setTo(0);
	Value_IN_r.setTo(0);
	Value_IN_b.setTo(0);
	Value_IN_g.setTo(0);
	Value_OUT_r.setTo(0);
	Value_OUT_b.setTo(0);
	Value_OUT_g.setTo(0);

	int *Value_r = (int *)ValueImg_r.data;
	int *Value_g = (int *)ValueImg_g.data;
	int *Value_b = (int *)ValueImg_b.data;
	int *Value_in_r = (int *)Value_IN_r.data;
	int *Value_in_b = (int *)Value_IN_b.data;
	int *Value_in_g = (int *)Value_IN_g.data;
	int *Value_out_r = (int *)Value_OUT_r.data;
	int *Value_out_b = (int *)Value_OUT_b.data;
	int *Value_out_g = (int *)Value_OUT_g.data;
	int *pixel_count = (int *)NumImg.data;

	for (int i = 0; i < Rows; ++i)
	{
		int pos = i * Cols;
		for (int j = 0; j < Cols; ++j)
		{
			redImg.data[pos + j] = colorImg.data[3 * (pos + j)];
			blueImg.data[pos + j] = colorImg.data[3 * (pos + j) + 1];
			greenImg.data[pos + j] = colorImg.data[3 * (pos + j) + 2];
		}
	}

	int cir_count = 0;
	int cir_x[10000] = { 0 };
	int cir_y[10000] = { 0 };
	int cir_r[10000] = { 0 };
	int cir_result[10000] = { 0 };
	int pos_x;
	int pos_y = 0;
	int temp_radius;
	int theta_bound;
	int theta_start;
	int radius_bound = max_radius + DIFF_RANGE + 1;
	int temp_result_r = 0;
	int temp_result_g = 0;
	int temp_result_b = 0;
	int temp_result;
	int count = 0;
	int theta = 0;
	int diff_th = min_center_dist * min_center_dist * 3;
	unsigned char *pixel_b = redImg.data;
	unsigned char *pixel_g = greenImg.data;
	unsigned char *pixel_r = blueImg.data;
	int delt = 2 * DIFF_RANGE;
	int length = Cols * Rows;
	int clean_length = sizeof(int) * length;

	for (int inc = 0; inc < delt; ++inc)
	{
		memset(Value_in_r, 0, clean_length);
		memset(Value_in_b, 0, clean_length);
		memset(Value_in_g, 0, clean_length);
		memset(Value_out_r, 0, clean_length);
		memset(Value_out_b, 0, clean_length);
		memset(Value_out_g, 0, clean_length);
		memset(Value_r, 0, clean_length);
		memset(Value_b, 0, clean_length);
		memset(Value_g, 0, clean_length);
		memset(pixel_count, 0, clean_length);

		temp_radius = min_radius - DIFF_RANGE + inc;
		for (theta = 0; theta < CIRCLE_RANGE; )
		{
			int sin_d = SIN_DISTANCE[temp_radius][theta][0];
			int cos_d = COS_DISTANCE[temp_radius][theta][0];
			int row_bound = Rows - sin_d - 1;
			int col_bound = Cols - cos_d - 1;
			int row_start = 0;
			int col_start = 0;
			row_bound = CIR_MIN(Rows, row_bound);
			col_bound = CIR_MIN(Cols, col_bound);
			row_start = CIR_MAX(row_start, (-sin_d));
			col_start = CIR_MAX(col_start, (-cos_d));
			theta = COS_DISTANCE[temp_radius][theta][1];
			for (pos_x = row_start; pos_x < row_bound; ++pos_x)
			{
				int temp_pos_x = pos_x + sin_d;
				int temp_pos_y = col_start + cos_d;
				int mat_pos = temp_pos_x * Cols + temp_pos_y - 1;
				int pos = pos_x * Cols + col_start - 1;
				for (pos_y = col_start; pos_y < col_bound; ++pos_y)
				{
					++pos;
					++mat_pos;
					Value_r[pos] += pixel_r[mat_pos];
					Value_b[pos] += pixel_b[mat_pos];
					Value_g[pos] += pixel_g[mat_pos];
					++pixel_count[pos];
				}
			}
		}

		for (int i = 0; i < length; ++i)
		{
			Value_in_r[i] = Value_r[i] / (pixel_count[i] + 1);
			Value_in_b[i] = Value_b[i] / (pixel_count[i] + 1);
			Value_in_g[i] = Value_g[i] / (pixel_count[i] + 1);
		}

		for (temp_radius += delt; temp_radius < radius_bound; temp_radius += delt)
		{
			memset(Value_out_r, 0, clean_length);
			memset(Value_out_b, 0, clean_length);
			memset(Value_out_g, 0, clean_length);
			memset(Value_r, 0, clean_length);
			memset(Value_b, 0, clean_length);
			memset(Value_g, 0, clean_length);
			memset(pixel_count, 0, clean_length);
			for (theta = 0; theta < CIRCLE_RANGE; )
			{
				int sin_d = SIN_DISTANCE[temp_radius][theta][0];
				int cos_d = COS_DISTANCE[temp_radius][theta][0];
				int row_bound = Rows - sin_d - 1;
				int col_bound = Cols - cos_d - 1;
				int row_start = 0;
				int col_start = 0;
				row_bound = CIR_MIN(Rows, row_bound);
				col_bound = CIR_MIN(Cols, col_bound);
				row_start = CIR_MAX(row_start, (-sin_d));
				col_start = CIR_MAX(col_start, (-cos_d));
				theta = COS_DISTANCE[temp_radius][theta][1];
				for (pos_x = row_start; pos_x < row_bound; ++pos_x)
				{
					int temp_pos_x = pos_x + sin_d;
					int temp_pos_y = col_start + cos_d;
					int mat_pos = temp_pos_x * Cols + temp_pos_y - 1;
					int pos = pos_x * Cols + col_start - 1;
					for (pos_y = col_start; pos_y < col_bound; ++pos_y)
					{
						++pos;
						++mat_pos;
						Value_r[pos] += pixel_r[mat_pos];
						Value_b[pos] += pixel_b[mat_pos];
						Value_g[pos] += pixel_g[mat_pos];
						++pixel_count[pos];
					}
				}
			}

			for (int i = 0; i < length; ++i)
			{
				Value_out_r[i] = Value_r[i] / (pixel_count[i] + 1);
				Value_out_b[i] = Value_b[i] / (pixel_count[i] + 1);
				Value_out_g[i] = Value_g[i] / (pixel_count[i] + 1);
			}

			for (pos_x = 0; pos_x < Rows; ++pos_x)
			{
				int pos;
				pos = pos_x * Cols;
				for (pos_y = 0; pos_y < Cols; ++pos_y, ++pos)
				{
					temp_result_r = Value_in_r[pos] - Value_out_r[pos];
					temp_result_r = ABS(temp_result_r);
					temp_result_b = Value_in_b[pos] - Value_out_b[pos];
					temp_result_b = ABS(temp_result_b);
					temp_result_g = Value_in_g[pos] - Value_out_g[pos];
					temp_result_g = ABS(temp_result_g);
					temp_result = CIR_MAX(temp_result_b, temp_result_g);
					temp_result = CIR_MAX(temp_result, temp_result_r);
					if (temp_result > max_circle_diff)
					{
						int i = 0;
						while (i < cir_count)
						{
							if ((cir_x[i] - pos_y) * (cir_x[i] - pos_y)
								+ (cir_y[i] - pos_x) * (cir_y[i] - pos_x)
								+ (cir_r[i] - temp_radius + DIFF_RANGE) * (cir_r[i] - temp_radius + DIFF_RANGE) <= diff_th)
							{
								if (temp_result >= cir_result[i])
								{
									cir_x[i] = pos_y;
									cir_y[i] = pos_x;
									cir_r[i] = temp_radius - DIFF_RANGE;
									cir_result[i] = temp_result;

								}
								break;
							}
							++i;
						}
						if (i == cir_count)
						{
							cir_x[cir_count] = pos_y;
							cir_y[cir_count] = pos_x;
							cir_r[cir_count] = temp_radius - DIFF_RANGE;
							cir_result[cir_count] = temp_result;
							++cir_count;
						}
					}
				}

				int *temp = Value_in_r;
				Value_in_r = Value_out_r;
				Value_out_r = temp;

				temp = Value_in_b;
				Value_in_b = Value_out_b;
				Value_out_b = temp;

				temp = Value_in_g;
				Value_in_g = Value_out_g;
				Value_out_g = temp;
			}
		}

	}
	if (cir_count <= max_circle)
	{
		*cir_cnt = cir_count;
	}
	else
	{
		*cir_cnt = max_circle;
		for (int i = 0; i < max_circle; ++i)
		{
			int temp1 = cir_result[i];
			int pos1 = i;
			for (int j = i + 1; j < cir_count; ++j)
			{
				if (temp1 < cir_result[j])
				{
					temp1 = cir_result[j];
					pos1 = j;
				}
			}
			cir_result[pos1] = cir_result[i];
			cir_result[i] = temp1;
			temp1 = cir_x[pos1];
			cir_x[pos1] = cir_x[i];
			cir_x[i] = temp1;
			temp1 = cir_y[pos1];
			cir_y[pos1] = cir_y[i];
			cir_y[i] = temp1;
		}
		cir_count = *cir_cnt;
	}


	cout << cir_count << endl;
	for (int i = 0; i < cir_count; ++i)
	{
		x[i] = cir_x[i];
		y[i] = cir_y[i];
		radius[i] = cir_r[i];
		cout << x[i] << ' ' << y[i] << ' ' << radius[i] << ' ' << cir_result[i] << endl;
	}


	return MY_OK;
}
