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
		cout << "image is NULL." << endl;
		return -1;
	}
	if (3 != colorImg.channels())
	{
		cout << "channel wrong." << endl;
		return -1;
	}
	if (max_circle_diff<=0|| max_circle<=0|| min_radius<30|| max_radius>300|| max_radius<min_radius)
	{
		cout << "something is wrong." << endl;
		return -1;
	}
	float sin_theta[360] = {
		0.0000,0.0175,0.0349,0.0523,0.0698,0.0872,0.1045,0.1219,0.1392,0.1564,0.1736,0.1908,
		0.2079,0.2249,0.2419,0.2588,0.2756,0.2924,0.3090,0.3256,0.3420,0.3584,0.3746,0.3907,
		0.4067,0.4226,0.4384,0.4540,0.4695,0.4848,0.5000,0.5150,0.5299,0.5446,0.5592,0.5736,
		0.5878,0.6018,0.6156,0.6293,0.6428,0.6560,0.6691,0.6820,0.6946,0.7071,0.7193,0.7313,
		0.7431,0.7547,0.7660,0.7771,0.7880,0.7986,0.8090,0.8191,0.8290,0.8387,0.8480,0.8572,
		0.8660,0.8746,0.8829,0.8910,0.8988,0.9063,0.9135,0.9205,0.9272,0.9336,0.9397,0.9455,
		0.9510,0.9563,0.9613,0.9659,0.9703,0.9744,0.9781,0.9816,0.9848,0.9877,0.9903,0.9925,
		0.9945,0.9962,0.9976,0.9986,0.9994,0.9998,1.0000,0.9998,0.9994,0.9986,0.9976,0.9962,
		0.9945,0.9926,0.9903,0.9877,0.9848,0.9816,0.9782,0.9744,0.9703,0.9659,0.9613,0.9563,
		0.9511,0.9455,0.9397,0.9336,0.9272,0.9205,0.9136,0.9063,0.8988,0.8910,0.8830,0.8746,
		0.8661,0.8572,0.8481,0.8387,0.8291,0.8192,0.8091,0.7987,0.7881,0.7772,0.7661,0.7548,
		0.7432,0.7314,0.7194,0.7072,0.6947,0.6820,0.6692,0.6561,0.6428,0.6294,0.6157,0.6019,
		0.5878,0.5736,0.5593,0.5447,0.5300,0.5151,0.5001,0.4849,0.4695,0.4541,0.4384,0.4227,
		0.4068,0.3908,0.3747,0.3584,0.3421,0.3256,0.3091,0.2925,0.2757,0.2589,0.2420,0.2250,
		0.2080,0.1909,0.1737,0.1565,0.1393,0.1220,0.1046,0.0872,0.0698,0.0524,0.0350,0.0175,
		0.0001,-0.0174,-0.0348,-0.0522,-0.0697,-0.0871,-0.1044,-0.1218,-0.1391,-0.1563,-0.1736,-0.1907,
		-0.2078,-0.2249,-0.2418,-0.2587,-0.2755,-0.2923,-0.3089,-0.3255,-0.3419,-0.3583,-0.3745,-0.3906,
		-0.4066,-0.4225,-0.4383,-0.4539,-0.4694,-0.4847,-0.4999,-0.5149,-0.5298,-0.5445,-0.5591,-0.5735,
		-0.5877,-0.6017,-0.6156,-0.6292,-0.6427,-0.6560,-0.6690,-0.6819,-0.6946,-0.7070,-0.7193,-0.7313,
		-0.7431,-0.7546,-0.7660,-0.7771,-0.7879,-0.7986,-0.8089,-0.8191,-0.8290,-0.8386,-0.8480,-0.8571,
		-0.8660,-0.8746,-0.8829,-0.8909,-0.8987,-0.9063,-0.9135,-0.9205,-0.9271,-0.9335,-0.9396,-0.9455,
		-0.9510,-0.9563,-0.9612,-0.9659,-0.9703,-0.9743,-0.9781,-0.9816,-0.9848,-0.9877,-0.9902,-0.9925,
		-0.9945,-0.9962,-0.9976,-0.9986,-0.9994,-0.9998,-1.0000,-0.9999,-0.9994,-0.9986,-0.9976,-0.9962,
		-0.9945,-0.9926,-0.9903,-0.9877,-0.9848,-0.9817,-0.9782,-0.9744,-0.9703,-0.9660,-0.9613,-0.9563,
		-0.9511,-0.9456,-0.9397,-0.9336,-0.9272,-0.9206,-0.9136,-0.9064,-0.8989,-0.8911,-0.8830,-0.8747,
		-0.8661,-0.8572,-0.8481,-0.8388,-0.8291,-0.8192,-0.8091,-0.7987,-0.7881,-0.7772,-0.7661,-0.7548,
		-0.7433,-0.7315,-0.7195,-0.7072,-0.6948,-0.6821,-0.6693,-0.6562,-0.6429,-0.6294,-0.6158,-0.6019,
		-0.5879,-0.5737,-0.5593,-0.5448,-0.5301,-0.5152,-0.5001,-0.4850,-0.4696,-0.4541,-0.4385,-0.4228,
		-0.4069,-0.3909,-0.3748,-0.3585,-0.3422,-0.3257,-0.3092,-0.2925,-0.2758,-0.2590,-0.2421,-0.2251,
		-0.2081,-0.1910,-0.1738,-0.1566,-0.1394,-0.1220,-0.1047,-0.0873,-0.0699,-0.0525,-0.0351,-0.0176
	};
	float cos_theta[360] = {
		1.0000,0.9998,0.9994,0.9986,0.9976,0.9962,0.9945,0.9925,0.9903,0.9877,0.9848,0.9816,
		0.9781,0.9744,0.9703,0.9659,0.9613,0.9563,0.9511,0.9455,0.9397,0.9336,0.9272,0.9205,
		0.9136,0.9063,0.8988,0.8910,0.8830,0.8746,0.8660,0.8572,0.8481,0.8387,0.8290,0.8192,
		0.8090,0.7986,0.7880,0.7772,0.7661,0.7547,0.7432,0.7314,0.7194,0.7071,0.6947,0.6820,
		0.6691,0.6561,0.6428,0.6293,0.6157,0.6018,0.5878,0.5736,0.5592,0.5447,0.5299,0.5151,
		0.5000,0.4848,0.4695,0.4540,0.4384,0.4226,0.4068,0.3908,0.3746,0.3584,0.3421,0.3256,
		0.3091,0.2924,0.2757,0.2589,0.2420,0.2250,0.2080,0.1908,0.1737,0.1565,0.1392,0.1219,
		0.1046,0.0872,0.0698,0.0524,0.0349,0.0175,0.0000,-0.0174,-0.0349,-0.0523,-0.0697,-0.0871,
		-0.1045,-0.1218,-0.1391,-0.1564,-0.1736,-0.1908,-0.2079,-0.2249,-0.2419,-0.2588,-0.2756,-0.2923,
		-0.3090,-0.3255,-0.3420,-0.3583,-0.3746,-0.3907,-0.4067,-0.4226,-0.4383,-0.4539,-0.4694,-0.4848,
		-0.4999,-0.5150,-0.5299,-0.5446,-0.5591,-0.5735,-0.5877,-0.6018,-0.6156,-0.6293,-0.6427,-0.6560,
		-0.6691,-0.6819,-0.6946,-0.7071,-0.7193,-0.7313,-0.7431,-0.7547,-0.7660,-0.7771,-0.7880,-0.7986,
		-0.8090,-0.8191,-0.8290,-0.8386,-0.8480,-0.8571,-0.8660,-0.8746,-0.8829,-0.8910,-0.8988,-0.9063,
		-0.9135,-0.9205,-0.9272,-0.9336,-0.9397,-0.9455,-0.9510,-0.9563,-0.9612,-0.9659,-0.9703,-0.9744,
		-0.9781,-0.9816,-0.9848,-0.9877,-0.9903,-0.9925,-0.9945,-0.9962,-0.9976,-0.9986,-0.9994,-0.9998,
		-1.0000,-0.9998,-0.9994,-0.9986,-0.9976,-0.9962,-0.9945,-0.9926,-0.9903,-0.9877,-0.9848,-0.9816,
		-0.9782,-0.9744,-0.9703,-0.9660,-0.9613,-0.9563,-0.9511,-0.9456,-0.9397,-0.9336,-0.9272,-0.9205,
		-0.9136,-0.9064,-0.8988,-0.8911,-0.8830,-0.8747,-0.8661,-0.8572,-0.8481,-0.8387,-0.8291,-0.8192,
		-0.8091,-0.7987,-0.7881,-0.7772,-0.7661,-0.7548,-0.7432,-0.7314,-0.7194,-0.7072,-0.6947,-0.6821,
		-0.6692,-0.6561,-0.6429,-0.6294,-0.6158,-0.6019,-0.5879,-0.5737,-0.5593,-0.5447,-0.5300,-0.5151,
		-0.5001,-0.4849,-0.4696,-0.4541,-0.4385,-0.4227,-0.4069,-0.3908,-0.3747,-0.3585,-0.3421,-0.3257,
		-0.3091,-0.2925,-0.2758,-0.2589,-0.2420,-0.2251,-0.2080,-0.1909,-0.1738,-0.1566,-0.1393,-0.1220,
		-0.1047,-0.0873,-0.0699,-0.0525,-0.0350,-0.0176,-0.0001,0.0173,0.0348,0.0522,0.0696,0.0870,
		0.1044,0.1217,0.1390,0.1563,0.1735,0.1907,0.2078,0.2248,0.2418,0.2587,0.2755,0.2922,
		0.3089,0.3254,0.3419,0.3582,0.3745,0.3906,0.4066,0.4225,0.4382,0.4539,0.4693,0.4847,
		0.4999,0.5149,0.5298,0.5445,0.5591,0.5734,0.5877,0.6017,0.6155,0.6292,0.6427,0.6559,
		0.6690,0.6819,0.6945,0.7070,0.7192,0.7312,0.7430,0.7546,0.7659,0.7770,0.7879,0.7985,
		0.8089,0.8191,0.8289,0.8386,0.8480,0.8571,0.8659,0.8745,0.8829,0.8909,0.8987,0.9062,
		0.9135,0.9204,0.9271,0.9335,0.9396,0.9455,0.9510,0.9563,0.9612,0.9659,0.9703,0.9743,
		0.9781,0.9816,0.9848,0.9877,0.9902,0.9925,0.9945,0.9962,0.9976,0.9986,0.9994,0.9998
	};
	int width = colorImg.cols;
	int height = colorImg.rows;
	int max = 0;
	int Rmax = max_radius;
	int Rmin = min_radius;
	int th = max_circle_diff;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_64F;

	Mat grayImg_B(height, width, CV_8UC1);
	Mat grayImg_R(height, width, CV_8UC1);
	Mat grayImg_G(height, width, CV_8UC1);
	Mat Threshold_B(height, width, CV_8UC1);
	Mat Threshold_R(height, width, CV_8UC1);
	Mat Threshold_G(height, width, CV_8UC1);
	Mat gradB_x, gradB_y;
	Mat abs_gradB_x, abs_gradB_y;
	Mat gradG_x, gradG_y;
	Mat abs_gradR_x, abs_gradR_y;
	Mat gradR_x, gradR_y;
	Mat abs_gradG_x, abs_gradG_y;
	for (int col_i = 0; col_i < height; col_i++) {
		int temp_gray = col_i*width;
		for (int row_j = 0; row_j < width; row_j++) {
			int temp_gray1 = temp_gray + row_j;
			grayImg_B.data[temp_gray1] = colorImg.data[3 * temp_gray1];
			grayImg_R.data[temp_gray1] = colorImg.data[3 * temp_gray1+1];
			grayImg_G.data[temp_gray1] = colorImg.data[3 * temp_gray1+2];
		}
	}    



	
	int flag_x = 0;
	int pf = 1;
	long long int* bing = (long long int*)malloc(height*width * sizeof(long long int));
	if (sizeof(long long int) >= 8) {
		flag_x = 1;
		for (int row_i = 0; row_i < height; row_i++) {
			for (int col_j = 0; col_j < width; col_j++) {
				*(bing + row_i*width + col_j) = 0;
				*(bing + row_i*width + col_j)+= grayImg_R.data[row_i*width + col_j];
				*(bing + row_i*width + col_j) = *(bing + row_i*width + col_j) << 20;
				*(bing + row_i*width + col_j) += grayImg_G.data[row_i*width + col_j];
				*(bing + row_i*width + col_j) = *(bing + row_i*width + col_j) << 20;
				*(bing + row_i*width + col_j) += grayImg_B.data[row_i*width + col_j];
			}
		}
	}
	else {
		flag_x = 0;
	}
	


	*circle_cnt = 0;
	int* door = (int *)malloc(height*width*sizeof(int));
	int* x_circle= (int *)malloc(height*width  * sizeof(int));
	int* y_circle = (int *)malloc(height*width  * sizeof(int));
	int* r_circle = (int *)malloc(height*width  * sizeof(int));
	int* door_th = (int *)malloc(height*width  * sizeof(int));
	if (!(door&&x_circle&&y_circle&&r_circle)) {
		printf("something is wrong!");
		return -1;
	}
	int num_circle = 0;
	int circle_x[310][360] = { 0 };
	int circle_y[310][360] = { 0 };
	int circle_len[310] = { 0 };
	for (int find_r = Rmin-5; find_r <= Rmax+5; find_r++) {
		int r_px = 0;
		int r_py = 0;
		for (int find_theta = 0; find_theta < 360; find_theta++) {
			int r_x = find_r*cos_theta[find_theta];
			int r_y = find_r*sin_theta[find_theta];
			if (r_x == r_px&&r_y == r_py);
			else {
				circle_x[find_r][circle_len[find_r]] = r_x;
				circle_y[find_r][circle_len[find_r]] = r_y;
				circle_len[find_r]++;
				r_px = r_x;
				r_py = r_y;
			}
		}
	}                                    



	if (flag_x == 1) {
		for (int col_i = Rmin; col_i < height - Rmin; col_i++) {
			for (int row_j = Rmin; row_j < width - Rmin; row_j++) {
				long long int diff_B[310] = { 0 };
				long long int diff_G[310] = { 0 };
				long long int diff_R[310] = { 0 };
				Rmax = max_radius;
				if (col_i - 5 < Rmax) Rmax = col_i - 5;
				if (height - col_i - 6 < Rmax) Rmax = height - col_i - 6;
				if (row_j - 5 < Rmax) Rmax = row_j - 5;
				if (width - row_j - 6 < Rmax) Rmax = width - row_j - 6;          
				for (int find_r = Rmin - 5; find_r <= Rmax + 5; find_r++) {
					int adv_r1_B = 0;
					int adv_r1_G = 0;
					int adv_r1_R = 0;
					long long int adv_r1 = 0;
					int theta_1 = circle_len[find_r];
					for (int theta = 0; theta < theta_1; theta++) {
						int theta_x1 = row_j + circle_x[find_r][theta];
						int theta_y1 = col_i + circle_y[find_r][theta];
						int theta_r = theta_y1*width + theta_x1;
						adv_r1 += *(bing + theta_r);                  
					}
					diff_B[find_r] = (adv_r1&long long(1048575)) / theta_1;
					diff_G[find_r] = (adv_r1>>20 & long long(1048575)) / theta_1;
					diff_R[find_r] = (adv_r1>>40 & long long(1048575)) / theta_1;
				}
				for (int find_r = Rmin; find_r < Rmax; find_r++) {
					int diff_circle_B = diff_B[find_r + 5] - diff_B[find_r - 5];
					if (diff_circle_B < 0) diff_circle_B = -diff_circle_B;
					int diff_circle_G = diff_G[find_r + 5] - diff_G[find_r - 5];;
					if (diff_circle_G < 0) diff_circle_G = -diff_circle_G;
					int diff_circle_R = diff_R[find_r + 5] - diff_R[find_r - 5];
					if (diff_circle_R < 0) diff_circle_R = -diff_circle_R;
					if (diff_circle_B > th) {
						*(door + num_circle) = diff_circle_B;
						*(x_circle + num_circle) = row_j;
						*(y_circle + num_circle) = col_i;
						*(r_circle + num_circle) = find_r;
						num_circle++;
					}
					if (diff_circle_G > th) {
						*(door + num_circle) = diff_circle_G;
						*(x_circle + num_circle) = row_j;
						*(y_circle + num_circle) = col_i;
						*(r_circle + num_circle) = find_r;
						num_circle++;
					}
					if (diff_circle_R > th) {
						*(door + num_circle) = diff_circle_R;
						*(x_circle + num_circle) = row_j;
						*(y_circle + num_circle) = col_i;
						*(r_circle + num_circle) = find_r;
						num_circle++;
					}
					if (num_circle >= height*width) {
						printf("th too low!\n");
						return -1;
					}
				}
			}
		}
	}
	else {                  
		for (int col_i = Rmin; col_i < height - Rmin; col_i++) {
			for (int row_j = Rmin; row_j < width - Rmin; row_j++) {
				int diff_B[310] = { 0 };
				int diff_G[310] = { 0 };
				int diff_R[310] = { 0 };
				Rmax = max_radius;
				if (col_i - 5 < Rmax) Rmax = col_i - 5;
				if (height - col_i - 6 < Rmax) Rmax = height - col_i - 6;
				if (row_j - 5 < Rmax) Rmax = row_j - 5;
				if (width - row_j - 6 < Rmax) Rmax = width - row_j - 6;         
				for (int find_r = Rmin - 5; find_r <= Rmax + 5; find_r++) {
					int adv_r1_B = 0;
					int adv_r1_G = 0;
					int adv_r1_R = 0;
					int adv_r1 = 0;
					int theta_1 = circle_len[find_r];
					for (int theta = 0; theta < theta_1; theta++) {
						int theta_x1 = row_j + circle_x[find_r][theta];
						int theta_y1 = col_i + circle_y[find_r][theta];
						int theta_r = theta_y1*width + theta_x1;
								adv_r1_B += grayImg_B.data[theta_r];
								adv_r1_G += grayImg_G.data[theta_r];
								adv_r1_R += grayImg_R.data[theta_r];
					}
					diff_B[find_r] = adv_r1_B / theta_1;
					diff_G[find_r] = adv_r1_G / theta_1;
					diff_R[find_r] = adv_r1_R / theta_1;
				}
				for (int find_r = Rmin; find_r < Rmax; find_r++) {
					int diff_circle_B = diff_B[find_r + 5] - diff_B[find_r - 5];
					if (diff_circle_B < 0) diff_circle_B = -diff_circle_B;
					int diff_circle_G = diff_G[find_r + 5] - diff_G[find_r - 5];;
					if (diff_circle_G < 0) diff_circle_G = -diff_circle_G;
					int diff_circle_R = diff_R[find_r + 5] - diff_R[find_r - 5];
					if (diff_circle_R < 0) diff_circle_R = -diff_circle_R;
					if (diff_circle_B > th) {
						*(door + num_circle) = diff_circle_B;
						*(x_circle + num_circle) = row_j;
						*(y_circle + num_circle) = col_i;
						*(r_circle + num_circle) = find_r;
						num_circle++;
					}
					if (diff_circle_G > th) {
						*(door + num_circle) = diff_circle_G;
						*(x_circle + num_circle) = row_j;
						*(y_circle + num_circle) = col_i;
						*(r_circle + num_circle) = find_r;
						num_circle++;
					}
					if (diff_circle_R > th) {
						*(door + num_circle) = diff_circle_R;
						*(x_circle + num_circle) = row_j;
						*(y_circle + num_circle) = col_i;
						*(r_circle + num_circle) = find_r;
						num_circle++;
					}
				}
			}
		}
	}


		int xy_2_th = min_center_dist*min_center_dist;
		int r_2_th = min_radius_dist*min_radius_dist;
		for (int row_j = 0; row_j < num_circle; row_j++) {
			int now_door = *(door + row_j);
			int now_x = *(x_circle + row_j);
			int now_y = *(y_circle + row_j);
			int now_r = *(r_circle + row_j);
			if (now_door) {
				for (int col_i = row_j + 1; col_i < num_circle&&now_door; col_i++) {
					int over_door = *(door + col_i);
					if (over_door) {
						int over_x = *(x_circle + col_i);
						int over_y = *(y_circle + col_i);
						int over_r = *(r_circle + col_i);
						int xy_2 = (now_x - over_x)*(now_x - over_x);
						xy_2 += (now_y - over_y)*(now_y - over_y);
						int r_2 = (now_r - over_r)*(now_r - over_r);
						if (xy_2 <= xy_2_th&&r_2 <= r_2_th) {
							if (now_door < over_door) {
								*(door + row_j) = 0;
								now_door = 0;
							}
							else *(door + col_i) = 0;
						}
					}
				}
				if (now_door) {
					x[*circle_cnt] = now_x;
					y[*circle_cnt] = now_y;
					radius[*circle_cnt] = now_r;
					*(door_th + *circle_cnt) = now_door;
					(*circle_cnt)++;
				}
			}
		}



		if (*circle_cnt > max_circle) {
			for (int col_j = 0; col_j < max_circle; col_j++) {
				for (int row_i = *circle_cnt - 1; row_i > col_j; row_i--) {
					if (*(door_th + row_i) > *(door_th + row_i - 1)) {
						int a = *(door_th + row_i);
						*(door_th + row_i) = *(door_th + row_i - 1);
						*(door_th + row_i - 1) = a;
						a = x[row_i];
						x[row_i] = x[row_i-1];
						x[row_i - 1] = a;
						a = y[row_i];
						y[row_i] = y[row_i - 1];
						y[row_i - 1] = a;
						a = radius[row_i];
						radius[row_i] = radius[row_i - 1];
						radius[row_i - 1] = a;
					}
				}
			}
			*circle_cnt = max_circle;
		}
		free(door);
		free(x_circle);
		free(y_circle);
		free(r_circle);
		free(door_th);
		free(bing);
	return 1;
}
