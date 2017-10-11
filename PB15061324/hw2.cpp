#include<opencv2/opencv.hpp>
using namespace cv;
#define MY_FAIL -1
#define MY_DONE 1
#define MY_PI 3.14159f
int mysin2[] = { 0	,17	,35	,53	,71	,89	,107	,124	,142	,
160	,177	,195	,212	,230	,247	,265	,282	,299	,316	,333	,350	,
366	,383	,400	,416	,432	,448	,464	,480	,496	,512	,527	,542	,
557	,572	,587	,601	,616	,630	,644	,658	,671	,685	,698	,711	,
724	,736	,748	,760	,772	,784	,795	,806	,817	,828	,838	,848	,
858	,868	,877	,886	,895	,904	,912	,920	,928	,935	,942	,949	,
955	,962	,968	,973	,979	,984	,989	,993	,997	,1001	,1005	,
1008	,1011	,1014	,1016	,1018	,1020	,1021	,1022	,
1023	,1023	,1024	
};
int mycos2[] = { 1024	,1023	,1023	,1022	,1021	,1020	,
1018	,1016	,1014	,1011	,1008	,1005	,1001	,997	,993	,
989	,984	,979	,973	,968	,962	,955	,949	,942	,935	,928	,920	,
912	,904	,895	,886	,877	,868	,858	,848	,838	,828	,817	,806	,
795	,784	,772	,760	,748	,736	,724	,711	,698	,685	,671	,658	,
644	,630	,616	,601	,587	,572	,557	,542	,527	,512	,496	,480	,
464	,448	,432	,416	,400	,383	,366	,350	,333	,316	,299	,282	,
265	,247	,230	,212	,195	,177	,160	,142	,124	,107	,89	,71	,
53	,35	,17	,0
};
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
	int i, j;
	int r;
	int theta;
	int row = colorImg.rows;
	int col = colorImg.cols;
	int count = 0;
	int xtemp[50000] = { 0 }, ytemp[50000] = { 0 }, rtemp[50000] = { 0 }, diff[50000] = { 0 };
	if (NULL == colorImg.data)
	{
		printf("error\n");
		return MY_FAIL;
	}

	Mat tempdata;
	tempdata.create(row, col, CV_32SC1);

	Mat singleChannel[3];
	split(colorImg, singleChannel);

	int out_r_y, out_r_x, in_r_y, in_r_x;
	int out_y_up, in_y_up, out_y_down,in_y_down,index;
	int total_circle_diff = 356 * max_circle_diff;

	for (int channel = 0; channel < 3; channel++)
	{
		Mat singleChannel_INT;
		singleChannel[channel].convertTo(singleChannel_INT,CV_32SC1);
		int* data = (int*)singleChannel_INT.data;
		for (r = min_radius; r <= max_radius; r++)
		{
			int out_r = r + 5;
			int in_r = r - 5;
			tempdata.setTo(0);
			int* temp = (int *)tempdata.data;
			for (theta = 1; theta < 90; theta++)
			{
				out_r_y = (out_r*mysin2[theta]) >>10;
				out_r_x = (out_r*mycos2[theta]) >>10;
				in_r_y = (in_r*mysin2[theta]) >>10;
				in_r_x = (in_r*mycos2[theta]) >>10;

				for (i = out_r; i < row- out_r; i++)
				{
					out_y_up = col*(i - out_r_y);
					in_y_up = col*(i - in_r_y);
					out_y_down = col*(i + out_r_y);
					in_y_down = col*(i + in_r_y);
					int divide = (col - out_r - out_r) / 8;
					index = col*i;
					for (int d = 0; d < divide; d++)
					{
						j = out_r + (d << 3);
						__m256i l1 = _mm256_loadu_si256((__m256i*)(&data[out_y_up + j - out_r_x]));
						__m256i l2 = _mm256_loadu_si256((__m256i*)(&data[out_y_up + j + out_r_x]));
						__m256i l3 = _mm256_loadu_si256((__m256i*)(&temp[index + j]));

						l3 = _mm256_add_epi32(l3, _mm256_add_epi32(l1,l2));

						l1 = _mm256_loadu_si256((__m256i*)(&data[in_y_up + j - in_r_x]));
						l2 = _mm256_loadu_si256((__m256i*)(&data[in_y_up + j + in_r_x]));
						l3 = _mm256_sub_epi32(l3, _mm256_add_epi32(l1, l2));

						l1 = _mm256_loadu_si256((__m256i*)(&data[out_y_down + j - out_r_x]));
						l2 = _mm256_loadu_si256((__m256i*)(&data[out_y_down + j + out_r_x]));
						l3 = _mm256_add_epi32(l3, _mm256_add_epi32(l1, l2));

						l1 = _mm256_loadu_si256((__m256i*)(&data[in_y_down + j - in_r_x]));
						l2 = _mm256_loadu_si256((__m256i*)(&data[in_y_down + j + in_r_x]));
						l3 = _mm256_sub_epi32(l3, _mm256_add_epi32(l1, l2));

						_mm256_storeu_si256((__m256i*)(&temp[index + j]), l3);
					}
					for (j = out_r+divide*8, index = col*i + j; j < col - out_r; j++, index++)
					{
						temp[index] += data[out_y_up + j - out_r_x] - data[in_y_up + j - in_r_x]
								+ data[out_y_up + j + out_r_x] - data[in_y_up + j + in_r_x];
						temp[index] += data[out_y_down + j - out_r_x] - data[in_y_down + j - in_r_x]
								+ data[out_y_down + j + out_r_x] - data[in_y_down + j + in_r_x];
					}
				}
			}
			for (i = out_r; i < row - out_r; i++)
			{
				for (j = out_r; j < col-out_r; j++)
				{
					index = col*i + j;
					if (abs(temp[index]) >= total_circle_diff)
					{
						xtemp[count] = j;
						ytemp[count] = i;
						rtemp[count] = r;
						diff[count] = temp[index];
						count++;
					}
				}
			}
		}
	}
	    int finalcnt = count;
		for (i = 0; i <count-1 ; i++)
		{
			for (j = i+1; j <count; j++)
			{
				float dist = sqrt((xtemp[i] - xtemp[j])*(xtemp[i] - xtemp[j]) + (ytemp[i] - ytemp[j])*(ytemp[i] - ytemp[j]));
				if(rtemp[i]!=0 && rtemp[j]!=0)
				    if (dist< min_center_dist && abs(rtemp[i] - rtemp[j]) < min_radius_dist)
				    {
					    if (diff[i] > diff[j])
						    rtemp[j] = 0;
					    else
						    rtemp[i] = 0;
						finalcnt --;
				    }
			}
		}

		if (finalcnt <= max_circle)
		{
			finalcnt = 0;
			for (i = 0; i < count ; i++)
			{
				if (rtemp[i] != 0)
				{
					x[finalcnt] = xtemp[i];
					y[finalcnt] = ytemp[i];
					radius[finalcnt] = rtemp[i];
					finalcnt++;
				}
			}
		}
		else
		{
			finalcnt = 0;
				for (i = 0; i < count - 1; i++)
				{
					int max = i;
					if (rtemp[i] != 0)
					{
						for (j = i + 1; j < count; j++)
						{
							if (rtemp[max] < rtemp[j])
								max = j;
						}
						x[finalcnt] = xtemp[max];
						y[finalcnt] = ytemp[max];
						radius[finalcnt] = rtemp[max];
						rtemp[max] = rtemp[i];
						xtemp[max] = xtemp[i];
						ytemp[max] = ytemp[i];
						finalcnt++;
					}
					if (finalcnt == max_circle) break;
				}
		}
	*circle_cnt = finalcnt;
	return MY_DONE;
}
