#include "CircleFinder.h"

#define VERSION_6

const int MIN_RASIUS = 5;
const int MAX_RASIUS = 1000;

const int MAX_CIRCLE_NUMBER = 1000;

const int STEP = 5;

#ifdef VERSION_6
/*
VERSION 6.0
Loop order r-theta-x-y
Based on opencv
Lossy optimization!!!
Same circle have removed, AT THE END
*/
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
	if (colorImg.data == NULL) return MY_FAIL;

	const int rows = colorImg.rows;
	const int cols = colorImg.cols;

	if (min_radius < MIN_RASIUS) return MY_FAIL;
	if (min_radius > max_radius) return MY_FAIL;
	if (max_radius > MAX_RASIUS) return MY_FAIL;

	if (max_radius > rows / 2 - STEP) max_radius = rows / 2 - STEP;
	if (max_radius > cols / 2 - STEP) max_radius = cols / 2 - STEP;
	if (min_radius > rows / 2 - STEP) min_radius = rows / 2 - STEP;
	if (min_radius > cols / 2 - STEP) min_radius = cols / 2 - STEP;

	if (min_center_dist < 0) return MY_FAIL;
	if (min_radius_dist < 0) return MY_FAIL;
	if (max_circle_diff <= 0 || max_circle_diff > 255) return MY_FAIL;

	if (max_circle <= 0) return MY_FAIL;

	int _circle_cnt = 0;
	int* diff = new int[max_circle];

	//Origin Image
	Mat originImg;
	colorImg.convertTo(originImg, CV_16UC3);
	originImg = originImg * 0.7;

	//Diff Threshold Image
	Mat diffThresholdImg;
	diffThresholdImg.create(rows, cols, CV_8UC1);
	diffThresholdImg.setTo(max_circle_diff);
	diffThresholdImg = diffThresholdImg * 0.7;
	diffThresholdImg.convertTo(diffThresholdImg, CV_16UC1);


	//Average Image
	Mat aveImg[MAX_RASIUS + STEP + 1];

	//Diff Image
	Mat diffImg[MAX_RASIUS + STEP + 1];

	//Calculate Diff Image
	for (int r = min_radius - STEP; r <= max_radius + STEP; r++)
	{
		Mat sumImg;
		sumImg.create(rows, cols, CV_16UC3);
		sumImg.setTo(0);



		int rows_start_table[360], rows_end_table[360], cols_start_table[360], cols_end_table[360];
		for (int theta = 0; theta < 360; theta++)
		{
			int theta_cos = r*cos(theta*3.1415 / 180);
			int theta_sin = r*sin(theta*3.1415 / 180);

			Mat subImg1, subImg2;
			subImg1 = sumImg(Range(r, rows - r), Range(r, cols - r));
			subImg2 = originImg(Range(r + theta_sin, rows - r + theta_sin), Range(r + theta_cos, cols - r + theta_cos));
			subImg1 = subImg1 + subImg2;
		}
		aveImg[r] = sumImg / 360;

		if (r >= min_radius + STEP)
		{
			int k = r - STEP;

			diffImg[k].create(rows, cols, CV_16UC3);
			diffImg[k].setTo(0);
			absdiff(aveImg[k - STEP](Range(r, rows - r), Range(r, cols - r)), aveImg[k + STEP](Range(r, rows - r), Range(r, cols - r)), diffImg[k](Range(r, rows - r), Range(r, cols - r)));
			vector<Mat> diffSplitedImg;
			split(diffImg[k], diffSplitedImg);
			diffImg[k] = (diffSplitedImg.at(0) + diffSplitedImg.at(1) + diffSplitedImg.at(2));
			diffImg[k] = diffImg[k] - diffThresholdImg * 3;

			//aveImg[k - STEP].release();
		}
	}

	for (int r = min_radius; r <= max_radius; r++)
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				uint16_t center_value = *((uint16_t*)diffImg[r].data + i*cols + j);
				if (center_value <= 0) continue;

				/***********************************************************/
				/*
				could be faster
				*/
				if (r + STEP > i || r + STEP > rows - i || r + STEP > j || r + STEP > cols - j) continue;
				/***********************************************************/

				int sub_r_start, sub_r_end;
				if (r - min_radius_dist >= min_radius) sub_r_start = r - min_radius_dist;
				else sub_r_start = min_radius;
				if (r + min_radius_dist <= max_radius) sub_r_end = r + min_radius_dist;
				else sub_r_end = max_radius;

				int sub_i_start, sub_i_end;
				if (i - min_center_dist >= 0) sub_i_start = i - min_center_dist;
				else sub_i_start = 0;
				if (i + min_center_dist <= rows) sub_i_end = i + min_center_dist;
				else sub_i_end = rows;

				int sub_j_start, sub_j_end;
				if (j - min_center_dist >= 0) sub_j_start = j - min_center_dist;
				else sub_j_start = 0;
				if (j + min_center_dist <= cols) sub_j_end = j + min_center_dist;
				else sub_j_end = cols;

				int flag = 0;

				//
				for (int sub_r = sub_r_start; sub_r <= sub_r_end; sub_r++)
				{
					for (int sub_i = sub_i_start; sub_i < sub_i_end; sub_i++)
					{
						for (int sub_j = sub_j_start; sub_j < sub_j_end; sub_j++)
						{
							uint16_t surround_value = *((uint16_t*)diffImg[sub_r].data + sub_i*cols + sub_j);
							if (surround_value > center_value) flag = 1;
							if (flag == 1)break;
						}
						if (flag == 1)break;
					}
					if (flag == 1)break;
				}

				//
				for (int p = 0; p < _circle_cnt; p++)
				{
					if (((j - x[p])*(j - x[p]) + (i - y[p])*(i - y[p])) < min_center_dist*min_center_dist && abs(radius[p] - r) < min_radius_dist)
					{
						if (center_value <= diff[p])
						{
							flag = 1;
							continue;
						}
					}
				}

				if (flag == 0)
				{
					x[_circle_cnt] = j;
					y[_circle_cnt] = i;
					radius[_circle_cnt] = r;
					diff[_circle_cnt] = center_value;
					_circle_cnt++;
				}

				if (_circle_cnt == max_circle)
				{
					*circle_cnt = _circle_cnt;
					return MY_OK;
				}
			}
		}
	}

	*circle_cnt = _circle_cnt;
	return MY_OK;
}
#endif // VERSION_6

#ifdef VERSION_5
/*
VERSION 5.0
Loop order r-theta-x-y
Based on opencv
Lossy optimization!!!
Same circle have removed, AT THE END
*/
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
	if (colorImg.data == NULL) return MY_FAIL;

	const int rows = colorImg.rows;
	const int cols = colorImg.cols;

	if (min_radius < MIN_RASIUS) return MY_FAIL;
	if (min_radius > max_radius) return MY_FAIL;
	if (max_radius > MAX_RASIUS) return MY_FAIL;

	if (max_radius > rows / 2) max_radius = rows / 2;
	if (max_radius > cols / 2) max_radius = cols / 2;
	if (min_radius > rows / 2) min_radius = rows / 2;
	if (min_radius > cols / 2) min_radius = cols / 2;

	if (min_center_dist < 0) return MY_FAIL;
	if (min_radius_dist < 0) return MY_FAIL;
	if (max_circle_diff <= 0 || max_circle_diff > 255) return MY_FAIL;

	if (max_circle <= 0) return MY_FAIL;

	int _circle_cnt = 0;
	int* diff = new int[max_circle];

	//Origin Image
	Mat originImg;
	colorImg.convertTo(originImg, CV_16UC3);
	originImg = originImg * 0.7;

	//Diff Threshold Image
	Mat diffThresholdImg;
	diffThresholdImg.create(rows, cols, CV_8UC1);
	diffThresholdImg.setTo(max_circle_diff);
	diffThresholdImg = diffThresholdImg * 0.7;
	diffThresholdImg.convertTo(diffThresholdImg, CV_16UC1);


	//Average Image
	Mat aveImg[MAX_RASIUS + STEP + 1];

	//Diff Image
	Mat diffImg[MAX_RASIUS + STEP + 1];

	//Calculate Diff Image
	for (int r = min_radius - STEP; r <= max_radius + STEP; r++)
	{
		Mat sumImg;
		sumImg.create(rows, cols, CV_16UC3);
		sumImg.setTo(0);

		int rows_start_table[360], rows_end_table[360], cols_start_table[360], cols_end_table[360];
		for (int theta = 0; theta < 360; theta++)
		{
			int theta_cos = r*cos(theta*3.1415 / 180);
			int theta_sin = r*sin(theta*3.1415 / 180);

			if (theta_sin > 0)
			{
				rows_start_table[theta] = theta_sin;
				rows_end_table[theta] = rows;
			}
			else
			{
				rows_start_table[theta] = 0;
				rows_end_table[theta] = rows + theta_sin;
			}

			if (theta_cos > 0)
			{
				cols_start_table[theta] = 0;
				cols_end_table[theta] = cols - theta_cos;

			}
			else
			{
				cols_start_table[theta] = -theta_cos;
				cols_end_table[theta] = cols;
			}
		}
		for (int theta = 0; theta < 180; theta++)
		{
			Mat subImg1, subImg2;
			subImg1 = originImg(Range(rows_start_table[theta], rows_end_table[theta]), Range(cols_start_table[theta], cols_end_table[theta]));
			subImg2 = sumImg(Range(rows - rows_end_table[theta], rows - rows_start_table[theta]), Range(cols - cols_end_table[theta], cols - cols_start_table[theta]));
			subImg2 = subImg1 + subImg2;
		}
		for (int theta = 180; theta < 360; theta++)
		{
			Mat subImg1, subImg2;
			subImg1 = originImg(Range(rows_start_table[theta], rows_end_table[theta]), Range(cols_start_table[theta], cols_end_table[theta]));
			subImg2 = sumImg(Range(rows - rows_end_table[theta], rows - rows_start_table[theta]), Range(cols - cols_end_table[theta], cols - cols_start_table[theta]));
			subImg2 = subImg1 + subImg2;
		}
		aveImg[r] = sumImg / 360;

		if (r >= min_radius + STEP)
		{
			int k = r - STEP;

			absdiff(aveImg[k - STEP], aveImg[k + STEP], diffImg[k]);
			vector<Mat> diffSplitedImg;
			split(diffImg[k], diffSplitedImg);
			diffImg[k] = (diffSplitedImg.at(0) + diffSplitedImg.at(1) + diffSplitedImg.at(2));
			diffImg[k] = diffImg[k] - diffThresholdImg * 3;

			aveImg[k - STEP].release();
		}
	}

	//Remove Same Ciecle
	for (int r = min_radius; r <= max_radius; r++)
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				uint16_t center_value = *((uint16_t*)diffImg[r].data + i*cols + j);
				if (center_value <= 0) continue;

				/***********************************************************/
				/*
				could be faster
				*/
				if (r > i || r > rows - i || r > j || r > cols - j) continue;
				/***********************************************************/

				int sub_r_start, sub_r_end;
				if (r - min_radius_dist >= min_radius) sub_r_start = r - min_radius_dist;
				else sub_r_start = min_radius;
				if (r + min_radius_dist <= max_radius) sub_r_end = r + min_radius_dist;
				else sub_r_end = max_radius;

				int sub_i_start, sub_i_end;
				if (i - min_center_dist >= 0) sub_i_start = i - min_center_dist;
				else sub_i_start = 0;
				if (i + min_center_dist <= rows) sub_i_end = i + min_center_dist;
				else sub_i_end = rows;

				int sub_j_start, sub_j_end;
				if (j - min_center_dist >= 0) sub_j_start = j - min_center_dist;
				else sub_j_start = 0;
				if (j + min_center_dist <= cols) sub_j_end = j + min_center_dist;
				else sub_j_end = cols;

				int flag = 0;

				//
				for (int sub_r = sub_r_start; sub_r <= sub_r_end; sub_r++)
				{
					for (int sub_i = sub_i_start; sub_i < sub_i_end; sub_i++)
					{
						for (int sub_j = sub_j_start; sub_j < sub_j_end; sub_j++)
						{
							uint16_t surround_value = *((uint16_t*)diffImg[sub_r].data + sub_i*cols + sub_j);
							if (surround_value > center_value) flag = 1;
							if (flag == 1)break;
						}
						if (flag == 1)break;
					}
					if (flag == 1)break;
				}

				//
				for (int p = 0; p < _circle_cnt; p++)
				{
					if (((j - x[p])*(j - x[p]) + (i - y[p])*(i - y[p])) < min_center_dist*min_center_dist && abs(radius[p] - r) < min_radius_dist)
					{
						if (center_value <= diff[p])
						{
							flag = 1;
							continue;
						}
					}
				}

				if (flag == 0)
				{
					x[_circle_cnt] = j;
					y[_circle_cnt] = i;
					radius[_circle_cnt] = r;
					diff[_circle_cnt] = center_value;
					_circle_cnt++;
				}

				if (_circle_cnt == max_circle)
				{
					*circle_cnt = _circle_cnt;
					return MY_OK;
				}
			}
		}
	}

	*circle_cnt = _circle_cnt;
	return MY_OK;
}
#endif // VERSION_5

#ifdef VERSION_4
/*
VERSION 4.0
Loop order r-theta-x-y
Based on opencv
Lossy optimization!!!
Same circle have removed, AT THE END
*/
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
	if (colorImg.data == NULL) return MY_FAIL;

	const int rows = colorImg.rows;
	const int cols = colorImg.cols;

	if (min_radius < MIN_RASIUS) return MY_FAIL;
	if (min_radius > max_radius) return MY_FAIL;
	if (max_radius > MAX_RASIUS) return MY_FAIL;

	if (max_circle <= 0) return MY_FAIL;

	int _circle_cnt = 0;
	int* diff = new int[max_circle];

	//Origin Image
	Mat originImg;
	colorImg.convertTo(originImg, CV_16UC3);
	originImg = originImg * 0.7;

	//Dot Image
	Mat dotImg;
	dotImg.create(rows, cols, CV_8UC1);
	dotImg.setTo(1);

	//Diff Threshold Image
	Mat diffThresholdImg;
	diffThresholdImg.create(rows, cols, CV_8UC1);
	diffThresholdImg.setTo(max_circle_diff);
	diffThresholdImg.convertTo(diffThresholdImg, CV_16UC1);
	//diffThresholdImg = diffThresholdImg * 3;

	//Average Image
	Mat aveImg[300];

	//Diff Image
	Mat diffImg[300];

	//Calculate Diff Image
	for (int r = min_radius - STEP; r <= max_radius + STEP; r++)
	{
		Mat sumImg;
		sumImg.create(rows, cols, CV_16UC3);
		sumImg.setTo(0);

		Mat numberImg;
		numberImg.create(rows, cols, CV_16UC3);
		numberImg.setTo(0);

		Mat numberImg1, numberImg2;
		numberImg1.create(rows, cols, CV_8UC1);
		numberImg2.create(rows, cols, CV_8UC1);
		numberImg1.setTo(0);
		numberImg2.setTo(0);

		int rows_start_table[360], rows_end_table[360], cols_start_table[360], cols_end_table[360];
		for (int theta = 0; theta < 360; theta++)
		{
			int theta_cos = r*cos(theta*3.1415 / 180);
			int theta_sin = r*sin(theta*3.1415 / 180);

			if (theta_sin > 0)
			{
				rows_start_table[theta] = theta_sin;
				rows_end_table[theta] = rows;
			}
			else
			{
				rows_start_table[theta] = 0;
				rows_end_table[theta] = rows + theta_sin;
			}

			if (theta_cos > 0)
			{
				cols_start_table[theta] = 0;
				cols_end_table[theta] = cols - theta_cos;

			}
			else
			{
				cols_start_table[theta] = -theta_cos;
				cols_end_table[theta] = cols;
			}
		}
		for (int theta = 0; theta < 180; theta++)
		{
			Mat subImg1, subImg2;
			subImg1 = originImg(Range(rows_start_table[theta], rows_end_table[theta]), Range(cols_start_table[theta], cols_end_table[theta]));
			subImg2 = sumImg(Range(rows - rows_end_table[theta], rows - rows_start_table[theta]), Range(cols - cols_end_table[theta], cols - cols_start_table[theta]));
			subImg2 = subImg1 + subImg2;

			subImg1 = dotImg(Range(rows_start_table[theta], rows_end_table[theta]), Range(cols_start_table[theta], cols_end_table[theta]));
			subImg2 = numberImg1(Range(rows - rows_end_table[theta], rows - rows_start_table[theta]), Range(cols - cols_end_table[theta], cols - cols_start_table[theta]));
			subImg2 = subImg1 + subImg2;
		}
		for (int theta = 180; theta < 360; theta++)
		{
			Mat subImg1, subImg2;
			subImg1 = originImg(Range(rows_start_table[theta], rows_end_table[theta]), Range(cols_start_table[theta], cols_end_table[theta]));
			subImg2 = sumImg(Range(rows - rows_end_table[theta], rows - rows_start_table[theta]), Range(cols - cols_end_table[theta], cols - cols_start_table[theta]));
			subImg2 = subImg1 + subImg2;

			subImg1 = dotImg(Range(rows_start_table[theta], rows_end_table[theta]), Range(cols_start_table[theta], cols_end_table[theta]));
			subImg2 = numberImg2(Range(rows - rows_end_table[theta], rows - rows_start_table[theta]), Range(cols - cols_end_table[theta], cols - cols_start_table[theta]));
			subImg2 = subImg1 + subImg2;
		}

		cvtColor(numberImg1, numberImg1, CV_GRAY2BGR);
		numberImg1.convertTo(numberImg1, sumImg.type());

		cvtColor(numberImg2, numberImg2, CV_GRAY2BGR);
		numberImg2.convertTo(numberImg2, sumImg.type());

		numberImg = numberImg1 + numberImg2;
		aveImg[r] = sumImg / numberImg * 1.43;

		if (r >= min_radius + STEP)
		{
			int k = r - STEP;

			diffImg[k] = (aveImg[k - STEP] - aveImg[k + STEP]) + (aveImg[k + STEP] - aveImg[k - STEP]);
			vector<Mat> diffSplitedImg;
			split(diffImg[k], diffSplitedImg);
			diffImg[k] = diffSplitedImg.at(0) + diffSplitedImg.at(1) + diffSplitedImg.at(2);
			diffImg[k] = diffImg[k] - diffThresholdImg * 3;

			aveImg[k - STEP].release();
		}
	}

	//Remove Same Ciecle
	for (int r = min_radius; r <= max_radius; r++)
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				uint16_t center_value = *((uint16_t*)diffImg[r].data + i*cols + j);
				if (center_value <= 0) continue;

				/***********************************************************/
				/*
				could be faster
				*/
				if (r > i || r > rows - i || r > j || r > cols - j) continue;
				/***********************************************************/

				int sub_r_start, sub_r_end;
				if (r - min_radius_dist >= min_radius) sub_r_start = r - min_radius_dist;
				else sub_r_start = min_radius;
				if (r + min_radius_dist <= max_radius) sub_r_end = r + min_radius_dist;
				else sub_r_end = max_radius;

				int sub_i_start, sub_i_end;
				if (i - min_center_dist >= 0) sub_i_start = i - min_center_dist;
				else sub_i_start = 0;
				if (i + min_center_dist <= rows) sub_i_end = i + min_center_dist;
				else sub_i_end = rows;

				int sub_j_start, sub_j_end;
				if (j - min_center_dist >= 0) sub_j_start = j - min_center_dist;
				else sub_j_start = 0;
				if (j + min_center_dist <= cols) sub_j_end = j + min_center_dist;
				else sub_j_end = cols;

				int flag = 0;

				//
				for (int sub_r = sub_r_start; sub_r <= sub_r_end; sub_r++)
				{
					for (int sub_i = sub_i_start; sub_i < sub_i_end; sub_i++)
					{
						for (int sub_j = sub_j_start; sub_j < sub_j_end; sub_j++)
						{
							uint16_t surround_value = *((uint16_t*)diffImg[sub_r].data + sub_i*cols + sub_j);
							if (surround_value > center_value) flag = 1;
						}
					}
				}

				//
				for (int p = 0; p < _circle_cnt; p++)
				{
					if (((j - x[p])*(j - x[p]) + (i - y[p])*(i - y[p])) < min_center_dist*min_center_dist && abs(radius[p] - r) < min_radius_dist)
					{
						if (center_value <= diff[p])
						{
							flag = 1;
							continue;
						}
					}
				}

				if (flag == 0)
				{
					x[_circle_cnt] = j;
					y[_circle_cnt] = i;
					radius[_circle_cnt] = r;
					diff[_circle_cnt] = center_value;
					_circle_cnt++;
				}

				if (_circle_cnt == max_circle)
				{
					*circle_cnt = _circle_cnt;
					return MY_OK;
				}
			}
		}
	}

	*circle_cnt = _circle_cnt;
	return MY_OK;
}
#endif // VERSION_4

#ifdef VERSION_3
/*
VERSION 3.0
Loop order r-theta-x-y
Based on opencv
Not optimized
Same circle have removed, Perfect
*/
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
	if (colorImg.data == NULL) return MY_FAIL;

	const int rows = colorImg.rows;
	const int cols = colorImg.cols;

	if (min_radius < MIN_RASIUS) return MY_FAIL;
	if (min_radius > max_radius) return MY_FAIL;
	if (max_radius > MAX_RASIUS) return MY_FAIL;

	if (max_circle <= 0) return MY_FAIL;

	int _circle_cnt = 0;
	int* diff = new int[max_circle];

	//Mat edgeImg;
	//Canny(colorImg, edgeImg, 70, 140);

	//Origin Image
	Mat originImg;
	colorImg.convertTo(originImg, CV_16UC3);

	//Dot Image
	Mat dotImg;
	dotImg.create(rows, cols, CV_8UC1);
	dotImg.setTo(1);

	//Diff Threshold Image
	Mat diffThresholdImg;
	diffThresholdImg.create(rows, cols, CV_8UC1);
	diffThresholdImg.setTo(max_circle_diff / 2);
	diffThresholdImg.convertTo(diffThresholdImg, CV_16UC1);

	//Average Image
	Mat aveImg[300];

	//Diff Image
	Mat diffImg[300];

	//Calculate Diff Image
	for (int r = min_radius - STEP; r <= max_radius + STEP; r++)
	{
		Mat sumImg1, sumImg2;
		sumImg1.create(rows, cols, CV_16UC3);
		sumImg2.create(rows, cols, CV_16UC3);
		sumImg1.setTo(0);
		sumImg2.setTo(0);

		Mat numberImg;
		numberImg.create(rows, cols, CV_16UC3);
		numberImg.setTo(0);

		Mat numberImg1, numberImg2;
		numberImg1.create(rows, cols, CV_8UC1);
		numberImg2.create(rows, cols, CV_8UC1);
		numberImg1.setTo(0);
		numberImg2.setTo(0);

		int rows_start_table[360], rows_end_table[360], cols_start_table[360], cols_end_table[360];
		for (int theta = 0; theta < 360; theta++)
		{
			int theta_cos = r*cos(theta*3.1415 / 180);
			int theta_sin = r*sin(theta*3.1415 / 180);

			if (theta_sin > 0)
			{
				rows_start_table[theta] = theta_sin;
				rows_end_table[theta] = rows;
			}
			else
			{
				rows_start_table[theta] = 0;
				rows_end_table[theta] = rows + theta_sin;
			}

			if (theta_cos > 0)
			{
				cols_start_table[theta] = 0;
				cols_end_table[theta] = cols - theta_cos;

			}
			else
			{
				cols_start_table[theta] = -theta_cos;
				cols_end_table[theta] = cols;
			}
		}
		for (int theta = 0; theta < 180; theta++)
		{
			Mat subImg1, subImg2;
			subImg1 = originImg(Range(rows_start_table[theta], rows_end_table[theta]), Range(cols_start_table[theta], cols_end_table[theta]));
			subImg2 = sumImg1(Range(rows - rows_end_table[theta], rows - rows_start_table[theta]), Range(cols - cols_end_table[theta], cols - cols_start_table[theta]));
			subImg2 = subImg1 + subImg2;

			subImg1 = dotImg(Range(rows_start_table[theta], rows_end_table[theta]), Range(cols_start_table[theta], cols_end_table[theta]));
			subImg2 = numberImg1(Range(rows - rows_end_table[theta], rows - rows_start_table[theta]), Range(cols - cols_end_table[theta], cols - cols_start_table[theta]));
			subImg2 = subImg1 + subImg2;
		}
		for (int theta = 180; theta < 360; theta++)
		{
			Mat subImg1, subImg2;
			subImg1 = originImg(Range(rows_start_table[theta], rows_end_table[theta]), Range(cols_start_table[theta], cols_end_table[theta]));
			subImg2 = sumImg2(Range(rows - rows_end_table[theta], rows - rows_start_table[theta]), Range(cols - cols_end_table[theta], cols - cols_start_table[theta]));
			subImg2 = subImg1 + subImg2;

			subImg1 = dotImg(Range(rows_start_table[theta], rows_end_table[theta]), Range(cols_start_table[theta], cols_end_table[theta]));
			subImg2 = numberImg2(Range(rows - rows_end_table[theta], rows - rows_start_table[theta]), Range(cols - cols_end_table[theta], cols - cols_start_table[theta]));
			subImg2 = subImg1 + subImg2;
		}

		cvtColor(numberImg1, numberImg1, CV_GRAY2BGR);
		numberImg1.convertTo(numberImg1, sumImg1.type());

		cvtColor(numberImg2, numberImg2, CV_GRAY2BGR);
		numberImg2.convertTo(numberImg2, sumImg2.type());

		numberImg = numberImg1 + numberImg2;
		aveImg[r] = (sumImg1*0.5 + sumImg2*0.5) / numberImg;

		if (r >= min_radius + STEP)
		{
			int k = r - STEP;

			diffImg[k] = (aveImg[k - STEP] - aveImg[k + STEP]) + (aveImg[k + STEP] - aveImg[k - STEP]);
			vector<Mat> diffSplitedImg;
			split(diffImg[k], diffSplitedImg);
			diffImg[k] = diffSplitedImg.at(0) + diffSplitedImg.at(1) + diffSplitedImg.at(2);
			diffImg[k] = diffImg[k] - diffThresholdImg * 3;

			aveImg[k - STEP].release();
		}
	}

	//Remove Same Ciecle
	for (int r = min_radius; r <= max_radius; r++)
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				uint16_t center_value = *((uint16_t*)diffImg[r].data + i*cols + j);
				if (center_value <= 0) continue;

				/***********************************************************/
				/*
					could be faster
				*/
				if (r > i || r > rows - i || r > j || r > cols - j) continue;
				/***********************************************************/

				int sub_r_start, sub_r_end;
				if (r - min_radius_dist >= min_radius) sub_r_start = r - min_radius_dist;
				else sub_r_start = min_radius;
				if (r + min_radius_dist <= max_radius) sub_r_end = r + min_radius_dist;
				else sub_r_end = max_radius;

				int sub_i_start, sub_i_end;
				if (i - min_center_dist >= 0) sub_i_start = i - min_center_dist;
				else sub_i_start = 0;
				if (i + min_center_dist <= rows) sub_i_end = i + min_center_dist;
				else sub_i_end = rows;

				int sub_j_start, sub_j_end;
				if (j - min_center_dist >= 0) sub_j_start = j - min_center_dist;
				else sub_j_start = 0;
				if (j + min_center_dist <= cols) sub_j_end = j + min_center_dist;
				else sub_j_end = cols;

				int flag = 0;

				//
				for (int sub_r = sub_r_start; sub_r <= sub_r_end; sub_r++)
				{
					for (int sub_i = sub_i_start; sub_i < sub_i_end; sub_i++)
					{
						for (int sub_j = sub_j_start; sub_j < sub_j_end; sub_j++)
						{
							uint16_t surround_value = *((uint16_t*)diffImg[sub_r].data + sub_i*cols + sub_j);
							if (surround_value > center_value) flag = 1;
						}
					}
				}

				//
				for (int p = 0; p < _circle_cnt; p++)
				{
					if (((j - x[p])*(j - x[p]) + (i - y[p])*(i - y[p])) < min_center_dist*min_center_dist && abs(radius[p] - r) < min_radius_dist)
					{
						if (center_value  <= diff[p])
						{
							flag = 1;
							continue;
						}
					}
				}

				if (flag == 0)
				{
					x[_circle_cnt] = j;
					y[_circle_cnt] = i;
					radius[_circle_cnt] = r;
					diff[_circle_cnt] = center_value;
					_circle_cnt++;
				}

				if (_circle_cnt == max_circle)
				{
					*circle_cnt = _circle_cnt;
					return MY_OK;
				}
			}
		}
	}

	*circle_cnt = _circle_cnt;
	return MY_OK;
}

#endif // VERSION_3

#ifdef VERSION_2
/*
VERSION 2.2
Loop order r-theta-x-y 
Based on opencv
Not optimized
Same circle have removed, Not perfect
*/
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
	if (colorImg.data == NULL) return MY_FAIL;

	const int rows = colorImg.rows;
	const int cols = colorImg.cols;

	if (min_radius < MIN_RASIUS) return MY_FAIL;
	if (min_radius > max_radius) return MY_FAIL;
	if (max_radius > MAX_RASIUS) return MY_FAIL;

	if (max_circle <= 0) return MY_FAIL;

	int* diff = new int[max_circle];
	int _circle_cnt = 0;

	//Mat edgeImg;
	//Canny(colorImg, edgeImg, 70, 140);

	//Dot Image
	Mat dotImg;
	dotImg.create(rows, cols, CV_8UC1);
	dotImg.setTo(1);

	//Diff Threshold Image
	Mat diffThresholdImg;
	diffThresholdImg.create(rows, cols, CV_8UC3);
	diffThresholdImg.setTo(max_circle_diff / 2);
	diffThresholdImg.convertTo(diffThresholdImg, CV_16UC3);

	//Average Image
	Mat aveImg[300];

	for (int r = min_radius - STEP; r <= max_radius + STEP; r++)
	{
		Mat sumImg1, sumImg2;
		sumImg1.create(rows, cols, CV_16UC3);
		sumImg2.create(rows, cols, CV_16UC3);
		sumImg1.setTo(0);
		sumImg2.setTo(0);

		Mat numberImg;
		numberImg.create(rows, cols, CV_16UC3);
		numberImg.setTo(0);

		Mat numberImg1, numberImg2;
		numberImg1.create(rows, cols, CV_8UC1);
		numberImg2.create(rows, cols, CV_8UC1);
		numberImg1.setTo(0);
		numberImg2.setTo(0);

		int rows_start_table[360], rows_end_table[360], cols_start_table[360], cols_end_table[360];
		for (int theta = 0; theta < 360; theta++)
		{
			int theta_cos = r*cos(theta*3.1415 / 180);
			int theta_sin = r*sin(theta*3.1415 / 180);

			if (theta_sin > 0)
			{
				rows_start_table[theta] = theta_sin;
				rows_end_table[theta] = rows;
			}
			else
			{
				rows_start_table[theta] = 0;
				rows_end_table[theta] = rows + theta_sin;
			}

			if (theta_cos > 0)
			{
				cols_start_table[theta] = 0;
				cols_end_table[theta] = cols - theta_cos;

			}
			else
			{
				cols_start_table[theta] = -theta_cos;
				cols_end_table[theta] = cols;
			}
		}
		for (int theta = 0; theta < 180; theta++)
		{
			Mat subImg1, subImg2;
			subImg1 = colorImg(Range(rows_start_table[theta], rows_end_table[theta]), Range(cols_start_table[theta], cols_end_table[theta]));
			subImg2 = sumImg1(Range(rows - rows_end_table[theta], rows - rows_start_table[theta]), Range(cols - cols_end_table[theta], cols - cols_start_table[theta]));
			subImg1.convertTo(subImg1, sumImg1.type(), 1, 0);
			subImg2 = subImg1 + subImg2;

			subImg1 = dotImg(Range(rows_start_table[theta], rows_end_table[theta]), Range(cols_start_table[theta], cols_end_table[theta]));
			subImg2 = numberImg1(Range(rows - rows_end_table[theta], rows - rows_start_table[theta]), Range(cols - cols_end_table[theta], cols - cols_start_table[theta]));
			subImg1.convertTo(subImg1, numberImg1.type(), 1, 0);
			subImg2 = subImg1 + subImg2;
		}
		for (int theta = 180; theta < 360; theta++)
		{
			Mat subImg1, subImg2;
			subImg1 = colorImg(Range(rows_start_table[theta], rows_end_table[theta]), Range(cols_start_table[theta], cols_end_table[theta]));
			subImg2 = sumImg2(Range(rows - rows_end_table[theta], rows - rows_start_table[theta]), Range(cols - cols_end_table[theta], cols - cols_start_table[theta]));
			subImg1.convertTo(subImg1, sumImg2.type(), 1, 0);
			subImg2 = subImg1 + subImg2;

			subImg1 = dotImg(Range(rows_start_table[theta], rows_end_table[theta]), Range(cols_start_table[theta], cols_end_table[theta]));
			subImg2 = numberImg2(Range(rows - rows_end_table[theta], rows - rows_start_table[theta]), Range(cols - cols_end_table[theta], cols - cols_start_table[theta]));
			subImg1.convertTo(subImg1, numberImg2.type(), 1, 0);
			subImg2 = subImg1 + subImg2;
		}

		cvtColor(numberImg1, numberImg1, CV_GRAY2BGR);
		numberImg1.convertTo(numberImg1, sumImg1.type());

		cvtColor(numberImg2, numberImg2, CV_GRAY2BGR);
		numberImg2.convertTo(numberImg2, sumImg2.type());

		numberImg = numberImg1 + numberImg2;
		aveImg[r] = (sumImg1*0.5 + sumImg2*0.5)/ numberImg;

		if (r >= min_radius + STEP)
		{
			int k = r - STEP;

			Mat diffImg;
			diffImg = (aveImg[k - STEP] - aveImg[k + STEP]) + (aveImg[k + STEP] - aveImg[k - STEP]);
			diffImg = diffImg - diffThresholdImg;
			for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < cols; j++)
				{
					short* pos = (short*)diffImg.data + i * cols * 3 + j * 3;

					/*
						Not a good mix way
					*/
					int diffB = *pos;
					int diffG = *(pos + 1);
					int diffR = *(pos + 2);
					int d = diffB;
					if (d < diffG) d = diffG;
					if (d < diffR) d = diffR;

					if (d > 0)
					{
						int flag = 0;
						for (int p = 0; p < _circle_cnt; p++)
						{
							if (((j - x[p])*(j - x[p]) + (i - y[p])*(i - y[p])) < min_center_dist*min_center_dist && abs(radius[p] - k) < min_radius_dist)
							{
								if (d <= diff[p])
								{
									flag = 1;
									continue;
								}
								else
								{
									for (int q = p + 1; q < _circle_cnt; q++)
									{
										x[q - 1] = x[q];
										y[q - 1] = y[q];
										radius[q - 1] = radius[q];
										diff[q - 1] = diff[q];
									}
									_circle_cnt--;
								}
							}
						}
						if (flag == 0)
						{
							x[_circle_cnt] = j;
							y[_circle_cnt] = i;
							radius[_circle_cnt] =k;
							diff[_circle_cnt] = d;
							_circle_cnt++;
						}
					}

					if (_circle_cnt == max_circle)
					{
						*circle_cnt = _circle_cnt;
						return MY_OK;
					}
				}
			}
		}
	}

	*circle_cnt = _circle_cnt;
	return MY_OK;
}

#endif // VERSION_2

#ifdef VERSION_1
/*
VERSION 1.0
Loop order x-y-r-theta
Not optimized
Same circle removed, Not perfect
*/
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
	int* len,
	int max_circle)
{
	if (colorImg.data == NULL) return MY_FAIL;
	//if (colorImg.channels != 3) return MY_FAIL;

	if (min_radius < MIN_RASIUS) return MY_FAIL;
	if (min_radius > max_radius) return MY_FAIL;
	if (max_radius > MAX_RASIUS) return MY_FAIL;

	const int rows = colorImg.rows;
	const int cols = colorImg.cols;
	const uchar* data = colorImg.data;

	Mat edgeImg;
	Canny(colorImg, edgeImg, 70, 140);

	int* diff = new int[MAX_CIRCLE_NUMBER];
	int _len = 0;

	int* bSum = new int[MAX_RASIUS + 10];
	int* gSum = new int[MAX_RASIUS + 10];
	int* rSum = new int[MAX_RASIUS + 10];
	int* number = new int[MAX_RASIUS + 10];

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			memset(bSum, 0, sizeof(int)*MAX_RASIUS + 10);
			memset(gSum, 0, sizeof(int)*MAX_RASIUS + 10);
			memset(rSum, 0, sizeof(int)*MAX_RASIUS + 10);
			memset(number, 0, sizeof(int)*MAX_RASIUS + 10);
			for (int r = min_radius - 5; r <= max_radius + 5; r++)
			{
				for (int theta = 0; theta < 360; theta++)
				{
					int subx = i + r*cos(theta*3.1415 / 180);
					int suby = j + r*sin(theta*3.1415 / 180);
					int pos;

					if (subx < 0 || subx >= rows) continue;
					if (suby < 0 || suby >= cols) continue;

					pos = subx*cols + suby;
					//if (*(edgeImg.data + pos) == 0) continue;

					//if (*(edgeImg.data + pos) == 0) continue;
					//number[r] = number[r] + 1;
					//bSum[r] = bSum[r] + *(edgeImg.data + pos);
					//gSum[r] = gSum[r] + *(edgeImg.data + pos);
					//rSum[r] = rSum[r] + *(edgeImg.data + pos);

					number[r] = number[r] + 1;
					bSum[r] = bSum[r] + *(colorImg.data + pos * 3);
					gSum[r] = gSum[r] + *(colorImg.data + pos * 3 + 1);
					rSum[r] = rSum[r] + *(colorImg.data + pos * 3 + 2);
				}
			}
			for (int k = min_radius; k <= max_radius; k++)
			{
				if (number[k - 5] > 90 && number[k + 5] > 90)
				{
					int d = abs(bSum[k - 5] / number[k - 5] - bSum[k + 5] / number[k + 5])
						+ abs(gSum[k - 5] / number[k - 5] - gSum[k + 5] / number[k + 5])
						+ abs(rSum[k - 5] / number[k - 5] - rSum[k + 5] / number[k + 5]);
					if (d > max_circle_diff * 3)
					{
						int flag = 0;
						for (int p = 0; p < _len; p++)
						{
							if (((j - x[p])*(j - x[p]) + (i - y[p])*(i - y[p])) < min_center_dist*min_center_dist && abs(radius[p] - k) < min_radius_dist)
							{
								if (d <= diff[p])
								{
									flag = 1;
									continue;
								}
								else
								{
									for (int q = p + 1; q < _len; q++)
									{
										x[q - 1] = x[q];
										y[q - 1] = y[q];
										radius[q - 1] = radius[q];
										diff[q - 1] = diff[q];
									}
									_len--;
								}
							}
						}
						if (flag == 0)
						{
							x[_len] = j;
							y[_len] = i;
							radius[_len] = k;
							diff[_len] = d;
							_len++;
						}

						//x[_len] = j;
						//y[_len] = i;
						//radius[_len] = k;
						//diff[_len] = d;
						//_len++;
					}
				}
				if (_len == MAX_CIRCLE_NUMBER - 1)
				{
					*len = _len;
					return 100;
				}
			}
		}
	}

	*len = _len;
	return MY_OK;
}
#endif // VERSION_1
