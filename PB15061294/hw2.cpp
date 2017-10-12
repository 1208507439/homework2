#include<opencv2\opencv.hpp>
#include<cv.h>
#include<time.h>
#include<math.h>
using namespace cv;
using namespace std;
float sinvalue[360];
float cosvalue[360];
int x_coordinates[280][360];
int y_coordinates[280][360];
int effective_theta_number[280];



int create_functionvalue(float* sinvalue, float* cosvalue)
{
	if (NULL == sinvalue || NULL == cosvalue)
	{
		cout << "the array is NULL" << endl;
		return 0;
	}
	float referencevalue[91] = { 0.0000,0.0175,0.0349,0.0523,0.0698,0.0872,0.1045,0.1219,0.1392,0.1564,
		0.1736,0.1908,0.2079,0.2250,0.2419,0.2588,0.2756,0.2924,0.3090,0.3256,
		0.3420,0.3584,0.3746,0.3907,0.4067,0.4226,0.4384,0.4540,0.4695,0.4848,
		0.5000,0.5150,0.5299,0.5446,0.5592,0.5736,0.5878,0.6018,0.6157,0.6293,
		0.6428,0.6561,0.6691,0.6820,0.6947,0.7071,0.7193,0.7314,0.7431,0.7547,
		0.7660,0.7771,0.7880,0.7986,0.8090,0.8192,0.8290,0.8387,0.8480,0.8572,
		0.8660,0.8746,0.8829,0.8910,0.8988,0.9063,0.9135,0.9205,0.9272,0.9336,
		0.9397,0.9455,0.9511,0.9563,0.9613,0.9659,0.9703,0.9744,0.9781,0.9816,
		0.9848,0.9877,0.9903,0.9925,0.9945,0.9962,0.9976,0.9986,0.9994,0.9998,
		1.0000 };
	for (int i = 0;i < 90;i++)
	{
		sinvalue[i] = referencevalue[i];
		cosvalue[i] = referencevalue[90 - i];
	}
	for (int i = 90;i < 180;i++)

	{
		sinvalue[i] = referencevalue[180 - i];
		cosvalue[i] = 0 - referencevalue[i - 90];
	}
	for (int i = 180;i < 270;i++)
	{
		sinvalue[i] = 0 - referencevalue[i - 180];
		cosvalue[i] = 0 - referencevalue[270 - i];
	}
	for (int i = 270;i < 360;i++)
	{
		sinvalue[i] = 0 - referencevalue[360 - i];
		cosvalue[i] = referencevalue[i - 270];
	}
	return 0;
}

int create_coordinatesvalue(int x_coordinates[][360], int y_coordinates[][360], int effective_theta_number[],int min_radius, int max_radius, int min_radius_dist)
{
	if (NULL == x_coordinates || NULL == y_coordinates)
	{
		cout << "the array is NULL" << endl;
		return 0;
	}
	int radius_lowerbound = min_radius - min_radius_dist;
	int radius_upperbound = max_radius + min_radius_dist;
	int length = 0;
	for (int r = radius_lowerbound;r <= radius_upperbound;r++)
	{
		for (int theta = 0;theta < 360;theta++)
		{
			x_coordinates[r - radius_lowerbound][length] = r*cosvalue[theta];
			y_coordinates[r - radius_lowerbound][length] = r*sinvalue[theta];
			length++;
			while (r*cosvalue[theta] == r*cosvalue[theta + 1] && r*sinvalue[theta] == r*sinvalue[theta + 1])
			{
				theta++;
			}
		}
		effective_theta_number[r - radius_lowerbound] = length;
		length = 0;
	}



	return 0;
}




int averagepixvalue(Mat colorImg, int i, int j, int radius,int sequence,int radius_lowerbound)
{
	int height = colorImg.rows;
	int width = colorImg.cols;
	int sum = 0;
	int radius_index = radius - radius_lowerbound;
	int theta_index = effective_theta_number[radius_index];
	for (int theta = 0;theta < theta_index;theta++)
	{
		int x =x_coordinates[radius_index][theta] + i;
		int y =y_coordinates[radius_index][theta] + j;
		int pixvalue = colorImg.data[3 * (x*width + y) + sequence];
	    sum += pixvalue;
	}
	int average = sum / theta_index;
	return average;
	
		
	}
	

int ustc_Find_Circles_By_difference(Mat colorImg, int min_radius, int max_radius, int min_center_dist,
	int min_radius_dist, int max_circle_diff, int* x, int* y, int* radius,int* circle_cnt,int max_circle)
{
	if (NULL == colorImg.data)
	{
		cout << "the image is NULL" << endl;
		return 0;
	}
	if (colorImg.channels()!= 3)
	{
		cout << "the format of the picture is incorrect" << endl;
		return 0;
	}
	int height = colorImg.rows;
	int width = colorImg.cols;
	int circle[30000] = { 0 };
	int k = 0;
	int sequence;
	int radius_upperbound;
	int radius_lowerbound = min_radius - min_radius_dist;
	create_functionvalue(sinvalue, cosvalue);
	create_coordinatesvalue(x_coordinates, y_coordinates,effective_theta_number,min_radius,max_radius,min_radius_dist);

	for (int i = min_radius+min_radius_dist;i <= height - min_radius-min_radius_dist;i++)
	{
		for (int j = min_radius+min_radius_dist;j <= width - min_radius-min_radius_dist;j++)
		{
			radius_upperbound = i;
			int reference = height - i;
			if (radius_upperbound > reference)
			{
				radius_upperbound = reference;
			}
			reference = j;
			if (radius_upperbound > reference)
			{
				radius_upperbound = reference;
			}
			reference = width - j;
			if (radius_upperbound > reference)
			{
				radius_upperbound = reference;
			}
			reference = max_radius;
			if (radius_upperbound > reference)
			{
				radius_upperbound = reference;
			}
			radius_upperbound = radius_upperbound - min_radius_dist;
			for (int r = min_radius;r <= radius_upperbound;r++)
			{
				sequence = 0;
				int pixvalue_in = averagepixvalue(colorImg, i, j, r - min_radius_dist, sequence, radius_lowerbound);
				int pixvalue_out = averagepixvalue(colorImg, i, j, r + min_radius_dist, sequence, radius_lowerbound);
				int difference = pixvalue_in - pixvalue_out;
				if (difference < 0) difference = 0 - difference;
				if (difference > max_circle_diff)
				{
					circle[4 * k + 0] = i;
					circle[4 * k + 1] = j;
					circle[4 * k + 2] = r;
					circle[4 * k + 3] = difference;
					k++;
					
					
				}
				sequence = 1;
				pixvalue_in = averagepixvalue(colorImg, i, j, r - min_radius_dist, sequence, radius_lowerbound);
				pixvalue_out = averagepixvalue(colorImg, i, j, r + min_radius_dist, sequence, radius_lowerbound);
				difference = pixvalue_in - pixvalue_out;
				if (difference < 0) difference = 0 - difference;
				if (difference > max_circle_diff)
				{
					circle[4 * k + 0] = i;
					circle[4 * k + 1] = j;
					circle[4 * k + 2] = r;
					circle[4 * k + 3] = difference;
					k++;
					
					
				}
				sequence = 2;
				pixvalue_in = averagepixvalue(colorImg, i, j, r - min_radius_dist, sequence, radius_lowerbound);
				pixvalue_out = averagepixvalue(colorImg, i, j, r + min_radius_dist, sequence, radius_lowerbound);
				difference = pixvalue_in - pixvalue_out;
				if (difference < 0) difference = 0 - difference;
				if (difference > max_circle_diff)
				{
					circle[4 * k + 0] = i;
					circle[4 * k + 1] = j;
					circle[4 * k + 2] = r;
					circle[4 * k + 3] = difference;
					k++;
					
					
				}
			}
		}
	}
	int circle_index = 1;
	int transition_number = 0;
	int max_index = 0;
	int additional_x[10000];
	int additional_y[10000];
	int additional_radius[10000];
	int difference[1000];
	additional_x[0] = circle[0];
	additional_y[0] = circle[1];
	additional_radius[0] = circle[2];
	difference[0] = circle[3];
	int indication;
	for (int m = 0;m < k;m++)
	{
		int reference_x = circle[4 * m + 0];
		int reference_y = circle[4 * m + 1];
		int reference_radius = circle[4 * m + 2];
		int reference_difference = circle[4 * m + 3];
		indication = 1;
		for (int n = 0;n < circle_index;n++)
		{
			int x_difference = reference_x - additional_x[n];
			if (x_difference < 0)
				x_difference = 0 - x_difference;
			int y_difference = reference_y - additional_y[n];
			if (y_difference < 0)
				y_difference = 0 - y_difference;
			int radius_difference = reference_radius - additional_radius[n];
			if (radius_difference < 0)
				radius_difference = 0 - radius_difference;
			if (x_difference < min_center_dist && y_difference < min_center_dist && radius_difference < min_radius_dist)
			{
				if (reference_difference > difference[n])
				{
					additional_x[n] = reference_x;
					additional_y[n] = reference_y;
					additional_radius[n] = reference_radius;
					difference[n] = reference_difference;
				}
				indication = 0;
				break;
			}
		}
		if (indication)
		{
			additional_x[circle_index] = reference_x;
			additional_y[circle_index] = reference_y;
			additional_radius[circle_index] = reference_radius;
			difference[circle_index] = reference_difference;
			printf("\n");
			circle_index++;
		}
		
		if (circle_index > 10000)
		{
			printf("the bound value is low enough to bring about so many detected circles");
			break;
		}
	}
	if (circle_index <= max_circle)
	{
		circle_cnt = &circle_index;
	}
	else
	{
		circle_cnt = &max_circle;
		for (int i = 0;i < max_circle;i++)
		{
			for (int j = i;j < max_circle;j++)
			{
				if (difference[i] < difference[j])
				{
					transition_number = difference[i];
					difference[i] = difference[j];
					difference[j] = transition_number;
					max_index = j;
				}
			}
			transition_number = additional_x[max_index];
			additional_x[max_index] = additional_x[i];
			additional_x[i] = transition_number;
			transition_number = additional_y[max_index];
			additional_y[max_index] = additional_y[i];
			additional_y[i] = transition_number;
			transition_number = additional_radius[max_index];
			additional_radius[max_index] = additional_radius[i];
			additional_radius[i] = transition_number;
		}
	}
	printf("\n\n");
	for (int i = 0;i < *circle_cnt;i++)
	{
		printf("%d\t", additional_x[i]);
		x[i] = additional_x[i];
		printf("%d\t", additional_y[i]);
		y[i] = additional_y[i];
		printf("%d\t", additional_radius[i]);
		radius[i] = additional_radius[i];
		printf("%d\t", difference[i]);
		printf("\n");
	}
	printf("the total number of the circles is %d", *circle_cnt);


	return 0;
}
