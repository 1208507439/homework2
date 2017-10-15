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
	int max_circle){

	if (NULL == colorImg.data) {
		return MY_FAIL;
	}

	int ColorImg_Height = colorImg.rows;
	int ColorImg_Width = colorImg.cols;

	//defend
	int MinSide = ColorImg_Height;
	if (MinSide > ColorImg_Width) {
		MinSide = ColorImg_Width;
	}

	if (MinSide < min_radius + 5) {
		return MY_FAIL;
	}
	if (min_radius - 5 < 0) {
		min_radius = 5;
	}
	MinSide /= 2;
	if (MinSide < max_radius + 5) {
		max_radius = MinSide - 5;
	}
	if (min_radius > max_radius) {
		return MY_FAIL;
	}

	if (max_circle_diff <= 0) {
		return MY_FAIL;
	}
	if (max_circle_diff >= 255) {
		(*circle_cnt) = 0;
		return MY_OK;
	}



	int Var_Temp[4];
	Mat SRC_IMG, SRC_IMG_ROI, SUM_IMG_ROI;
	colorImg.convertTo(SRC_IMG, CV_16UC3);

	int Height_Index, Width_Index, Radius_Index, Angle_Index;

	Mat SumImg1[11], SumImg2[11], SumImg[11], diffmat1, diffmat2;
	//256*180 < u16        256*360 > u16

	for (int i = 0; i<11; i++){
		SumImg1[i] = Mat::zeros(ColorImg_Height, ColorImg_Width, CV_16UC3);
		SumImg2[i] = Mat::zeros(ColorImg_Height, ColorImg_Width, CV_16UC3);
	
	}

	int diffimg_lens = max_radius - min_radius + 10;
	Mat *diffimg = new Mat[diffimg_lens];

	for (int i = 0; i < 5; i++) {
		diffimg[i] = Mat::zeros(ColorImg_Height, ColorImg_Width, CV_8UC1);
	}

	for (int i = 0; i < 5; i++) {
		diffimg[diffimg_lens - i - 1] = Mat::zeros(ColorImg_Height, ColorImg_Width, CV_8UC1);
	}

	Mat max_circle_diff_img(ColorImg_Height, ColorImg_Width, CV_8UC3, Scalar(max_circle_diff, max_circle_diff, max_circle_diff));
	

	int Top_Point = 0, Bottom_Point;
	//Initialization   make stack full
	for (Radius_Index = min_radius - 5; Radius_Index < min_radius + 5; Radius_Index++, Top_Point++) {

		for (Angle_Index = 0; Angle_Index < 180; Angle_Index++) {
			Var_Temp[0] = (int)(Radius_Index - Radius_Index*sin(Angle_Index*0.0174532));
			Var_Temp[1] = ColorImg_Height - 2 * Radius_Index + Var_Temp[0];
			Var_Temp[2] = (int)(Radius_Index + Radius_Index* cos(Angle_Index*0.0174532));
			Var_Temp[3] = ColorImg_Width - 2 * Radius_Index + Var_Temp[2];
			SRC_IMG_ROI = SRC_IMG(Range(Var_Temp[0], Var_Temp[1]), Range(Var_Temp[2], Var_Temp[3]));
			SUM_IMG_ROI = SumImg1[Top_Point](Range(Radius_Index, ColorImg_Height - Radius_Index), Range(Radius_Index, ColorImg_Width - Radius_Index));
			SUM_IMG_ROI += SRC_IMG_ROI;

		}

		for (Angle_Index = 180; Angle_Index < 360; Angle_Index++) {

			Var_Temp[0] = (int)(Radius_Index - Radius_Index*sin(Angle_Index*0.0174532));
			Var_Temp[1] = ColorImg_Height - 2 * Radius_Index + Var_Temp[0];
			Var_Temp[2] = (int)(Radius_Index + Radius_Index* cos(Angle_Index*0.0174532));
			Var_Temp[3] = ColorImg_Width - 2 * Radius_Index + Var_Temp[2];
			SRC_IMG_ROI = SRC_IMG(Range(Var_Temp[0], Var_Temp[1]), Range(Var_Temp[2], Var_Temp[3]));
			SUM_IMG_ROI = SumImg2[Top_Point](Range(Radius_Index, ColorImg_Height - Radius_Index), Range(Radius_Index, ColorImg_Width - Radius_Index));
			SUM_IMG_ROI += SRC_IMG_ROI;
	
		}

	   //Push
		SumImg[Top_Point] = (SumImg1[Top_Point] + SumImg2[Top_Point])/360;
		
	}
	
	//Move on
	for (Radius_Index = min_radius + 5; Radius_Index < max_radius + 5; Radius_Index++, Top_Point++, Top_Point %= 11) {

		for (Angle_Index = 0; Angle_Index < 180; Angle_Index++) {
			Var_Temp[0] = (int)(Radius_Index - Radius_Index*sin(Angle_Index*0.0174532));
			Var_Temp[1] = ColorImg_Height - 2 * Radius_Index + Var_Temp[0];
			Var_Temp[2] = (int)(Radius_Index + Radius_Index* cos(Angle_Index*0.0174532));
			Var_Temp[3] = ColorImg_Width - 2 * Radius_Index + Var_Temp[2];
			SRC_IMG_ROI = SRC_IMG(Range(Var_Temp[0], Var_Temp[1]), Range(Var_Temp[2], Var_Temp[3]));
			SUM_IMG_ROI = SumImg1[Top_Point](Range(Radius_Index, ColorImg_Height - Radius_Index), Range(Radius_Index, ColorImg_Width - Radius_Index));
			SUM_IMG_ROI += SRC_IMG_ROI;

		}
		for (Angle_Index = 180; Angle_Index < 360; Angle_Index++) {

			Var_Temp[0] = (int)(Radius_Index - Radius_Index*sin(Angle_Index*0.0174532));
			Var_Temp[1] = ColorImg_Height - 2 * Radius_Index + Var_Temp[0];
			Var_Temp[2] = (int)(Radius_Index + Radius_Index* cos(Angle_Index*0.0174532));
			Var_Temp[3] = ColorImg_Width - 2 * Radius_Index + Var_Temp[2];
			SRC_IMG_ROI = SRC_IMG(Range(Var_Temp[0], Var_Temp[1]), Range(Var_Temp[2], Var_Temp[3]));
			SUM_IMG_ROI = SumImg2[Top_Point](Range(Radius_Index, ColorImg_Height - Radius_Index), Range(Radius_Index, ColorImg_Width - Radius_Index));
			SUM_IMG_ROI += SRC_IMG_ROI;

		}

		Bottom_Point = (Top_Point + 1) % 11;
		SumImg[Top_Point] = (SumImg1[Top_Point] + SumImg2[Top_Point]) / 360;

		Mat diffmat = Mat::zeros(ColorImg_Height, ColorImg_Width, CV_16UC3);
		absdiff(SumImg[Top_Point](Range(Radius_Index, ColorImg_Height - Radius_Index), Range(Radius_Index, ColorImg_Width - Radius_Index)), SumImg[Bottom_Point](Range(Radius_Index, ColorImg_Height - Radius_Index), Range(Radius_Index, ColorImg_Width - Radius_Index)), diffmat(Range(Radius_Index, ColorImg_Height - Radius_Index), Range(Radius_Index, ColorImg_Width - Radius_Index)));

		diffmat.convertTo(diffmat, CV_8UC3);
		diffmat -= max_circle_diff_img;

		std::vector<Mat> channels;
		split(diffmat, channels);
		diffimg[Radius_Index - min_radius] = max(max(channels.at(0), channels.at(1)), channels.at(2));

		SumImg1[Bottom_Point].setTo(0);
		SumImg2[Bottom_Point].setTo(0);
	}

	//deal with the repeated circles
	int circle_num = 0;
	int rows_index, cols_index;

	for (int r = 5; r < diffimg_lens - 5; r++) {
		int rc_index_start = r + min_radius - 5, r_index_end = ColorImg_Height - r - min_radius + 5, c_index_end =
			ColorImg_Width - r - min_radius + 5;
		uchar *ptr_diffimg = diffimg[r].data;
		for (rows_index = rc_index_start; rows_index < r_index_end; rows_index++) {
			for (cols_index = rc_index_start; cols_index < c_index_end; cols_index++) {
				int ptr_index = rows_index * ColorImg_Width + cols_index;
				int ROI_max = ptr_diffimg[ptr_index];
				if (ROI_max == 0) continue;

				int getflag = 1;

				int inner_r_begin = r - min_radius_dist, inner_r_end = r + min_radius_dist + 1;
				int inner_rows_index_begin = rows_index - min_center_dist, inner_rows_index_end = rows_index + min_center_dist + 1;
				int inner_cols_index_begin = cols_index - min_center_dist, inner_cols_index_end = cols_index + min_center_dist + 1;

				if (inner_r_begin < 0) inner_r_begin = 0;
				else if (inner_r_end > diffimg_lens) inner_r_end = diffimg_lens;

				if (inner_rows_index_begin < 0) inner_rows_index_begin = 0;
				else if (inner_rows_index_end > r_index_end)  inner_rows_index_end = r_index_end;

				if (inner_cols_index_begin < 0) inner_cols_index_begin = 0;
				else if (inner_cols_index_end > c_index_end) inner_cols_index_end = c_index_end;


				for (int i = inner_r_begin; i < inner_r_end; i++) {
					uchar *ptr_inner_diffimg = diffimg[i].data;
					for (int j = inner_rows_index_begin; j < inner_rows_index_end; j++) {
						for (int k = inner_cols_index_begin; k < inner_cols_index_end; k++) {
							int temp_inner_value = ptr_inner_diffimg[j * ColorImg_Width + k];
							if (ROI_max < temp_inner_value) {
								//break three for-loop
								k = inner_cols_index_end;
								j = inner_rows_index_end;
								i = inner_r_end;

								getflag = 0;
							}
						}
					}
				}

				if (getflag == 1) {
					ptr_diffimg[ptr_index] += 1;    //To solve the same max-value problem
					x[circle_num] = cols_index;
					y[circle_num] = rows_index;
					radius[circle_num] = r + min_radius - 5;
					circle_num++;
				}
			}
		}
	}

	(*circle_cnt) = circle_num;
	delete[] diffimg;
	return MY_OK;
}
