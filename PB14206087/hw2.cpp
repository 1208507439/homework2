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
	if (nullptr == colorImg.data)
	{
		std::cout << "colorImg is null!\n";
		return -1;
	}
	if (nullptr == x || nullptr == y || nullptr == radius || nullptr == circle_cnt)
	{
		std::cout << "some int pointers is null!\n";
		return -1;
	}
	if (colorImg.channels() != 3)
	{
		std::cout << "colorImg is not a color img!\n";
		return -1;
	}
	if (min_radius > max_radius)
	{
		std::cout << "min_radius > max_radius!\n";
		return -1;
	}
	if (min_radius < 6 || min_center_dist < 0 || min_radius_dist < 0 || max_circle_diff < 0 || max_circle < 0)
	{
		std::cout << "some int are wrong!\n";
		return -1;
	}

	if ((colorImg.rows < 2 * min_radius + 1) || (colorImg.cols < 2 * min_radius + 1))
	{
		*circle_cnt = 0;
		return 1;
	}

    float COS[90] = { 0 };
	float SIN[90] = { 0 };
	int R_COS[320][90] = { 0 };
	int R_SIN[320][90] = { 0 };
	int row = colorImg.rows;
	int col = colorImg.cols;
	int i, j;
	int k;
    int r, theta;
    Mat grayImg_B(row, col, CV_8UC1);
	Mat grayImg_G(row, col, CV_8UC1);
	Mat grayImg_R(row, col, CV_8UC1);
	uchar *data_B = grayImg_B.data;
	uchar *data_G = grayImg_G.data;
    uchar *data_R = grayImg_R.data;
    int x_center[4000] = { 0 };
    int y_center[4000] = { 0 };
    int r_tmp[4000] = { 0 };                       
	int diff_gray[4000] = { 0 };
	int circle_num = 1;
    int circle_num_tmp = 0;
    int gray_sum_B[320] = { 0 };
	int gray_sum_G[320] = { 0 };
	int gray_sum_R[320] = { 0 };
	int point_num[320] = { 0 };
	int x_L, x_R;
	int y_U, y_D;
	int r_bound_low = min_radius - 5;
	int r_bound_up = max_radius + 5;
	int diff_B, diff_G, diff_R, diff_MAX;
	int temp_index_U, temp_index_D;
    int sub_x, sub_y, sub_r;
    int cent_dist;
	int x_dist, y_dist;

	
	for (i = 89;i >= 0;i--)
	{
		COS[i] = cos(i*0.0174533f);//i*2pi/360
		SIN[i] = sin(i*0.0174533f);
	}
	for (r = 319; r >= 0; r--)
	{
		for (theta = 89; theta >= 0; theta--)
		{
			R_COS[r][theta] = r * COS[theta];
			R_SIN[r][theta] = r * SIN[theta];
		}
	}
	
	for (i = row*col - 1;i >= 0;i--)
	{
		j = 3 * i;
		*(data_B + i) = *(colorImg.data + j);
		*(data_G + i) = *(colorImg.data + j + 1);
		*(data_R + i) = *(colorImg.data + j + 2);
	}

	memset(x_center, -1, 16000);
	memset(y_center, -1, 16000);

	for (i = min_radius;i < row - min_radius;i++)
	{
		for (j = min_radius;j < col - min_radius;j++)
		{
			for (k = 319; k >= 0; k--)
			{
				gray_sum_B[k] = 0;
				gray_sum_G[k] = 0;
				gray_sum_R[k] = 0;
				point_num[k] = 0;
			}
			for (r = r_bound_low;r <= r_bound_up;r++)
			{
				for (theta = 89; theta > 0; theta--)
				{
					x_R = j + R_COS[r][theta];
					x_L = j - R_COS[r][theta];
					y_U = i - R_SIN[r][theta];
					y_D = i + R_SIN[r][theta];
					temp_index_U = y_U * col;
					temp_index_D = y_D * col;
					if (x_L >= 0)
					{
						if (y_U >= 0)
						{
							gray_sum_B[r] += *(data_B + temp_index_U + x_L);
							gray_sum_G[r] += *(data_G + temp_index_U + x_L);
							gray_sum_R[r] += *(data_R + temp_index_U + x_L);
							point_num[r]++;
						}
						if (y_D < row)
						{
							gray_sum_B[r] += *(data_B + temp_index_D + x_L);
							gray_sum_G[r] += *(data_G + temp_index_D + x_L);
							gray_sum_R[r] += *(data_R + temp_index_D + x_L);
							point_num[r]++;
						}
					}
					if (x_R < col)
					{
						if (y_U >= 0)
						{
							gray_sum_B[r] += *(data_B + temp_index_U + x_R);
							gray_sum_G[r] += *(data_G + temp_index_U + x_R);
							gray_sum_R[r] += *(data_R + temp_index_U + x_R);
							point_num[r]++;
						}
						if (y_D < row)
						{
							gray_sum_B[r] += *(data_B + temp_index_D + x_R);
							gray_sum_G[r] += *(data_G + temp_index_D + x_R);
							gray_sum_R[r] += *(data_R + temp_index_D + x_R);
							point_num[r]++;
						}
					}
				}
				if (point_num[r])
				{
					gray_sum_B[r] /= point_num[r];
					gray_sum_G[r] /= point_num[r];
					gray_sum_R[r] /= point_num[r];
				}
			}
			for (r = min_radius;r <= max_radius;r++)
			{
				if (point_num[r] == 356)
				{
					diff_MAX = abs(gray_sum_B[r - 5] - gray_sum_B[r + 5]);
					diff_G = abs(gray_sum_G[r - 5] - gray_sum_G[r + 5]);
					diff_R = abs(gray_sum_R[r - 5] - gray_sum_R[r + 5]);
					if (diff_G > diff_MAX)
						diff_MAX = diff_G;
					if (diff_R > diff_MAX)
						diff_MAX = diff_R;
				}
				else
				{
					diff_MAX = 0;
				}

				if (diff_MAX >= max_circle_diff)
				{
					sub_x = abs(j - x_center[circle_num - 1]);
					sub_y = abs(i - y_center[circle_num - 1]);
					sub_r = abs(r - r_tmp[circle_num - 1]);
					if (sub_x <= min_center_dist && sub_y <= min_center_dist && sub_r <= min_radius_dist)
					{
						if (diff_MAX > diff_gray[circle_num - 1])
						{
							x_center[circle_num - 1] = j;
							y_center[circle_num - 1] = i;
							r_tmp[circle_num - 1] = r;
						}
					}
					else
					{
						x_center[circle_num] = j;
						y_center[circle_num] = i;
						r_tmp[circle_num] = r;
						diff_gray[circle_num] = diff_MAX;
						circle_num++;
					}	
				}
			}
		}
	}


	circle_num_tmp = circle_num;
	
	for (i = circle_num_tmp - 1; i > 1; i--)
	{
		if (r_tmp[i])
		{
			for (j = i - 1; j >= 1; j--)
			{
				if (r_tmp[j])
				{
					sub_x = abs(x_center[i] - x_center[j]);
					sub_y = abs(y_center[i] - y_center[j]);
					sub_r = abs(r_tmp[i] - r_tmp[j]);
					x_dist = x_center[i] - x_center[j];
					y_dist = y_center[i] - y_center[j];
					cent_dist = sqrt(x_dist * x_dist + y_dist * y_dist);
					if (sub_x <= min_center_dist && sub_y <= min_center_dist && sub_r <= min_radius_dist)
					{
						if (diff_gray[i] > diff_gray[j])
						{
							x_center[j] = -1;
							y_center[j] = -1;
							r_tmp[j] = 0;
							diff_gray[j] = 0;
						}
						else
						{
							x_center[i] = -1;
							y_center[i] = -1;
							r_tmp[i] = 0;
							diff_gray[i] = 0;
							j = 0;
						}
						circle_num--;
					}
					else
					{
						if (cent_dist > abs(r_tmp[i] - r_tmp[j]) && cent_dist < r_tmp[i] + r_tmp[j])
						{
							if (diff_gray[i] > diff_gray[j])
							{
								x_center[j] = -1;
								y_center[j] = -1;
								r_tmp[j] = 0;
								diff_gray[j] = 0;
							}
							else
							{
								x_center[i] = -1;
								y_center[i] = -1;
								r_tmp[i] = 0;
								diff_gray[i] = 0;
								j = 0;
							}
							circle_num--;
						}
					}
				}
			}
		}
	}
	

	if (circle_num - 1 <= max_circle)
	{
		*circle_cnt = circle_num - 1;
		i = 0;
		for (j = circle_num_tmp - 1;j > 0;j--)
		{
			if (r_tmp[j])
			{
				x[i] = x_center[j];
				y[i] = y_center[j];
				radius[i] = r_tmp[j];
				i++;
			}
		}
	}
	else
	{
		*circle_cnt = max_circle;
		int x_center_flow[4000] = { 0 };
		int y_center_flow[4000] = { 0 };
		int r_tmp_flow[4000] = { 0 };
		int diff_gray_flow[4000] = { 0 };
		i = 0;
		for (j = circle_num_tmp - 1;j > 0;j--)
		{
			if (r_tmp[j])
			{
				x_center_flow[i] = x_center[j];
				y_center_flow[i] = y_center[j];
				r_tmp_flow[i] = r_tmp[j];
				diff_gray_flow[i] = diff_gray[j];
				i++;
			}
		}
		circle_num = i;
		for (j = max_circle; j < circle_num; j++)
		{
			for (i = 0; i < max_circle; i++)
			{
				if (diff_gray_flow[i] < diff_gray_flow[j])
				{
					x_center_flow[i] = x_center_flow[j];
					y_center_flow[i] = y_center_flow[j];
					r_tmp_flow[i] = r_tmp_flow[j];
					diff_gray_flow[i] = diff_gray_flow[j];
					i = max_circle;
				}
			}
		}
		for (i = 0; i < max_circle; i++)
		{
			x[i] = x_center_flow[i];
			y[i] = y_center_flow[i];
			radius[i] = r_tmp_flow[i];
		}
	}

	return 1;
}
