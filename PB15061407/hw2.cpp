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
		return MY_FAIL;
	}
	if (max_radius < min_radius || min_radius <= 0)
	{
		cout << "canshu cuowu" << endl;
		return MY_FAIL;
	}
	if (colorImg.rows < 2 * min_radius+10|| colorImg.cols<2*min_radius+10)
	{
		cout << "image is too small for r" << endl;
		return MY_FAIL;
	}
	if (NULL == x || NULL == y || NULL == radius)
	{
		cout << "x,y,r is null" << endl;
		return MY_FAIL;
	}
	int height = colorImg.rows;
	int width = colorImg.cols;
	int nowminr;
	int nowmaxr;
	int nowr;
	int nown=0;
	int finaln=0;
	int tempxyr[30000];
	int tempdiff[30000];
	int diff[30000];
	int inr, outr;
	int inhuidub[5],inhuidug[5],inhuidur[5];
	int outhuidub[5],outhuidug[5],outhuidur[5];
	int inhuidubb,inhuidugg,inhuidurr;
	int outhuidubb,outhuidugg,outhuidurr;
	int row, col;
	int xr, xy;
	int theta, r;
	int i, j;
	float sinx[360];
	float cosx[360];
	int sincosxr[360 * 306];
	for (theta = 0; theta <=359; ++theta)
	{
		for (r = 0; r <= 305; ++r)
		{
			sincosxr[r * 360 + theta] = (int)(3.0*(float)r*sin((float)theta*3.141592654 / 180.0))*width;
			sincosxr[r * 360 + theta] += (int)(3.0*(float)r*cos((float)theta*3.141592654 / 180.0));
		}
	}

	int maxdiff=0;
	int xx, yy;
	int rr;
	float test;
	float rct;
	float rct1;
	int intrct;
	int intrct1;
	int tempb;
	int tempg;
	int tempr;
	for (i = 0; i <= 359; ++i)
	{
		sinx[i] = sin((float)i*3.141592654 / 180.0);
	}
	for (j = 0; j <= 359; ++j)
	{
		cosx[j] = cos((float)j*3.141592654 / 180.0);
	}
	for (row = min_radius+6; row < height - min_radius-6; row++)
	{
		for (col = min_radius + 6; col < width - min_radius - 6; col++)
		{
			nowr = min_radius;
			nowmaxr = min(col - 6, row - 6);
			nowmaxr = min(nowmaxr, height - row - 7);
			nowmaxr = min(nowmaxr, width - col - 7);
			
			for (int k = 0; k <= 4; ++k)
			{
				inhuidub[k] = 0;
				inhuidug[k] = 0;
				inhuidur[k] = 0;
				outhuidub[k] = 0;
				outhuidug[k] = 0;
				outhuidur[k] = 0;
			}
			for (int k = 0; k <= 4; ++k)
			{
				inr = nowr - k;
				outr = nowr + 1 + k;
				int rc = 3 * (row*width + col);
				//int inr360 = inr * 360;
				//int outr360 = outr * 360;
				for (theta = 0; theta <= 359; theta++)
				{
					//rct = rc + 3 * (inr*cosx[theta] + inr*width*sinx[theta]);
					intrct = rc + sincosxr[inr * 360 + theta];
					//rct1 = rc + 3 * (outr*cosx[theta] + outr*width*sinx[theta]);
					intrct1 = rc + sincosxr[outr * 360 + theta];
					outhuidub[k] += colorImg.data[intrct1];
					inhuidub[4-k] += colorImg.data[intrct];
					inhuidug[4-k] += colorImg.data[intrct + 1];
					outhuidug[k] += colorImg.data[intrct1 + 1];
					inhuidur[4-k] += colorImg.data[intrct + 2];
					outhuidur[k] += colorImg.data[intrct1 + 2];

				}
			}
			inhuidubb = 0;
			inhuidugg = 0;
			inhuidurr = 0;
			outhuidubb = 0;
			outhuidugg = 0;
			outhuidurr = 0;
			for (int k =0 ; k <= 4; ++k)
			{
				inhuidubb += inhuidub[k];
				inhuidurr += inhuidur[k];
				inhuidugg += inhuidug[k];
				outhuidubb += outhuidub[k];
				outhuidugg += outhuidug[k];
				outhuidurr += outhuidur[k];
			}
			for (nowr = min_radius; nowr <= nowmaxr; nowr++)
			{
				

				int diffb = inhuidubb - outhuidubb;
				int diffg = inhuidugg - outhuidugg;
				int diffr = inhuidurr - outhuidurr;
				/*if (diffr > maxdiff || diffr < -maxdiff)
				{
					maxdiff = abs(diffr);
					xx = row;
					yy = col;
					rr = nowr;
				}*/
				if (diffb> max_circle_diff || diffb < -max_circle_diff)
				{
					if (nown == 20000)
					{
						break;
					}
					tempxyr[3 * nown] = row;
					tempxyr[3 * nown + 1] = col;
					tempxyr[3 * nown + 2] = nowr;
					
					tempdiff[nown] = abs(diffb);
					nown++;
				}
				else if (diffg > max_circle_diff || diffg < -max_circle_diff)
				{
					if (nown == 20000)
					{
						break;
					}
					tempxyr[3 * nown] = row;
					tempxyr[3 * nown + 1] = col;
					tempxyr[3 * nown + 2] = nowr;
					tempdiff[nown] = abs(diffg);
					nown++;
				}
				else if (diffr > max_circle_diff || diffr < -max_circle_diff)
				{
					if (nown == 20000)
					{
						break;
					}
					tempxyr[3 * nown] = row;
					tempxyr[3 * nown + 1] = col;
					tempxyr[3 * nown + 2] = nowr;
					tempdiff[nown] = abs(diffr);
					nown++;
				}
				int k = (nowr - min_radius) % 5;
				inhuidubb -= inhuidub[k];
				inhuidugg -= inhuidug[k];
				inhuidurr -= inhuidur[k];
				outhuidubb -= outhuidub[k];
				outhuidugg -= outhuidug[k];
				outhuidurr -= outhuidur[k];
				inhuidub[k]= outhuidub[k];
				inhuidug[k] = outhuidug[k];
				inhuidur[k] = outhuidur[k];
				inhuidurr += inhuidur[k];
				inhuidubb += inhuidub[k];
				inhuidugg += inhuidug[k];
				outr = nowr + 6;
				int rc = 3 * (row*width + col);
				//int inr360 = inr * 360;
				//int outr360 = outr * 360;
				//int k = (nowr - min_radius) % 5;
				outhuidub[k] = 0;
				outhuidug[k] = 0;
				outhuidur[k] = 0;
				for (theta = 0; theta <= 359; theta++)
				{
					//rct = rc + 3 * (inr*cosx[theta] + inr*width*sinx[theta]);
					//intrct = rc + sincosxr[inr * 360 + theta];
					//rct1 = rc + 3 * (outr*cosx[theta] + outr*width*sinx[theta]);
					
					intrct1 = rc + sincosxr[outr * 360 + theta];
					outhuidub[k] += colorImg.data[intrct1];
					outhuidug[k] += colorImg.data[intrct1 + 1];
					outhuidur[k] += colorImg.data[intrct1 + 2];

				}
				outhuidubb += outhuidub[k];
				outhuidugg += outhuidug[k];
				outhuidurr += outhuidur[k];

			}

		}
	}
	
	x[0] = tempxyr[0];
	y[0] = tempxyr[1];
	radius[0] = tempxyr[2];
	finaln = 0;
	int judge1 = 0;
	int judge2 = 0;
	for(i = 0; i <= nown; ++i)
	{
		judge1 = 0;
		for (j = 0; j <= finaln; j++)
		{
			if (min_center_dist < sqrt((tempxyr[3 * i] - x[j])*(tempxyr[3 * i] - x[j]) + (tempxyr[3 * i + 1] - y[j])*(tempxyr[3 * i + 1] - y[j])))
			{
				judge1 = 1;
				continue;
				
			}
			else if (sqrt((tempxyr[3 * i] - x[j])*(tempxyr[3 * i] - x[j]) + (tempxyr[3 * i + 1] - y[j])*(tempxyr[3 * i + 1] - y[j])) == 0)
			{
				if (abs(radius[j] - tempxyr[3 * i + 2]) >= min_center_dist)
				{
					if (finaln < max_circle-1)
					{
						finaln++;
						x[finaln] = tempxyr[3 * i];
						y[finaln] = tempxyr[3 * i + 1];
						radius[finaln] = tempxyr[3 * i + 2];
						diff[finaln] = tempdiff[i];
						break;
					}
				}
			}
			else
			{
				judge1 = 0;
				break;
			}
		}
		if (judge1 == 1)
		{
			if (finaln < max_circle-1)
			{
				finaln++;
				x[finaln] = tempxyr[3 * i];
				y[finaln] = tempxyr[3 * i + 1];
				radius[finaln] = tempxyr[3 * i + 2];
				diff[finaln] = tempdiff[i];
			}
		}
	}
	finaln++;
	if (finaln == 2)
	{
		*circle_cnt = finaln-1;
	}
	else
		*circle_cnt = finaln;
	int temp;
	if (finaln == max_circle-1)
	{
		for (i = 0; i < finaln;i++)
		{
			for (j = i + 1; j <= finaln; j++)
			{
				if (diff[i] < diff[j])
				{
					temp = diff[i];
					diff[i] = diff[j];
					diff[j] = temp;
					temp = x[i];
					x[i] = x[j];
					x[j] = temp;
					temp = y[i];
					y[i] = y[j];
					y[j] = temp;
					temp = radius[i];
					radius[i] = radius[j];
					radius[j] = temp;
				}
			}
		}
	}
	return MY_OK;

}
