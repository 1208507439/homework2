#include<hw2.h>
#define Pi 3.1415927
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
	int* len)
{
	int rows = colorImg.rows;
	int cols = colorImg.cols;
	int InnerCircle[2][360];
	int OuterCircle[2][360];

	uchar* pointer = colorImg.ptr<uchar>(0);

	for (int r = max_radius;r >= min_radius;r--)
	{
		for (int th = 0;th < 360;th++)
		{
			InnerCircle[0][th] = (r - 5)*cos(th * Pi / 180);
			InnerCircle[1][th] = (r - 5)*sin(th * Pi / 180);
			OuterCircle[0][th] = (r + 5)*cos(th * Pi / 180);
			OuterCircle[1][th] = (r + 5)*sin(th * Pi / 180);
		}
		for (int i = 0;i < rows;i++)
		{
			for (int j = 0;j < cols;j++)
			{
				int flag = 0;
				for (int k = 0;k < *len;k++)	//test if there is a repeated circle
				{
					int xx = x[k] - i;
					int yy = y[k] - j;
					if (xx*xx + yy*yy < min_center_dist*min_center_dist && abs(radius[k] - r) < min_radius_dist)
					{
						flag = 1;
						break;
					}
				}
				if (flag) continue;

				int dif_B = 0;
				int dif_G = 0;
				int dif_R = 0;
				int count = 0;
				for (int th = 0;th < 360;th++)
				{
					int xx1 = i + OuterCircle[0][th];
					int yy1 = j + OuterCircle[1][th];
					int xx2 = i + InnerCircle[0][th];
					int yy2 = j + InnerCircle[1][th];
					
					if (xx1 < 0 || yy1 < 0 || xx1 >= rows || yy1 >= cols ||
						xx2 < 0 || yy2 < 0 || xx2 >= rows || yy2 >= cols)
						continue;
					count++;
					uchar *p = pointer + xx1 * cols * 3 + yy1 * 3;
					dif_B += *p;
					dif_G += *(p + 1);
					dif_R += *(p + 2);
					p = pointer + xx2 * cols * 3 + yy2 * 3;
					dif_B -= *p;
					dif_G -= *(p + 1);
					dif_R -= *(p + 2);
				}
				int max = max_circle_diff * count;
				if (abs(dif_B) > max || abs(dif_G) > max || abs(dif_R) > max)
				{
					int k = *len;
					x[k] = i;
					y[k] = j;
					radius[k] = r;
					(*len)++;
				}
			}
		}
	}

	return MY_OK;
}
