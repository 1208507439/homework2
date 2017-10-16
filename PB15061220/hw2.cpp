int ustc_Find_Circles_By_Difference(Mat colorImg, int min_radius, int max_radius,
	int min_center_dist, int min_radius_dist,
	int max_circle_diff, int* x, int* y, int* radius, int* circle_cnt,int max_circle) {
	if (NULL == colorImg.data||NULL==x||NULL==y||NULL==radius ||NULL==circle_cnt|| colorImg.channels() != 3) {
		cout << "img wrong." << endl;
		return MY_FAIL;
	}
	if (min_radius <= 0 || max_radius > colorImg.cols || max_radius > colorImg.rows) {
		cout << "radius wrong." << endl;
		return MY_FAIL;
	}
	if (min_radius_dist < 0 || min_center_dist < 0) {
		cout << "dist<0." << endl;
		return MY_FAIL;
	}
	if (max_circle_diff < 0 || max_circle_diff>255) {
		cout << "diff is too small or big." << endl;
		return MY_FAIL;
	}
	memset(x, 0, max_circle);
	memset(y, 0, max_circle);
	memset(radius, 0, max_circle);
	int cols = colorImg.cols;
	int rows = colorImg.rows;
	int all = cols*rows;
	*circle_cnt = 0;
	Mat b;
	Mat g;
	Mat r;
	Mat channels[3];
	split(colorImg, channels);
	b = channels[0];
	g = channels[1];
	r = channels[2];
	
	int *round_out_x = (int*)malloc(380 * sizeof(int));
	int *round_out_y = (int*)malloc(380 * sizeof(int));
	int *round_in_x = (int*)malloc(380 * sizeof(int));
	int *round_in_y = (int*)malloc(380 * sizeof(int));
	uchar*datab = b.data;
	uchar*datag = g.data;
	uchar*datar = r.data;
	int nx = 0;

	for (int r =min_radius; r <= max_radius; r++) {
		int *flag_out_x = round_out_x;
		int *flag_out_y = round_out_y;
		int *flag_in_x = round_in_x;
		int *flag_in_y = round_in_y;
		for (int rad =0; rad < 360; rad++) {
			flag_out_x[rad] = (int)(r + 5)*cos((float)rad/180*CV_PI);
			flag_out_y[rad] = (int)(r + 5)*sin((float)rad/180*CV_PI);
			flag_in_x[rad] = (int)(r - 5)*cos((float)rad/180*CV_PI);
			flag_in_y[rad] = (int)(r - 5)*sin((float)rad/180*CV_PI);
		}
		
		for (int i = r+5; i < rows-r-5; i++) {
			int mm = i *cols;
			for (int j=r+5; j < cols-r-5; j++) {
				int outer_c = 0;
				int inner_c = 0;
				int outer_c_g = 0;
				int inner_c_g = 0;
				int outer_c_r = 0;
				int inner_c_r = 0;
				int nn = mm + j;
				for (int rad = 0; rad < 360; rad++) {
					int out_r = nn+ flag_out_y[rad]*cols + flag_out_x[rad];
					int in_r= nn + flag_in_y[rad]*cols + flag_in_x[rad];
					outer_c += datab[out_r];
					inner_c += datab[in_r];
					outer_c_g+= datag[out_r];
					inner_c_g+= datag[in_r];
					outer_c_r+= datar[out_r];
					inner_c_r+= datar[in_r];
				}
					float outer_cf = (float)outer_c / 360;
					float inner_cf = (float)inner_c / 360;
					float diff = abs(outer_cf - inner_cf);
					float outer_cf_g = (float)outer_c_g / 360;
					float inner_cf_g = (float)inner_c_g / 360;
					float diff_g = abs(outer_cf_g - inner_cf_g);
					float outer_cf_r = (float)outer_c_r / 360;
					float inner_cf_r = (float)inner_c_r / 360;
					float diff_r = abs(outer_cf_r - inner_cf_r);
					if (diff >= max_circle_diff||diff_g>= max_circle_diff || diff_r>= max_circle_diff ) {
						int flag = 0;
						for (int idx = 0; idx < nx; idx++) {
							if (sqrt((i - y[idx])*(i - y[idx]) + (j - x[idx])*(j - x[idx])) <= min_center_dist && (r - radius[idx]) <= min_radius_dist) {
								flag = 1;
								break;
							}
						}
						if (flag == 0) {
							x[nx] = j;
							y[nx] = i;
							radius[nx] = r;
							nx++;
							(*circle_cnt)++;
						}
					}
			}
		}
	}
	return MY_OK;
}
