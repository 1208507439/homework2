#include "hw2.h"
int angSin_whole[360] = 
{	
0,1144,2287,3430,4572,5712,6850,7987,9121,10252,11380,12505,13626,14742,15855,16962,18064,19161,20252,21336,22415,23486,24550,25607,26656,27697,28729,29753,30767,31772,32768,33754,34729,35693,36647,37590,38521,39441,40348,41243,42126,42995,43852,44695,45525,46341,47143,47930,48703,49461,50203,50931,51643,52339,53020,53684,54332,54963,55578,56175,56756,57319,57865,58393,58903,59396,59870,60326,60764,61183,61584,61966,62328,62672,62997,63303,63589,63856,64104,64332,64540,64729,64898,65048,65177,65287,65376,65446,65496,65526,
65536,65526,65496,65446,65376,65287,65177,65048,64898,64729,64540,64332,64104,63856,63589,63303,62997,62672,62328,61966,61584,61183,60764,60326,59870,59396,58903,58393,57865,57319,56756,56175,55578,54963,54332,53684,53020,52339,51643,50931,50203,49461,48703,47930,47143,46341,45525,44695,43852,42995,42126,41243,40348,39441,38521,37590,36647,35693,34729,33754,32768,31772,30767,29753,28729,27697,26656,25607,24550,23486,22415,21336,20252,19161,18064,16962,15855,14742,13626,12505,11380,10252,9121,7987,6850,5712,4572,3430,2287,1144,
0,-1144,-2287,-3430,-4572,-5712,-6850,-7987,-9121,-10252,-11380,-12505,-13626,-14742,-15855,-16962,-18064,-19161,-20252,-21336,-22415,-23486,-24550,-25607,-26656,-27697,-28729,-29753,-30767,-31772,-32768,-33754,-34729,-35693,-36647,-37590,-38521,-39441,-40348,-41243,-42126,-42995,-43852,-44695,-45525,-46341,-47143,-47930,-48703,-49461,-50203,-50931,-51643,-52339,-53020,-53684,-54332,-54963,-55578,-56175,-56756,-57319,-57865,-58393,-58903,-59396,-59870,-60326,-60764,-61183,-61584,-61966,-62328,-62672,-62997,-63303,-63589,-63856,-64104,-64332,-64540,-64729,-64898,-65048,-65177,-65287,-65376,-65446,-65496,-65526,
-65536,-65526,-65496,-65446,-65376,-65287,-65177,-65048,-64898,-64729,-64540,-64332,-64104,-63856,-63589,-63303,-62997,-62672,-62328,-61966,-61584,-61183,-60764,-60326,-59870,-59396,-58903,-58393,-57865,-57319,-56756,-56175,-55578,-54963,-54332,-53684,-53020,-52339,-51643,-50931,-50203,-49461,-48703,-47930,-47143,-46341,-45525,-44695,-43852,-42995,-42126,-41243,-40348,-39441,-38521,-37590,-36647,-35693,-34729,-33754,-32768,-31772,-30767,-29753,-28729,-27697,-26656,-25607,-24550,-23486,-22415,-21336,-20252,-19161,-18064,-16962,-15855,-14742,-13626,-12505,-11380,-10252,-9121,-7987,-6850,-5712,-4572,-3430,-2287,-1144
};
int angCos_whole[360] = 
{	
65536,65526,65496,65446,65376,65287,65177,65048,64898,64729,64540,64332,64104,63856,63589,63303,62997,62672,62328,61966,61584,61183,60764,60326,59870,59396,58903,58393,57865,57319,56756,56175,55578,54963,54332,53684,53020,52339,51643,50931,50203,49461,48703,47930,47143,46341,45525,44695,43852,42995,42126,41243,40348,39441,38521,37590,36647,35693,34729,33754,32768,31772,30767,29753,28729,27697,26656,25607,24550,23486,22415,21336,20252,19161,18064,16962,15855,14742,13626,12505,11380,10252,9121,7987,6850,5712,4572,3430,2287,1144,
0,-1144,-2287,-3430,-4572,-5712,-6850,-7987,-9121,-10252,-11380,-12505,-13626,-14742,-15855,-16962,-18064,-19161,-20252,-21336,-22415,-23486,-24550,-25607,-26656,-27697,-28729,-29753,-30767,-31772,-32768,-33754,-34729,-35693,-36647,-37590,-38521,-39441,-40348,-41243,-42126,-42995,-43852,-44695,-45525,-46341,-47143,-47930,-48703,-49461,-50203,-50931,-51643,-52339,-53020,-53684,-54332,-54963,-55578,-56175,-56756,-57319,-57865,-58393,-58903,-59396,-59870,-60326,-60764,-61183,-61584,-61966,-62328,-62672,-62997,-63303,-63589,-63856,-64104,-64332,-64540,-64729,-64898,-65048,-65177,-65287,-65376,-65446,-65496,-65526,
-65536,-65526,-65496,-65446,-65376,-65287,-65177,-65048,-64898,-64729,-64540,-64332,-64104,-63856,-63589,-63303,-62997,-62672,-62328,-61966,-61584,-61183,-60764,-60326,-59870,-59396,-58903,-58393,-57865,-57319,-56756,-56175,-55578,-54963,-54332,-53684,-53020,-52339,-51643,-50931,-50203,-49461,-48703,-47930,-47143,-46341,-45525,-44695,-43852,-42995,-42126,-41243,-40348,-39441,-38521,-37590,-36647,-35693,-34729,-33754,-32768,-31772,-30767,-29753,-28729,-27697,-26656,-25607,-24550,-23486,-22415,-21336,-20252,-19161,-18064,-16962,-15855,-14742,-13626,-12505,-11380,-10252,-9121,-7987,-6850,-5712,-4572,-3430,-2287,-1144,
0,1144,2287,3430,4572,5712,6850,7987,9121,10252,11380,12505,13626,14742,15855,16962,18064,19161,20252,21336,22415,23486,24550,25607,26656,27697,28729,29753,30767,31772,32768,33754,34729,35693,36647,37590,38521,39441,40348,41243,42126,42995,43852,44695,45525,46341,47143,47930,48703,49461,50203,50931,51643,52339,53020,53684,54332,54963,55578,56175,56756,57319,57865,58393,58903,59396,59870,60326,60764,61183,61584,61966,62328,62672,62997,63303,63589,63856,64104,64332,64540,64729,64898,65048,65177,65287,65376,65446,65496,65526
};
int angSin_half[180] =	
{	0,2287,4571,6850,9120,11380,13625,15854,18064,20251,22414,24550,26655,28729,30767,32767,34728,36647,38521,40347,42125,43852,45525,47142,48702,50203,51643,53019,54331,55577,56755,57864,58903,59870,60763,61583,62328,62997,63589,64103,64540,64898,65176,65376,65496,65536,65496,65376,65176,64898,64540,64103,63589,62997,62328,61583,60763,59870,58903,57864,56755,55577,54331,53019,51643,50203,48702,47142,45525,43852,42125,40347,38521,36647,34728,32767,30767,28729,26655,24550,22414,20251,18064,15854,13625,11380,9120,6850,4571,2287,
0,-2287,-4571,-6850,-9120,-11380,-13625,-15854,-18064,-20251,-22414,-24550,-26655,-28729,-30767,-32768,-34728,-36647,-38521,-40347,-42125,-43852,-45525,-47142,-48702,-50203,-51643,-53019,-54331,-55577,-56755,-57864,-58903,-59870,-60763,-61583,-62328,-62997,-63589,-64103,-64540,-64898,-65176,-65376,-65496,-65536,-65496,-65376,-65176,-64898,-64540,-64103,-63589,-62997,-62328,-61583,-60763,-59870,-58903,-57864,-56755,-55577,-54331,-53019,-51643,-50203,-48702,-47142,-45525,-43852,-42125,-40347,-38521,-36647,-34728,-32768,-30767,-28729,-26655,-24550,-22414,-20251,-18064,-15854,-13625,-11380,-9120,-6850,-4571,-2287
};
int angCos_half[180] = 
{	
65536,65496,65376,65176,64898,64540,64103,63589,62997,62328,61583,60763,59870,58903,57864,56755,55577,54331,53019,51643,50203,48702,47142,45525,43852,42125,40347,38521,36647,34728,32768,30767,28729,26655,24550,22414,20251,18064,15854,13625,11380,9120,6850,4571,2287,0,-2287,-4571,-6850,-9120,-11380,-13625,-15854,-18064,-20251,-22414,-24550,-26655,-28729,-30767,-32767,-34728,-36647,-38521,-40347,-42125,-43852,-45525,-47142,-48702,-50203,-51643,-53019,-54331,-55577,-56755,-57864,-58903,-59870,-60763,-61583,-62328,-62997,-63589,-64103,-64540,-64898,-65176,-65376,-65496,
-65536,-65496,-65376,-65176,-64898,-64540,-64103,-63589,-62997,-62328,-61583,-60763,-59870,-58903,-57864,-56755,-55577,-54331,-53019,-51643,-50203,-48702,-47142,-45525,-43852,-42125,-40347,-38521,-36647,-34728,-32768,-30767,-28729,-26655,-24550,-22414,-20251,-18064,-15854,-13625,-11380,-9120,-6850,-4571,-2287,0,2287,4571,6850,9120,11380,13625,15854,18064,20251,22414,24550,26655,28729,30767,32768,34728,36647,38521,40347,42125,43852,45525,47142,48702,50203,51643,53019,54331,55577,56755,57864,58903,59870,60763,61583,62328,62997,63589,64103,64540,64898,65176,65376,65496
};
int angSin_qtr[90] = 
{	
0,4571,9120,13625,18064,22414,26655,30767,34728,38521,42125,45525,48702,51643,54331,56755,58903,60763,62328,63589,64540,65176,65496,65496,65176,64540,63589,62328,60763,58903,56755,54331,51643,48702,45525,42125,38521,34728,30767,26655,22414,18064,13625,9120,4571,0,-4571,-9120,-13625,-18064,-22414,-26655,-30767,-34728,-38521,-42125,-45525,-48702,-51643,-54331,-56755,-58903,-60763,-62328,-63589,-64540,-65176,-65496,-65496,-65176,-64540,-63589,-62328,-60763,-58903,-56755,-54331,-51643,-48702,-45525,-42125,-38521,-34728,-30767,-26655,-22414,-18064,-13625,-9120,-4571
};
int angCos_qtr[90] =
{
65536,65376,64898,64103,62997,61583,59870,57864,55577,53019,50203,47142,43852,40347,36647,32768,28729,24550,20251,15854,11380,6850,2287,-2287,-6850,-11380,-15854,-20251,-24550,-28729,-32767,-36647,-40347,-43852,-47142,-50203,-53019,-55577,-57864,-59870,-61583,-62997,-64103,-64898,-65376,-65536,-65376,-64898,-64103,-62997,-61583,-59870,-57864,-55577,-53019,-50203,-47142,-43852,-40347,-36647,-32768,-28729,-24550,-20251,-15854,-11380,-6850,-2287,2287,6850,11380,15854,20251,24550,28729,32768,36647,40347,43852,47142,50203,53019,55577,57864,59870,61583,62997,64103,64898,65376
};
#define elge_whole 114
#define elge_half 57
#define RADIUS_DIFF 5

int ustc_Find_Circles_By_Difference(Mat colorImg, int min_radius, int max_radius, int min_center_dist, int min_radius_dist, int max_circle_diff, int* x, int* y, int* radius, int* circle_cnt, int max_circle)
{
	int hugeX[10000] = { 0 };
	int hugeY[10000] = { 0 };
	int hugeR[10000] = { 0 };
	int *xp = hugeX, *yp = hugeY, *rp = hugeR;
	int *hugeN = new int;
	*hugeN = 0;
	if (NULL == colorImg.data)
	{
		cout << "image is NULL." << endl;
		return MY_FAIL;
	}
	int nRows = colorImg.rows;
	int nCols = colorImg.cols;
	if ((max_radius * 2 + 11) > nRows)
		max_radius = (nRows - 11) / 2;
	if ((max_radius * 2 + 11) > nCols)
		max_radius = (nCols - 11) / 2;
	Mat BImg, GImg, RImg;
	uchar *c, *b, *g, *r;
	BImg.create(nRows, nCols, CV_8UC1);
	GImg.create(nRows, nCols, CV_8UC1);
	RImg.create(nRows, nCols, CV_8UC1);
	int *Judge = new int[nRows*nCols];
	int *jud;
	memset(Judge, 0, nRows*nCols * 4);
	int minR, maxR;
	int i, j, k;
	int ii, jj;
	int keyX, keyY;
	int diff;
	int angle;
	for (i = nRows*nCols, c = colorImg.data, b = BImg.data, g = GImg.data, r = RImg.data; i; i--)
	{
		*b++ = *c++;
		*g++ = *c++;
		*r++ = *c++;
	}
	uchar *bigW[360], *smallW[360];
	uchar *bigH[180], *smallH[180];
	uchar *bigQ[90], *smallQ[90];
	uchar *imgP;
	uchar *rP;
	uchar **bigP, **smallP;
	int R;
	int temp;
	int count;

	if (min_radius <= elge_half && max_radius > elge_half)
	{
		minR = min_radius;
		maxR = elge_half;
		angle = 90;
		imgP = BImg.data;
		for (R = minR; R < maxR; R++)
		{
			rP = imgP + (R + RADIUS_DIFF)*nCols + R + RADIUS_DIFF;
			jud = Judge + (R + RADIUS_DIFF)*nCols + R + RADIUS_DIFF;
			for (i = 0; i < angle; ++i)
			{
				keyX = (((R + RADIUS_DIFF)*angSin_qtr[i]) >> 16);
				keyY = (((R + RADIUS_DIFF)*angCos_qtr[i]) >> 16);
				bigQ[i] = rP + keyX*nCols + keyY;
				keyX = (((R - RADIUS_DIFF)*angSin_qtr[i]) >> 16);
				keyY = (((R - RADIUS_DIFF)*angCos_qtr[i]) >> 16);
				smallQ[i] = rP + keyX*nCols + keyY;
			}
			for (k = nCols - (R + RADIUS_DIFF) * 2 - 1, i = (nRows - (R + RADIUS_DIFF) * 2)*(k + 1); i; --i, --k, rP++, jud++)
			{
				count = 81;
				if ((*jud) == 1 || ((R < ((*jud) + min_radius_dist)) && (R >((*jud) - min_radius_dist))))
				{
					temp = (!k) * 2 * (R + RADIUS_DIFF);
					rP += temp;
					jud += temp;
					k += (!k)*(nCols - (R + RADIUS_DIFF) * 2);
					for (j = 0, bigP = bigQ, smallP = smallQ; j < angle; ++j)
					{
						(*bigP)++;
						(*smallP)++;
						(*bigP) += temp;
						(*smallP) += temp;
						bigP++;
						smallP++;
					}
					continue;
				}
				for (j = 0, bigP = bigQ, smallP = smallQ; j < angle; j++)
				{
					diff = (**bigP) - (**smallP);
					diff = !(diff >> 31)*diff + ((diff >> 31) & 1)*(-diff);
					diff -= max_circle_diff;
					count -= !(diff >> 31);
					(*bigP)++;
					(*smallP)++;
					temp = (!k) * 2 * (R + RADIUS_DIFF);
					(*bigP) += temp;
					(*smallP) += temp;
					bigP++;
					smallP++;
				}
				count = !((count - 1) >> 31);
				if (!count)
				{
					temp = (nRows - (R + RADIUS_DIFF) * 2)*(nCols - (R + RADIUS_DIFF) * 2);
					temp = temp - i;
					*xp = temp % (nCols - (R + RADIUS_DIFF) * 2) + R + RADIUS_DIFF;
					*yp = temp / (nCols - (R + RADIUS_DIFF) * 2) + R + RADIUS_DIFF;
					*rp = R;
					for (ii = -min_center_dist; ii <= min_center_dist; ii++)
					{
						for (jj = -min_center_dist; jj <= min_center_dist; jj++)
						{
							if (((ii + *yp) >> 31) || ((jj + *xp) >> 31) || ((nRows - ii - *yp - 1) >> 31) || ((nCols - jj - *xp - 1) >> 31))continue;
							jud[ii*nCols + jj] = 1;
						}
					}
					*jud = R;
					(*hugeN)++;
					xp++;
					yp++;
					rp++;
				}
				temp = (!k) * 2 * (R + RADIUS_DIFF);
				rP += temp;
				jud += temp;
				k += (!k)*(nCols - (R + RADIUS_DIFF) * 2);
			}
		}
		imgP = GImg.data;
		for (R = minR; R < maxR; R++)
		{
			rP = imgP + (R + RADIUS_DIFF)*nCols + R + RADIUS_DIFF;
			jud = Judge + (R + RADIUS_DIFF)*nCols + R + RADIUS_DIFF;
			for (i = 0; i < angle; ++i)
			{
				keyX = (((R + RADIUS_DIFF)*angSin_qtr[i]) >> 16);
				keyY = (((R + RADIUS_DIFF)*angCos_qtr[i]) >> 16);
				bigQ[i] = rP + keyX*nCols + keyY;
				keyX = (((R - RADIUS_DIFF)*angSin_qtr[i]) >> 16);
				keyY = (((R - RADIUS_DIFF)*angCos_qtr[i]) >> 16);
				smallQ[i] = rP + keyX*nCols + keyY;
			}
			for (k = nCols - (R + RADIUS_DIFF) * 2 - 1, i = (nRows - (R + RADIUS_DIFF) * 2)*(k + 1); i; --i, --k, rP++, jud++)
			{
				count = 81;
				if ((*jud) == 1 || ((R < ((*jud) + min_radius_dist)) && (R >((*jud) - min_radius_dist))))
				{
					temp = (!k) * 2 * (R + RADIUS_DIFF);
					rP += temp;
					jud += temp;
					k += (!k)*(nCols - (R + RADIUS_DIFF) * 2);
					for (j = 0, bigP = bigQ, smallP = smallQ; j < angle; ++j)
					{
						(*bigP)++;
						(*smallP)++;
						(*bigP) += temp;
						(*smallP) += temp;
						bigP++;
						smallP++;
					}
					continue;
				}
				for (j = 0, bigP = bigQ, smallP = smallQ; j < angle; j++)
				{
					diff = (**bigP) - (**smallP);
					diff = !(diff >> 31)*diff + ((diff >> 31) & 1)*(-diff);
					diff -= max_circle_diff;
					count -= !(diff >> 31);
					(*bigP)++;
					(*smallP)++;
					temp = (!k) * 2 * (R + RADIUS_DIFF);
					(*bigP) += temp;
					(*smallP) += temp;
					bigP++;
					smallP++;
				}
				count = !((count - 1) >> 31);
				if (!count)
				{
					temp = (nRows - (R + RADIUS_DIFF) * 2)*(nCols - (R + RADIUS_DIFF) * 2);
					temp = temp - i;
					*xp = temp % (nCols - (R + RADIUS_DIFF) * 2) + R + RADIUS_DIFF;
					*yp = temp / (nCols - (R + RADIUS_DIFF) * 2) + R + RADIUS_DIFF;
					*rp = R;
					for (ii = -min_center_dist; ii <= min_center_dist; ii++)
					{
						for (jj = -min_center_dist; jj <= min_center_dist; jj++)
						{
							if (((ii + *yp) >> 31) || ((jj + *xp) >> 31) || ((nRows - ii - *yp - 1) >> 31) || ((nCols - jj - *xp - 1) >> 31))continue;
							jud[ii*nCols + jj] = 1;
						}
					}
					*jud = R;
					(*hugeN)++;
					xp++;
					yp++;
					rp++;
				}
				temp = (!k) * 2 * (R + RADIUS_DIFF);
				rP += temp;
				jud += temp;
				k += (!k)*(nCols - (R + RADIUS_DIFF) * 2);
			}
		}
		imgP = RImg.data;
		for (R = minR; R < maxR; R++)
		{
			rP = imgP + (R + RADIUS_DIFF)*nCols + R + RADIUS_DIFF;
			jud = Judge + (R + RADIUS_DIFF)*nCols + R + RADIUS_DIFF;
			for (i = 0; i < angle; ++i)
			{
				keyX = (((R + RADIUS_DIFF)*angSin_qtr[i]) >> 16);
				keyY = (((R + RADIUS_DIFF)*angCos_qtr[i]) >> 16);
				bigQ[i] = rP + keyX*nCols + keyY;
				keyX = (((R - RADIUS_DIFF)*angSin_qtr[i]) >> 16);
				keyY = (((R - RADIUS_DIFF)*angCos_qtr[i]) >> 16);
				smallQ[i] = rP + keyX*nCols + keyY;
			}
			for (k = nCols - (R + RADIUS_DIFF) * 2 - 1, i = (nRows - (R + RADIUS_DIFF) * 2)*(k + 1); i; --i, --k, rP++, jud++)
			{
				count = 81;
				if ((*jud) == 1 || ((R < ((*jud) + min_radius_dist)) && (R >((*jud) - min_radius_dist))))
				{
					temp = (!k) * 2 * (R + RADIUS_DIFF);
					rP += temp;
					jud += temp;
					k += (!k)*(nCols - (R + RADIUS_DIFF) * 2);
					for (j = 0, bigP = bigQ, smallP = smallQ; j < angle; ++j)
					{
						(*bigP)++;
						(*smallP)++;
						(*bigP) += temp;
						(*smallP) += temp;
						bigP++;
						smallP++;
					}
					continue;
				}
				for (j = 0, bigP = bigQ, smallP = smallQ; j < angle; j++)
				{
					diff = (**bigP) - (**smallP);
					diff = !(diff >> 31)*diff + ((diff >> 31) & 1)*(-diff);
					diff -= max_circle_diff;
					count -= !(diff >> 31);
					(*bigP)++;
					(*smallP)++;
					temp = (!k) * 2 * (R + RADIUS_DIFF);
					(*bigP) += temp;
					(*smallP) += temp;
					bigP++;
					smallP++;
				}
				count = !((count - 1) >> 31);
				if (!count)
				{
					temp = (nRows - (R + RADIUS_DIFF) * 2)*(nCols - (R + RADIUS_DIFF) * 2);
					temp = temp - i;
					*xp = temp % (nCols - (R + RADIUS_DIFF) * 2) + R + RADIUS_DIFF;
					*yp = temp / (nCols - (R + RADIUS_DIFF) * 2) + R + RADIUS_DIFF;
					*rp = R;
					for (ii = -min_center_dist; ii <= min_center_dist; ii++)
					{
						for (jj = -min_center_dist; jj <= min_center_dist; jj++)
						{
							if (((ii + *yp) >> 31) || ((jj + *xp) >> 31) || ((nRows - ii - *yp - 1) >> 31) || ((nCols - jj - *xp - 1) >> 31))continue;
							jud[ii*nCols + jj] = 1;
						}
					}
					*jud = R;
					(*hugeN)++;
					xp++;
					yp++;
					rp++;
				}
				temp = (!k) * 2 * (R + RADIUS_DIFF);
				rP += temp;
				jud += temp;
				k += (!k)*(nCols - (R + RADIUS_DIFF) * 2);
			}
		}
	}
	else if (min_radius <= elge_half && max_radius <= elge_half)
	{
		minR = min_radius;
		maxR = max_radius;
		angle = 90;
		imgP = BImg.data;
		for (R = minR; R < maxR; R++)
		{
			rP = imgP + (R + RADIUS_DIFF)*nCols + R + RADIUS_DIFF;
			jud = Judge + (R + RADIUS_DIFF)*nCols + R + RADIUS_DIFF;
			for (i = 0; i < angle; ++i)
			{
				keyX = (((R + RADIUS_DIFF)*angSin_qtr[i]) >> 16);
				keyY = (((R + RADIUS_DIFF)*angCos_qtr[i]) >> 16);
				bigQ[i] = rP + keyX*nCols + keyY;
				keyX = (((R - RADIUS_DIFF)*angSin_qtr[i]) >> 16);
				keyY = (((R - RADIUS_DIFF)*angCos_qtr[i]) >> 16);
				smallQ[i] = rP + keyX*nCols + keyY;
			}
			for (k = nCols - (R + RADIUS_DIFF) * 2 - 1, i = (nRows - (R + RADIUS_DIFF) * 2)*(k + 1); i; --i, --k, rP++, jud++)
			{
				count = 81;
				if ((*jud) == 1 || ((R < ((*jud) + min_radius_dist)) && (R >((*jud) - min_radius_dist))))
				{
					temp = (!k) * 2 * (R + RADIUS_DIFF);
					rP += temp;
					jud += temp;
					k += (!k)*(nCols - (R + RADIUS_DIFF) * 2);
					for (j = 0, bigP = bigQ, smallP = smallQ; j < angle; ++j)
					{
						(*bigP)++;
						(*smallP)++;
						(*bigP) += temp;
						(*smallP) += temp;
						bigP++;
						smallP++;
					}
					continue;
				}
				for (j = 0, bigP = bigQ, smallP = smallQ; j < angle; j++)
				{
					diff = (**bigP) - (**smallP);
					diff = !(diff >> 31)*diff + ((diff >> 31) & 1)*(-diff);
					diff -= max_circle_diff;
					count -= !(diff >> 31);
					(*bigP)++;
					(*smallP)++;
					temp = (!k) * 2 * (R + RADIUS_DIFF);
					(*bigP) += temp;
					(*smallP) += temp;
					bigP++;
					smallP++;
				}
				count = !((count - 1) >> 31);
				if (!count)
				{
					temp = (nRows - (R + RADIUS_DIFF) * 2)*(nCols - (R + RADIUS_DIFF) * 2);
					temp = temp - i;
					*xp = temp % (nCols - (R + RADIUS_DIFF) * 2) + R + RADIUS_DIFF;
					*yp = temp / (nCols - (R + RADIUS_DIFF) * 2) + R + RADIUS_DIFF;
					*rp = R;
					for (ii = -min_center_dist; ii <= min_center_dist; ii++)
					{
						for (jj = -min_center_dist; jj <= min_center_dist; jj++)
						{
							if (((ii + *yp) >> 31) || ((jj + *xp) >> 31) || ((nRows - ii - *yp - 1) >> 31) || ((nCols - jj - *xp - 1) >> 31))continue;
							jud[ii*nCols + jj] = 1;
						}
					}
					*jud = R;
					(*hugeN)++;
					xp++;
					yp++;
					rp++;
				}
				temp = (!k) * 2 * (R + RADIUS_DIFF);
				rP += temp;
				jud += temp;
				k += (!k)*(nCols - (R + RADIUS_DIFF) * 2);
			}
		}
		imgP = GImg.data;
		for (R = minR; R < maxR; R++)
		{
			rP = imgP + (R + RADIUS_DIFF)*nCols + R + RADIUS_DIFF;
			jud = Judge + (R + RADIUS_DIFF)*nCols + R + RADIUS_DIFF;
			for (i = 0; i < angle; ++i)
			{
				keyX = (((R + RADIUS_DIFF)*angSin_qtr[i]) >> 16);
				keyY = (((R + RADIUS_DIFF)*angCos_qtr[i]) >> 16);
				bigQ[i] = rP + keyX*nCols + keyY;
				keyX = (((R - RADIUS_DIFF)*angSin_qtr[i]) >> 16);
				keyY = (((R - RADIUS_DIFF)*angCos_qtr[i]) >> 16);
				smallQ[i] = rP + keyX*nCols + keyY;
			}
			for (k = nCols - (R + RADIUS_DIFF) * 2 - 1, i = (nRows - (R + RADIUS_DIFF) * 2)*(k + 1); i; --i, --k, rP++, jud++)
			{
				count = 81;
				if ((*jud) == 1 || ((R < ((*jud) + min_radius_dist)) && (R >((*jud) - min_radius_dist))))
				{
					temp = (!k) * 2 * (R + RADIUS_DIFF);
					rP += temp;
					jud += temp;
					k += (!k)*(nCols - (R + RADIUS_DIFF) * 2);
					for (j = 0, bigP = bigQ, smallP = smallQ; j < angle; ++j)
					{
						(*bigP)++;
						(*smallP)++;
						(*bigP) += temp;
						(*smallP) += temp;
						bigP++;
						smallP++;
					}
					continue;
				}
				for (j = 0, bigP = bigQ, smallP = smallQ; j < angle; j++)
				{
					diff = (**bigP) - (**smallP);
					diff = !(diff >> 31)*diff + ((diff >> 31) & 1)*(-diff);
					diff -= max_circle_diff;
					count -= !(diff >> 31);
					(*bigP)++;
					(*smallP)++;
					temp = (!k) * 2 * (R + RADIUS_DIFF);
					(*bigP) += temp;
					(*smallP) += temp;
					bigP++;
					smallP++;
				}
				count = !((count - 1) >> 31);
				if (!count)
				{
					temp = (nRows - (R + RADIUS_DIFF) * 2)*(nCols - (R + RADIUS_DIFF) * 2);
					temp = temp - i;
					*xp = temp % (nCols - (R + RADIUS_DIFF) * 2) + R + RADIUS_DIFF;
					*yp = temp / (nCols - (R + RADIUS_DIFF) * 2) + R + RADIUS_DIFF;
					*rp = R;
					for (ii = -min_center_dist; ii <= min_center_dist; ii++)
					{
						for (jj = -min_center_dist; jj <= min_center_dist; jj++)
						{
							if (((ii + *yp) >> 31) || ((jj + *xp) >> 31) || ((nRows - ii - *yp - 1) >> 31) || ((nCols - jj - *xp - 1) >> 31))continue;
							jud[ii*nCols + jj] = 1;
						}
					}
					*jud = R;
					(*hugeN)++;
					xp++;
					yp++;
					rp++;
				}
				temp = (!k) * 2 * (R + RADIUS_DIFF);
				rP += temp;
				jud += temp;
				k += (!k)*(nCols - (R + RADIUS_DIFF) * 2);
			}
		}
		imgP = RImg.data;
		for (R = minR; R < maxR; R++)
		{
			rP = imgP + (R + RADIUS_DIFF)*nCols + R + RADIUS_DIFF;
			jud = Judge + (R + RADIUS_DIFF)*nCols + R + RADIUS_DIFF;
			for (i = 0; i < angle; ++i)
			{
				keyX = (((R + RADIUS_DIFF)*angSin_qtr[i]) >> 16);
				keyY = (((R + RADIUS_DIFF)*angCos_qtr[i]) >> 16);
				bigQ[i] = rP + keyX*nCols + keyY;
				keyX = (((R - RADIUS_DIFF)*angSin_qtr[i]) >> 16);
				keyY = (((R - RADIUS_DIFF)*angCos_qtr[i]) >> 16);
				smallQ[i] = rP + keyX*nCols + keyY;
			}
			for (k = nCols - (R + RADIUS_DIFF) * 2 - 1, i = (nRows - (R + RADIUS_DIFF) * 2)*(k + 1); i; --i, --k, rP++, jud++)
			{
				count = 81;
				if ((*jud) == 1 || ((R < ((*jud) + min_radius_dist)) && (R >((*jud) - min_radius_dist))))
				{
					temp = (!k) * 2 * (R + RADIUS_DIFF);
					rP += temp;
					jud += temp;
					k += (!k)*(nCols - (R + RADIUS_DIFF) * 2);
					for (j = 0, bigP = bigQ, smallP = smallQ; j < angle; ++j)
					{
						(*bigP)++;
						(*smallP)++;
						(*bigP) += temp;
						(*smallP) += temp;
						bigP++;
						smallP++;
					}
					continue;
				}
				for (j = 0, bigP = bigQ, smallP = smallQ; j < angle; j++)
				{
					diff = (**bigP) - (**smallP);
					diff = !(diff >> 31)*diff + ((diff >> 31) & 1)*(-diff);
					diff -= max_circle_diff;
					count -= !(diff >> 31);
					(*bigP)++;
					(*smallP)++;
					temp = (!k) * 2 * (R + RADIUS_DIFF);
					(*bigP) += temp;
					(*smallP) += temp;
					bigP++;
					smallP++;
				}
				count = !((count - 1) >> 31);
				if (!count)
				{
					temp = (nRows - (R + RADIUS_DIFF) * 2)*(nCols - (R + RADIUS_DIFF) * 2);
					temp = temp - i;
					*xp = temp % (nCols - (R + RADIUS_DIFF) * 2) + R + RADIUS_DIFF;
					*yp = temp / (nCols - (R + RADIUS_DIFF) * 2) + R + RADIUS_DIFF;
					*rp = R;
					for (ii = -min_center_dist; ii <= min_center_dist; ii++)
					{
						for (jj = -min_center_dist; jj <= min_center_dist; jj++)
						{
							if (((ii + *yp) >> 31) || ((jj + *xp) >> 31) || ((nRows - ii - *yp - 1) >> 31) || ((nCols - jj - *xp - 1) >> 31))continue;
							jud[ii*nCols + jj] = 1;
						}
					}
					*jud = R;
					(*hugeN)++;
					xp++;
					yp++;
					rp++;
				}
				temp = (!k) * 2 * (R + RADIUS_DIFF);
				rP += temp;
				jud += temp;
				k += (!k)*(nCols - (R + RADIUS_DIFF) * 2);
			}
		}
	}



	if (min_radius <= elge_half && max_radius > elge_whole)
	{
		minR = elge_half;
		maxR = elge_whole;
		angle = 180;
		imgP = BImg.data;
		for (R = minR; R < maxR; R++)
		{
			rP = imgP + (R + RADIUS_DIFF)*nCols + R + RADIUS_DIFF;
			jud = Judge + (R + RADIUS_DIFF)*nCols + R + RADIUS_DIFF;
			for (i = 0; i < angle; ++i)
			{
				keyX = (((R + RADIUS_DIFF)*angSin_half[i]) >> 16);
				keyY = (((R + RADIUS_DIFF)*angCos_half[i]) >> 16);
				bigH[i] = rP + keyX*nCols + keyY;
				keyX = (((R - RADIUS_DIFF)*angSin_half[i]) >> 16);
				keyY = (((R - RADIUS_DIFF)*angCos_half[i]) >> 16);
				smallH[i] = rP + keyX*nCols + keyY;
			}
			for (k = nCols - (R + RADIUS_DIFF) * 2 - 1, i = (nRows - (R + RADIUS_DIFF) * 2)*(k + 1); i; --i, --k, rP++, jud++)
			{
				count = 162;
				if ((*jud) == 1 || ((R < ((*jud) + min_radius_dist)) && (R >((*jud) - min_radius_dist))))
				{
					temp = (!k) * 2 * (R + RADIUS_DIFF);
					rP += temp;
					jud += temp;
					k += (!k)*(nCols - (R + RADIUS_DIFF) * 2);
					for (j = 0, bigP = bigH, smallP = smallH; j < angle; ++j)
					{
						(*bigP)++;
						(*smallP)++;
						(*bigP) += temp;
						(*smallP) += temp;
						bigP++;
						smallP++;
					}
					continue;
				}
				for (j = 0, bigP = bigH, smallP = smallH; j < angle; j++)
				{
					diff = (**bigP) - (**smallP);
					diff = !(diff >> 31)*diff + ((diff >> 31) & 1)*(-diff);
					diff -= max_circle_diff;
					count -= !(diff >> 31);
					(*bigP)++;
					(*smallP)++;
					temp = (!k) * 2 * (R + RADIUS_DIFF);
					(*bigP) += temp;
					(*smallP) += temp;
					bigP++;
					smallP++;
				}
				count = !((count - 1) >> 31);
				if (!count)
				{
					temp = (nRows - (R + RADIUS_DIFF) * 2)*(nCols - (R + RADIUS_DIFF) * 2);
					temp = temp - i;
					*xp = temp % (nCols - (R + RADIUS_DIFF) * 2) + R + RADIUS_DIFF;
					*yp = temp / (nCols - (R + RADIUS_DIFF) * 2) + R + RADIUS_DIFF;
					*rp = R;
					for (ii = -min_center_dist; ii <= min_center_dist; ii++)
					{
						for (jj = -min_center_dist; jj <= min_center_dist; jj++)
						{
							if (((ii + *yp) >> 31) || ((jj + *xp) >> 31) || ((nRows - ii - *yp - 1) >> 31) || ((nCols - jj - *xp - 1) >> 31))continue;
							jud[ii*nCols + jj] = 1;
						}
					}
					*jud = R;
					(*hugeN)++;
					xp++;
					yp++;
					rp++;
				}
				temp = (!k) * 2 * (R + RADIUS_DIFF);
				rP += temp;
				jud += temp;
				k += (!k)*(nCols - (R + RADIUS_DIFF) * 2);
			}
		}
		imgP = GImg.data;
		for (R = minR; R < maxR; R++)
		{
			rP = imgP + (R + RADIUS_DIFF)*nCols + R + RADIUS_DIFF;
			jud = Judge + (R + RADIUS_DIFF)*nCols + R + RADIUS_DIFF;
			for (i = 0; i < angle; ++i)
			{
				keyX = (((R + RADIUS_DIFF)*angSin_half[i]) >> 16);
				keyY = (((R + RADIUS_DIFF)*angCos_half[i]) >> 16);
				bigH[i] = rP + keyX*nCols + keyY;
				keyX = (((R - RADIUS_DIFF)*angSin_half[i]) >> 16);
				keyY = (((R - RADIUS_DIFF)*angCos_half[i]) >> 16);
				smallH[i] = rP + keyX*nCols + keyY;
			}
			for (k = nCols - (R + RADIUS_DIFF) * 2 - 1, i = (nRows - (R + RADIUS_DIFF) * 2)*(k + 1); i; --i, --k, rP++, jud++)
			{
				count = 162;
				if ((*jud) == 1 || ((R < ((*jud) + min_radius_dist)) && (R >((*jud) - min_radius_dist))))
				{
					temp = (!k) * 2 * (R + RADIUS_DIFF);
					rP += temp;
					jud += temp;
					k += (!k)*(nCols - (R + RADIUS_DIFF) * 2);
					for (j = 0, bigP = bigH, smallP = smallH; j < angle; ++j)
					{
						(*bigP)++;
						(*smallP)++;
						(*bigP) += temp;
						(*smallP) += temp;
						bigP++;
						smallP++;
					}
					continue;
				}
				for (j = 0, bigP = bigH, smallP = smallH; j < angle; j++)
				{
					diff = (**bigP) - (**smallP);
					diff = !(diff >> 31)*diff + ((diff >> 31) & 1)*(-diff);
					diff -= max_circle_diff;
					count -= !(diff >> 31);
					(*bigP)++;
					(*smallP)++;
					temp = (!k) * 2 * (R + RADIUS_DIFF);
					(*bigP) += temp;
					(*smallP) += temp;
					bigP++;
					smallP++;
				}
				count = !((count - 1) >> 31);
				if (!count)
				{
					temp = (nRows - (R + RADIUS_DIFF) * 2)*(nCols - (R + RADIUS_DIFF) * 2);
					temp = temp - i;
					*xp = temp % (nCols - (R + RADIUS_DIFF) * 2) + R + RADIUS_DIFF;
					*yp = temp / (nCols - (R + RADIUS_DIFF) * 2) + R + RADIUS_DIFF;
					*rp = R;
					for (ii = -min_center_dist; ii <= min_center_dist; ii++)
					{
						for (jj = -min_center_dist; jj <= min_center_dist; jj++)
						{
							if (((ii + *yp) >> 31) || ((jj + *xp) >> 31) || ((nRows - ii - *yp - 1) >> 31) || ((nCols - jj - *xp - 1) >> 31))continue;
							jud[ii*nCols + jj] = 1;
						}
					}
					*jud = R;
					(*hugeN)++;
					xp++;
					yp++;
					rp++;
				}
				temp = (!k) * 2 * (R + RADIUS_DIFF);
				rP += temp;
				jud += temp;
				k += (!k)*(nCols - (R + RADIUS_DIFF) * 2);
			}
		}
		imgP = RImg.data;
		for (R = minR; R < maxR; R++)
		{
			rP = imgP + (R + RADIUS_DIFF)*nCols + R + RADIUS_DIFF;
			jud = Judge + (R + RADIUS_DIFF)*nCols + R + RADIUS_DIFF;
			for (i = 0; i < angle; ++i)
			{
				keyX = (((R + RADIUS_DIFF)*angSin_half[i]) >> 16);
				keyY = (((R + RADIUS_DIFF)*angCos_half[i]) >> 16);
				bigH[i] = rP + keyX*nCols + keyY;
				keyX = (((R - RADIUS_DIFF)*angSin_half[i]) >> 16);
				keyY = (((R - RADIUS_DIFF)*angCos_half[i]) >> 16);
				smallH[i] = rP + keyX*nCols + keyY;
			}
			for (k = nCols - (R + RADIUS_DIFF) * 2 - 1, i = (nRows - (R + RADIUS_DIFF) * 2)*(k + 1); i; --i, --k, rP++, jud++)
			{
				count = 162;
				if ((*jud) == 1 || ((R < ((*jud) + min_radius_dist)) && (R >((*jud) - min_radius_dist))))
				{
					temp = (!k) * 2 * (R + RADIUS_DIFF);
					rP += temp;
					jud += temp;
					k += (!k)*(nCols - (R + RADIUS_DIFF) * 2);
					for (j = 0, bigP = bigH, smallP = smallH; j < angle; ++j)
					{
						(*bigP)++;
						(*smallP)++;
						(*bigP) += temp;
						(*smallP) += temp;
						bigP++;
						smallP++;
					}
					continue;
				}
				for (j = 0, bigP = bigH, smallP = smallH; j < angle; j++)
				{
					diff = (**bigP) - (**smallP);
					diff = !(diff >> 31)*diff + ((diff >> 31) & 1)*(-diff);
					diff -= max_circle_diff;
					count -= !(diff >> 31);
					(*bigP)++;
					(*smallP)++;
					temp = (!k) * 2 * (R + RADIUS_DIFF);
					(*bigP) += temp;
					(*smallP) += temp;
					bigP++;
					smallP++;
				}
				count = !((count - 1) >> 31);
				if (!count)
				{
					temp = (nRows - (R + RADIUS_DIFF) * 2)*(nCols - (R + RADIUS_DIFF) * 2);
					temp = temp - i;
					*xp = temp % (nCols - (R + RADIUS_DIFF) * 2) + R + RADIUS_DIFF;
					*yp = temp / (nCols - (R + RADIUS_DIFF) * 2) + R + RADIUS_DIFF;
					*rp = R;
					for (ii = -min_center_dist; ii <= min_center_dist; ii++)
					{
						for (jj = -min_center_dist; jj <= min_center_dist; jj++)
						{
							if (((ii + *yp) >> 31) || ((jj + *xp) >> 31) || ((nRows - ii - *yp - 1) >> 31) || ((nCols - jj - *xp - 1) >> 31))continue;
							jud[ii*nCols + jj] = 1;
						}
					}
					*jud = R;
					(*hugeN)++;
					xp++;
					yp++;
					rp++;
				}
				temp = (!k) * 2 * (R + RADIUS_DIFF);
				rP += temp;
				jud += temp;
				k += (!k)*(nCols - (R + RADIUS_DIFF) * 2);
			}
		}
	}
	else if (min_radius <= elge_half && max_radius <= elge_whole)
	{
		minR = elge_half;
		maxR = max_radius;
		angle = 180;
		imgP = BImg.data;
		for (R = minR; R < maxR; R++)
		{
			rP = imgP + (R + RADIUS_DIFF)*nCols + R + RADIUS_DIFF;
			jud = Judge + (R + RADIUS_DIFF)*nCols + R + RADIUS_DIFF;
			for (i = 0; i < angle; ++i)
			{
				keyX = (((R + RADIUS_DIFF)*angSin_half[i]) >> 16);
				keyY = (((R + RADIUS_DIFF)*angCos_half[i]) >> 16);
				bigH[i] = rP + keyX*nCols + keyY;
				keyX = (((R - RADIUS_DIFF)*angSin_half[i]) >> 16);
				keyY = (((R - RADIUS_DIFF)*angCos_half[i]) >> 16);
				smallH[i] = rP + keyX*nCols + keyY;
			}
			for (k = nCols - (R + RADIUS_DIFF) * 2 - 1, i = (nRows - (R + RADIUS_DIFF) * 2)*(k + 1); i; --i, --k, rP++, jud++)
			{
				count = 162;
				if ((*jud) == 1 || ((R < ((*jud) + min_radius_dist)) && (R >((*jud) - min_radius_dist))))
				{
					temp = (!k) * 2 * (R + RADIUS_DIFF);
					rP += temp;
					jud += temp;
					k += (!k)*(nCols - (R + RADIUS_DIFF) * 2);
					for (j = 0, bigP = bigH, smallP = smallH; j < angle; ++j)
					{
						(*bigP)++;
						(*smallP)++;
						(*bigP) += temp;
						(*smallP) += temp;
						bigP++;
						smallP++;
					}
					continue;
				}
				for (j = 0, bigP = bigH, smallP = smallH; j < angle; j++)
				{
					diff = (**bigP) - (**smallP);
					diff = !(diff >> 31)*diff + ((diff >> 31) & 1)*(-diff);
					diff -= max_circle_diff;
					count -= !(diff >> 31);
					(*bigP)++;
					(*smallP)++;
					temp = (!k) * 2 * (R + RADIUS_DIFF);
					(*bigP) += temp;
					(*smallP) += temp;
					bigP++;
					smallP++;
				}
				count = !((count - 1) >> 31);
				if (!count)
				{
					temp = (nRows - (R + RADIUS_DIFF) * 2)*(nCols - (R + RADIUS_DIFF) * 2);
					temp = temp - i;
					*xp = temp % (nCols - (R + RADIUS_DIFF) * 2) + R + RADIUS_DIFF;
					*yp = temp / (nCols - (R + RADIUS_DIFF) * 2) + R + RADIUS_DIFF;
					*rp = R;
					for (ii = -min_center_dist; ii <= min_center_dist; ii++)
					{
						for (jj = -min_center_dist; jj <= min_center_dist; jj++)
						{
							if (((ii + *yp) >> 31) || ((jj + *xp) >> 31) || ((nRows - ii - *yp - 1) >> 31) || ((nCols - jj - *xp - 1) >> 31))continue;
							jud[ii*nCols + jj] = 1;
						}
					}
					*jud = R;
					(*hugeN)++;
					xp++;
					yp++;
					rp++;
				}
				temp = (!k) * 2 * (R + RADIUS_DIFF);
				rP += temp;
				jud += temp;
				k += (!k)*(nCols - (R + RADIUS_DIFF) * 2);
			}
		}
		imgP = GImg.data;
		for (R = minR; R < maxR; R++)
		{
			rP = imgP + (R + RADIUS_DIFF)*nCols + R + RADIUS_DIFF;
			jud = Judge + (R + RADIUS_DIFF)*nCols + R + RADIUS_DIFF;
			for (i = 0; i < angle; ++i)
			{
				keyX = (((R + RADIUS_DIFF)*angSin_half[i]) >> 16);
				keyY = (((R + RADIUS_DIFF)*angCos_half[i]) >> 16);
				bigH[i] = rP + keyX*nCols + keyY;
				keyX = (((R - RADIUS_DIFF)*angSin_half[i]) >> 16);
				keyY = (((R - RADIUS_DIFF)*angCos_half[i]) >> 16);
				smallH[i] = rP + keyX*nCols + keyY;
			}
			for (k = nCols - (R + RADIUS_DIFF) * 2 - 1, i = (nRows - (R + RADIUS_DIFF) * 2)*(k + 1); i; --i, --k, rP++, jud++)
			{
				count = 162;
				if ((*jud) == 1 || ((R < ((*jud) + min_radius_dist)) && (R >((*jud) - min_radius_dist))))
				{
					temp = (!k) * 2 * (R + RADIUS_DIFF);
					rP += temp;
					jud += temp;
					k += (!k)*(nCols - (R + RADIUS_DIFF) * 2);
					for (j = 0, bigP = bigH, smallP = smallH; j < angle; ++j)
					{
						(*bigP)++;
						(*smallP)++;
						(*bigP) += temp;
						(*smallP) += temp;
						bigP++;
						smallP++;
					}
					continue;
				}
				for (j = 0, bigP = bigH, smallP = smallH; j < angle; j++)
				{
					diff = (**bigP) - (**smallP);
					diff = !(diff >> 31)*diff + ((diff >> 31) & 1)*(-diff);
					diff -= max_circle_diff;
					count -= !(diff >> 31);
					(*bigP)++;
					(*smallP)++;
					temp = (!k) * 2 * (R + RADIUS_DIFF);
					(*bigP) += temp;
					(*smallP) += temp;
					bigP++;
					smallP++;
				}
				count = !((count - 1) >> 31);
				if (!count)
				{
					temp = (nRows - (R + RADIUS_DIFF) * 2)*(nCols - (R + RADIUS_DIFF) * 2);
					temp = temp - i;
					*xp = temp % (nCols - (R + RADIUS_DIFF) * 2) + R + RADIUS_DIFF;
					*yp = temp / (nCols - (R + RADIUS_DIFF) * 2) + R + RADIUS_DIFF;
					*rp = R;
					for (ii = -min_center_dist; ii <= min_center_dist; ii++)
					{
						for (jj = -min_center_dist; jj <= min_center_dist; jj++)
						{
							if (((ii + *yp) >> 31) || ((jj + *xp) >> 31) || ((nRows - ii - *yp - 1) >> 31) || ((nCols - jj - *xp - 1) >> 31))continue;
							jud[ii*nCols + jj] = 1;
						}
					}
					*jud = R;
					(*hugeN)++;
					xp++;
					yp++;
					rp++;
				}
				temp = (!k) * 2 * (R + RADIUS_DIFF);
				rP += temp;
				jud += temp;
				k += (!k)*(nCols - (R + RADIUS_DIFF) * 2);
			}
		}
		imgP = RImg.data;
		for (R = minR; R < maxR; R++)
		{
			rP = imgP + (R + RADIUS_DIFF)*nCols + R + RADIUS_DIFF;
			jud = Judge + (R + RADIUS_DIFF)*nCols + R + RADIUS_DIFF;
			for (i = 0; i < angle; ++i)
			{
				keyX = (((R + RADIUS_DIFF)*angSin_half[i]) >> 16);
				keyY = (((R + RADIUS_DIFF)*angCos_half[i]) >> 16);
				bigH[i] = rP + keyX*nCols + keyY;
				keyX = (((R - RADIUS_DIFF)*angSin_half[i]) >> 16);
				keyY = (((R - RADIUS_DIFF)*angCos_half[i]) >> 16);
				smallH[i] = rP + keyX*nCols + keyY;
			}
			for (k = nCols - (R + RADIUS_DIFF) * 2 - 1, i = (nRows - (R + RADIUS_DIFF) * 2)*(k + 1); i; --i, --k, rP++, jud++)
			{
				count = 162;
				if ((*jud) == 1 || ((R < ((*jud) + min_radius_dist)) && (R >((*jud) - min_radius_dist))))
				{
					temp = (!k) * 2 * (R + RADIUS_DIFF);
					rP += temp;
					jud += temp;
					k += (!k)*(nCols - (R + RADIUS_DIFF) * 2);
					for (j = 0, bigP = bigH, smallP = smallH; j < angle; ++j)
					{
						(*bigP)++;
						(*smallP)++;
						(*bigP) += temp;
						(*smallP) += temp;
						bigP++;
						smallP++;
					}
					continue;
				}
				for (j = 0, bigP = bigH, smallP = smallH; j < angle; j++)
				{
					diff = (**bigP) - (**smallP);
					diff = !(diff >> 31)*diff + ((diff >> 31) & 1)*(-diff);
					diff -= max_circle_diff;
					count -= !(diff >> 31);
					(*bigP)++;
					(*smallP)++;
					temp = (!k) * 2 * (R + RADIUS_DIFF);
					(*bigP) += temp;
					(*smallP) += temp;
					bigP++;
					smallP++;
				}
				count = !((count - 1) >> 31);
				if (!count)
				{
					temp = (nRows - (R + RADIUS_DIFF) * 2)*(nCols - (R + RADIUS_DIFF) * 2);
					temp = temp - i;
					*xp = temp % (nCols - (R + RADIUS_DIFF) * 2) + R + RADIUS_DIFF;
					*yp = temp / (nCols - (R + RADIUS_DIFF) * 2) + R + RADIUS_DIFF;
					*rp = R;
					for (ii = -min_center_dist; ii <= min_center_dist; ii++)
					{
						for (jj = -min_center_dist; jj <= min_center_dist; jj++)
						{
							if (((ii + *yp) >> 31) || ((jj + *xp) >> 31) || ((nRows - ii - *yp - 1) >> 31) || ((nCols - jj - *xp - 1) >> 31))continue;
							jud[ii*nCols + jj] = 1;
						}
					}
					*jud = R;
					(*hugeN)++;
					xp++;
					yp++;
					rp++;
				}
				temp = (!k) * 2 * (R + RADIUS_DIFF);
				rP += temp;
				jud += temp;
				k += (!k)*(nCols - (R + RADIUS_DIFF) * 2);
			}
		}
	}
	else if (min_radius > elge_half && max_radius > elge_whole)
	{
		minR = min_radius;
		maxR = elge_whole;
		angle = 180;
		imgP = BImg.data;
		for (R = minR; R < maxR; R++)
		{
			rP = imgP + (R + RADIUS_DIFF)*nCols + R + RADIUS_DIFF;
			jud = Judge + (R + RADIUS_DIFF)*nCols + R + RADIUS_DIFF;
			for (i = 0; i < angle; ++i)
			{
				keyX = (((R + RADIUS_DIFF)*angSin_half[i]) >> 16);
				keyY = (((R + RADIUS_DIFF)*angCos_half[i]) >> 16);
				bigH[i] = rP + keyX*nCols + keyY;
				keyX = (((R - RADIUS_DIFF)*angSin_half[i]) >> 16);
				keyY = (((R - RADIUS_DIFF)*angCos_half[i]) >> 16);
				smallH[i] = rP + keyX*nCols + keyY;
			}
			for (k = nCols - (R + RADIUS_DIFF) * 2 - 1, i = (nRows - (R + RADIUS_DIFF) * 2)*(k + 1); i; --i, --k, rP++, jud++)
			{
				count = 162;
				if ((*jud) == 1 || ((R < ((*jud) + min_radius_dist)) && (R >((*jud) - min_radius_dist))))
				{
					temp = (!k) * 2 * (R + RADIUS_DIFF);
					rP += temp;
					jud += temp;
					k += (!k)*(nCols - (R + RADIUS_DIFF) * 2);
					for (j = 0, bigP = bigH, smallP = smallH; j < angle; ++j)
					{
						(*bigP)++;
						(*smallP)++;
						(*bigP) += temp;
						(*smallP) += temp;
						bigP++;
						smallP++;
					}
					continue;
				}
				for (j = 0, bigP = bigH, smallP = smallH; j < angle; j++)
				{
					diff = (**bigP) - (**smallP);
					diff = !(diff >> 31)*diff + ((diff >> 31) & 1)*(-diff);
					diff -= max_circle_diff;
					count -= !(diff >> 31);
					(*bigP)++;
					(*smallP)++;
					temp = (!k) * 2 * (R + RADIUS_DIFF);
					(*bigP) += temp;
					(*smallP) += temp;
					bigP++;
					smallP++;
				}
				count = !((count - 1) >> 31);
				if (!count)
				{
					temp = (nRows - (R + RADIUS_DIFF) * 2)*(nCols - (R + RADIUS_DIFF) * 2);
					temp = temp - i;
					*xp = temp % (nCols - (R + RADIUS_DIFF) * 2) + R + RADIUS_DIFF;
					*yp = temp / (nCols - (R + RADIUS_DIFF) * 2) + R + RADIUS_DIFF;
					*rp = R;
					for (ii = -min_center_dist; ii <= min_center_dist; ii++)
					{
						for (jj = -min_center_dist; jj <= min_center_dist; jj++)
						{
							if (((ii + *yp) >> 31) || ((jj + *xp) >> 31) || ((nRows - ii - *yp - 1) >> 31) || ((nCols - jj - *xp - 1) >> 31))continue;
							jud[ii*nCols + jj] = 1;
						}
					}
					*jud = R;
					(*hugeN)++;
					xp++;
					yp++;
					rp++;
				}
				temp = (!k) * 2 * (R + RADIUS_DIFF);
				rP += temp;
				jud += temp;
				k += (!k)*(nCols - (R + RADIUS_DIFF) * 2);
			}
		}
		imgP = GImg.data;
		for (R = minR; R < maxR; R++)
		{
			rP = imgP + (R + RADIUS_DIFF)*nCols + R + RADIUS_DIFF;
			jud = Judge + (R + RADIUS_DIFF)*nCols + R + RADIUS_DIFF;
			for (i = 0; i < angle; ++i)
			{
				keyX = (((R + RADIUS_DIFF)*angSin_half[i]) >> 16);
				keyY = (((R + RADIUS_DIFF)*angCos_half[i]) >> 16);
				bigH[i] = rP + keyX*nCols + keyY;
				keyX = (((R - RADIUS_DIFF)*angSin_half[i]) >> 16);
				keyY = (((R - RADIUS_DIFF)*angCos_half[i]) >> 16);
				smallH[i] = rP + keyX*nCols + keyY;
			}
			for (k = nCols - (R + RADIUS_DIFF) * 2 - 1, i = (nRows - (R + RADIUS_DIFF) * 2)*(k + 1); i; --i, --k, rP++, jud++)
			{
				count = 162;
				if ((*jud) == 1 || ((R < ((*jud) + min_radius_dist)) && (R >((*jud) - min_radius_dist))))
				{
					temp = (!k) * 2 * (R + RADIUS_DIFF);
					rP += temp;
					jud += temp;
					k += (!k)*(nCols - (R + RADIUS_DIFF) * 2);
					for (j = 0, bigP = bigH, smallP = smallH; j < angle; ++j)
					{
						(*bigP)++;
						(*smallP)++;
						(*bigP) += temp;
						(*smallP) += temp;
						bigP++;
						smallP++;
					}
					continue;
				}
				for (j = 0, bigP = bigH, smallP = smallH; j < angle; j++)
				{
					diff = (**bigP) - (**smallP);
					diff = !(diff >> 31)*diff + ((diff >> 31) & 1)*(-diff);
					diff -= max_circle_diff;
					count -= !(diff >> 31);
					(*bigP)++;
					(*smallP)++;
					temp = (!k) * 2 * (R + RADIUS_DIFF);
					(*bigP) += temp;
					(*smallP) += temp;
					bigP++;
					smallP++;
				}
				count = !((count - 1) >> 31);
				if (!count)
				{
					temp = (nRows - (R + RADIUS_DIFF) * 2)*(nCols - (R + RADIUS_DIFF) * 2);
					temp = temp - i;
					*xp = temp % (nCols - (R + RADIUS_DIFF) * 2) + R + RADIUS_DIFF;
					*yp = temp / (nCols - (R + RADIUS_DIFF) * 2) + R + RADIUS_DIFF;
					*rp = R;
					for (ii = -min_center_dist; ii <= min_center_dist; ii++)
					{
						for (jj = -min_center_dist; jj <= min_center_dist; jj++)
						{
							if (((ii + *yp) >> 31) || ((jj + *xp) >> 31) || ((nRows - ii - *yp - 1) >> 31) || ((nCols - jj - *xp - 1) >> 31))continue;
							jud[ii*nCols + jj] = 1;
						}
					}
					*jud = R;
					(*hugeN)++;
					xp++;
					yp++;
					rp++;
				}
				temp = (!k) * 2 * (R + RADIUS_DIFF);
				rP += temp;
				jud += temp;
				k += (!k)*(nCols - (R + RADIUS_DIFF) * 2);
			}
		}
		imgP = RImg.data;
		for (R = minR; R < maxR; R++)
		{
			rP = imgP + (R + RADIUS_DIFF)*nCols + R + RADIUS_DIFF;
			jud = Judge + (R + RADIUS_DIFF)*nCols + R + RADIUS_DIFF;
			for (i = 0; i < angle; ++i)
			{
				keyX = (((R + RADIUS_DIFF)*angSin_half[i]) >> 16);
				keyY = (((R + RADIUS_DIFF)*angCos_half[i]) >> 16);
				bigH[i] = rP + keyX*nCols + keyY;
				keyX = (((R - RADIUS_DIFF)*angSin_half[i]) >> 16);
				keyY = (((R - RADIUS_DIFF)*angCos_half[i]) >> 16);
				smallH[i] = rP + keyX*nCols + keyY;
			}
			for (k = nCols - (R + RADIUS_DIFF) * 2 - 1, i = (nRows - (R + RADIUS_DIFF) * 2)*(k + 1); i; --i, --k, rP++, jud++)
			{
				count = 162;
				if ((*jud) == 1 || ((R < ((*jud) + min_radius_dist)) && (R >((*jud) - min_radius_dist))))
				{
					temp = (!k) * 2 * (R + RADIUS_DIFF);
					rP += temp;
					jud += temp;
					k += (!k)*(nCols - (R + RADIUS_DIFF) * 2);
					for (j = 0, bigP = bigH, smallP = smallH; j < angle; ++j)
					{
						(*bigP)++;
						(*smallP)++;
						(*bigP) += temp;
						(*smallP) += temp;
						bigP++;
						smallP++;
					}
					continue;
				}
				for (j = 0, bigP = bigH, smallP = smallH; j < angle; j++)
				{
					diff = (**bigP) - (**smallP);
					diff = !(diff >> 31)*diff + ((diff >> 31) & 1)*(-diff);
					diff -= max_circle_diff;
					count -= !(diff >> 31);
					(*bigP)++;
					(*smallP)++;
					temp = (!k) * 2 * (R + RADIUS_DIFF);
					(*bigP) += temp;
					(*smallP) += temp;
					bigP++;
					smallP++;
				}
				count = !((count - 1) >> 31);
				if (!count)
				{
					temp = (nRows - (R + RADIUS_DIFF) * 2)*(nCols - (R + RADIUS_DIFF) * 2);
					temp = temp - i;
					*xp = temp % (nCols - (R + RADIUS_DIFF) * 2) + R + RADIUS_DIFF;
					*yp = temp / (nCols - (R + RADIUS_DIFF) * 2) + R + RADIUS_DIFF;
					*rp = R;
					for (ii = -min_center_dist; ii <= min_center_dist; ii++)
					{
						for (jj = -min_center_dist; jj <= min_center_dist; jj++)
						{
							if (((ii + *yp) >> 31) || ((jj + *xp) >> 31) || ((nRows - ii - *yp - 1) >> 31) || ((nCols - jj - *xp - 1) >> 31))continue;
							jud[ii*nCols + jj] = 1;
						}
					}
					*jud = R;
					(*hugeN)++;
					xp++;
					yp++;
					rp++;
				}
				temp = (!k) * 2 * (R + RADIUS_DIFF);
				rP += temp;
				jud += temp;
				k += (!k)*(nCols - (R + RADIUS_DIFF) * 2);
			}
		}
	}
	else if (min_radius > elge_half && max_radius <= elge_whole)
	{
		minR = min_radius;
		maxR = max_radius;
		angle = 180;
		imgP = BImg.data;
		for (R = minR; R < maxR; R++)
		{
			rP = imgP + (R + RADIUS_DIFF)*nCols + R + RADIUS_DIFF;
			jud = Judge + (R + RADIUS_DIFF)*nCols + R + RADIUS_DIFF;
			for (i = 0; i < angle; ++i)
			{
				keyX = (((R + RADIUS_DIFF)*angSin_half[i]) >> 16);
				keyY = (((R + RADIUS_DIFF)*angCos_half[i]) >> 16);
				bigH[i] = rP + keyX*nCols + keyY;
				keyX = (((R - RADIUS_DIFF)*angSin_half[i]) >> 16);
				keyY = (((R - RADIUS_DIFF)*angCos_half[i]) >> 16);
				smallH[i] = rP + keyX*nCols + keyY;
			}
			for (k = nCols - (R + RADIUS_DIFF) * 2 - 1, i = (nRows - (R + RADIUS_DIFF) * 2)*(k + 1); i; --i, --k, rP++, jud++)
			{
				count = 162;
				if ((*jud) == 1 || ((R < ((*jud) + min_radius_dist)) && (R >((*jud) - min_radius_dist))))
				{
					temp = (!k) * 2 * (R + RADIUS_DIFF);
					rP += temp;
					jud += temp;
					k += (!k)*(nCols - (R + RADIUS_DIFF) * 2);
					for (j = 0, bigP = bigH, smallP = smallH; j < angle; ++j)
					{
						(*bigP)++;
						(*smallP)++;
						(*bigP) += temp;
						(*smallP) += temp;
						bigP++;
						smallP++;
					}
					continue;
				}
				for (j = 0, bigP = bigH, smallP = smallH; j < angle; j++)
				{
					diff = (**bigP) - (**smallP);
					diff = !(diff >> 31)*diff + ((diff >> 31) & 1)*(-diff);
					diff -= max_circle_diff;
					count -= !(diff >> 31);
					(*bigP)++;
					(*smallP)++;
					temp = (!k) * 2 * (R + RADIUS_DIFF);
					(*bigP) += temp;
					(*smallP) += temp;
					bigP++;
					smallP++;
				}
				count = !((count - 1) >> 31);
				if (!count)
				{
					temp = (nRows - (R + RADIUS_DIFF) * 2)*(nCols - (R + RADIUS_DIFF) * 2);
					temp = temp - i;
					*xp = temp % (nCols - (R + RADIUS_DIFF) * 2) + R + RADIUS_DIFF;
					*yp = temp / (nCols - (R + RADIUS_DIFF) * 2) + R + RADIUS_DIFF;
					*rp = R;
					for (ii = -min_center_dist; ii <= min_center_dist; ii++)
					{
						for (jj = -min_center_dist; jj <= min_center_dist; jj++)
						{
							if (((ii + *yp) >> 31) || ((jj + *xp) >> 31) || ((nRows - ii - *yp - 1) >> 31) || ((nCols - jj - *xp - 1) >> 31))continue;
							jud[ii*nCols + jj] = 1;
						}
					}
					*jud = R;
					(*hugeN)++;
					xp++;
					yp++;
					rp++;
				}
				temp = (!k) * 2 * (R + RADIUS_DIFF);
				rP += temp;
				jud += temp;
				k += (!k)*(nCols - (R + RADIUS_DIFF) * 2);
			}
		}
		imgP = GImg.data;
		for (R = minR; R < maxR; R++)
		{
			rP = imgP + (R + RADIUS_DIFF)*nCols + R + RADIUS_DIFF;
			jud = Judge + (R + RADIUS_DIFF)*nCols + R + RADIUS_DIFF;
			for (i = 0; i < angle; ++i)
			{
				keyX = (((R + RADIUS_DIFF)*angSin_half[i]) >> 16);
				keyY = (((R + RADIUS_DIFF)*angCos_half[i]) >> 16);
				bigH[i] = rP + keyX*nCols + keyY;
				keyX = (((R - RADIUS_DIFF)*angSin_half[i]) >> 16);
				keyY = (((R - RADIUS_DIFF)*angCos_half[i]) >> 16);
				smallH[i] = rP + keyX*nCols + keyY;
			}
			for (k = nCols - (R + RADIUS_DIFF) * 2 - 1, i = (nRows - (R + RADIUS_DIFF) * 2)*(k + 1); i; --i, --k, rP++, jud++)
			{
				count = 162;
				if ((*jud) == 1 || ((R < ((*jud) + min_radius_dist)) && (R >((*jud) - min_radius_dist))))
				{
					temp = (!k) * 2 * (R + RADIUS_DIFF);
					rP += temp;
					jud += temp;
					k += (!k)*(nCols - (R + RADIUS_DIFF) * 2);
					for (j = 0, bigP = bigH, smallP = smallH; j < angle; ++j)
					{
						(*bigP)++;
						(*smallP)++;
						(*bigP) += temp;
						(*smallP) += temp;
						bigP++;
						smallP++;
					}
					continue;
				}
				for (j = 0, bigP = bigH, smallP = smallH; j < angle; j++)
				{
					diff = (**bigP) - (**smallP);
					diff = !(diff >> 31)*diff + ((diff >> 31) & 1)*(-diff);
					diff -= max_circle_diff;
					count -= !(diff >> 31);
					(*bigP)++;
					(*smallP)++;
					temp = (!k) * 2 * (R + RADIUS_DIFF);
					(*bigP) += temp;
					(*smallP) += temp;
					bigP++;
					smallP++;
				}
				count = !((count - 1) >> 31);
				if (!count)
				{
					temp = (nRows - (R + RADIUS_DIFF) * 2)*(nCols - (R + RADIUS_DIFF) * 2);
					temp = temp - i;
					*xp = temp % (nCols - (R + RADIUS_DIFF) * 2) + R + RADIUS_DIFF;
					*yp = temp / (nCols - (R + RADIUS_DIFF) * 2) + R + RADIUS_DIFF;
					*rp = R;
					for (ii = -min_center_dist; ii <= min_center_dist; ii++)
					{
						for (jj = -min_center_dist; jj <= min_center_dist; jj++)
						{
							if (((ii + *yp) >> 31) || ((jj + *xp) >> 31) || ((nRows - ii - *yp - 1) >> 31) || ((nCols - jj - *xp - 1) >> 31))continue;
							jud[ii*nCols + jj] = 1;
						}
					}
					*jud = R;
					(*hugeN)++;
					xp++;
					yp++;
					rp++;
				}
				temp = (!k) * 2 * (R + RADIUS_DIFF);
				rP += temp;
				jud += temp;
				k += (!k)*(nCols - (R + RADIUS_DIFF) * 2);
			}
		}
		imgP = RImg.data;
		for (R = minR; R < maxR; R++)
		{
			rP = imgP + (R + RADIUS_DIFF)*nCols + R + RADIUS_DIFF;
			jud = Judge + (R + RADIUS_DIFF)*nCols + R + RADIUS_DIFF;
			for (i = 0; i < angle; ++i)
			{
				keyX = (((R + RADIUS_DIFF)*angSin_half[i]) >> 16);
				keyY = (((R + RADIUS_DIFF)*angCos_half[i]) >> 16);
				bigH[i] = rP + keyX*nCols + keyY;
				keyX = (((R - RADIUS_DIFF)*angSin_half[i]) >> 16);
				keyY = (((R - RADIUS_DIFF)*angCos_half[i]) >> 16);
				smallH[i] = rP + keyX*nCols + keyY;
			}
			for (k = nCols - (R + RADIUS_DIFF) * 2 - 1, i = (nRows - (R + RADIUS_DIFF) * 2)*(k + 1); i; --i, --k, rP++, jud++)
			{
				count = 162;
				if ((*jud) == 1 || ((R < ((*jud) + min_radius_dist)) && (R >((*jud) - min_radius_dist))))
				{
					temp = (!k) * 2 * (R + RADIUS_DIFF);
					rP += temp;
					jud += temp;
					k += (!k)*(nCols - (R + RADIUS_DIFF) * 2);
					for (j = 0, bigP = bigH, smallP = smallH; j < angle; ++j)
					{
						(*bigP)++;
						(*smallP)++;
						(*bigP) += temp;
						(*smallP) += temp;
						bigP++;
						smallP++;
					}
					continue;
				}
				for (j = 0, bigP = bigH, smallP = smallH; j < angle; j++)
				{
					diff = (**bigP) - (**smallP);
					diff = !(diff >> 31)*diff + ((diff >> 31) & 1)*(-diff);
					diff -= max_circle_diff;
					count -= !(diff >> 31);
					(*bigP)++;
					(*smallP)++;
					temp = (!k) * 2 * (R + RADIUS_DIFF);
					(*bigP) += temp;
					(*smallP) += temp;
					bigP++;
					smallP++;
				}
				count = !((count - 1) >> 31);
				if (!count)
				{
					temp = (nRows - (R + RADIUS_DIFF) * 2)*(nCols - (R + RADIUS_DIFF) * 2);
					temp = temp - i;
					*xp = temp % (nCols - (R + RADIUS_DIFF) * 2) + R + RADIUS_DIFF;
					*yp = temp / (nCols - (R + RADIUS_DIFF) * 2) + R + RADIUS_DIFF;
					*rp = R;
					for (ii = -min_center_dist; ii <= min_center_dist; ii++)
					{
						for (jj = -min_center_dist; jj <= min_center_dist; jj++)
						{
							if (((ii + *yp) >> 31) || ((jj + *xp) >> 31) || ((nRows - ii - *yp - 1) >> 31) || ((nCols - jj - *xp - 1) >> 31))continue;
							jud[ii*nCols + jj] = 1;
						}
					}
					*jud = R;
					(*hugeN)++;
					xp++;
					yp++;
					rp++;
				}
				temp = (!k) * 2 * (R + RADIUS_DIFF);
				rP += temp;
				jud += temp;
				k += (!k)*(nCols - (R + RADIUS_DIFF) * 2);
			}
		}
	}



	if (min_radius <= elge_whole && max_radius > elge_whole)
	{
		minR = elge_whole;
		maxR = max_radius;
		angle = 360;
		imgP = BImg.data;
		for (R = minR; R < maxR; R++)
		{
			rP = imgP + (R + RADIUS_DIFF)*nCols + R + RADIUS_DIFF;
			jud = Judge + (R + RADIUS_DIFF)*nCols + R + RADIUS_DIFF;
			for (i = 0; i < angle; ++i)
			{
				keyX = (((R + RADIUS_DIFF)*angSin_whole[i]) >> 16);
				keyY = (((R + RADIUS_DIFF)*angCos_whole[i]) >> 16);
				bigW[i] = rP + keyX*nCols + keyY;
				keyX = (((R - RADIUS_DIFF)*angSin_whole[i]) >> 16);
				keyY = (((R - RADIUS_DIFF)*angCos_whole[i]) >> 16);
				smallW[i] = rP + keyX*nCols + keyY;
			}
			for (k = nCols - (R + RADIUS_DIFF) * 2 - 1, i = (nRows - (R + RADIUS_DIFF) * 2)*(k + 1); i; --i, --k, rP++, jud++)
			{
				count = 324;
				if ((*jud) == 1 || ((R < ((*jud) + min_radius_dist)) && (R > ((*jud) - min_radius_dist))))
				{
					temp = (!k) * 2 * (R + RADIUS_DIFF);
					rP += temp;
					jud += temp;
					k += (!k)*(nCols - (R + RADIUS_DIFF) * 2);
					for (j = 0, bigP = bigW, smallP = smallW; j < angle; ++j)
					{
						(*bigP)++;
						(*smallP)++;
						(*bigP) += temp;
						(*smallP) += temp;
						bigP++;
						smallP++;
					}
					continue;
				}
				for (j = 0, bigP = bigW, smallP = smallW; j < angle; j++)
				{
					diff = (**bigP) - (**smallP);
					diff = !(diff >> 31)*diff + ((diff >> 31) & 1)*(-diff);
					diff -= max_circle_diff;
					count -= !(diff >> 31);
					(*bigP)++;
					(*smallP)++;
					temp = (!k) * 2 * (R + RADIUS_DIFF);
					(*bigP) += temp;
					(*smallP) += temp;
					bigP++;
					smallP++;
				}
				count = !((count - 1) >> 31);
				if (!count)
				{
					temp = (nRows - (R + RADIUS_DIFF) * 2)*(nCols - (R + RADIUS_DIFF) * 2);
					temp = temp - i;
					*xp = temp % (nCols - (R + RADIUS_DIFF) * 2) + R + RADIUS_DIFF;
					*yp = temp / (nCols - (R + RADIUS_DIFF) * 2) + R + RADIUS_DIFF;
					*rp = R;
					for (ii = -min_center_dist; ii <= min_center_dist; ii++)
					{
						for (jj = -min_center_dist; jj <= min_center_dist; jj++)
						{
							if (((ii + *yp) >> 31) || ((jj + *xp) >> 31) || ((nRows - ii - *yp - 1) >> 31) || ((nCols - jj - *xp - 1) >> 31))continue;
							jud[ii*nCols + jj] = 1;
						}
					}
					*jud = R;
					(*hugeN)++;
					xp++;
					yp++;
					rp++;
				}
				temp = (!k) * 2 * (R + RADIUS_DIFF);
				rP += temp;
				jud += temp;
				k += (!k)*(nCols - (R + RADIUS_DIFF) * 2);
			}
		}
		imgP = GImg.data;
		for (R = minR; R < maxR; R++)
		{
			rP = imgP + (R + RADIUS_DIFF)*nCols + R + RADIUS_DIFF;
			jud = Judge + (R + RADIUS_DIFF)*nCols + R + RADIUS_DIFF;
			for (i = 0; i < angle; ++i)
			{
				keyX = (((R + RADIUS_DIFF)*angSin_whole[i]) >> 16);
				keyY = (((R + RADIUS_DIFF)*angCos_whole[i]) >> 16);
				bigW[i] = rP + keyX*nCols + keyY;
				keyX = (((R - RADIUS_DIFF)*angSin_whole[i]) >> 16);
				keyY = (((R - RADIUS_DIFF)*angCos_whole[i]) >> 16);
				smallW[i] = rP + keyX*nCols + keyY;
			}
			for (k = nCols - (R + RADIUS_DIFF) * 2 - 1, i = (nRows - (R + RADIUS_DIFF) * 2)*(k + 1); i; --i, --k, rP++, jud++)
			{
				count = 324;
				if ((*jud) == 1 || ((R < ((*jud) + min_radius_dist)) && (R >((*jud) - min_radius_dist))))
				{
					temp = (!k) * 2 * (R + RADIUS_DIFF);
					rP += temp;
					jud += temp;
					k += (!k)*(nCols - (R + RADIUS_DIFF) * 2);
					for (j = 0, bigP = bigW, smallP = smallW; j < angle; ++j)
					{
						(*bigP)++;
						(*smallP)++;
						(*bigP) += temp;
						(*smallP) += temp;
						bigP++;
						smallP++;
					}
					continue;
				}
				for (j = 0, bigP = bigW, smallP = smallW; j < angle; j++)
				{
					diff = (**bigP) - (**smallP);
					diff = !(diff >> 31)*diff + ((diff >> 31) & 1)*(-diff);
					diff -= max_circle_diff;
					count -= !(diff >> 31);
					(*bigP)++;
					(*smallP)++;
					temp = (!k) * 2 * (R + RADIUS_DIFF);
					(*bigP) += temp;
					(*smallP) += temp;
					bigP++;
					smallP++;
				}
				count = !((count - 1) >> 31);
				if (!count)
				{
					temp = (nRows - (R + RADIUS_DIFF) * 2)*(nCols - (R + RADIUS_DIFF) * 2);
					temp = temp - i;
					*xp = temp % (nCols - (R + RADIUS_DIFF) * 2) + R + RADIUS_DIFF;
					*yp = temp / (nCols - (R + RADIUS_DIFF) * 2) + R + RADIUS_DIFF;
					*rp = R;
					for (ii = -min_center_dist; ii <= min_center_dist; ii++)
					{
						for (jj = -min_center_dist; jj <= min_center_dist; jj++)
						{
							if (((ii + *yp) >> 31) || ((jj + *xp) >> 31) || ((nRows - ii - *yp - 1) >> 31) || ((nCols - jj - *xp - 1) >> 31))continue;
							jud[ii*nCols + jj] = 1;
						}
					}
					*jud = R;
					(*hugeN)++;
					xp++;
					yp++;
					rp++;
				}
				temp = (!k) * 2 * (R + RADIUS_DIFF);
				rP += temp;
				jud += temp;
				k += (!k)*(nCols - (R + RADIUS_DIFF) * 2);
			}
		}
		imgP = RImg.data;
		for (R = minR; R < maxR; R++)
		{
			rP = imgP + (R + RADIUS_DIFF)*nCols + R + RADIUS_DIFF;
			jud = Judge + (R + RADIUS_DIFF)*nCols + R + RADIUS_DIFF;
			for (i = 0; i < angle; ++i)
			{
				keyX = (((R + RADIUS_DIFF)*angSin_whole[i]) >> 16);
				keyY = (((R + RADIUS_DIFF)*angCos_whole[i]) >> 16);
				bigW[i] = rP + keyX*nCols + keyY;
				keyX = (((R - RADIUS_DIFF)*angSin_whole[i]) >> 16);
				keyY = (((R - RADIUS_DIFF)*angCos_whole[i]) >> 16);
				smallW[i] = rP + keyX*nCols + keyY;
			}
			for (k = nCols - (R + RADIUS_DIFF) * 2 - 1, i = (nRows - (R + RADIUS_DIFF) * 2)*(k + 1); i; --i, --k, rP++, jud++)
			{
				count = 324;
				if ((*jud) == 1 || ((R < ((*jud) + min_radius_dist)) && (R >((*jud) - min_radius_dist))))
				{
					temp = (!k) * 2 * (R + RADIUS_DIFF);
					rP += temp;
					jud += temp;
					k += (!k)*(nCols - (R + RADIUS_DIFF) * 2);
					for (j = 0, bigP = bigW, smallP = smallW; j < angle; ++j)
					{
						(*bigP)++;
						(*smallP)++;
						(*bigP) += temp;
						(*smallP) += temp;
						bigP++;
						smallP++;
					}
					continue;
				}
				for (j = 0, bigP = bigW, smallP = smallW; j < angle; j++)
				{
					diff = (**bigP) - (**smallP);
					diff = !(diff >> 31)*diff + ((diff >> 31) & 1)*(-diff);
					diff -= max_circle_diff;
					count -= !(diff >> 31);
					(*bigP)++;
					(*smallP)++;
					temp = (!k) * 2 * (R + RADIUS_DIFF);
					(*bigP) += temp;
					(*smallP) += temp;
					bigP++;
					smallP++;
				}
				count = !((count - 1) >> 31);
				if (!count)
				{
					temp = (nRows - (R + RADIUS_DIFF) * 2)*(nCols - (R + RADIUS_DIFF) * 2);
					temp = temp - i;
					*xp = temp % (nCols - (R + RADIUS_DIFF) * 2) + R + RADIUS_DIFF;
					*yp = temp / (nCols - (R + RADIUS_DIFF) * 2) + R + RADIUS_DIFF;
					*rp = R;
					for (ii = -min_center_dist; ii <= min_center_dist; ii++)
					{
						for (jj = -min_center_dist; jj <= min_center_dist; jj++)
						{
							if (((ii + *yp) >> 31) || ((jj + *xp) >> 31) || ((nRows - ii - *yp - 1) >> 31) || ((nCols - jj - *xp - 1) >> 31))continue;
							jud[ii*nCols + jj] = 1;
						}
					}
					*jud = R;
					(*hugeN)++;
					xp++;
					yp++;
					rp++;
				}
				temp = (!k) * 2 * (R + RADIUS_DIFF);
				rP += temp;
				jud += temp;
				k += (!k)*(nCols - (R + RADIUS_DIFF) * 2);
			}
		}
	}
	else if (min_radius > elge_whole && max_radius > elge_whole)
	{
		minR = min_radius;
		maxR = max_radius;
		angle = 360;
		imgP = BImg.data;
		for (R = minR; R < maxR; R++)
		{
			rP = imgP + (R + RADIUS_DIFF)*nCols + R + RADIUS_DIFF;
			jud = Judge + (R + RADIUS_DIFF)*nCols + R + RADIUS_DIFF;
			for (i = 0; i < angle; ++i)
			{
				keyX = (((R + RADIUS_DIFF)*angSin_whole[i]) >> 16);
				keyY = (((R + RADIUS_DIFF)*angCos_whole[i]) >> 16);
				bigW[i] = rP + keyX*nCols + keyY;
				keyX = (((R - RADIUS_DIFF)*angSin_whole[i]) >> 16);
				keyY = (((R - RADIUS_DIFF)*angCos_whole[i]) >> 16);
				smallW[i] = rP + keyX*nCols + keyY;
			}
			for (k = nCols - (R + RADIUS_DIFF) * 2 - 1, i = (nRows - (R + RADIUS_DIFF) * 2)*(k + 1); i; --i, --k, rP++, jud++)
			{
				count = 324;
				if ((*jud) == 1 || ((R < ((*jud) + min_radius_dist)) && (R >((*jud) - min_radius_dist))))
				{
					temp = (!k) * 2 * (R + RADIUS_DIFF);
					rP += temp;
					jud += temp;
					k += (!k)*(nCols - (R + RADIUS_DIFF) * 2);
					for (j = 0, bigP = bigW, smallP = smallW; j < angle; ++j)
					{
						(*bigP)++;
						(*smallP)++;
						(*bigP) += temp;
						(*smallP) += temp;
						bigP++;
						smallP++;
					}
					continue;
				}
				for (j = 0, bigP = bigW, smallP = smallW; j < angle; j++)
				{
					diff = (**bigP) - (**smallP);
					diff = !(diff >> 31)*diff + ((diff >> 31) & 1)*(-diff);
					diff -= max_circle_diff;
					count -= !(diff >> 31);
					(*bigP)++;
					(*smallP)++;
					temp = (!k) * 2 * (R + RADIUS_DIFF);
					(*bigP) += temp;
					(*smallP) += temp;
					bigP++;
					smallP++;
				}
				count = !((count - 1) >> 31);
				if (!count)
				{
					temp = (nRows - (R + RADIUS_DIFF) * 2)*(nCols - (R + RADIUS_DIFF) * 2);
					temp = temp - i;
					*xp = temp % (nCols - (R + RADIUS_DIFF) * 2) + R + RADIUS_DIFF;
					*yp = temp / (nCols - (R + RADIUS_DIFF) * 2) + R + RADIUS_DIFF;
					*rp = R;
					for (ii = -min_center_dist; ii <= min_center_dist; ii++)
					{
						for (jj = -min_center_dist; jj <= min_center_dist; jj++)
						{
							if (((ii + *yp) >> 31) || ((jj + *xp) >> 31) || ((nRows - ii - *yp - 1) >> 31) || ((nCols - jj - *xp - 1) >> 31))continue;
							jud[ii*nCols + jj] = 1;
						}
					}
					*jud = R;
					(*hugeN)++;
					xp++;
					yp++;
					rp++;
				}
				temp = (!k) * 2 * (R + RADIUS_DIFF);
				rP += temp;
				jud += temp;
				k += (!k)*(nCols - (R + RADIUS_DIFF) * 2);
			}
		}
		imgP = GImg.data;
		for (R = minR; R < maxR; R++)
		{
			rP = imgP + (R + RADIUS_DIFF)*nCols + R + RADIUS_DIFF;
			jud = Judge + (R + RADIUS_DIFF)*nCols + R + RADIUS_DIFF;
			for (i = 0; i < angle; ++i)
			{
				keyX = (((R + RADIUS_DIFF)*angSin_whole[i]) >> 16);
				keyY = (((R + RADIUS_DIFF)*angCos_whole[i]) >> 16);
				bigW[i] = rP + keyX*nCols + keyY;
				keyX = (((R - RADIUS_DIFF)*angSin_whole[i]) >> 16);
				keyY = (((R - RADIUS_DIFF)*angCos_whole[i]) >> 16);
				smallW[i] = rP + keyX*nCols + keyY;
			}
			for (k = nCols - (R + RADIUS_DIFF) * 2 - 1, i = (nRows - (R + RADIUS_DIFF) * 2)*(k + 1); i; --i, --k, rP++, jud++)
			{
				count = 324;
				if ((*jud) == 1 || ((R < ((*jud) + min_radius_dist)) && (R >((*jud) - min_radius_dist))))
				{
					temp = (!k) * 2 * (R + RADIUS_DIFF);
					rP += temp;
					jud += temp;
					k += (!k)*(nCols - (R + RADIUS_DIFF) * 2);
					for (j = 0, bigP = bigW, smallP = smallW; j < angle; ++j)
					{
						(*bigP)++;
						(*smallP)++;
						(*bigP) += temp;
						(*smallP) += temp;
						bigP++;
						smallP++;
					}
					continue;
				}
				for (j = 0, bigP = bigW, smallP = smallW; j < angle; j++)
				{
					diff = (**bigP) - (**smallP);
					diff = !(diff >> 31)*diff + ((diff >> 31) & 1)*(-diff);
					diff -= max_circle_diff;
					count -= !(diff >> 31);
					(*bigP)++;
					(*smallP)++;
					temp = (!k) * 2 * (R + RADIUS_DIFF);
					(*bigP) += temp;
					(*smallP) += temp;
					bigP++;
					smallP++;
				}
				count = !((count - 1) >> 31);
				if (!count)
				{
					temp = (nRows - (R + RADIUS_DIFF) * 2)*(nCols - (R + RADIUS_DIFF) * 2);
					temp = temp - i;
					*xp = temp % (nCols - (R + RADIUS_DIFF) * 2) + R + RADIUS_DIFF;
					*yp = temp / (nCols - (R + RADIUS_DIFF) * 2) + R + RADIUS_DIFF;
					*rp = R;
					for (ii = -min_center_dist; ii <= min_center_dist; ii++)
					{
						for (jj = -min_center_dist; jj <= min_center_dist; jj++)
						{
							if (((ii + *yp) >> 31) || ((jj + *xp) >> 31) || ((nRows - ii - *yp - 1) >> 31) || ((nCols - jj - *xp - 1) >> 31))continue;
							jud[ii*nCols + jj] = 1;
						}
					}
					*jud = R;
					(*hugeN)++;
					xp++;
					yp++;
					rp++;
				}
				temp = (!k) * 2 * (R + RADIUS_DIFF);
				rP += temp;
				jud += temp;
				k += (!k)*(nCols - (R + RADIUS_DIFF) * 2);
			}
		}
		imgP = RImg.data;
		for (R = minR; R < maxR; R++)
		{
			rP = imgP + (R + RADIUS_DIFF)*nCols + R + RADIUS_DIFF;
			jud = Judge + (R + RADIUS_DIFF)*nCols + R + RADIUS_DIFF;
			for (i = 0; i < angle; ++i)
			{
				keyX = (((R + RADIUS_DIFF)*angSin_whole[i]) >> 16);
				keyY = (((R + RADIUS_DIFF)*angCos_whole[i]) >> 16);
				bigW[i] = rP + keyX*nCols + keyY;
				keyX = (((R - RADIUS_DIFF)*angSin_whole[i]) >> 16);
				keyY = (((R - RADIUS_DIFF)*angCos_whole[i]) >> 16);
				smallW[i] = rP + keyX*nCols + keyY;
			}
			for (k = nCols - (R + RADIUS_DIFF) * 2 - 1, i = (nRows - (R + RADIUS_DIFF) * 2)*(k + 1); i; --i, --k, rP++, jud++)
			{
				count = 324;
				if ((*jud) == 1 || ((R < ((*jud) + min_radius_dist)) && (R >((*jud) - min_radius_dist))))
				{
					temp = (!k) * 2 * (R + RADIUS_DIFF);
					rP += temp;
					jud += temp;
					k += (!k)*(nCols - (R + RADIUS_DIFF) * 2);
					for (j = 0, bigP = bigW, smallP = smallW; j < angle; ++j)
					{
						(*bigP)++;
						(*smallP)++;
						(*bigP) += temp;
						(*smallP) += temp;
						bigP++;
						smallP++;
					}
					continue;
				}
				for (j = 0, bigP = bigW, smallP = smallW; j < angle; j++)
				{
					diff = (**bigP) - (**smallP);
					diff = !(diff >> 31)*diff + ((diff >> 31) & 1)*(-diff);
					diff -= max_circle_diff;
					count -= !(diff >> 31);
					(*bigP)++;
					(*smallP)++;
					temp = (!k) * 2 * (R + RADIUS_DIFF);
					(*bigP) += temp;
					(*smallP) += temp;
					bigP++;
					smallP++;
				}
				count = !((count - 1) >> 31);
				if (!count)
				{
					temp = (nRows - (R + RADIUS_DIFF) * 2)*(nCols - (R + RADIUS_DIFF) * 2);
					temp = temp - i;
					*xp = temp % (nCols - (R + RADIUS_DIFF) * 2) + R + RADIUS_DIFF;
					*yp = temp / (nCols - (R + RADIUS_DIFF) * 2) + R + RADIUS_DIFF;
					*rp = R;
					for (ii = -min_center_dist; ii <= min_center_dist; ii++)
					{
						for (jj = -min_center_dist; jj <= min_center_dist; jj++)
						{
							if (((ii + *yp) >> 31) || ((jj + *xp) >> 31) || ((nRows - ii - *yp - 1) >> 31) || ((nCols - jj - *xp - 1) >> 31))continue;
							jud[ii*nCols + jj] = 1;
						}
					}
					*jud = R;
					(*hugeN)++;
					xp++;
					yp++;
					rp++;
				}
				temp = (!k) * 2 * (R + RADIUS_DIFF);
				rP += temp;
				jud += temp;
				k += (!k)*(nCols - (R + RADIUS_DIFF) * 2);
			}
		}
	}

	if ((*hugeN) > max_circle)
	{
		for (i = 0; i < max_circle; i++)
		{
			for (j = i + 1; j < *hugeN; j++)
			{
				if (hugeR[j] > hugeR[i])
				{
					temp = hugeR[i];
					hugeR[i] = hugeR[j];
					hugeR[j] = temp;
				}
			}
		}
		*hugeN = max_circle;
	}
	for (i = 0; i < *hugeN; i++)
	{
		x[i] = hugeX[i];
		y[i] = hugeY[i];
		radius[i] = hugeR[i];
	}
	*circle_cnt = *hugeN;
	return MY_OK;
}
