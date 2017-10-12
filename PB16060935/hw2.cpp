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
	int array_size = 10000;
	
	int circle_x [10000];
	int circle_y [10000];
	int circle_radius [10000];
	float circle_cha [10000];
	float cha [10000];
	int exclude_flag [10000];


	for (int p = 0; p < array_size; p++)
	{
		circle_x[p] = 0;
		circle_y[p] = 0;
		circle_radius[p] = 0;
		cha[p] = 0;
		exclude_flag[p] = 1;
	}


	int width = colorImg.cols;
	int height = colorImg.rows;

	float triangle_value[2][360];
	for (int Alpha = 0; Alpha < 360; Alpha++)
	{
		float Beta = Alpha / 180.0 * CV_PI;
		triangle_value[0][Alpha] = cos(Beta);
		triangle_value[1][Alpha] = sin(Beta);
	}


	(*circle_cnt) = 0;
	int cir_cnt_for_origin = 0;
	int FULL_flag = 0;
	
	for (int i = 0; i < height&&!FULL_flag; i++)
	{
		for (int j = 0; j < width&&!FULL_flag; j++)
		{

			int tempt_x = j;
			int tempt_y = i;

			for ( int r = min_radius; r <= max_radius && !FULL_flag; r++)
			{

				int total_big_b = 0;
				int total_big_g = 0;
				int total_big_r = 0;

				int total_sml_b = 0;
				int total_sml_g = 0;
				int total_sml_r = 0;

				int big_r = r + 5;
				int sml_r = r - 5;

				int _cnt = 0;

				for (int theta = 0; theta < 360 && !FULL_flag; theta++)
				{
					float cos_value = triangle_value[0][theta];
					float sin_value = triangle_value[1][theta];

					int big_x = tempt_x + big_r*cos_value;
					int big_y = tempt_y + big_r*sin_value;
					int sml_x = tempt_x + sml_r*cos_value;
					int sml_y = tempt_y + sml_r*sin_value;

					if (0 <= big_x&&big_x < width && 0 <= big_y&&big_y < height)
					{
						int big_position = 3 * (big_y*width + big_x);
						int big_b = colorImg.data[big_position + 0];
						int big_g = colorImg.data[big_position + 1];
						int big_r = colorImg.data[big_position + 2];
						total_big_b += big_b;
						total_big_g += big_g;
						total_big_r += big_r;
						
						int sml_position = 3 * (sml_y*width + sml_x);
						int sml_b = colorImg.data[sml_position + 0];
						int sml_g = colorImg.data[sml_position + 1];
						int sml_r = colorImg.data[sml_position + 2];
						total_sml_b += sml_b;
						total_sml_g += sml_g;
						total_sml_r += sml_r;

						_cnt++;
					}
				}

				if (_cnt != 0)
				{
					float cha_b = abs((float)total_big_b / _cnt - (float)total_sml_b / _cnt);
					float cha_g = abs((float)total_big_g / _cnt - (float)total_sml_g / _cnt);
					float cha_r = abs((float)total_big_r / _cnt - (float)total_sml_r / _cnt);

					float chafen_max = 0;
					chafen_max = cha_b > cha_g ? cha_b : cha_g;
					chafen_max = chafen_max > cha_r ? chafen_max : cha_r;

					if (chafen_max>max_circle_diff)
					{
						circle_x[cir_cnt_for_origin] = tempt_x;
						circle_y[cir_cnt_for_origin] = tempt_y;
						circle_radius[cir_cnt_for_origin] = r;
						circle_cha[cir_cnt_for_origin] = chafen_max;
						cir_cnt_for_origin++;
					}
				}

				if (cir_cnt_for_origin == array_size)
				{
					printf("cir_cnt_for_origin=%d\n", cir_cnt_for_origin);
					FULL_flag = 1;
				}
			
			}
		}
	}

	if (1 == FULL_flag)
	{
		printf("Please try again with higher max_circle_diff\n");
		getchar();
		return 0;
	}


	for(int i = 0; i < cir_cnt_for_origin; i++)
	{
		for (int j = i + 1; j < cir_cnt_for_origin; j++)
		{
			float distance = sqrt(pow((circle_x[i] - circle_x[j]), 2) + pow((circle_y[i] - circle_y[j]), 2));
			int delta_r = abs(circle_radius[i] - circle_radius[j]);
			if (delta_r <= min_radius_dist&&distance <= min_center_dist)
			{
				if (circle_cha[i] >= circle_cha[j]) exclude_flag[j] = 0;
				else exclude_flag[i] = 0;
			}
		}
	}


	for (int i = 0; i < cir_cnt_for_origin; i++)
	{
		if (0 == exclude_flag[i]) continue;
		else
		{
			x[*circle_cnt] = circle_x[i];
			y[*circle_cnt] = circle_y[i];
			radius[*circle_cnt] = circle_radius[i];
			cha[*circle_cnt] = circle_cha[i];
			(*circle_cnt)++;
		}
		
	}

	//排序 记得之后把cha的排序去掉
	for (int i = 0; i < (*circle_cnt); i++) 
	{
		int m = i;
		for (int j = i + 1; j <(*circle_cnt); j++)
		{
			if (cha[j] > cha[m]) m = j;
		}
		if (i != m) 
		{
			int tempt_x = x[i];
			int tempt_y = y[i];
			int tempt_radius = radius[i];
			x[i] = x[m];
			y[i] = y[m];
			radius[i] = radius[m];
			x[m] = tempt_x;
			y[m] = tempt_y;
			radius[m] = tempt_radius;
		}
	}

	return MY_OK;
}
