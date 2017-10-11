#include "SubImageMatch.h"
float FindMax(float x, float y, float z)
//find  the largest number in x,y,z
{
	float para;
	if (x > y) para = x;
	else para = y;
	if (para > z) return para;
	else return z;
}

int exclude(int i, int j, int r, int* x, int* y, int* radius, int* len, int min_center_dist, int min_radius_dist)
//to exclude some similar circle 
{
	 
	if (abs(i - x[(*len)-1]) < min_center_dist || abs(j - y[(*len)-1]) < min_center_dist)
	{
		 
		if (abs(radius[(*len)-1] - r) < min_radius_dist) return 0;
		else return 1;
	}
	else if (abs(radius[(*len)-1] - r) < min_radius_dist)
	{
		 
		if (abs(i - x[(*len)-1]) < min_center_dist || abs(j - y[(*len)-1]) < min_center_dist) return 0;
		else return 1;
	}
	else return 1;
}

int ustc_Find_Circles_By_Difference(Mat colorImg, int min_radius, int max_radius, int min_center_dist, int min_radius_dist, int max_circle_diff, int* x, int* y, int* radius, int* len)
{
	if (NULL == colorImg.data)
	{
		cout << "image is NULL." << endl;
		return MY_FAIL;
	}

	int width = colorImg.cols;
	int height = colorImg.rows;
	 
	 
	 
	float sin_0to360[360];
	float cos_0to360[360];

	for (int i = 0; i < 360; i++)
	{
		float rad = (i*3.14) / 180;
		sin_0to360[i] = sin(rad);
		cos_0to360[i] = cos(rad);
		 
	}
	
	for (int r = min_radius; r < max_radius; r++ )
	{
		for (int i= r; i < width - r; i++)
		{
			for (int j = r; j < height - r; j++)
			{
				int sum_bigcircle_B = 0;
				int sum_bigcircle_G = 0;
				int sum_bigcircle_R = 0;
				int bigcircle_flag = 0;
				int smallcircle_flag = 0;
				 

				//count the average brightness of the bigger circle
				for (int theta = 0; theta < 360; theta++)
				{
					int m = i + (r + 5)*cos_0to360[theta];
					int n= j + (r + 5)*sin_0to360[theta];
					 
					
					if (m >= 0 && n >= 0 && m < width && n < height)
					{
						int seq = 3 * (n*width + m);

						sum_bigcircle_B += colorImg.data[seq];
						sum_bigcircle_G += colorImg.data[seq + 1];
						sum_bigcircle_R += colorImg.data[seq + 2];
						bigcircle_flag++;
					}
				}
				float average_bigcircle_B = ((float)sum_bigcircle_B) / bigcircle_flag;
				float average_bigcircle_G = ((float)sum_bigcircle_G) / bigcircle_flag;
				float average_bigcircle_R = ((float)sum_bigcircle_R) / bigcircle_flag;

				int sum_smallcircle_B = 0;
				int sum_smallcircle_G = 0;
				int sum_smallcircle_R = 0;
				
				//count the average brightness of the smaller circle
				for (int theta = 0; theta < 360; theta++)
				{
					int m = i + (r - 5)*cos_0to360[theta];
					int n = j + (r - 5)*sin_0to360[theta];
					 
					if (m >= 0 && n >= 0 && m < width&&n < height)
					{
						int seq = 3 * (n*width + m);
						sum_smallcircle_B += colorImg.data[seq];
						sum_smallcircle_G += colorImg.data[seq + 1];
						sum_smallcircle_R += colorImg.data[seq + 2];
						smallcircle_flag++;
					}
					
				}
				float average_smallcircle_B = ((float)sum_smallcircle_B) / smallcircle_flag;
				float average_smallcircle_G = ((float)sum_smallcircle_G) / smallcircle_flag;
				float average_smallcircle_R = ((float)sum_smallcircle_R) / smallcircle_flag;

				float circle_diff_B = abs(average_bigcircle_B - average_smallcircle_B);
				float circle_diff_G = abs(average_bigcircle_G - average_smallcircle_G);
				float circle_diff_R = abs(average_bigcircle_R - average_smallcircle_R);
				
				//to judge whether this point is the center of a circle
				float circle_diff = FindMax(circle_diff_B, circle_diff_G, circle_diff_R);
				
				if (circle_diff > max_circle_diff)
				{
					if (*len > 0)
					{
						if (exclude(i, j, r, x, y, radius, len,min_center_dist,min_radius))
						{ 
							x[*len] = i;
							y[*len] = j;
							radius[*len] = r;
							(*len)++;
						}
					}
					else
					{
						x[*len] = i;
						y[*len] = j;
						radius[*len] = r;
						(*len)++;
					}
				}	 
			}	 
		}
		//printf("r=%d\n", r);
	}
	printf("\n\n");
	for (int i = 0; i < *len; i++)
		printf("x=%d,y=%d,r=%d\n",x[i],y[i],radius[i]);
	printf("%d", *len);
	waitKey();
		
}
