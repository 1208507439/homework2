#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
#define Radius180 150
#define Radius90 60
const int SinTable360[360] = {	0,1144,2287,3430,4572,5712,6850,7987,9121,10252,11380,12505,13626,14742,15855,16962,18064,19161,20252,21336,22415,23486,24550,25607,26656,27697,28729,29753,30767,31772,32768,33754,34729,35693,36647,37590,38521,39441,40348,41243,42126,42995,43852,44695,45525,46341,47143,47930,48703,49461,50203,50931,51643,52339,53020,53684,54332,54963,55578,56175,56756,57319,57865,58393,58903,59396,59870,60326,60764,61183,61584,61966,62328,62672,62997,63303,63589,63856,64104,64332,64540,64729,64898,65048,65177,65287,65376,65446,65496,65526,
							65536,65526,65496,65446,65376,65287,65177,65048,64898,64729,64540,64332,64104,63856,63589,63303,62997,62672,62328,61966,61584,61183,60764,60326,59870,59396,58903,58393,57865,57319,56756,56175,55578,54963,54332,53684,53020,52339,51643,50931,50203,49461,48703,47930,47143,46341,45525,44695,43852,42995,42126,41243,40348,39441,38521,37590,36647,35693,34729,33754,32768,31772,30767,29753,28729,27697,26656,25607,24550,23486,22415,21336,20252,19161,18064,16962,15855,14742,13626,12505,11380,10252,9121,7987,6850,5712,4572,3430,2287,1144,
							0,-1144,-2287,-3430,-4572,-5712,-6850,-7987,-9121,-10252,-11380,-12505,-13626,-14742,-15855,-16962,-18064,-19161,-20252,-21336,-22415,-23486,-24550,-25607,-26656,-27697,-28729,-29753,-30767,-31772,-32768,-33754,-34729,-35693,-36647,-37590,-38521,-39441,-40348,-41243,-42126,-42995,-43852,-44695,-45525,-46341,-47143,-47930,-48703,-49461,-50203,-50931,-51643,-52339,-53020,-53684,-54332,-54963,-55578,-56175,-56756,-57319,-57865,-58393,-58903,-59396,-59870,-60326,-60764,-61183,-61584,-61966,-62328,-62672,-62997,-63303,-63589,-63856,-64104,-64332,-64540,-64729,-64898,-65048,-65177,-65287,-65376,-65446,-65496,-65526,
							-65536,-65526,-65496,-65446,-65376,-65287,-65177,-65048,-64898,-64729,-64540,-64332,-64104,-63856,-63589,-63303,-62997,-62672,-62328,-61966,-61584,-61183,-60764,-60326,-59870,-59396,-58903,-58393,-57865,-57319,-56756,-56175,-55578,-54963,-54332,-53684,-53020,-52339,-51643,-50931,-50203,-49461,-48703,-47930,-47143,-46341,-45525,-44695,-43852,-42995,-42126,-41243,-40348,-39441,-38521,-37590,-36647,-35693,-34729,-33754,-32768,-31772,-30767,-29753,-28729,-27697,-26656,-25607,-24550,-23486,-22415,-21336,-20252,-19161,-18064,-16962,-15855,-14742,-13626,-12505,-11380,-10252,-9121,-7987,-6850,-5712,-4572,-3430,-2287,-1144
						};
const int CosTable360[360] = {	65536,65526,65496,65446,65376,65287,65177,65048,64898,64729,64540,64332,64104,63856,63589,63303,62997,62672,62328,61966,61584,61183,60764,60326,59870,59396,58903,58393,57865,57319,56756,56175,55578,54963,54332,53684,53020,52339,51643,50931,50203,49461,48703,47930,47143,46341,45525,44695,43852,42995,42126,41243,40348,39441,38521,37590,36647,35693,34729,33754,32768,31772,30767,29753,28729,27697,26656,25607,24550,23486,22415,21336,20252,19161,18064,16962,15855,14742,13626,12505,11380,10252,9121,7987,6850,5712,4572,3430,2287,1144,
							0,-1144,-2287,-3430,-4572,-5712,-6850,-7987,-9121,-10252,-11380,-12505,-13626,-14742,-15855,-16962,-18064,-19161,-20252,-21336,-22415,-23486,-24550,-25607,-26656,-27697,-28729,-29753,-30767,-31772,-32768,-33754,-34729,-35693,-36647,-37590,-38521,-39441,-40348,-41243,-42126,-42995,-43852,-44695,-45525,-46341,-47143,-47930,-48703,-49461,-50203,-50931,-51643,-52339,-53020,-53684,-54332,-54963,-55578,-56175,-56756,-57319,-57865,-58393,-58903,-59396,-59870,-60326,-60764,-61183,-61584,-61966,-62328,-62672,-62997,-63303,-63589,-63856,-64104,-64332,-64540,-64729,-64898,-65048,-65177,-65287,-65376,-65446,-65496,-65526,
							-65536,-65526,-65496,-65446,-65376,-65287,-65177,-65048,-64898,-64729,-64540,-64332,-64104,-63856,-63589,-63303,-62997,-62672,-62328,-61966,-61584,-61183,-60764,-60326,-59870,-59396,-58903,-58393,-57865,-57319,-56756,-56175,-55578,-54963,-54332,-53684,-53020,-52339,-51643,-50931,-50203,-49461,-48703,-47930,-47143,-46341,-45525,-44695,-43852,-42995,-42126,-41243,-40348,-39441,-38521,-37590,-36647,-35693,-34729,-33754,-32768,-31772,-30767,-29753,-28729,-27697,-26656,-25607,-24550,-23486,-22415,-21336,-20252,-19161,-18064,-16962,-15855,-14742,-13626,-12505,-11380,-10252,-9121,-7987,-6850,-5712,-4572,-3430,-2287,-1144,
							0,1144,2287,3430,4572,5712,6850,7987,9121,10252,11380,12505,13626,14742,15855,16962,18064,19161,20252,21336,22415,23486,24550,25607,26656,27697,28729,29753,30767,31772,32768,33754,34729,35693,36647,37590,38521,39441,40348,41243,42126,42995,43852,44695,45525,46341,47143,47930,48703,49461,50203,50931,51643,52339,53020,53684,54332,54963,55578,56175,56756,57319,57865,58393,58903,59396,59870,60326,60764,61183,61584,61966,62328,62672,62997,63303,63589,63856,64104,64332,64540,64729,64898,65048,65177,65287,65376,65446,65496,65526
						};
const int SinTable180[180]  = {	0,2287,4571,6850,9120,11380,13625,15854,18064,20251,22414,24550,26655,28729,30767,32767,34728,36647,38521,40347,42125,43852,45525,47142,48702,50203,51643,53019,54331,55577,56755,57864,58903,59870,60763,61583,62328,62997,63589,64103,64540,64898,65176,65376,65496,65536,65496,65376,65176,64898,64540,64103,63589,62997,62328,61583,60763,59870,58903,57864,56755,55577,54331,53019,51643,50203,48702,47142,45525,43852,42125,40347,38521,36647,34728,32767,30767,28729,26655,24550,22414,20251,18064,15854,13625,11380,9120,6850,4571,2287,
							0,-2287,-4571,-6850,-9120,-11380,-13625,-15854,-18064,-20251,-22414,-24550,-26655,-28729,-30767,-32768,-34728,-36647,-38521,-40347,-42125,-43852,-45525,-47142,-48702,-50203,-51643,-53019,-54331,-55577,-56755,-57864,-58903,-59870,-60763,-61583,-62328,-62997,-63589,-64103,-64540,-64898,-65176,-65376,-65496,-65536,-65496,-65376,-65176,-64898,-64540,-64103,-63589,-62997,-62328,-61583,-60763,-59870,-58903,-57864,-56755,-55577,-54331,-53019,-51643,-50203,-48702,-47142,-45525,-43852,-42125,-40347,-38521,-36647,-34728,-32768,-30767,-28729,-26655,-24550,-22414,-20251,-18064,-15854,-13625,-11380,-9120,-6850,-4571,-2287
						};
const int CosTable180[180]  = {	65536,65496,65376,65176,64898,64540,64103,63589,62997,62328,61583,60763,59870,58903,57864,56755,55577,54331,53019,51643,50203,48702,47142,45525,43852,42125,40347,38521,36647,34728,32768,30767,28729,26655,24550,22414,20251,18064,15854,13625,11380,9120,6850,4571,2287,0,-2287,-4571,-6850,-9120,-11380,-13625,-15854,-18064,-20251,-22414,-24550,-26655,-28729,-30767,-32767,-34728,-36647,-38521,-40347,-42125,-43852,-45525,-47142,-48702,-50203,-51643,-53019,-54331,-55577,-56755,-57864,-58903,-59870,-60763,-61583,-62328,-62997,-63589,-64103,-64540,-64898,-65176,-65376,-65496,
							-65536,-65496,-65376,-65176,-64898,-64540,-64103,-63589,-62997,-62328,-61583,-60763,-59870,-58903,-57864,-56755,-55577,-54331,-53019,-51643,-50203,-48702,-47142,-45525,-43852,-42125,-40347,-38521,-36647,-34728,-32768,-30767,-28729,-26655,-24550,-22414,-20251,-18064,-15854,-13625,-11380,-9120,-6850,-4571,-2287,0,2287,4571,6850,9120,11380,13625,15854,18064,20251,22414,24550,26655,28729,30767,32768,34728,36647,38521,40347,42125,43852,45525,47142,48702,50203,51643,53019,54331,55577,56755,57864,58903,59870,60763,61583,62328,62997,63589,64103,64540,64898,65176,65376,65496
						};
const int SinTable90[90]    = {	0,4571,9120,13625,18064,22414,26655,30767,34728,38521,42125,45525,48702,51643,54331,56755,58903,60763,62328,63589,64540,65176,65496,65496,65176,64540,63589,62328,60763,58903,56755,54331,51643,48702,45525,42125,38521,34728,30767,26655,22414,18064,13625,9120,4571,0,-4571,-9120,-13625,-18064,-22414,-26655,-30767,-34728,-38521,-42125,-45525,-48702,-51643,-54331,-56755,-58903,-60763,-62328,-63589,-64540,-65176,-65496,-65496,-65176,-64540,-63589,-62328,-60763,-58903,-56755,-54331,-51643,-48702,-45525,-42125,-38521,-34728,-30767,-26655,-22414,-18064,-13625,-9120,-4571
						};
const int CosTable90[90]    = {	65536,65376,64898,64103,62997,61583,59870,57864,55577,53019,50203,47142,43852,40347,36647,32768,28729,24550,20251,15854,11380,6850,2287,-2287,-6850,-11380,-15854,-20251,-24550,-28729,-32767,-36647,-40347,-43852,-47142,-50203,-53019,-55577,-57864,-59870,-61583,-62997,-64103,-64898,-65376,-65536,-65376,-64898,-64103,-62997,-61583,-59870,-57864,-55577,-53019,-50203,-47142,-43852,-40347,-36647,-32768,-28729,-24550,-20251,-15854,-11380,-6850,-2287,2287,6850,11380,15854,20251,24550,28729,32768,36647,40347,43852,47142,50203,53019,55577,57864,59870,61583,62997,64103,64898,65376
						};


int ustc_Find_Circles_By_Difference(Mat colorImg, int min_radius, int max_radius, int min_center_dist, int min_radius_dist, int max_circle_diff, int* x, int* y, int* radius, int* circle_cnt, int max_circle)
{
	if (NULL == colorImg.data)
	{
		cout << "image is NULL." << endl;
		return MY_FAIL;
	}
	Mat blueImg, greenImg, redImg;
	uchar *outerCirclePtr360[360], *innerCirclePtr360[360];
	uchar *outerCirclePtr180[180], *innerCirclePtr180[180];
	uchar *outerCirclePtr90[90], *innerCirclePtr90[90];
	uchar *colorImgPtr, *blueImgPtr, *greenImgPtr, *redImgPtr;
	uchar *imageHeadPtr, *imagePtr;
	uchar **outerArrayPtr, **innerArrayPtr;
	const int imageRows = colorImg.rows;
	const int imageCols = colorImg.cols;
	const int radiusDiff = 5;
	int *tempResultX = new int[10000]();
	int *tempResultY = new int[10000]();
	int *tempReslutR = new int[10000]();
	int *tempResultN = new int(0);
	int *circleJudgeArray = new int[imageRows*imageCols]();
	int *tempXPtr, *tempYPtr, *tempRPtr, *judgePtr;
	int minRadius, maxRadius;
	int centerDist_i, centerDist_j;
	int tempOffsetX, tempOffsetY;
	int tempDiff, tempAngle;
	int resetMaxRadius;
	int i, j, k;
	int indexRadius;
	int outerCircleSum, innerCiecleSum;
	int temp;
	blueImg.create(imageRows, imageCols, CV_8UC1);
	greenImg.create(imageRows, imageCols, CV_8UC1);
	redImg.create(imageRows, imageCols, CV_8UC1);
	colorImgPtr = colorImg.data;
	blueImgPtr = blueImg.data;
	greenImgPtr = greenImg.data;
	redImgPtr = redImg.data;
	tempXPtr = tempResultX;
	tempYPtr = tempResultY;
	tempRPtr = tempReslutR;
	resetMaxRadius = max_radius;
	if (((resetMaxRadius + radiusDiff) * 2 + 1) > imageRows)
	{
		resetMaxRadius = (imageRows - 1) / 2 - radiusDiff;
	}
	if (((resetMaxRadius + radiusDiff) * 2 + 1) > imageCols)
	{
		resetMaxRadius = (imageCols - 1) / 2 - radiusDiff;
	}
	for (i = imageRows*imageCols; i; i--)
	{
		*blueImgPtr++ = *colorImgPtr++;
		*greenImgPtr++ = *colorImgPtr++;
		*redImgPtr++ = *colorImgPtr++;
	}
	if (min_radius <= Radius90 && resetMaxRadius > Radius90)
	{
		minRadius = min_radius;
		maxRadius = Radius90;
		tempAngle = 90;
		imageHeadPtr = blueImg.data;
		for (indexRadius = maxRadius; indexRadius >= minRadius; indexRadius--)
		{
			imagePtr = imageHeadPtr + (indexRadius + radiusDiff)*imageCols + indexRadius + radiusDiff;
			judgePtr = circleJudgeArray + (indexRadius + radiusDiff)*imageCols + indexRadius + radiusDiff;
			for (i = 0; i < tempAngle; ++i)
			{
				tempOffsetX = (((indexRadius + radiusDiff)*SinTable90[i]) >> 16);
				tempOffsetY = (((indexRadius + radiusDiff)*CosTable90[i]) >> 16);
				outerCirclePtr90[i] = imagePtr + tempOffsetX*imageCols + tempOffsetY;
				tempOffsetX = (((indexRadius - radiusDiff)*SinTable90[i]) >> 16);
				tempOffsetY = (((indexRadius - radiusDiff)*CosTable90[i]) >> 16);
				innerCirclePtr90[i] = imagePtr + tempOffsetX*imageCols + tempOffsetY;
			}
			for (k = imageCols - (indexRadius + radiusDiff) * 2 - 1, i = (imageRows - (indexRadius + radiusDiff) * 2)*(k + 1); i; --i, --k, imagePtr++, judgePtr++)
			{
				if ((*judgePtr) == 1 || ((indexRadius < ((*judgePtr) + min_radius_dist)) && (indexRadius >((*judgePtr) - min_radius_dist))))
				{
					temp = (!k) * 2 * (indexRadius + radiusDiff);
					imagePtr += temp;
					judgePtr += temp;
					k += (!k)*(imageCols - (indexRadius + radiusDiff) * 2);
					for (j = 0, outerArrayPtr = outerCirclePtr90, innerArrayPtr = innerCirclePtr90; j < tempAngle; ++j)
					{
						(*outerArrayPtr)++;
						(*innerArrayPtr)++;
						(*outerArrayPtr) += temp;
						(*innerArrayPtr) += temp;
						outerArrayPtr++;
						innerArrayPtr++;
					}
					continue;
				}
				outerCircleSum = innerCiecleSum = 0;
				for (j = 0, outerArrayPtr = outerCirclePtr90, innerArrayPtr = innerCirclePtr90; j < tempAngle; j++)
				{
					tempDiff = (**outerArrayPtr) - (**innerArrayPtr);
					tempDiff = !(tempDiff >> 31)*tempDiff + ((tempDiff >> 31) & 1)*(-tempDiff);
					tempDiff -= max_circle_diff;
					outerCircleSum += (**outerArrayPtr);
					innerCiecleSum += (**innerArrayPtr);
					(*outerArrayPtr)++;
					(*innerArrayPtr)++;
					temp = (!k) * 2 * (indexRadius + radiusDiff);
					(*outerArrayPtr) += temp;
					(*innerArrayPtr) += temp;
					outerArrayPtr++;
					innerArrayPtr++;
				}
				tempDiff = outerCircleSum - innerCiecleSum;
				tempDiff = !(tempDiff >> 31)*tempDiff + ((tempDiff >> 31) & 1)*(-tempDiff);
				if ((tempDiff / tempAngle) > max_circle_diff)
				{
					temp = (imageRows - (indexRadius + radiusDiff) * 2)*(imageCols - (indexRadius + radiusDiff) * 2);
					temp = temp - i;
					*tempXPtr = temp % (imageCols - (indexRadius + radiusDiff) * 2) + indexRadius + radiusDiff;
					*tempYPtr = temp / (imageCols - (indexRadius + radiusDiff) * 2) + indexRadius + radiusDiff;
					*tempRPtr = indexRadius;
					for (centerDist_i = -min_center_dist; centerDist_i <= min_center_dist; centerDist_i++)
					{
						for (centerDist_j = -min_center_dist; centerDist_j <= min_center_dist; centerDist_j++)
						{
							if (((centerDist_i + *tempYPtr) >> 31) || ((centerDist_j + *tempXPtr) >> 31) || ((imageRows - centerDist_i - *tempYPtr - 1) >> 31) || ((imageCols - centerDist_j - *tempXPtr - 1) >> 31))continue;
							judgePtr[centerDist_i*imageCols + centerDist_j] = 1;
						}
					}
					*judgePtr = indexRadius;
					(*tempResultN)++;
					tempXPtr++;
					tempYPtr++;
					tempRPtr++;
				}
				temp = (!k) * 2 * (indexRadius + radiusDiff);
				imagePtr += temp;
				judgePtr += temp;
				k += (!k)*(imageCols - (indexRadius + radiusDiff) * 2);
			}
		}
		imageHeadPtr = greenImg.data;
		for (indexRadius = maxRadius; indexRadius >= minRadius; indexRadius--)
		{
			imagePtr = imageHeadPtr + (indexRadius + radiusDiff)*imageCols + indexRadius + radiusDiff;
			judgePtr = circleJudgeArray + (indexRadius + radiusDiff)*imageCols + indexRadius + radiusDiff;
			for (i = 0; i < tempAngle; ++i)
			{
				tempOffsetX = (((indexRadius + radiusDiff)*SinTable90[i]) >> 16);
				tempOffsetY = (((indexRadius + radiusDiff)*CosTable90[i]) >> 16);
				outerCirclePtr90[i] = imagePtr + tempOffsetX*imageCols + tempOffsetY;
				tempOffsetX = (((indexRadius - radiusDiff)*SinTable90[i]) >> 16);
				tempOffsetY = (((indexRadius - radiusDiff)*CosTable90[i]) >> 16);
				innerCirclePtr90[i] = imagePtr + tempOffsetX*imageCols + tempOffsetY;
			}
			for (k = imageCols - (indexRadius + radiusDiff) * 2 - 1, i = (imageRows - (indexRadius + radiusDiff) * 2)*(k + 1); i; --i, --k, imagePtr++, judgePtr++)
			{
				if ((*judgePtr) == 1 || ((indexRadius < ((*judgePtr) + min_radius_dist)) && (indexRadius >((*judgePtr) - min_radius_dist))))
				{
					temp = (!k) * 2 * (indexRadius + radiusDiff);
					imagePtr += temp;
					judgePtr += temp;
					k += (!k)*(imageCols - (indexRadius + radiusDiff) * 2);
					for (j = 0, outerArrayPtr = outerCirclePtr90, innerArrayPtr = innerCirclePtr90; j < tempAngle; ++j)
					{
						(*outerArrayPtr)++;
						(*innerArrayPtr)++;
						(*outerArrayPtr) += temp;
						(*innerArrayPtr) += temp;
						outerArrayPtr++;
						innerArrayPtr++;
					}
					continue;
				}
				outerCircleSum = innerCiecleSum = 0;
				for (j = 0, outerArrayPtr = outerCirclePtr90, innerArrayPtr = innerCirclePtr90; j < tempAngle; j++)
				{
					tempDiff = (**outerArrayPtr) - (**innerArrayPtr);
					tempDiff = !(tempDiff >> 31)*tempDiff + ((tempDiff >> 31) & 1)*(-tempDiff);
					tempDiff -= max_circle_diff;
					outerCircleSum += (**outerArrayPtr);
					innerCiecleSum += (**innerArrayPtr);
					(*outerArrayPtr)++;
					(*innerArrayPtr)++;
					temp = (!k) * 2 * (indexRadius + radiusDiff);
					(*outerArrayPtr) += temp;
					(*innerArrayPtr) += temp;
					outerArrayPtr++;
					innerArrayPtr++;
				}
				tempDiff = outerCircleSum - innerCiecleSum;
				tempDiff = !(tempDiff >> 31)*tempDiff + ((tempDiff >> 31) & 1)*(-tempDiff);
				if ((tempDiff / tempAngle) > max_circle_diff)
				{
					temp = (imageRows - (indexRadius + radiusDiff) * 2)*(imageCols - (indexRadius + radiusDiff) * 2);
					temp = temp - i;
					*tempXPtr = temp % (imageCols - (indexRadius + radiusDiff) * 2) + indexRadius + radiusDiff;
					*tempYPtr = temp / (imageCols - (indexRadius + radiusDiff) * 2) + indexRadius + radiusDiff;
					*tempRPtr = indexRadius;
					for (centerDist_i = -min_center_dist; centerDist_i <= min_center_dist; centerDist_i++)
					{
						for (centerDist_j = -min_center_dist; centerDist_j <= min_center_dist; centerDist_j++)
						{
							if (((centerDist_i + *tempYPtr) >> 31) || ((centerDist_j + *tempXPtr) >> 31) || ((imageRows - centerDist_i - *tempYPtr - 1) >> 31) || ((imageCols - centerDist_j - *tempXPtr - 1) >> 31))continue;
							judgePtr[centerDist_i*imageCols + centerDist_j] = 1;
						}
					}
					*judgePtr = indexRadius;
					(*tempResultN)++;
					tempXPtr++;
					tempYPtr++;
					tempRPtr++;
				}
				temp = (!k) * 2 * (indexRadius + radiusDiff);
				imagePtr += temp;
				judgePtr += temp;
				k += (!k)*(imageCols - (indexRadius + radiusDiff) * 2);
			}
		}
		imageHeadPtr = redImg.data;
		for (indexRadius = maxRadius; indexRadius >= minRadius; indexRadius--)
		{
			imagePtr = imageHeadPtr + (indexRadius + radiusDiff)*imageCols + indexRadius + radiusDiff;
			judgePtr = circleJudgeArray + (indexRadius + radiusDiff)*imageCols + indexRadius + radiusDiff;
			for (i = 0; i < tempAngle; ++i)
			{
				tempOffsetX = (((indexRadius + radiusDiff)*SinTable90[i]) >> 16);
				tempOffsetY = (((indexRadius + radiusDiff)*CosTable90[i]) >> 16);
				outerCirclePtr90[i] = imagePtr + tempOffsetX*imageCols + tempOffsetY;
				tempOffsetX = (((indexRadius - radiusDiff)*SinTable90[i]) >> 16);
				tempOffsetY = (((indexRadius - radiusDiff)*CosTable90[i]) >> 16);
				innerCirclePtr90[i] = imagePtr + tempOffsetX*imageCols + tempOffsetY;
			}
			for (k = imageCols - (indexRadius + radiusDiff) * 2 - 1, i = (imageRows - (indexRadius + radiusDiff) * 2)*(k + 1); i; --i, --k, imagePtr++, judgePtr++)
			{
				if ((*judgePtr) == 1 || ((indexRadius < ((*judgePtr) + min_radius_dist)) && (indexRadius >((*judgePtr) - min_radius_dist))))
				{
					temp = (!k) * 2 * (indexRadius + radiusDiff);
					imagePtr += temp;
					judgePtr += temp;
					k += (!k)*(imageCols - (indexRadius + radiusDiff) * 2);
					for (j = 0, outerArrayPtr = outerCirclePtr90, innerArrayPtr = innerCirclePtr90; j < tempAngle; ++j)
					{
						(*outerArrayPtr)++;
						(*innerArrayPtr)++;
						(*outerArrayPtr) += temp;
						(*innerArrayPtr) += temp;
						outerArrayPtr++;
						innerArrayPtr++;
					}
					continue;
				}
				outerCircleSum = innerCiecleSum = 0;
				for (j = 0, outerArrayPtr = outerCirclePtr90, innerArrayPtr = innerCirclePtr90; j < tempAngle; j++)
				{
					tempDiff = (**outerArrayPtr) - (**innerArrayPtr);
					tempDiff = !(tempDiff >> 31)*tempDiff + ((tempDiff >> 31) & 1)*(-tempDiff);
					tempDiff -= max_circle_diff;
					outerCircleSum += (**outerArrayPtr);
					innerCiecleSum += (**innerArrayPtr);
					(*outerArrayPtr)++;
					(*innerArrayPtr)++;
					temp = (!k) * 2 * (indexRadius + radiusDiff);
					(*outerArrayPtr) += temp;
					(*innerArrayPtr) += temp;
					outerArrayPtr++;
					innerArrayPtr++;
				}
				tempDiff = outerCircleSum - innerCiecleSum;
				tempDiff = !(tempDiff >> 31)*tempDiff + ((tempDiff >> 31) & 1)*(-tempDiff);
				if ((tempDiff / tempAngle) > max_circle_diff)
				{
					temp = (imageRows - (indexRadius + radiusDiff) * 2)*(imageCols - (indexRadius + radiusDiff) * 2);
					temp = temp - i;
					*tempXPtr = temp % (imageCols - (indexRadius + radiusDiff) * 2) + indexRadius + radiusDiff;
					*tempYPtr = temp / (imageCols - (indexRadius + radiusDiff) * 2) + indexRadius + radiusDiff;
					*tempRPtr = indexRadius;
					for (centerDist_i = -min_center_dist; centerDist_i <= min_center_dist; centerDist_i++)
					{
						for (centerDist_j = -min_center_dist; centerDist_j <= min_center_dist; centerDist_j++)
						{
							if (((centerDist_i + *tempYPtr) >> 31) || ((centerDist_j + *tempXPtr) >> 31) || ((imageRows - centerDist_i - *tempYPtr - 1) >> 31) || ((imageCols - centerDist_j - *tempXPtr - 1) >> 31))continue;
							judgePtr[centerDist_i*imageCols + centerDist_j] = 1;
						}
					}
					*judgePtr = indexRadius;
					(*tempResultN)++;
					tempXPtr++;
					tempYPtr++;
					tempRPtr++;
				}
				temp = (!k) * 2 * (indexRadius + radiusDiff);
				imagePtr += temp;
				judgePtr += temp;
				k += (!k)*(imageCols - (indexRadius + radiusDiff) * 2);
			}
		}
	}
	else if (min_radius <= Radius90 && resetMaxRadius <= Radius90)
	{
		minRadius = min_radius;
		maxRadius = resetMaxRadius;
		tempAngle = 90;
		imageHeadPtr = blueImg.data;
		for (indexRadius = maxRadius; indexRadius >= minRadius; indexRadius--)
		{
			imagePtr = imageHeadPtr + (indexRadius + radiusDiff)*imageCols + indexRadius + radiusDiff;
			judgePtr = circleJudgeArray + (indexRadius + radiusDiff)*imageCols + indexRadius + radiusDiff;
			for (i = 0; i < tempAngle; ++i)
			{
				tempOffsetX = (((indexRadius + radiusDiff)*SinTable90[i]) >> 16);
				tempOffsetY = (((indexRadius + radiusDiff)*CosTable90[i]) >> 16);
				outerCirclePtr90[i] = imagePtr + tempOffsetX*imageCols + tempOffsetY;
				tempOffsetX = (((indexRadius - radiusDiff)*SinTable90[i]) >> 16);
				tempOffsetY = (((indexRadius - radiusDiff)*CosTable90[i]) >> 16);
				innerCirclePtr90[i] = imagePtr + tempOffsetX*imageCols + tempOffsetY;
			}
			for (k = imageCols - (indexRadius + radiusDiff) * 2 - 1, i = (imageRows - (indexRadius + radiusDiff) * 2)*(k + 1); i; --i, --k, imagePtr++, judgePtr++)
			{
				if ((*judgePtr) == 1 || ((indexRadius < ((*judgePtr) + min_radius_dist)) && (indexRadius >((*judgePtr) - min_radius_dist))))
				{
					temp = (!k) * 2 * (indexRadius + radiusDiff);
					imagePtr += temp;
					judgePtr += temp;
					k += (!k)*(imageCols - (indexRadius + radiusDiff) * 2);
					for (j = 0, outerArrayPtr = outerCirclePtr90, innerArrayPtr = innerCirclePtr90; j < tempAngle; ++j)
					{
						(*outerArrayPtr)++;
						(*innerArrayPtr)++;
						(*outerArrayPtr) += temp;
						(*innerArrayPtr) += temp;
						outerArrayPtr++;
						innerArrayPtr++;
					}
					continue;
				}
				outerCircleSum = innerCiecleSum = 0;
				for (j = 0, outerArrayPtr = outerCirclePtr90, innerArrayPtr = innerCirclePtr90; j < tempAngle; j++)
				{
					tempDiff = (**outerArrayPtr) - (**innerArrayPtr);
					tempDiff = !(tempDiff >> 31)*tempDiff + ((tempDiff >> 31) & 1)*(-tempDiff);
					tempDiff -= max_circle_diff;
					outerCircleSum += (**outerArrayPtr);
					innerCiecleSum += (**innerArrayPtr);
					(*outerArrayPtr)++;
					(*innerArrayPtr)++;
					temp = (!k) * 2 * (indexRadius + radiusDiff);
					(*outerArrayPtr) += temp;
					(*innerArrayPtr) += temp;
					outerArrayPtr++;
					innerArrayPtr++;
				}
				tempDiff = outerCircleSum - innerCiecleSum;
				tempDiff = !(tempDiff >> 31)*tempDiff + ((tempDiff >> 31) & 1)*(-tempDiff);
				if ((tempDiff / tempAngle) > max_circle_diff)
				{
					temp = (imageRows - (indexRadius + radiusDiff) * 2)*(imageCols - (indexRadius + radiusDiff) * 2);
					temp = temp - i;
					*tempXPtr = temp % (imageCols - (indexRadius + radiusDiff) * 2) + indexRadius + radiusDiff;
					*tempYPtr = temp / (imageCols - (indexRadius + radiusDiff) * 2) + indexRadius + radiusDiff;
					*tempRPtr = indexRadius;
					for (centerDist_i = -min_center_dist; centerDist_i <= min_center_dist; centerDist_i++)
					{
						for (centerDist_j = -min_center_dist; centerDist_j <= min_center_dist; centerDist_j++)
						{
							if (((centerDist_i + *tempYPtr) >> 31) || ((centerDist_j + *tempXPtr) >> 31) || ((imageRows - centerDist_i - *tempYPtr - 1) >> 31) || ((imageCols - centerDist_j - *tempXPtr - 1) >> 31))continue;
							judgePtr[centerDist_i*imageCols + centerDist_j] = 1;
						}
					}
					*judgePtr = indexRadius;
					(*tempResultN)++;
					tempXPtr++;
					tempYPtr++;
					tempRPtr++;
				}
				temp = (!k) * 2 * (indexRadius + radiusDiff);
				imagePtr += temp;
				judgePtr += temp;
				k += (!k)*(imageCols - (indexRadius + radiusDiff) * 2);
			}
		}
		imageHeadPtr = greenImg.data;
		for (indexRadius = maxRadius; indexRadius >= minRadius; indexRadius--)
		{
			imagePtr = imageHeadPtr + (indexRadius + radiusDiff)*imageCols + indexRadius + radiusDiff;
			judgePtr = circleJudgeArray + (indexRadius + radiusDiff)*imageCols + indexRadius + radiusDiff;
			for (i = 0; i < tempAngle; ++i)
			{
				tempOffsetX = (((indexRadius + radiusDiff)*SinTable90[i]) >> 16);
				tempOffsetY = (((indexRadius + radiusDiff)*CosTable90[i]) >> 16);
				outerCirclePtr90[i] = imagePtr + tempOffsetX*imageCols + tempOffsetY;
				tempOffsetX = (((indexRadius - radiusDiff)*SinTable90[i]) >> 16);
				tempOffsetY = (((indexRadius - radiusDiff)*CosTable90[i]) >> 16);
				innerCirclePtr90[i] = imagePtr + tempOffsetX*imageCols + tempOffsetY;
			}
			for (k = imageCols - (indexRadius + radiusDiff) * 2 - 1, i = (imageRows - (indexRadius + radiusDiff) * 2)*(k + 1); i; --i, --k, imagePtr++, judgePtr++)
			{
				if ((*judgePtr) == 1 || ((indexRadius < ((*judgePtr) + min_radius_dist)) && (indexRadius >((*judgePtr) - min_radius_dist))))
				{
					temp = (!k) * 2 * (indexRadius + radiusDiff);
					imagePtr += temp;
					judgePtr += temp;
					k += (!k)*(imageCols - (indexRadius + radiusDiff) * 2);
					for (j = 0, outerArrayPtr = outerCirclePtr90, innerArrayPtr = innerCirclePtr90; j < tempAngle; ++j)
					{
						(*outerArrayPtr)++;
						(*innerArrayPtr)++;
						(*outerArrayPtr) += temp;
						(*innerArrayPtr) += temp;
						outerArrayPtr++;
						innerArrayPtr++;
					}
					continue;
				}
				outerCircleSum = innerCiecleSum = 0;
				for (j = 0, outerArrayPtr = outerCirclePtr90, innerArrayPtr = innerCirclePtr90; j < tempAngle; j++)
				{
					tempDiff = (**outerArrayPtr) - (**innerArrayPtr);
					tempDiff = !(tempDiff >> 31)*tempDiff + ((tempDiff >> 31) & 1)*(-tempDiff);
					tempDiff -= max_circle_diff;
					outerCircleSum += (**outerArrayPtr);
					innerCiecleSum += (**innerArrayPtr);
					(*outerArrayPtr)++;
					(*innerArrayPtr)++;
					temp = (!k) * 2 * (indexRadius + radiusDiff);
					(*outerArrayPtr) += temp;
					(*innerArrayPtr) += temp;
					outerArrayPtr++;
					innerArrayPtr++;
				}
				tempDiff = outerCircleSum - innerCiecleSum;
				tempDiff = !(tempDiff >> 31)*tempDiff + ((tempDiff >> 31) & 1)*(-tempDiff);
				if ((tempDiff / tempAngle) > max_circle_diff)
				{
					temp = (imageRows - (indexRadius + radiusDiff) * 2)*(imageCols - (indexRadius + radiusDiff) * 2);
					temp = temp - i;
					*tempXPtr = temp % (imageCols - (indexRadius + radiusDiff) * 2) + indexRadius + radiusDiff;
					*tempYPtr = temp / (imageCols - (indexRadius + radiusDiff) * 2) + indexRadius + radiusDiff;
					*tempRPtr = indexRadius;
					for (centerDist_i = -min_center_dist; centerDist_i <= min_center_dist; centerDist_i++)
					{
						for (centerDist_j = -min_center_dist; centerDist_j <= min_center_dist; centerDist_j++)
						{
							if (((centerDist_i + *tempYPtr) >> 31) || ((centerDist_j + *tempXPtr) >> 31) || ((imageRows - centerDist_i - *tempYPtr - 1) >> 31) || ((imageCols - centerDist_j - *tempXPtr - 1) >> 31))continue;
							judgePtr[centerDist_i*imageCols + centerDist_j] = 1;
						}
					}
					*judgePtr = indexRadius;
					(*tempResultN)++;
					tempXPtr++;
					tempYPtr++;
					tempRPtr++;
				}
				temp = (!k) * 2 * (indexRadius + radiusDiff);
				imagePtr += temp;
				judgePtr += temp;
				k += (!k)*(imageCols - (indexRadius + radiusDiff) * 2);
			}
		}
		imageHeadPtr = redImg.data;
		for (indexRadius = maxRadius; indexRadius >= minRadius; indexRadius--)
		{
			imagePtr = imageHeadPtr + (indexRadius + radiusDiff)*imageCols + indexRadius + radiusDiff;
			judgePtr = circleJudgeArray + (indexRadius + radiusDiff)*imageCols + indexRadius + radiusDiff;
			for (i = 0; i < tempAngle; ++i)
			{
				tempOffsetX = (((indexRadius + radiusDiff)*SinTable90[i]) >> 16);
				tempOffsetY = (((indexRadius + radiusDiff)*CosTable90[i]) >> 16);
				outerCirclePtr90[i] = imagePtr + tempOffsetX*imageCols + tempOffsetY;
				tempOffsetX = (((indexRadius - radiusDiff)*SinTable90[i]) >> 16);
				tempOffsetY = (((indexRadius - radiusDiff)*CosTable90[i]) >> 16);
				innerCirclePtr90[i] = imagePtr + tempOffsetX*imageCols + tempOffsetY;
			}
			for (k = imageCols - (indexRadius + radiusDiff) * 2 - 1, i = (imageRows - (indexRadius + radiusDiff) * 2)*(k + 1); i; --i, --k, imagePtr++, judgePtr++)
			{
				if ((*judgePtr) == 1 || ((indexRadius < ((*judgePtr) + min_radius_dist)) && (indexRadius >((*judgePtr) - min_radius_dist))))
				{
					temp = (!k) * 2 * (indexRadius + radiusDiff);
					imagePtr += temp;
					judgePtr += temp;
					k += (!k)*(imageCols - (indexRadius + radiusDiff) * 2);
					for (j = 0, outerArrayPtr = outerCirclePtr90, innerArrayPtr = innerCirclePtr90; j < tempAngle; ++j)
					{
						(*outerArrayPtr)++;
						(*innerArrayPtr)++;
						(*outerArrayPtr) += temp;
						(*innerArrayPtr) += temp;
						outerArrayPtr++;
						innerArrayPtr++;
					}
					continue;
				}
				outerCircleSum = innerCiecleSum = 0;
				for (j = 0, outerArrayPtr = outerCirclePtr90, innerArrayPtr = innerCirclePtr90; j < tempAngle; j++)
				{
					tempDiff = (**outerArrayPtr) - (**innerArrayPtr);
					tempDiff = !(tempDiff >> 31)*tempDiff + ((tempDiff >> 31) & 1)*(-tempDiff);
					tempDiff -= max_circle_diff;
					outerCircleSum += (**outerArrayPtr);
					innerCiecleSum += (**innerArrayPtr);
					(*outerArrayPtr)++;
					(*innerArrayPtr)++;
					temp = (!k) * 2 * (indexRadius + radiusDiff);
					(*outerArrayPtr) += temp;
					(*innerArrayPtr) += temp;
					outerArrayPtr++;
					innerArrayPtr++;
				}
				tempDiff = outerCircleSum - innerCiecleSum;
				tempDiff = !(tempDiff >> 31)*tempDiff + ((tempDiff >> 31) & 1)*(-tempDiff);
				if ((tempDiff / tempAngle) > max_circle_diff)
				{
					temp = (imageRows - (indexRadius + radiusDiff) * 2)*(imageCols - (indexRadius + radiusDiff) * 2);
					temp = temp - i;
					*tempXPtr = temp % (imageCols - (indexRadius + radiusDiff) * 2) + indexRadius + radiusDiff;
					*tempYPtr = temp / (imageCols - (indexRadius + radiusDiff) * 2) + indexRadius + radiusDiff;
					*tempRPtr = indexRadius;
					for (centerDist_i = -min_center_dist; centerDist_i <= min_center_dist; centerDist_i++)
					{
						for (centerDist_j = -min_center_dist; centerDist_j <= min_center_dist; centerDist_j++)
						{
							if (((centerDist_i + *tempYPtr) >> 31) || ((centerDist_j + *tempXPtr) >> 31) || ((imageRows - centerDist_i - *tempYPtr - 1) >> 31) || ((imageCols - centerDist_j - *tempXPtr - 1) >> 31))continue;
							judgePtr[centerDist_i*imageCols + centerDist_j] = 1;
						}
					}
					*judgePtr = indexRadius;
					(*tempResultN)++;
					tempXPtr++;
					tempYPtr++;
					tempRPtr++;
				}
				temp = (!k) * 2 * (indexRadius + radiusDiff);
				imagePtr += temp;
				judgePtr += temp;
				k += (!k)*(imageCols - (indexRadius + radiusDiff) * 2);
			}
		}
	}
	if (min_radius <= Radius90 && resetMaxRadius > Radius180)
	{
		minRadius = Radius90;
		maxRadius = Radius180;
		tempAngle = 180;
		imageHeadPtr = blueImg.data;
		for (indexRadius = minRadius; indexRadius < maxRadius; indexRadius++)
		{
			imagePtr = imageHeadPtr + (indexRadius + radiusDiff)*imageCols + indexRadius + radiusDiff;
			judgePtr = circleJudgeArray + (indexRadius + radiusDiff)*imageCols + indexRadius + radiusDiff;
			for (i = 0; i < tempAngle; ++i)
			{
				tempOffsetX = (((indexRadius + radiusDiff)*SinTable180[i]) >> 16);
				tempOffsetY = (((indexRadius + radiusDiff)*CosTable180[i]) >> 16);
				outerCirclePtr180[i] = imagePtr + tempOffsetX*imageCols + tempOffsetY;
				tempOffsetX = (((indexRadius - radiusDiff)*SinTable180[i]) >> 16);
				tempOffsetY = (((indexRadius - radiusDiff)*CosTable180[i]) >> 16);
				innerCirclePtr180[i] = imagePtr + tempOffsetX*imageCols + tempOffsetY;
			}
			for (k = imageCols - (indexRadius + radiusDiff) * 2 - 1, i = (imageRows - (indexRadius + radiusDiff) * 2)*(k + 1); i; --i, --k, imagePtr++, judgePtr++)
			{
				if ((*judgePtr) == 1 || ((indexRadius < ((*judgePtr) + min_radius_dist)) && (indexRadius >((*judgePtr) - min_radius_dist))))
				{
					temp = (!k) * 2 * (indexRadius + radiusDiff);
					imagePtr += temp;
					judgePtr += temp;
					k += (!k)*(imageCols - (indexRadius + radiusDiff) * 2);
					for (j = 0, outerArrayPtr = outerCirclePtr180, innerArrayPtr = innerCirclePtr180; j < tempAngle; ++j)
					{
						(*outerArrayPtr)++;
						(*innerArrayPtr)++;
						(*outerArrayPtr) += temp;
						(*innerArrayPtr) += temp;
						outerArrayPtr++;
						innerArrayPtr++;
					}
					continue;
				}
				outerCircleSum = innerCiecleSum = 0;
				for (j = 0, outerArrayPtr = outerCirclePtr180, innerArrayPtr = innerCirclePtr180; j < tempAngle; j++)
				{
					tempDiff = (**outerArrayPtr) - (**innerArrayPtr);
					tempDiff = !(tempDiff >> 31)*tempDiff + ((tempDiff >> 31) & 1)*(-tempDiff);
					tempDiff -= max_circle_diff;
					outerCircleSum += (**outerArrayPtr);
					innerCiecleSum += (**innerArrayPtr);
					(*outerArrayPtr)++;
					(*innerArrayPtr)++;
					temp = (!k) * 2 * (indexRadius + radiusDiff);
					(*outerArrayPtr) += temp;
					(*innerArrayPtr) += temp;
					outerArrayPtr++;
					innerArrayPtr++;
				}
				tempDiff = outerCircleSum - innerCiecleSum;
				tempDiff = !(tempDiff >> 31)*tempDiff + ((tempDiff >> 31) & 1)*(-tempDiff);
				if ((tempDiff / tempAngle) > max_circle_diff)
				{
					temp = (imageRows - (indexRadius + radiusDiff) * 2)*(imageCols - (indexRadius + radiusDiff) * 2);
					temp = temp - i;
					*tempXPtr = temp % (imageCols - (indexRadius + radiusDiff) * 2) + indexRadius + radiusDiff;
					*tempYPtr = temp / (imageCols - (indexRadius + radiusDiff) * 2) + indexRadius + radiusDiff;
					*tempRPtr = indexRadius;
					for (centerDist_i = -min_center_dist; centerDist_i <= min_center_dist; centerDist_i++)
					{
						for (centerDist_j = -min_center_dist; centerDist_j <= min_center_dist; centerDist_j++)
						{
							if (((centerDist_i + *tempYPtr) >> 31) || ((centerDist_j + *tempXPtr) >> 31) || ((imageRows - centerDist_i - *tempYPtr - 1) >> 31) || ((imageCols - centerDist_j - *tempXPtr - 1) >> 31))continue;
							judgePtr[centerDist_i*imageCols + centerDist_j] = 1;
						}
					}
					*judgePtr = indexRadius;
					(*tempResultN)++;
					tempXPtr++;
					tempYPtr++;
					tempRPtr++;
				}
				temp = (!k) * 2 * (indexRadius + radiusDiff);
				imagePtr += temp;
				judgePtr += temp;
				k += (!k)*(imageCols - (indexRadius + radiusDiff) * 2);
			}
		}
		imageHeadPtr = greenImg.data;
		for (indexRadius = minRadius; indexRadius < maxRadius; indexRadius++)
		{
			imagePtr = imageHeadPtr + (indexRadius + radiusDiff)*imageCols + indexRadius + radiusDiff;
			judgePtr = circleJudgeArray + (indexRadius + radiusDiff)*imageCols + indexRadius + radiusDiff;
			for (i = 0; i < tempAngle; ++i)
			{
				tempOffsetX = (((indexRadius + radiusDiff)*SinTable180[i]) >> 16);
				tempOffsetY = (((indexRadius + radiusDiff)*CosTable180[i]) >> 16);
				outerCirclePtr180[i] = imagePtr + tempOffsetX*imageCols + tempOffsetY;
				tempOffsetX = (((indexRadius - radiusDiff)*SinTable180[i]) >> 16);
				tempOffsetY = (((indexRadius - radiusDiff)*CosTable180[i]) >> 16);
				innerCirclePtr180[i] = imagePtr + tempOffsetX*imageCols + tempOffsetY;
			}
			for (k = imageCols - (indexRadius + radiusDiff) * 2 - 1, i = (imageRows - (indexRadius + radiusDiff) * 2)*(k + 1); i; --i, --k, imagePtr++, judgePtr++)
			{
				if ((*judgePtr) == 1 || ((indexRadius < ((*judgePtr) + min_radius_dist)) && (indexRadius >((*judgePtr) - min_radius_dist))))
				{
					temp = (!k) * 2 * (indexRadius + radiusDiff);
					imagePtr += temp;
					judgePtr += temp;
					k += (!k)*(imageCols - (indexRadius + radiusDiff) * 2);
					for (j = 0, outerArrayPtr = outerCirclePtr180, innerArrayPtr = innerCirclePtr180; j < tempAngle; ++j)
					{
						(*outerArrayPtr)++;
						(*innerArrayPtr)++;
						(*outerArrayPtr) += temp;
						(*innerArrayPtr) += temp;
						outerArrayPtr++;
						innerArrayPtr++;
					}
					continue;
				}
				outerCircleSum = innerCiecleSum = 0;
				for (j = 0, outerArrayPtr = outerCirclePtr180, innerArrayPtr = innerCirclePtr180; j < tempAngle; j++)
				{
					tempDiff = (**outerArrayPtr) - (**innerArrayPtr);
					tempDiff = !(tempDiff >> 31)*tempDiff + ((tempDiff >> 31) & 1)*(-tempDiff);
					tempDiff -= max_circle_diff;
					outerCircleSum += (**outerArrayPtr);
					innerCiecleSum += (**innerArrayPtr);
					(*outerArrayPtr)++;
					(*innerArrayPtr)++;
					temp = (!k) * 2 * (indexRadius + radiusDiff);
					(*outerArrayPtr) += temp;
					(*innerArrayPtr) += temp;
					outerArrayPtr++;
					innerArrayPtr++;
				}
				tempDiff = outerCircleSum - innerCiecleSum;
				tempDiff = !(tempDiff >> 31)*tempDiff + ((tempDiff >> 31) & 1)*(-tempDiff);
				if ((tempDiff / tempAngle) > max_circle_diff)
				{
					temp = (imageRows - (indexRadius + radiusDiff) * 2)*(imageCols - (indexRadius + radiusDiff) * 2);
					temp = temp - i;
					*tempXPtr = temp % (imageCols - (indexRadius + radiusDiff) * 2) + indexRadius + radiusDiff;
					*tempYPtr = temp / (imageCols - (indexRadius + radiusDiff) * 2) + indexRadius + radiusDiff;
					*tempRPtr = indexRadius;
					for (centerDist_i = -min_center_dist; centerDist_i <= min_center_dist; centerDist_i++)
					{
						for (centerDist_j = -min_center_dist; centerDist_j <= min_center_dist; centerDist_j++)
						{
							if (((centerDist_i + *tempYPtr) >> 31) || ((centerDist_j + *tempXPtr) >> 31) || ((imageRows - centerDist_i - *tempYPtr - 1) >> 31) || ((imageCols - centerDist_j - *tempXPtr - 1) >> 31))continue;
							judgePtr[centerDist_i*imageCols + centerDist_j] = 1;
						}
					}
					*judgePtr = indexRadius;
					(*tempResultN)++;
					tempXPtr++;
					tempYPtr++;
					tempRPtr++;
				}
				temp = (!k) * 2 * (indexRadius + radiusDiff);
				imagePtr += temp;
				judgePtr += temp;
				k += (!k)*(imageCols - (indexRadius + radiusDiff) * 2);
			}
		}
		imageHeadPtr = redImg.data;
		for (indexRadius = minRadius; indexRadius < maxRadius; indexRadius++)
		{
			imagePtr = imageHeadPtr + (indexRadius + radiusDiff)*imageCols + indexRadius + radiusDiff;
			judgePtr = circleJudgeArray + (indexRadius + radiusDiff)*imageCols + indexRadius + radiusDiff;
			for (i = 0; i < tempAngle; ++i)
			{
				tempOffsetX = (((indexRadius + radiusDiff)*SinTable180[i]) >> 16);
				tempOffsetY = (((indexRadius + radiusDiff)*CosTable180[i]) >> 16);
				outerCirclePtr180[i] = imagePtr + tempOffsetX*imageCols + tempOffsetY;
				tempOffsetX = (((indexRadius - radiusDiff)*SinTable180[i]) >> 16);
				tempOffsetY = (((indexRadius - radiusDiff)*CosTable180[i]) >> 16);
				innerCirclePtr180[i] = imagePtr + tempOffsetX*imageCols + tempOffsetY;
			}
			for (k = imageCols - (indexRadius + radiusDiff) * 2 - 1, i = (imageRows - (indexRadius + radiusDiff) * 2)*(k + 1); i; --i, --k, imagePtr++, judgePtr++)
			{
				if ((*judgePtr) == 1 || ((indexRadius < ((*judgePtr) + min_radius_dist)) && (indexRadius >((*judgePtr) - min_radius_dist))))
				{
					temp = (!k) * 2 * (indexRadius + radiusDiff);
					imagePtr += temp;
					judgePtr += temp;
					k += (!k)*(imageCols - (indexRadius + radiusDiff) * 2);
					for (j = 0, outerArrayPtr = outerCirclePtr180, innerArrayPtr = innerCirclePtr180; j < tempAngle; ++j)
					{
						(*outerArrayPtr)++;
						(*innerArrayPtr)++;
						(*outerArrayPtr) += temp;
						(*innerArrayPtr) += temp;
						outerArrayPtr++;
						innerArrayPtr++;
					}
					continue;
				}
				outerCircleSum = innerCiecleSum = 0;
				for (j = 0, outerArrayPtr = outerCirclePtr180, innerArrayPtr = innerCirclePtr180; j < tempAngle; j++)
				{
					tempDiff = (**outerArrayPtr) - (**innerArrayPtr);
					tempDiff = !(tempDiff >> 31)*tempDiff + ((tempDiff >> 31) & 1)*(-tempDiff);
					tempDiff -= max_circle_diff;
					outerCircleSum += (**outerArrayPtr);
					innerCiecleSum += (**innerArrayPtr);
					(*outerArrayPtr)++;
					(*innerArrayPtr)++;
					temp = (!k) * 2 * (indexRadius + radiusDiff);
					(*outerArrayPtr) += temp;
					(*innerArrayPtr) += temp;
					outerArrayPtr++;
					innerArrayPtr++;
				}
				tempDiff = outerCircleSum - innerCiecleSum;
				tempDiff = !(tempDiff >> 31)*tempDiff + ((tempDiff >> 31) & 1)*(-tempDiff);
				if ((tempDiff / tempAngle) > max_circle_diff)
				{
					temp = (imageRows - (indexRadius + radiusDiff) * 2)*(imageCols - (indexRadius + radiusDiff) * 2);
					temp = temp - i;
					*tempXPtr = temp % (imageCols - (indexRadius + radiusDiff) * 2) + indexRadius + radiusDiff;
					*tempYPtr = temp / (imageCols - (indexRadius + radiusDiff) * 2) + indexRadius + radiusDiff;
					*tempRPtr = indexRadius;
					for (centerDist_i = -min_center_dist; centerDist_i <= min_center_dist; centerDist_i++)
					{
						for (centerDist_j = -min_center_dist; centerDist_j <= min_center_dist; centerDist_j++)
						{
							if (((centerDist_i + *tempYPtr) >> 31) || ((centerDist_j + *tempXPtr) >> 31) || ((imageRows - centerDist_i - *tempYPtr - 1) >> 31) || ((imageCols - centerDist_j - *tempXPtr - 1) >> 31))continue;
							judgePtr[centerDist_i*imageCols + centerDist_j] = 1;
						}
					}
					*judgePtr = indexRadius;
					(*tempResultN)++;
					tempXPtr++;
					tempYPtr++;
					tempRPtr++;
				}
				temp = (!k) * 2 * (indexRadius + radiusDiff);
				imagePtr += temp;
				judgePtr += temp;
				k += (!k)*(imageCols - (indexRadius + radiusDiff) * 2);
			}
		}
	}
	else if (min_radius <= Radius90 && resetMaxRadius <= Radius180)
	{
		minRadius = Radius90;
		maxRadius = resetMaxRadius;
		tempAngle = 180;
		imageHeadPtr = blueImg.data;
		for (indexRadius = minRadius; indexRadius < maxRadius; indexRadius++)
		{
			imagePtr = imageHeadPtr + (indexRadius + radiusDiff)*imageCols + indexRadius + radiusDiff;
			judgePtr = circleJudgeArray + (indexRadius + radiusDiff)*imageCols + indexRadius + radiusDiff;
			for (i = 0; i < tempAngle; ++i)
			{
				tempOffsetX = (((indexRadius + radiusDiff)*SinTable180[i]) >> 16);
				tempOffsetY = (((indexRadius + radiusDiff)*CosTable180[i]) >> 16);
				outerCirclePtr180[i] = imagePtr + tempOffsetX*imageCols + tempOffsetY;
				tempOffsetX = (((indexRadius - radiusDiff)*SinTable180[i]) >> 16);
				tempOffsetY = (((indexRadius - radiusDiff)*CosTable180[i]) >> 16);
				innerCirclePtr180[i] = imagePtr + tempOffsetX*imageCols + tempOffsetY;
			}
			for (k = imageCols - (indexRadius + radiusDiff) * 2 - 1, i = (imageRows - (indexRadius + radiusDiff) * 2)*(k + 1); i; --i, --k, imagePtr++, judgePtr++)
			{
				if ((*judgePtr) == 1 || ((indexRadius < ((*judgePtr) + min_radius_dist)) && (indexRadius >((*judgePtr) - min_radius_dist))))
				{
					temp = (!k) * 2 * (indexRadius + radiusDiff);
					imagePtr += temp;
					judgePtr += temp;
					k += (!k)*(imageCols - (indexRadius + radiusDiff) * 2);
					for (j = 0, outerArrayPtr = outerCirclePtr180, innerArrayPtr = innerCirclePtr180; j < tempAngle; ++j)
					{
						(*outerArrayPtr)++;
						(*innerArrayPtr)++;
						(*outerArrayPtr) += temp;
						(*innerArrayPtr) += temp;
						outerArrayPtr++;
						innerArrayPtr++;
					}
					continue;
				}
				outerCircleSum = innerCiecleSum = 0;
				for (j = 0, outerArrayPtr = outerCirclePtr180, innerArrayPtr = innerCirclePtr180; j < tempAngle; j++)
				{
					tempDiff = (**outerArrayPtr) - (**innerArrayPtr);
					tempDiff = !(tempDiff >> 31)*tempDiff + ((tempDiff >> 31) & 1)*(-tempDiff);
					tempDiff -= max_circle_diff;
					outerCircleSum += (**outerArrayPtr);
					innerCiecleSum += (**innerArrayPtr);
					(*outerArrayPtr)++;
					(*innerArrayPtr)++;
					temp = (!k) * 2 * (indexRadius + radiusDiff);
					(*outerArrayPtr) += temp;
					(*innerArrayPtr) += temp;
					outerArrayPtr++;
					innerArrayPtr++;
				}
				tempDiff = outerCircleSum - innerCiecleSum;
				tempDiff = !(tempDiff >> 31)*tempDiff + ((tempDiff >> 31) & 1)*(-tempDiff);
				if ((tempDiff / tempAngle) > max_circle_diff)
				{
					temp = (imageRows - (indexRadius + radiusDiff) * 2)*(imageCols - (indexRadius + radiusDiff) * 2);
					temp = temp - i;
					*tempXPtr = temp % (imageCols - (indexRadius + radiusDiff) * 2) + indexRadius + radiusDiff;
					*tempYPtr = temp / (imageCols - (indexRadius + radiusDiff) * 2) + indexRadius + radiusDiff;
					*tempRPtr = indexRadius;
					for (centerDist_i = -min_center_dist; centerDist_i <= min_center_dist; centerDist_i++)
					{
						for (centerDist_j = -min_center_dist; centerDist_j <= min_center_dist; centerDist_j++)
						{
							if (((centerDist_i + *tempYPtr) >> 31) || ((centerDist_j + *tempXPtr) >> 31) || ((imageRows - centerDist_i - *tempYPtr - 1) >> 31) || ((imageCols - centerDist_j - *tempXPtr - 1) >> 31))continue;
							judgePtr[centerDist_i*imageCols + centerDist_j] = 1;
						}
					}
					*judgePtr = indexRadius;
					(*tempResultN)++;
					tempXPtr++;
					tempYPtr++;
					tempRPtr++;
				}
				temp = (!k) * 2 * (indexRadius + radiusDiff);
				imagePtr += temp;
				judgePtr += temp;
				k += (!k)*(imageCols - (indexRadius + radiusDiff) * 2);
			}
		}
		imageHeadPtr = greenImg.data;
		for (indexRadius = minRadius; indexRadius < maxRadius; indexRadius++)
		{
			imagePtr = imageHeadPtr + (indexRadius + radiusDiff)*imageCols + indexRadius + radiusDiff;
			judgePtr = circleJudgeArray + (indexRadius + radiusDiff)*imageCols + indexRadius + radiusDiff;
			for (i = 0; i < tempAngle; ++i)
			{
				tempOffsetX = (((indexRadius + radiusDiff)*SinTable180[i]) >> 16);
				tempOffsetY = (((indexRadius + radiusDiff)*CosTable180[i]) >> 16);
				outerCirclePtr180[i] = imagePtr + tempOffsetX*imageCols + tempOffsetY;
				tempOffsetX = (((indexRadius - radiusDiff)*SinTable180[i]) >> 16);
				tempOffsetY = (((indexRadius - radiusDiff)*CosTable180[i]) >> 16);
				innerCirclePtr180[i] = imagePtr + tempOffsetX*imageCols + tempOffsetY;
			}
			for (k = imageCols - (indexRadius + radiusDiff) * 2 - 1, i = (imageRows - (indexRadius + radiusDiff) * 2)*(k + 1); i; --i, --k, imagePtr++, judgePtr++)
			{
				if ((*judgePtr) == 1 || ((indexRadius < ((*judgePtr) + min_radius_dist)) && (indexRadius >((*judgePtr) - min_radius_dist))))
				{
					temp = (!k) * 2 * (indexRadius + radiusDiff);
					imagePtr += temp;
					judgePtr += temp;
					k += (!k)*(imageCols - (indexRadius + radiusDiff) * 2);
					for (j = 0, outerArrayPtr = outerCirclePtr180, innerArrayPtr = innerCirclePtr180; j < tempAngle; ++j)
					{
						(*outerArrayPtr)++;
						(*innerArrayPtr)++;
						(*outerArrayPtr) += temp;
						(*innerArrayPtr) += temp;
						outerArrayPtr++;
						innerArrayPtr++;
					}
					continue;
				}
				outerCircleSum = innerCiecleSum = 0;
				for (j = 0, outerArrayPtr = outerCirclePtr180, innerArrayPtr = innerCirclePtr180; j < tempAngle; j++)
				{
					tempDiff = (**outerArrayPtr) - (**innerArrayPtr);
					tempDiff = !(tempDiff >> 31)*tempDiff + ((tempDiff >> 31) & 1)*(-tempDiff);
					tempDiff -= max_circle_diff;
					outerCircleSum += (**outerArrayPtr);
					innerCiecleSum += (**innerArrayPtr);
					(*outerArrayPtr)++;
					(*innerArrayPtr)++;
					temp = (!k) * 2 * (indexRadius + radiusDiff);
					(*outerArrayPtr) += temp;
					(*innerArrayPtr) += temp;
					outerArrayPtr++;
					innerArrayPtr++;
				}
				tempDiff = outerCircleSum - innerCiecleSum;
				tempDiff = !(tempDiff >> 31)*tempDiff + ((tempDiff >> 31) & 1)*(-tempDiff);
				if ((tempDiff / tempAngle) > max_circle_diff)
				{
					temp = (imageRows - (indexRadius + radiusDiff) * 2)*(imageCols - (indexRadius + radiusDiff) * 2);
					temp = temp - i;
					*tempXPtr = temp % (imageCols - (indexRadius + radiusDiff) * 2) + indexRadius + radiusDiff;
					*tempYPtr = temp / (imageCols - (indexRadius + radiusDiff) * 2) + indexRadius + radiusDiff;
					*tempRPtr = indexRadius;
					for (centerDist_i = -min_center_dist; centerDist_i <= min_center_dist; centerDist_i++)
					{
						for (centerDist_j = -min_center_dist; centerDist_j <= min_center_dist; centerDist_j++)
						{
							if (((centerDist_i + *tempYPtr) >> 31) || ((centerDist_j + *tempXPtr) >> 31) || ((imageRows - centerDist_i - *tempYPtr - 1) >> 31) || ((imageCols - centerDist_j - *tempXPtr - 1) >> 31))continue;
							judgePtr[centerDist_i*imageCols + centerDist_j] = 1;
						}
					}
					*judgePtr = indexRadius;
					(*tempResultN)++;
					tempXPtr++;
					tempYPtr++;
					tempRPtr++;
				}
				temp = (!k) * 2 * (indexRadius + radiusDiff);
				imagePtr += temp;
				judgePtr += temp;
				k += (!k)*(imageCols - (indexRadius + radiusDiff) * 2);
			}
		}
		imageHeadPtr = redImg.data;
		for (indexRadius = minRadius; indexRadius < maxRadius; indexRadius++)
		{
			imagePtr = imageHeadPtr + (indexRadius + radiusDiff)*imageCols + indexRadius + radiusDiff;
			judgePtr = circleJudgeArray + (indexRadius + radiusDiff)*imageCols + indexRadius + radiusDiff;
			for (i = 0; i < tempAngle; ++i)
			{
				tempOffsetX = (((indexRadius + radiusDiff)*SinTable180[i]) >> 16);
				tempOffsetY = (((indexRadius + radiusDiff)*CosTable180[i]) >> 16);
				outerCirclePtr180[i] = imagePtr + tempOffsetX*imageCols + tempOffsetY;
				tempOffsetX = (((indexRadius - radiusDiff)*SinTable180[i]) >> 16);
				tempOffsetY = (((indexRadius - radiusDiff)*CosTable180[i]) >> 16);
				innerCirclePtr180[i] = imagePtr + tempOffsetX*imageCols + tempOffsetY;
			}
			for (k = imageCols - (indexRadius + radiusDiff) * 2 - 1, i = (imageRows - (indexRadius + radiusDiff) * 2)*(k + 1); i; --i, --k, imagePtr++, judgePtr++)
			{
				if ((*judgePtr) == 1 || ((indexRadius < ((*judgePtr) + min_radius_dist)) && (indexRadius >((*judgePtr) - min_radius_dist))))
				{
					temp = (!k) * 2 * (indexRadius + radiusDiff);
					imagePtr += temp;
					judgePtr += temp;
					k += (!k)*(imageCols - (indexRadius + radiusDiff) * 2);
					for (j = 0, outerArrayPtr = outerCirclePtr180, innerArrayPtr = innerCirclePtr180; j < tempAngle; ++j)
					{
						(*outerArrayPtr)++;
						(*innerArrayPtr)++;
						(*outerArrayPtr) += temp;
						(*innerArrayPtr) += temp;
						outerArrayPtr++;
						innerArrayPtr++;
					}
					continue;
				}
				outerCircleSum = innerCiecleSum = 0;
				for (j = 0, outerArrayPtr = outerCirclePtr180, innerArrayPtr = innerCirclePtr180; j < tempAngle; j++)
				{
					tempDiff = (**outerArrayPtr) - (**innerArrayPtr);
					tempDiff = !(tempDiff >> 31)*tempDiff + ((tempDiff >> 31) & 1)*(-tempDiff);
					tempDiff -= max_circle_diff;
					outerCircleSum += (**outerArrayPtr);
					innerCiecleSum += (**innerArrayPtr);
					(*outerArrayPtr)++;
					(*innerArrayPtr)++;
					temp = (!k) * 2 * (indexRadius + radiusDiff);
					(*outerArrayPtr) += temp;
					(*innerArrayPtr) += temp;
					outerArrayPtr++;
					innerArrayPtr++;
				}
				tempDiff = outerCircleSum - innerCiecleSum;
				tempDiff = !(tempDiff >> 31)*tempDiff + ((tempDiff >> 31) & 1)*(-tempDiff);
				if ((tempDiff / tempAngle) > max_circle_diff)
				{
					temp = (imageRows - (indexRadius + radiusDiff) * 2)*(imageCols - (indexRadius + radiusDiff) * 2);
					temp = temp - i;
					*tempXPtr = temp % (imageCols - (indexRadius + radiusDiff) * 2) + indexRadius + radiusDiff;
					*tempYPtr = temp / (imageCols - (indexRadius + radiusDiff) * 2) + indexRadius + radiusDiff;
					*tempRPtr = indexRadius;
					for (centerDist_i = -min_center_dist; centerDist_i <= min_center_dist; centerDist_i++)
					{
						for (centerDist_j = -min_center_dist; centerDist_j <= min_center_dist; centerDist_j++)
						{
							if (((centerDist_i + *tempYPtr) >> 31) || ((centerDist_j + *tempXPtr) >> 31) || ((imageRows - centerDist_i - *tempYPtr - 1) >> 31) || ((imageCols - centerDist_j - *tempXPtr - 1) >> 31))continue;
							judgePtr[centerDist_i*imageCols + centerDist_j] = 1;
						}
					}
					*judgePtr = indexRadius;
					(*tempResultN)++;
					tempXPtr++;
					tempYPtr++;
					tempRPtr++;
				}
				temp = (!k) * 2 * (indexRadius + radiusDiff);
				imagePtr += temp;
				judgePtr += temp;
				k += (!k)*(imageCols - (indexRadius + radiusDiff) * 2);
			}
		}
	}
	else if (min_radius > Radius90 && resetMaxRadius > Radius180)
	{
		minRadius = min_radius;
		maxRadius = Radius180;
		tempAngle = 180;
		imageHeadPtr = blueImg.data;
		for (indexRadius = minRadius; indexRadius < maxRadius; indexRadius++)
		{
			imagePtr = imageHeadPtr + (indexRadius + radiusDiff)*imageCols + indexRadius + radiusDiff;
			judgePtr = circleJudgeArray + (indexRadius + radiusDiff)*imageCols + indexRadius + radiusDiff;
			for (i = 0; i < tempAngle; ++i)
			{
				tempOffsetX = (((indexRadius + radiusDiff)*SinTable180[i]) >> 16);
				tempOffsetY = (((indexRadius + radiusDiff)*CosTable180[i]) >> 16);
				outerCirclePtr180[i] = imagePtr + tempOffsetX*imageCols + tempOffsetY;
				tempOffsetX = (((indexRadius - radiusDiff)*SinTable180[i]) >> 16);
				tempOffsetY = (((indexRadius - radiusDiff)*CosTable180[i]) >> 16);
				innerCirclePtr180[i] = imagePtr + tempOffsetX*imageCols + tempOffsetY;
			}
			for (k = imageCols - (indexRadius + radiusDiff) * 2 - 1, i = (imageRows - (indexRadius + radiusDiff) * 2)*(k + 1); i; --i, --k, imagePtr++, judgePtr++)
			{
				if ((*judgePtr) == 1 || ((indexRadius < ((*judgePtr) + min_radius_dist)) && (indexRadius >((*judgePtr) - min_radius_dist))))
				{
					temp = (!k) * 2 * (indexRadius + radiusDiff);
					imagePtr += temp;
					judgePtr += temp;
					k += (!k)*(imageCols - (indexRadius + radiusDiff) * 2);
					for (j = 0, outerArrayPtr = outerCirclePtr180, innerArrayPtr = innerCirclePtr180; j < tempAngle; ++j)
					{
						(*outerArrayPtr)++;
						(*innerArrayPtr)++;
						(*outerArrayPtr) += temp;
						(*innerArrayPtr) += temp;
						outerArrayPtr++;
						innerArrayPtr++;
					}
					continue;
				}
				outerCircleSum = innerCiecleSum = 0;
				for (j = 0, outerArrayPtr = outerCirclePtr180, innerArrayPtr = innerCirclePtr180; j < tempAngle; j++)
				{
					tempDiff = (**outerArrayPtr) - (**innerArrayPtr);
					tempDiff = !(tempDiff >> 31)*tempDiff + ((tempDiff >> 31) & 1)*(-tempDiff);
					tempDiff -= max_circle_diff;
					outerCircleSum += (**outerArrayPtr);
					innerCiecleSum += (**innerArrayPtr);
					(*outerArrayPtr)++;
					(*innerArrayPtr)++;
					temp = (!k) * 2 * (indexRadius + radiusDiff);
					(*outerArrayPtr) += temp;
					(*innerArrayPtr) += temp;
					outerArrayPtr++;
					innerArrayPtr++;
				}
				tempDiff = outerCircleSum - innerCiecleSum;
				tempDiff = !(tempDiff >> 31)*tempDiff + ((tempDiff >> 31) & 1)*(-tempDiff);
				if ((tempDiff / tempAngle) > max_circle_diff)
				{
					temp = (imageRows - (indexRadius + radiusDiff) * 2)*(imageCols - (indexRadius + radiusDiff) * 2);
					temp = temp - i;
					*tempXPtr = temp % (imageCols - (indexRadius + radiusDiff) * 2) + indexRadius + radiusDiff;
					*tempYPtr = temp / (imageCols - (indexRadius + radiusDiff) * 2) + indexRadius + radiusDiff;
					*tempRPtr = indexRadius;
					for (centerDist_i = -min_center_dist; centerDist_i <= min_center_dist; centerDist_i++)
					{
						for (centerDist_j = -min_center_dist; centerDist_j <= min_center_dist; centerDist_j++)
						{
							if (((centerDist_i + *tempYPtr) >> 31) || ((centerDist_j + *tempXPtr) >> 31) || ((imageRows - centerDist_i - *tempYPtr - 1) >> 31) || ((imageCols - centerDist_j - *tempXPtr - 1) >> 31))continue;
							judgePtr[centerDist_i*imageCols + centerDist_j] = 1;
						}
					}
					*judgePtr = indexRadius;
					(*tempResultN)++;
					tempXPtr++;
					tempYPtr++;
					tempRPtr++;
				}
				temp = (!k) * 2 * (indexRadius + radiusDiff);
				imagePtr += temp;
				judgePtr += temp;
				k += (!k)*(imageCols - (indexRadius + radiusDiff) * 2);
			}
		}
		imageHeadPtr = greenImg.data;
		for (indexRadius = minRadius; indexRadius < maxRadius; indexRadius++)
		{
			imagePtr = imageHeadPtr + (indexRadius + radiusDiff)*imageCols + indexRadius + radiusDiff;
			judgePtr = circleJudgeArray + (indexRadius + radiusDiff)*imageCols + indexRadius + radiusDiff;
			for (i = 0; i < tempAngle; ++i)
			{
				tempOffsetX = (((indexRadius + radiusDiff)*SinTable180[i]) >> 16);
				tempOffsetY = (((indexRadius + radiusDiff)*CosTable180[i]) >> 16);
				outerCirclePtr180[i] = imagePtr + tempOffsetX*imageCols + tempOffsetY;
				tempOffsetX = (((indexRadius - radiusDiff)*SinTable180[i]) >> 16);
				tempOffsetY = (((indexRadius - radiusDiff)*CosTable180[i]) >> 16);
				innerCirclePtr180[i] = imagePtr + tempOffsetX*imageCols + tempOffsetY;
			}
			for (k = imageCols - (indexRadius + radiusDiff) * 2 - 1, i = (imageRows - (indexRadius + radiusDiff) * 2)*(k + 1); i; --i, --k, imagePtr++, judgePtr++)
			{
				if ((*judgePtr) == 1 || ((indexRadius < ((*judgePtr) + min_radius_dist)) && (indexRadius >((*judgePtr) - min_radius_dist))))
				{
					temp = (!k) * 2 * (indexRadius + radiusDiff);
					imagePtr += temp;
					judgePtr += temp;
					k += (!k)*(imageCols - (indexRadius + radiusDiff) * 2);
					for (j = 0, outerArrayPtr = outerCirclePtr180, innerArrayPtr = innerCirclePtr180; j < tempAngle; ++j)
					{
						(*outerArrayPtr)++;
						(*innerArrayPtr)++;
						(*outerArrayPtr) += temp;
						(*innerArrayPtr) += temp;
						outerArrayPtr++;
						innerArrayPtr++;
					}
					continue;
				}
				outerCircleSum = innerCiecleSum = 0;
				for (j = 0, outerArrayPtr = outerCirclePtr180, innerArrayPtr = innerCirclePtr180; j < tempAngle; j++)
				{
					tempDiff = (**outerArrayPtr) - (**innerArrayPtr);
					tempDiff = !(tempDiff >> 31)*tempDiff + ((tempDiff >> 31) & 1)*(-tempDiff);
					tempDiff -= max_circle_diff;
					outerCircleSum += (**outerArrayPtr);
					innerCiecleSum += (**innerArrayPtr);
					(*outerArrayPtr)++;
					(*innerArrayPtr)++;
					temp = (!k) * 2 * (indexRadius + radiusDiff);
					(*outerArrayPtr) += temp;
					(*innerArrayPtr) += temp;
					outerArrayPtr++;
					innerArrayPtr++;
				}
				tempDiff = outerCircleSum - innerCiecleSum;
				tempDiff = !(tempDiff >> 31)*tempDiff + ((tempDiff >> 31) & 1)*(-tempDiff);
				if ((tempDiff / tempAngle) > max_circle_diff)
				{
					temp = (imageRows - (indexRadius + radiusDiff) * 2)*(imageCols - (indexRadius + radiusDiff) * 2);
					temp = temp - i;
					*tempXPtr = temp % (imageCols - (indexRadius + radiusDiff) * 2) + indexRadius + radiusDiff;
					*tempYPtr = temp / (imageCols - (indexRadius + radiusDiff) * 2) + indexRadius + radiusDiff;
					*tempRPtr = indexRadius;
					for (centerDist_i = -min_center_dist; centerDist_i <= min_center_dist; centerDist_i++)
					{
						for (centerDist_j = -min_center_dist; centerDist_j <= min_center_dist; centerDist_j++)
						{
							if (((centerDist_i + *tempYPtr) >> 31) || ((centerDist_j + *tempXPtr) >> 31) || ((imageRows - centerDist_i - *tempYPtr - 1) >> 31) || ((imageCols - centerDist_j - *tempXPtr - 1) >> 31))continue;
							judgePtr[centerDist_i*imageCols + centerDist_j] = 1;
						}
					}
					*judgePtr = indexRadius;
					(*tempResultN)++;
					tempXPtr++;
					tempYPtr++;
					tempRPtr++;
				}
				temp = (!k) * 2 * (indexRadius + radiusDiff);
				imagePtr += temp;
				judgePtr += temp;
				k += (!k)*(imageCols - (indexRadius + radiusDiff) * 2);
			}
		}
		imageHeadPtr = redImg.data;
		for (indexRadius = minRadius; indexRadius < maxRadius; indexRadius++)
		{
			imagePtr = imageHeadPtr + (indexRadius + radiusDiff)*imageCols + indexRadius + radiusDiff;
			judgePtr = circleJudgeArray + (indexRadius + radiusDiff)*imageCols + indexRadius + radiusDiff;
			for (i = 0; i < tempAngle; ++i)
			{
				tempOffsetX = (((indexRadius + radiusDiff)*SinTable180[i]) >> 16);
				tempOffsetY = (((indexRadius + radiusDiff)*CosTable180[i]) >> 16);
				outerCirclePtr180[i] = imagePtr + tempOffsetX*imageCols + tempOffsetY;
				tempOffsetX = (((indexRadius - radiusDiff)*SinTable180[i]) >> 16);
				tempOffsetY = (((indexRadius - radiusDiff)*CosTable180[i]) >> 16);
				innerCirclePtr180[i] = imagePtr + tempOffsetX*imageCols + tempOffsetY;
			}
			for (k = imageCols - (indexRadius + radiusDiff) * 2 - 1, i = (imageRows - (indexRadius + radiusDiff) * 2)*(k + 1); i; --i, --k, imagePtr++, judgePtr++)
			{
				if ((*judgePtr) == 1 || ((indexRadius < ((*judgePtr) + min_radius_dist)) && (indexRadius >((*judgePtr) - min_radius_dist))))
				{
					temp = (!k) * 2 * (indexRadius + radiusDiff);
					imagePtr += temp;
					judgePtr += temp;
					k += (!k)*(imageCols - (indexRadius + radiusDiff) * 2);
					for (j = 0, outerArrayPtr = outerCirclePtr180, innerArrayPtr = innerCirclePtr180; j < tempAngle; ++j)
					{
						(*outerArrayPtr)++;
						(*innerArrayPtr)++;
						(*outerArrayPtr) += temp;
						(*innerArrayPtr) += temp;
						outerArrayPtr++;
						innerArrayPtr++;
					}
					continue;
				}
				outerCircleSum = innerCiecleSum = 0;
				for (j = 0, outerArrayPtr = outerCirclePtr180, innerArrayPtr = innerCirclePtr180; j < tempAngle; j++)
				{
					tempDiff = (**outerArrayPtr) - (**innerArrayPtr);
					tempDiff = !(tempDiff >> 31)*tempDiff + ((tempDiff >> 31) & 1)*(-tempDiff);
					tempDiff -= max_circle_diff;
					outerCircleSum += (**outerArrayPtr);
					innerCiecleSum += (**innerArrayPtr);
					(*outerArrayPtr)++;
					(*innerArrayPtr)++;
					temp = (!k) * 2 * (indexRadius + radiusDiff);
					(*outerArrayPtr) += temp;
					(*innerArrayPtr) += temp;
					outerArrayPtr++;
					innerArrayPtr++;
				}
				tempDiff = outerCircleSum - innerCiecleSum;
				tempDiff = !(tempDiff >> 31)*tempDiff + ((tempDiff >> 31) & 1)*(-tempDiff);
				if ((tempDiff / tempAngle) > max_circle_diff)
				{
					temp = (imageRows - (indexRadius + radiusDiff) * 2)*(imageCols - (indexRadius + radiusDiff) * 2);
					temp = temp - i;
					*tempXPtr = temp % (imageCols - (indexRadius + radiusDiff) * 2) + indexRadius + radiusDiff;
					*tempYPtr = temp / (imageCols - (indexRadius + radiusDiff) * 2) + indexRadius + radiusDiff;
					*tempRPtr = indexRadius;
					for (centerDist_i = -min_center_dist; centerDist_i <= min_center_dist; centerDist_i++)
					{
						for (centerDist_j = -min_center_dist; centerDist_j <= min_center_dist; centerDist_j++)
						{
							if (((centerDist_i + *tempYPtr) >> 31) || ((centerDist_j + *tempXPtr) >> 31) || ((imageRows - centerDist_i - *tempYPtr - 1) >> 31) || ((imageCols - centerDist_j - *tempXPtr - 1) >> 31))continue;
							judgePtr[centerDist_i*imageCols + centerDist_j] = 1;
						}
					}
					*judgePtr = indexRadius;
					(*tempResultN)++;
					tempXPtr++;
					tempYPtr++;
					tempRPtr++;
				}
				temp = (!k) * 2 * (indexRadius + radiusDiff);
				imagePtr += temp;
				judgePtr += temp;
				k += (!k)*(imageCols - (indexRadius + radiusDiff) * 2);
			}
		}
	}
	else if (min_radius > Radius90 && resetMaxRadius <= Radius180)
	{
		minRadius = min_radius;
		maxRadius = resetMaxRadius;
		tempAngle = 180;
		imageHeadPtr = blueImg.data;
		for (indexRadius = minRadius; indexRadius < maxRadius; indexRadius++)
		{
			imagePtr = imageHeadPtr + (indexRadius + radiusDiff)*imageCols + indexRadius + radiusDiff;
			judgePtr = circleJudgeArray + (indexRadius + radiusDiff)*imageCols + indexRadius + radiusDiff;
			for (i = 0; i < tempAngle; ++i)
			{
				tempOffsetX = (((indexRadius + radiusDiff)*SinTable180[i]) >> 16);
				tempOffsetY = (((indexRadius + radiusDiff)*CosTable180[i]) >> 16);
				outerCirclePtr180[i] = imagePtr + tempOffsetX*imageCols + tempOffsetY;
				tempOffsetX = (((indexRadius - radiusDiff)*SinTable180[i]) >> 16);
				tempOffsetY = (((indexRadius - radiusDiff)*CosTable180[i]) >> 16);
				innerCirclePtr180[i] = imagePtr + tempOffsetX*imageCols + tempOffsetY;
			}
			for (k = imageCols - (indexRadius + radiusDiff) * 2 - 1, i = (imageRows - (indexRadius + radiusDiff) * 2)*(k + 1); i; --i, --k, imagePtr++, judgePtr++)
			{
				if ((*judgePtr) == 1 || ((indexRadius < ((*judgePtr) + min_radius_dist)) && (indexRadius >((*judgePtr) - min_radius_dist))))
				{
					temp = (!k) * 2 * (indexRadius + radiusDiff);
					imagePtr += temp;
					judgePtr += temp;
					k += (!k)*(imageCols - (indexRadius + radiusDiff) * 2);
					for (j = 0, outerArrayPtr = outerCirclePtr180, innerArrayPtr = innerCirclePtr180; j < tempAngle; ++j)
					{
						(*outerArrayPtr)++;
						(*innerArrayPtr)++;
						(*outerArrayPtr) += temp;
						(*innerArrayPtr) += temp;
						outerArrayPtr++;
						innerArrayPtr++;
					}
					continue;
				}
				outerCircleSum = innerCiecleSum = 0;
				for (j = 0, outerArrayPtr = outerCirclePtr180, innerArrayPtr = innerCirclePtr180; j < tempAngle; j++)
				{
					tempDiff = (**outerArrayPtr) - (**innerArrayPtr);
					tempDiff = !(tempDiff >> 31)*tempDiff + ((tempDiff >> 31) & 1)*(-tempDiff);
					tempDiff -= max_circle_diff;
					outerCircleSum += (**outerArrayPtr);
					innerCiecleSum += (**innerArrayPtr);
					(*outerArrayPtr)++;
					(*innerArrayPtr)++;
					temp = (!k) * 2 * (indexRadius + radiusDiff);
					(*outerArrayPtr) += temp;
					(*innerArrayPtr) += temp;
					outerArrayPtr++;
					innerArrayPtr++;
				}
				tempDiff = outerCircleSum - innerCiecleSum;
				tempDiff = !(tempDiff >> 31)*tempDiff + ((tempDiff >> 31) & 1)*(-tempDiff);
				if ((tempDiff / tempAngle) > max_circle_diff)
				{
					temp = (imageRows - (indexRadius + radiusDiff) * 2)*(imageCols - (indexRadius + radiusDiff) * 2);
					temp = temp - i;
					*tempXPtr = temp % (imageCols - (indexRadius + radiusDiff) * 2) + indexRadius + radiusDiff;
					*tempYPtr = temp / (imageCols - (indexRadius + radiusDiff) * 2) + indexRadius + radiusDiff;
					*tempRPtr = indexRadius;
					for (centerDist_i = -min_center_dist; centerDist_i <= min_center_dist; centerDist_i++)
					{
						for (centerDist_j = -min_center_dist; centerDist_j <= min_center_dist; centerDist_j++)
						{
							if (((centerDist_i + *tempYPtr) >> 31) || ((centerDist_j + *tempXPtr) >> 31) || ((imageRows - centerDist_i - *tempYPtr - 1) >> 31) || ((imageCols - centerDist_j - *tempXPtr - 1) >> 31))continue;
							judgePtr[centerDist_i*imageCols + centerDist_j] = 1;
						}
					}
					*judgePtr = indexRadius;
					(*tempResultN)++;
					tempXPtr++;
					tempYPtr++;
					tempRPtr++;
				}
				temp = (!k) * 2 * (indexRadius + radiusDiff);
				imagePtr += temp;
				judgePtr += temp;
				k += (!k)*(imageCols - (indexRadius + radiusDiff) * 2);
			}
		}
		imageHeadPtr = greenImg.data;
		for (indexRadius = minRadius; indexRadius < maxRadius; indexRadius++)
		{
			imagePtr = imageHeadPtr + (indexRadius + radiusDiff)*imageCols + indexRadius + radiusDiff;
			judgePtr = circleJudgeArray + (indexRadius + radiusDiff)*imageCols + indexRadius + radiusDiff;
			for (i = 0; i < tempAngle; ++i)
			{
				tempOffsetX = (((indexRadius + radiusDiff)*SinTable180[i]) >> 16);
				tempOffsetY = (((indexRadius + radiusDiff)*CosTable180[i]) >> 16);
				outerCirclePtr180[i] = imagePtr + tempOffsetX*imageCols + tempOffsetY;
				tempOffsetX = (((indexRadius - radiusDiff)*SinTable180[i]) >> 16);
				tempOffsetY = (((indexRadius - radiusDiff)*CosTable180[i]) >> 16);
				innerCirclePtr180[i] = imagePtr + tempOffsetX*imageCols + tempOffsetY;
			}
			for (k = imageCols - (indexRadius + radiusDiff) * 2 - 1, i = (imageRows - (indexRadius + radiusDiff) * 2)*(k + 1); i; --i, --k, imagePtr++, judgePtr++)
			{
				if ((*judgePtr) == 1 || ((indexRadius < ((*judgePtr) + min_radius_dist)) && (indexRadius >((*judgePtr) - min_radius_dist))))
				{
					temp = (!k) * 2 * (indexRadius + radiusDiff);
					imagePtr += temp;
					judgePtr += temp;
					k += (!k)*(imageCols - (indexRadius + radiusDiff) * 2);
					for (j = 0, outerArrayPtr = outerCirclePtr180, innerArrayPtr = innerCirclePtr180; j < tempAngle; ++j)
					{
						(*outerArrayPtr)++;
						(*innerArrayPtr)++;
						(*outerArrayPtr) += temp;
						(*innerArrayPtr) += temp;
						outerArrayPtr++;
						innerArrayPtr++;
					}
					continue;
				}
				outerCircleSum = innerCiecleSum = 0;
				for (j = 0, outerArrayPtr = outerCirclePtr180, innerArrayPtr = innerCirclePtr180; j < tempAngle; j++)
				{
					tempDiff = (**outerArrayPtr) - (**innerArrayPtr);
					tempDiff = !(tempDiff >> 31)*tempDiff + ((tempDiff >> 31) & 1)*(-tempDiff);
					tempDiff -= max_circle_diff;
					outerCircleSum += (**outerArrayPtr);
					innerCiecleSum += (**innerArrayPtr);
					(*outerArrayPtr)++;
					(*innerArrayPtr)++;
					temp = (!k) * 2 * (indexRadius + radiusDiff);
					(*outerArrayPtr) += temp;
					(*innerArrayPtr) += temp;
					outerArrayPtr++;
					innerArrayPtr++;
				}
				tempDiff = outerCircleSum - innerCiecleSum;
				tempDiff = !(tempDiff >> 31)*tempDiff + ((tempDiff >> 31) & 1)*(-tempDiff);
				if ((tempDiff / tempAngle) > max_circle_diff)
				{
					temp = (imageRows - (indexRadius + radiusDiff) * 2)*(imageCols - (indexRadius + radiusDiff) * 2);
					temp = temp - i;
					*tempXPtr = temp % (imageCols - (indexRadius + radiusDiff) * 2) + indexRadius + radiusDiff;
					*tempYPtr = temp / (imageCols - (indexRadius + radiusDiff) * 2) + indexRadius + radiusDiff;
					*tempRPtr = indexRadius;
					for (centerDist_i = -min_center_dist; centerDist_i <= min_center_dist; centerDist_i++)
					{
						for (centerDist_j = -min_center_dist; centerDist_j <= min_center_dist; centerDist_j++)
						{
							if (((centerDist_i + *tempYPtr) >> 31) || ((centerDist_j + *tempXPtr) >> 31) || ((imageRows - centerDist_i - *tempYPtr - 1) >> 31) || ((imageCols - centerDist_j - *tempXPtr - 1) >> 31))continue;
							judgePtr[centerDist_i*imageCols + centerDist_j] = 1;
						}
					}
					*judgePtr = indexRadius;
					(*tempResultN)++;
					tempXPtr++;
					tempYPtr++;
					tempRPtr++;
				}
				temp = (!k) * 2 * (indexRadius + radiusDiff);
				imagePtr += temp;
				judgePtr += temp;
				k += (!k)*(imageCols - (indexRadius + radiusDiff) * 2);
			}
		}
		imageHeadPtr = redImg.data;
		for (indexRadius = minRadius; indexRadius < maxRadius; indexRadius++)
		{
			imagePtr = imageHeadPtr + (indexRadius + radiusDiff)*imageCols + indexRadius + radiusDiff;
			judgePtr = circleJudgeArray + (indexRadius + radiusDiff)*imageCols + indexRadius + radiusDiff;
			for (i = 0; i < tempAngle; ++i)
			{
				tempOffsetX = (((indexRadius + radiusDiff)*SinTable180[i]) >> 16);
				tempOffsetY = (((indexRadius + radiusDiff)*CosTable180[i]) >> 16);
				outerCirclePtr180[i] = imagePtr + tempOffsetX*imageCols + tempOffsetY;
				tempOffsetX = (((indexRadius - radiusDiff)*SinTable180[i]) >> 16);
				tempOffsetY = (((indexRadius - radiusDiff)*CosTable180[i]) >> 16);
				innerCirclePtr180[i] = imagePtr + tempOffsetX*imageCols + tempOffsetY;
			}
			for (k = imageCols - (indexRadius + radiusDiff) * 2 - 1, i = (imageRows - (indexRadius + radiusDiff) * 2)*(k + 1); i; --i, --k, imagePtr++, judgePtr++)
			{
				if ((*judgePtr) == 1 || ((indexRadius < ((*judgePtr) + min_radius_dist)) && (indexRadius >((*judgePtr) - min_radius_dist))))
				{
					temp = (!k) * 2 * (indexRadius + radiusDiff);
					imagePtr += temp;
					judgePtr += temp;
					k += (!k)*(imageCols - (indexRadius + radiusDiff) * 2);
					for (j = 0, outerArrayPtr = outerCirclePtr180, innerArrayPtr = innerCirclePtr180; j < tempAngle; ++j)
					{
						(*outerArrayPtr)++;
						(*innerArrayPtr)++;
						(*outerArrayPtr) += temp;
						(*innerArrayPtr) += temp;
						outerArrayPtr++;
						innerArrayPtr++;
					}
					continue;
				}
				outerCircleSum = innerCiecleSum = 0;
				for (j = 0, outerArrayPtr = outerCirclePtr180, innerArrayPtr = innerCirclePtr180; j < tempAngle; j++)
				{
					tempDiff = (**outerArrayPtr) - (**innerArrayPtr);
					tempDiff = !(tempDiff >> 31)*tempDiff + ((tempDiff >> 31) & 1)*(-tempDiff);
					tempDiff -= max_circle_diff;
					outerCircleSum += (**outerArrayPtr);
					innerCiecleSum += (**innerArrayPtr);
					(*outerArrayPtr)++;
					(*innerArrayPtr)++;
					temp = (!k) * 2 * (indexRadius + radiusDiff);
					(*outerArrayPtr) += temp;
					(*innerArrayPtr) += temp;
					outerArrayPtr++;
					innerArrayPtr++;
				}
				tempDiff = outerCircleSum - innerCiecleSum;
				tempDiff = !(tempDiff >> 31)*tempDiff + ((tempDiff >> 31) & 1)*(-tempDiff);
				if ((tempDiff / tempAngle) > max_circle_diff)
				{
					temp = (imageRows - (indexRadius + radiusDiff) * 2)*(imageCols - (indexRadius + radiusDiff) * 2);
					temp = temp - i;
					*tempXPtr = temp % (imageCols - (indexRadius + radiusDiff) * 2) + indexRadius + radiusDiff;
					*tempYPtr = temp / (imageCols - (indexRadius + radiusDiff) * 2) + indexRadius + radiusDiff;
					*tempRPtr = indexRadius;
					for (centerDist_i = -min_center_dist; centerDist_i <= min_center_dist; centerDist_i++)
					{
						for (centerDist_j = -min_center_dist; centerDist_j <= min_center_dist; centerDist_j++)
						{
							if (((centerDist_i + *tempYPtr) >> 31) || ((centerDist_j + *tempXPtr) >> 31) || ((imageRows - centerDist_i - *tempYPtr - 1) >> 31) || ((imageCols - centerDist_j - *tempXPtr - 1) >> 31))continue;
							judgePtr[centerDist_i*imageCols + centerDist_j] = 1;
						}
					}
					*judgePtr = indexRadius;
					(*tempResultN)++;
					tempXPtr++;
					tempYPtr++;
					tempRPtr++;
				}
				temp = (!k) * 2 * (indexRadius + radiusDiff);
				imagePtr += temp;
				judgePtr += temp;
				k += (!k)*(imageCols - (indexRadius + radiusDiff) * 2);
			}
		}
	}
	if (min_radius <= Radius180 && resetMaxRadius > Radius180)
	{
		minRadius = Radius180;
		maxRadius = resetMaxRadius;
		tempAngle = 360;
		imageHeadPtr = blueImg.data;
		for (indexRadius = minRadius; indexRadius < maxRadius; indexRadius++)
		{
			imagePtr = imageHeadPtr + (indexRadius + radiusDiff)*imageCols + indexRadius + radiusDiff;
			judgePtr = circleJudgeArray + (indexRadius + radiusDiff)*imageCols + indexRadius + radiusDiff;
			for (i = 0; i < tempAngle; ++i)
			{
				tempOffsetX = (((indexRadius + radiusDiff)*SinTable360[i]) >> 16);
				tempOffsetY = (((indexRadius + radiusDiff)*CosTable360[i]) >> 16);
				outerCirclePtr360[i] = imagePtr + tempOffsetX*imageCols + tempOffsetY;
				tempOffsetX = (((indexRadius - radiusDiff)*SinTable360[i]) >> 16);
				tempOffsetY = (((indexRadius - radiusDiff)*CosTable360[i]) >> 16);
				innerCirclePtr360[i] = imagePtr + tempOffsetX*imageCols + tempOffsetY;
			}
			for (k = imageCols - (indexRadius + radiusDiff) * 2 - 1, i = (imageRows - (indexRadius + radiusDiff) * 2)*(k + 1); i; --i, --k, imagePtr++, judgePtr++)
			{
				if ((*judgePtr) == 1 || ((indexRadius < ((*judgePtr) + min_radius_dist)) && (indexRadius >((*judgePtr) - min_radius_dist))))
				{
					temp = (!k) * 2 * (indexRadius + radiusDiff);
					imagePtr += temp;
					judgePtr += temp;
					k += (!k)*(imageCols - (indexRadius + radiusDiff) * 2);
					for (j = 0, outerArrayPtr = outerCirclePtr360, innerArrayPtr = innerCirclePtr360; j < tempAngle; ++j)
					{
						(*outerArrayPtr)++;
						(*innerArrayPtr)++;
						(*outerArrayPtr) += temp;
						(*innerArrayPtr) += temp;
						outerArrayPtr++;
						innerArrayPtr++;
					}
					continue;
				}
				outerCircleSum = innerCiecleSum = 0;
				for (j = 0, outerArrayPtr = outerCirclePtr360, innerArrayPtr = innerCirclePtr360; j < tempAngle; j++)
				{
					tempDiff = (**outerArrayPtr) - (**innerArrayPtr);
					tempDiff = !(tempDiff >> 31)*tempDiff + ((tempDiff >> 31) & 1)*(-tempDiff);
					tempDiff -= max_circle_diff;
					outerCircleSum += (**outerArrayPtr);
					innerCiecleSum += (**innerArrayPtr);
					(*outerArrayPtr)++;
					(*innerArrayPtr)++;
					temp = (!k) * 2 * (indexRadius + radiusDiff);
					(*outerArrayPtr) += temp;
					(*innerArrayPtr) += temp;
					outerArrayPtr++;
					innerArrayPtr++;
				}
				tempDiff = outerCircleSum - innerCiecleSum;
				tempDiff = !(tempDiff >> 31)*tempDiff + ((tempDiff >> 31) & 1)*(-tempDiff);
				if ((tempDiff / tempAngle) > max_circle_diff)
				{
					temp = (imageRows - (indexRadius + radiusDiff) * 2)*(imageCols - (indexRadius + radiusDiff) * 2);
					temp = temp - i;
					*tempXPtr = temp % (imageCols - (indexRadius + radiusDiff) * 2) + indexRadius + radiusDiff;
					*tempYPtr = temp / (imageCols - (indexRadius + radiusDiff) * 2) + indexRadius + radiusDiff;
					*tempRPtr = indexRadius;
					for (centerDist_i = -min_center_dist; centerDist_i <= min_center_dist; centerDist_i++)
					{
						for (centerDist_j = -min_center_dist; centerDist_j <= min_center_dist; centerDist_j++)
						{
							if (((centerDist_i + *tempYPtr) >> 31) || ((centerDist_j + *tempXPtr) >> 31) || ((imageRows - centerDist_i - *tempYPtr - 1) >> 31) || ((imageCols - centerDist_j - *tempXPtr - 1) >> 31))continue;
							judgePtr[centerDist_i*imageCols + centerDist_j] = 1;
						}
					}
					*judgePtr = indexRadius;
					(*tempResultN)++;
					tempXPtr++;
					tempYPtr++;
					tempRPtr++;
				}
				temp = (!k) * 2 * (indexRadius + radiusDiff);
				imagePtr += temp;
				judgePtr += temp;
				k += (!k)*(imageCols - (indexRadius + radiusDiff) * 2);
			}
		}
		imageHeadPtr = greenImg.data;
		for (indexRadius = minRadius; indexRadius < maxRadius; indexRadius++)
		{
			imagePtr = imageHeadPtr + (indexRadius + radiusDiff)*imageCols + indexRadius + radiusDiff;
			judgePtr = circleJudgeArray + (indexRadius + radiusDiff)*imageCols + indexRadius + radiusDiff;
			for (i = 0; i < tempAngle; ++i)
			{
				tempOffsetX = (((indexRadius + radiusDiff)*SinTable360[i]) >> 16);
				tempOffsetY = (((indexRadius + radiusDiff)*CosTable360[i]) >> 16);
				outerCirclePtr360[i] = imagePtr + tempOffsetX*imageCols + tempOffsetY;
				tempOffsetX = (((indexRadius - radiusDiff)*SinTable360[i]) >> 16);
				tempOffsetY = (((indexRadius - radiusDiff)*CosTable360[i]) >> 16);
				innerCirclePtr360[i] = imagePtr + tempOffsetX*imageCols + tempOffsetY;
			}
			for (k = imageCols - (indexRadius + radiusDiff) * 2 - 1, i = (imageRows - (indexRadius + radiusDiff) * 2)*(k + 1); i; --i, --k, imagePtr++, judgePtr++)
			{
				if ((*judgePtr) == 1 || ((indexRadius < ((*judgePtr) + min_radius_dist)) && (indexRadius >((*judgePtr) - min_radius_dist))))
				{
					temp = (!k) * 2 * (indexRadius + radiusDiff);
					imagePtr += temp;
					judgePtr += temp;
					k += (!k)*(imageCols - (indexRadius + radiusDiff) * 2);
					for (j = 0, outerArrayPtr = outerCirclePtr360, innerArrayPtr = innerCirclePtr360; j < tempAngle; ++j)
					{
						(*outerArrayPtr)++;
						(*innerArrayPtr)++;
						(*outerArrayPtr) += temp;
						(*innerArrayPtr) += temp;
						outerArrayPtr++;
						innerArrayPtr++;
					}
					continue;
				}
				outerCircleSum = innerCiecleSum = 0;
				for (j = 0, outerArrayPtr = outerCirclePtr360, innerArrayPtr = innerCirclePtr360; j < tempAngle; j++)
				{
					tempDiff = (**outerArrayPtr) - (**innerArrayPtr);
					tempDiff = !(tempDiff >> 31)*tempDiff + ((tempDiff >> 31) & 1)*(-tempDiff);
					tempDiff -= max_circle_diff;
					outerCircleSum += (**outerArrayPtr);
					innerCiecleSum += (**innerArrayPtr);
					(*outerArrayPtr)++;
					(*innerArrayPtr)++;
					temp = (!k) * 2 * (indexRadius + radiusDiff);
					(*outerArrayPtr) += temp;
					(*innerArrayPtr) += temp;
					outerArrayPtr++;
					innerArrayPtr++;
				}
				tempDiff = outerCircleSum - innerCiecleSum;
				tempDiff = !(tempDiff >> 31)*tempDiff + ((tempDiff >> 31) & 1)*(-tempDiff);
				if ((tempDiff / tempAngle) > max_circle_diff)
				{
					temp = (imageRows - (indexRadius + radiusDiff) * 2)*(imageCols - (indexRadius + radiusDiff) * 2);
					temp = temp - i;
					*tempXPtr = temp % (imageCols - (indexRadius + radiusDiff) * 2) + indexRadius + radiusDiff;
					*tempYPtr = temp / (imageCols - (indexRadius + radiusDiff) * 2) + indexRadius + radiusDiff;
					*tempRPtr = indexRadius;
					for (centerDist_i = -min_center_dist; centerDist_i <= min_center_dist; centerDist_i++)
					{
						for (centerDist_j = -min_center_dist; centerDist_j <= min_center_dist; centerDist_j++)
						{
							if (((centerDist_i + *tempYPtr) >> 31) || ((centerDist_j + *tempXPtr) >> 31) || ((imageRows - centerDist_i - *tempYPtr - 1) >> 31) || ((imageCols - centerDist_j - *tempXPtr - 1) >> 31))continue;
							judgePtr[centerDist_i*imageCols + centerDist_j] = 1;
						}
					}
					*judgePtr = indexRadius;
					(*tempResultN)++;
					tempXPtr++;
					tempYPtr++;
					tempRPtr++;
				}
				temp = (!k) * 2 * (indexRadius + radiusDiff);
				imagePtr += temp;
				judgePtr += temp;
				k += (!k)*(imageCols - (indexRadius + radiusDiff) * 2);
			}
		}
		imageHeadPtr = redImg.data;
		for (indexRadius = minRadius; indexRadius < maxRadius; indexRadius++)
		{
			imagePtr = imageHeadPtr + (indexRadius + radiusDiff)*imageCols + indexRadius + radiusDiff;
			judgePtr = circleJudgeArray + (indexRadius + radiusDiff)*imageCols + indexRadius + radiusDiff;
			for (i = 0; i < tempAngle; ++i)
			{
				tempOffsetX = (((indexRadius + radiusDiff)*SinTable360[i]) >> 16);
				tempOffsetY = (((indexRadius + radiusDiff)*CosTable360[i]) >> 16);
				outerCirclePtr360[i] = imagePtr + tempOffsetX*imageCols + tempOffsetY;
				tempOffsetX = (((indexRadius - radiusDiff)*SinTable360[i]) >> 16);
				tempOffsetY = (((indexRadius - radiusDiff)*CosTable360[i]) >> 16);
				innerCirclePtr360[i] = imagePtr + tempOffsetX*imageCols + tempOffsetY;
			}
			for (k = imageCols - (indexRadius + radiusDiff) * 2 - 1, i = (imageRows - (indexRadius + radiusDiff) * 2)*(k + 1); i; --i, --k, imagePtr++, judgePtr++)
			{
				if ((*judgePtr) == 1 || ((indexRadius < ((*judgePtr) + min_radius_dist)) && (indexRadius >((*judgePtr) - min_radius_dist))))
				{
					temp = (!k) * 2 * (indexRadius + radiusDiff);
					imagePtr += temp;
					judgePtr += temp;
					k += (!k)*(imageCols - (indexRadius + radiusDiff) * 2);
					for (j = 0, outerArrayPtr = outerCirclePtr360, innerArrayPtr = innerCirclePtr360; j < tempAngle; ++j)
					{
						(*outerArrayPtr)++;
						(*innerArrayPtr)++;
						(*outerArrayPtr) += temp;
						(*innerArrayPtr) += temp;
						outerArrayPtr++;
						innerArrayPtr++;
					}
					continue;
				}
				outerCircleSum = innerCiecleSum = 0;
				for (j = 0, outerArrayPtr = outerCirclePtr360, innerArrayPtr = innerCirclePtr360; j < tempAngle; j++)
				{
					tempDiff = (**outerArrayPtr) - (**innerArrayPtr);
					tempDiff = !(tempDiff >> 31)*tempDiff + ((tempDiff >> 31) & 1)*(-tempDiff);
					tempDiff -= max_circle_diff;
					outerCircleSum += (**outerArrayPtr);
					innerCiecleSum += (**innerArrayPtr);
					(*outerArrayPtr)++;
					(*innerArrayPtr)++;
					temp = (!k) * 2 * (indexRadius + radiusDiff);
					(*outerArrayPtr) += temp;
					(*innerArrayPtr) += temp;
					outerArrayPtr++;
					innerArrayPtr++;
				}
				tempDiff = outerCircleSum - innerCiecleSum;
				tempDiff = !(tempDiff >> 31)*tempDiff + ((tempDiff >> 31) & 1)*(-tempDiff);
				if ((tempDiff / tempAngle) > max_circle_diff)
				{
					temp = (imageRows - (indexRadius + radiusDiff) * 2)*(imageCols - (indexRadius + radiusDiff) * 2);
					temp = temp - i;
					*tempXPtr = temp % (imageCols - (indexRadius + radiusDiff) * 2) + indexRadius + radiusDiff;
					*tempYPtr = temp / (imageCols - (indexRadius + radiusDiff) * 2) + indexRadius + radiusDiff;
					*tempRPtr = indexRadius;
					for (centerDist_i = -min_center_dist; centerDist_i <= min_center_dist; centerDist_i++)
					{
						for (centerDist_j = -min_center_dist; centerDist_j <= min_center_dist; centerDist_j++)
						{
							if (((centerDist_i + *tempYPtr) >> 31) || ((centerDist_j + *tempXPtr) >> 31) || ((imageRows - centerDist_i - *tempYPtr - 1) >> 31) || ((imageCols - centerDist_j - *tempXPtr - 1) >> 31))continue;
							judgePtr[centerDist_i*imageCols + centerDist_j] = 1;
						}
					}
					*judgePtr = indexRadius;
					(*tempResultN)++;
					tempXPtr++;
					tempYPtr++;
					tempRPtr++;
				}
				temp = (!k) * 2 * (indexRadius + radiusDiff);
				imagePtr += temp;
				judgePtr += temp;
				k += (!k)*(imageCols - (indexRadius + radiusDiff) * 2);
			}
		}
	}
	else if (min_radius > Radius180 && resetMaxRadius > Radius180)
	{
		minRadius = min_radius;
		maxRadius = resetMaxRadius;
		tempAngle = 360;
		imageHeadPtr = blueImg.data;
		for (indexRadius = minRadius; indexRadius < maxRadius; indexRadius++)
		{
			imagePtr = imageHeadPtr + (indexRadius + radiusDiff)*imageCols + indexRadius + radiusDiff;
			judgePtr = circleJudgeArray + (indexRadius + radiusDiff)*imageCols + indexRadius + radiusDiff;
			for (i = 0; i < tempAngle; ++i)
			{
				tempOffsetX = (((indexRadius + radiusDiff)*SinTable360[i]) >> 16);
				tempOffsetY = (((indexRadius + radiusDiff)*CosTable360[i]) >> 16);
				outerCirclePtr360[i] = imagePtr + tempOffsetX*imageCols + tempOffsetY;
				tempOffsetX = (((indexRadius - radiusDiff)*SinTable360[i]) >> 16);
				tempOffsetY = (((indexRadius - radiusDiff)*CosTable360[i]) >> 16);
				innerCirclePtr360[i] = imagePtr + tempOffsetX*imageCols + tempOffsetY;
			}
			for (k = imageCols - (indexRadius + radiusDiff) * 2 - 1, i = (imageRows - (indexRadius + radiusDiff) * 2)*(k + 1); i; --i, --k, imagePtr++, judgePtr++)
			{
				if ((*judgePtr) == 1 || ((indexRadius < ((*judgePtr) + min_radius_dist)) && (indexRadius >((*judgePtr) - min_radius_dist))))
				{
					temp = (!k) * 2 * (indexRadius + radiusDiff);
					imagePtr += temp;
					judgePtr += temp;
					k += (!k)*(imageCols - (indexRadius + radiusDiff) * 2);
					for (j = 0, outerArrayPtr = outerCirclePtr360, innerArrayPtr = innerCirclePtr360; j < tempAngle; ++j)
					{
						(*outerArrayPtr)++;
						(*innerArrayPtr)++;
						(*outerArrayPtr) += temp;
						(*innerArrayPtr) += temp;
						outerArrayPtr++;
						innerArrayPtr++;
					}
					continue;
				}
				outerCircleSum = innerCiecleSum = 0;
				for (j = 0, outerArrayPtr = outerCirclePtr360, innerArrayPtr = innerCirclePtr360; j < tempAngle; j++)
				{
					tempDiff = (**outerArrayPtr) - (**innerArrayPtr);
					tempDiff = !(tempDiff >> 31)*tempDiff + ((tempDiff >> 31) & 1)*(-tempDiff);
					tempDiff -= max_circle_diff;
					outerCircleSum += (**outerArrayPtr);
					innerCiecleSum += (**innerArrayPtr);
					(*outerArrayPtr)++;
					(*innerArrayPtr)++;
					temp = (!k) * 2 * (indexRadius + radiusDiff);
					(*outerArrayPtr) += temp;
					(*innerArrayPtr) += temp;
					outerArrayPtr++;
					innerArrayPtr++;
				}
				tempDiff = outerCircleSum - innerCiecleSum;
				tempDiff = !(tempDiff >> 31)*tempDiff + ((tempDiff >> 31) & 1)*(-tempDiff);
				if ((tempDiff / tempAngle) > max_circle_diff)
				{
					temp = (imageRows - (indexRadius + radiusDiff) * 2)*(imageCols - (indexRadius + radiusDiff) * 2);
					temp = temp - i;
					*tempXPtr = temp % (imageCols - (indexRadius + radiusDiff) * 2) + indexRadius + radiusDiff;
					*tempYPtr = temp / (imageCols - (indexRadius + radiusDiff) * 2) + indexRadius + radiusDiff;
					*tempRPtr = indexRadius;
					for (centerDist_i = -min_center_dist; centerDist_i <= min_center_dist; centerDist_i++)
					{
						for (centerDist_j = -min_center_dist; centerDist_j <= min_center_dist; centerDist_j++)
						{
							if (((centerDist_i + *tempYPtr) >> 31) || ((centerDist_j + *tempXPtr) >> 31) || ((imageRows - centerDist_i - *tempYPtr - 1) >> 31) || ((imageCols - centerDist_j - *tempXPtr - 1) >> 31))continue;
							judgePtr[centerDist_i*imageCols + centerDist_j] = 1;
						}
					}
					*judgePtr = indexRadius;
					(*tempResultN)++;
					tempXPtr++;
					tempYPtr++;
					tempRPtr++;
				}
				temp = (!k) * 2 * (indexRadius + radiusDiff);
				imagePtr += temp;
				judgePtr += temp;
				k += (!k)*(imageCols - (indexRadius + radiusDiff) * 2);
			}
		}
		imageHeadPtr = greenImg.data;
		for (indexRadius = minRadius; indexRadius < maxRadius; indexRadius++)
		{
			imagePtr = imageHeadPtr + (indexRadius + radiusDiff)*imageCols + indexRadius + radiusDiff;
			judgePtr = circleJudgeArray + (indexRadius + radiusDiff)*imageCols + indexRadius + radiusDiff;
			for (i = 0; i < tempAngle; ++i)
			{
				tempOffsetX = (((indexRadius + radiusDiff)*SinTable360[i]) >> 16);
				tempOffsetY = (((indexRadius + radiusDiff)*CosTable360[i]) >> 16);
				outerCirclePtr360[i] = imagePtr + tempOffsetX*imageCols + tempOffsetY;
				tempOffsetX = (((indexRadius - radiusDiff)*SinTable360[i]) >> 16);
				tempOffsetY = (((indexRadius - radiusDiff)*CosTable360[i]) >> 16);
				innerCirclePtr360[i] = imagePtr + tempOffsetX*imageCols + tempOffsetY;
			}
			for (k = imageCols - (indexRadius + radiusDiff) * 2 - 1, i = (imageRows - (indexRadius + radiusDiff) * 2)*(k + 1); i; --i, --k, imagePtr++, judgePtr++)
			{
				if ((*judgePtr) == 1 || ((indexRadius < ((*judgePtr) + min_radius_dist)) && (indexRadius >((*judgePtr) - min_radius_dist))))
				{
					temp = (!k) * 2 * (indexRadius + radiusDiff);
					imagePtr += temp;
					judgePtr += temp;
					k += (!k)*(imageCols - (indexRadius + radiusDiff) * 2);
					for (j = 0, outerArrayPtr = outerCirclePtr360, innerArrayPtr = innerCirclePtr360; j < tempAngle; ++j)
					{
						(*outerArrayPtr)++;
						(*innerArrayPtr)++;
						(*outerArrayPtr) += temp;
						(*innerArrayPtr) += temp;
						outerArrayPtr++;
						innerArrayPtr++;
					}
					continue;
				}
				outerCircleSum = innerCiecleSum = 0;
				for (j = 0, outerArrayPtr = outerCirclePtr360, innerArrayPtr = innerCirclePtr360; j < tempAngle; j++)
				{
					tempDiff = (**outerArrayPtr) - (**innerArrayPtr);
					tempDiff = !(tempDiff >> 31)*tempDiff + ((tempDiff >> 31) & 1)*(-tempDiff);
					tempDiff -= max_circle_diff;
					outerCircleSum += (**outerArrayPtr);
					innerCiecleSum += (**innerArrayPtr);
					(*outerArrayPtr)++;
					(*innerArrayPtr)++;
					temp = (!k) * 2 * (indexRadius + radiusDiff);
					(*outerArrayPtr) += temp;
					(*innerArrayPtr) += temp;
					outerArrayPtr++;
					innerArrayPtr++;
				}
				tempDiff = outerCircleSum - innerCiecleSum;
				tempDiff = !(tempDiff >> 31)*tempDiff + ((tempDiff >> 31) & 1)*(-tempDiff);
				if ((tempDiff / tempAngle) > max_circle_diff)
				{
					temp = (imageRows - (indexRadius + radiusDiff) * 2)*(imageCols - (indexRadius + radiusDiff) * 2);
					temp = temp - i;
					*tempXPtr = temp % (imageCols - (indexRadius + radiusDiff) * 2) + indexRadius + radiusDiff;
					*tempYPtr = temp / (imageCols - (indexRadius + radiusDiff) * 2) + indexRadius + radiusDiff;
					*tempRPtr = indexRadius;
					for (centerDist_i = -min_center_dist; centerDist_i <= min_center_dist; centerDist_i++)
					{
						for (centerDist_j = -min_center_dist; centerDist_j <= min_center_dist; centerDist_j++)
						{
							if (((centerDist_i + *tempYPtr) >> 31) || ((centerDist_j + *tempXPtr) >> 31) || ((imageRows - centerDist_i - *tempYPtr - 1) >> 31) || ((imageCols - centerDist_j - *tempXPtr - 1) >> 31))continue;
							judgePtr[centerDist_i*imageCols + centerDist_j] = 1;
						}
					}
					*judgePtr = indexRadius;
					(*tempResultN)++;
					tempXPtr++;
					tempYPtr++;
					tempRPtr++;
				}
				temp = (!k) * 2 * (indexRadius + radiusDiff);
				imagePtr += temp;
				judgePtr += temp;
				k += (!k)*(imageCols - (indexRadius + radiusDiff) * 2);
			}
		}
		imageHeadPtr = redImg.data;
		for (indexRadius = minRadius; indexRadius < maxRadius; indexRadius++)
		{
			imagePtr = imageHeadPtr + (indexRadius + radiusDiff)*imageCols + indexRadius + radiusDiff;
			judgePtr = circleJudgeArray + (indexRadius + radiusDiff)*imageCols + indexRadius + radiusDiff;
			for (i = 0; i < tempAngle; ++i)
			{
				tempOffsetX = (((indexRadius + radiusDiff)*SinTable360[i]) >> 16);
				tempOffsetY = (((indexRadius + radiusDiff)*CosTable360[i]) >> 16);
				outerCirclePtr360[i] = imagePtr + tempOffsetX*imageCols + tempOffsetY;
				tempOffsetX = (((indexRadius - radiusDiff)*SinTable360[i]) >> 16);
				tempOffsetY = (((indexRadius - radiusDiff)*CosTable360[i]) >> 16);
				innerCirclePtr360[i] = imagePtr + tempOffsetX*imageCols + tempOffsetY;
			}
			for (k = imageCols - (indexRadius + radiusDiff) * 2 - 1, i = (imageRows - (indexRadius + radiusDiff) * 2)*(k + 1); i; --i, --k, imagePtr++, judgePtr++)
			{
				if ((*judgePtr) == 1 || ((indexRadius < ((*judgePtr) + min_radius_dist)) && (indexRadius >((*judgePtr) - min_radius_dist))))
				{
					temp = (!k) * 2 * (indexRadius + radiusDiff);
					imagePtr += temp;
					judgePtr += temp;
					k += (!k)*(imageCols - (indexRadius + radiusDiff) * 2);
					for (j = 0, outerArrayPtr = outerCirclePtr360, innerArrayPtr = innerCirclePtr360; j < tempAngle; ++j)
					{
						(*outerArrayPtr)++;
						(*innerArrayPtr)++;
						(*outerArrayPtr) += temp;
						(*innerArrayPtr) += temp;
						outerArrayPtr++;
						innerArrayPtr++;
					}
					continue;
				}
				outerCircleSum = innerCiecleSum = 0;
				for (j = 0, outerArrayPtr = outerCirclePtr360, innerArrayPtr = innerCirclePtr360; j < tempAngle; j++)
				{
					tempDiff = (**outerArrayPtr) - (**innerArrayPtr);
					tempDiff = !(tempDiff >> 31)*tempDiff + ((tempDiff >> 31) & 1)*(-tempDiff);
					tempDiff -= max_circle_diff;
					outerCircleSum += (**outerArrayPtr);
					innerCiecleSum += (**innerArrayPtr);
					(*outerArrayPtr)++;
					(*innerArrayPtr)++;
					temp = (!k) * 2 * (indexRadius + radiusDiff);
					(*outerArrayPtr) += temp;
					(*innerArrayPtr) += temp;
					outerArrayPtr++;
					innerArrayPtr++;
				}
				tempDiff = outerCircleSum - innerCiecleSum;
				tempDiff = !(tempDiff >> 31)*tempDiff + ((tempDiff >> 31) & 1)*(-tempDiff);
				if ((tempDiff / tempAngle) > max_circle_diff)
				{
					temp = (imageRows - (indexRadius + radiusDiff) * 2)*(imageCols - (indexRadius + radiusDiff) * 2);
					temp = temp - i;
					*tempXPtr = temp % (imageCols - (indexRadius + radiusDiff) * 2) + indexRadius + radiusDiff;
					*tempYPtr = temp / (imageCols - (indexRadius + radiusDiff) * 2) + indexRadius + radiusDiff;
					*tempRPtr = indexRadius;
					for (centerDist_i = -min_center_dist; centerDist_i <= min_center_dist; centerDist_i++)
					{
						for (centerDist_j = -min_center_dist; centerDist_j <= min_center_dist; centerDist_j++)
						{
							if (((centerDist_i + *tempYPtr) >> 31) || ((centerDist_j + *tempXPtr) >> 31) || ((imageRows - centerDist_i - *tempYPtr - 1) >> 31) || ((imageCols - centerDist_j - *tempXPtr - 1) >> 31))continue;
							judgePtr[centerDist_i*imageCols + centerDist_j] = 1;
						}
					}
					*judgePtr = indexRadius;
					(*tempResultN)++;
					tempXPtr++;
					tempYPtr++;
					tempRPtr++;
				}
				temp = (!k) * 2 * (indexRadius + radiusDiff);
				imagePtr += temp;
				judgePtr += temp;
				k += (!k)*(imageCols - (indexRadius + radiusDiff) * 2);
			}
		}
	}
	if ((*tempResultN) > max_circle)
	{
		for (i = 0; i < max_circle; i++)
		{
			for (j = i + 1; j < *tempResultN; j++)
			{
				if (tempReslutR[j] > tempReslutR[i])
				{
					temp = tempReslutR[i];
					tempReslutR[i] = tempReslutR[j];
					tempReslutR[j] = temp;
				}
			}
		}
		*tempResultN = max_circle;
	}
	for (i = 0; i < *tempResultN; i++)
	{
		x[i] = tempResultX[i];
		y[i] = tempResultY[i];
		radius[i] = tempReslutR[i];
	}
	*circle_cnt = *tempResultN;
	delete tempResultX;
	delete tempResultY;
	delete tempReslutR;
	delete tempResultN;
	delete circleJudgeArray;
	return MY_OK;
}
