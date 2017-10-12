
#define PI 3.1415926
#define MY_OK 0
#define MY_FAIL -1


int ustc_Find_Circles_By_Difference(Mat colorImg, int min_radius, int max_radius,int min_center_dist, int min_radius_dist, int max_circle_diff,int *x, int *y, int *radius, int *circle_cnt, int max_circle)
{
	//判断传入图片的正确性
	if (NULL == colorImg.data)
	{
		cout << "colorImg ERROR!!" << endl;
		return MY_FAIL;
	}

	//对传入图片的通道数的判断
	if (3 != colorImg.channels())
	{
		cout << "Channels ERROR!!" << endl;
		return MY_FAIL;
	}

	
	int temp_x[50000];
	int temp_y[50000];
	int temp_r[50000];

	
	int radius_range = max_radius - min_radius + 1;

	//建立r*sin sita与r*cos sita的表，名为table,以备查询
	float *table = (float*)malloc((max_radius + 5) * 360 * 2 * sizeof(float));
	float sita_table[360 * 2];
	float translate = PI / 180;
	

	
	for (int table_sita = 0; table_sita < 360; table_sita++)
	{
		sita_table[table_sita * 2 + 0] = cos(table_sita * translate);
		sita_table[table_sita * 2 + 1] = sin(table_sita * translate);
	}
	
	for (int table_r = 0; table_r <= max_radius + 5; table_r++)
	{
		for (int table_sita = 0; table_sita < 360; table_sita++)
		{
			table[table_r * 720 + table_sita * 2 + 0] = table_r * sita_table[table_sita * 2 + 0];
			table[table_r * 720 + table_sita * 2 + 1] = table_r * sita_table[table_sita * 2 + 1];
		}
	}
	//起始的半径为0，一个半径有720个数据，先储存cos，再储存sin
	//制表结束
	

	int low_table_r = min_radius - 5;
	int Width = colorImg.cols;
	int Height = colorImg.rows;
	int now_x, now_y, now_r;
	int len = 0;//目前已经的圆的数目&正在写入的圆的数组序号

	for (now_r = min_radius; now_r <= max_radius; now_r++)//半径循环
	{
		int max_x = Width - now_r;
		for (now_x = now_r; now_x < max_x; now_x++)//横坐标循环
		{
			int max_y = Height - now_r;
			for	(now_y = now_r; now_y < max_y; now_y++)//纵坐标循环
			{	
				int now_channel = 0;
				
				while (now_channel<3)	//通道循环
				{
					
					int now_place = now_y * Width + now_x;  //当前位置
					int circle_radius_in = now_r - 5;    //内圆半径
					int circle_radius_out = now_r - 5;   //外圆半径
					float circle_diff = 0.0;
					float circle_light_in = 0.0, circle_light_out = 0.0;  //内外圆的亮度 和 & 均值
					
					float length_of_place=0.0;//重置有效位置个数
					int last_temp_place = 0;//重置“上一位置”
                    int temp_place_0 = now_place + circle_radius_in;//定义“第0位置”
					
					//内圆求平均亮度
					for (int temp_sita_angle = 0; temp_sita_angle < 360; temp_sita_angle++)//角度循环
					{
						float temp_sita_radian = temp_sita_angle * translate;
						int temp_place = now_place + (int)(table[1440 * circle_radius_in + 2 * temp_sita_angle + 0]) +
							(int)(table[1440 * circle_radius_in + 2 * temp_sita_angle + 1]) * Width;

						
						if (temp_sita_angle == 0 || temp_place != last_temp_place )
						{
							circle_light_in += colorImg.data[3 * temp_place + now_channel];  //累加求均值
							length_of_place = length_of_place + 1.0;  //记录有效临时位置的个数，记为float型，便于后面的除法  （  <=360  )
							last_temp_place = temp_place;  //将此时的有效位置记为“上一位置”
							
						}

					}
					
					circle_light_in /= length_of_place;  // 将和取为均值
					


					//外圆求平均亮度
					length_of_place = 0.0; //重置有效位置个数
					temp_place_0 = now_place + circle_radius_out;  //重置“第0位置”
					last_temp_place = 0;//重置“上一位置”为0
					for (int temp_sita_angle = 0; temp_sita_angle < 360; temp_sita_angle++)//角度循环
					{
						float temp_sita_radian = temp_sita_angle * translate;
						int temp_place = now_place + (int)(table[1440 * circle_radius_out + temp_sita_angle * 2 + 0]) +
							(int)(table[1440 * circle_radius_out + temp_sita_angle * 2 + 1]) * Width;

						if (temp_sita_angle == 0 || (temp_place != last_temp_place && temp_place != temp_place_0))
						{
							circle_light_out += colorImg.data[3 * temp_place + now_channel];  //累加求均值
							length_of_place = length_of_place + 1.0;  //记录有效临时位置的个数，记为float型，便于后面的除法  （  <=360  )
							last_temp_place = temp_place;  //将此时的有效位置记为“上一位置
						}
					}
					circle_light_out /= length_of_place;  //将和取为均值

					//求圆的差分
					circle_diff = abs(circle_light_in - circle_light_out);
					
					if (circle_diff >= max_circle_diff)
					{
						//记录圆心的坐标与半径
						temp_x[len] = now_x;
						temp_y[len] = now_y;
						temp_r[len] = now_r;
						len++;
						break;
					}
					now_channel++;
				}
			}
		}
	}
	
	//排除圆心相近的同半径圆
	int min_center_dist2 = min_center_dist*min_center_dist;
	int last_r=0;
	int temp_r_x[1000] = { 0 };
	int temp_r_y[1000] = { 0 };
	int flag = 1;
	int k=0;
	for (int i = 0; i < len; i++)
	{
		if (temp_r[i] != last_r)
		{
			last_r = temp_r[i];
			for (int j = 0; j<k; j++)
			{
				temp_r_x[j] = temp_r_y[j] = 0;
			}
			k = 0;
		}
		else
		{
			for (int j = 0; j<k&&flag; j++)
			{
				
				if (((temp_r_x[j] - temp_x[i])*(temp_r_x[j] - temp_x[i]) + (temp_r_y[j] - temp_y[i])*(temp_r_y[j] - temp_y[i])) <= min_center_dist2)
				{
					flag = 0;
				}
			}
			if (flag)
			{
				temp_r_x[k] = temp_x[i];
				temp_r_y[k] = temp_y[i];
				k++;
			}
			else
			{
				temp_r[i] = 0;
			}
		}
		flag = 1;
	}

	//对三个临时数组进行整合
	int j=0;
	for (int i = 0, j = 0; i < len; i++)
	{
		if (temp_r[i] != 0)
		{
			temp_r[j] = temp_r[i];
			temp_x[j] = temp_x[i];
			temp_y[j] = temp_y[i];
			j++;
		}
	}
	len = j;//第一次排除之后的实际圆个数赋给len

	//排除同心半径相近的圆
	for (int i = 0; i < len; i++)
	{
		int check_r = temp_r[i];
		int check_x = temp_x[i];
		int check_y = temp_y[i];
		for (int l = i; temp_r[l] - check_r > min_radius_dist; l++)
		{
			if (temp_x[l] == check_x && temp_y[l] == check_y)
			{
				temp_r[i] = 0;
				break;
			}
		}
	}

	//对三个临时数组进行整合
	for (int i = 0, j = 0; i < len; i++)
	{
		if (temp_r[i] != 0)
		{
			temp_r[j] = temp_r[i];
			temp_x[j] = temp_x[i];
			temp_y[j] = temp_y[i];
			j++;
		}
	}
	len = j;
	
	
	
	//将临时数组中的信息导入传出数组中
	*circle_cnt = 0;
	if (len <= max_circle)
	{
		for (int i = 0; i < len; i++)
		{
			if (temp_r[i])
			{
				radius[*circle_cnt] = temp_r[i];
				x[*circle_cnt] = temp_x[i];
				y[*circle_cnt] = temp_y[i];
				(*circle_cnt)++;
			}
		}
	}
	else
	{
		*circle_cnt = max_circle;
		for (int i = 1; i <= max_circle; i++)
		{
			radius[i - 1] = temp_r[len - i];
			x[i - 1] = temp_x[len - i];
			y[i - 1] = temp_y[len - i];
		}
	}


	return MY_OK;
}
