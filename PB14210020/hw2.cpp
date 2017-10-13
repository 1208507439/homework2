#define PI 3.1415927
#define FIXPOINT_SHIFT 8
#define FIXPOINT_SCALE 256
#define FIXPOINT_HALF 0x80 //用定点数表示的0.5

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
#include <iostream>
using namespace std;

//返回int型数i的绝对值
inline int AbsInt(int i);

//功能说明：对xCenters, yCenters, radii, differences所表示的已找到的nCircle个圆进行非极大值抑制，留
//下其中differences最大的
//xCenters：圆心的横坐标
//yCenters：圆心的纵坐标
//radii：圆的半径
//differences：圆周差分值
//nCircle：已找到的圆的个数
int NonMaxSuppress
(
	int*xCenters, int*yCenters, int*radii, int*differences, int&nCircle,
	int min_center_dist, int min_radius_dist
);

//用圆周差分法找出单通道图像img中半径在[min_radius, max_radius]中的圆，把这些圆的圆心的坐标和半径存
//入xCenters、yCenters和radii，圆周差分值存入differences，起始地址分别为 xCenters + nCircle,
//yCenters + nCircle, radii + nCircle和differences + nCircle。nCircle是xCenters, yCenters, radii和
//differences中已有圆的数目，每找到一个圆就使其加1，但保持小于等于nCirclrMax。2 * dr是圆周差分中内
//、外圆的半径之差。maxCircleDiff是定点数，表示圆周差分的阈值。min_center_dist和min_radius_dist用于
//非极大值抑制。
int ustc_FindCircles1Channel
(
	Mat img, int min_radius, int max_radius, int dr,
	int min_center_dist, int min_radius_dist, int maxCircleDiff,
	int*xCenters, int*yCenters, int*radii, int*differences, int&nCircle, int nCircleMax
);

//功能说明：找到图像中所有圆心在图像内的圆，得到中心点和半径
//colorImg：用来搜索圆形目标的彩色图像
//min_radius：需要搜索的圆的最小半径
//max_radius：需要搜索的圆的最大半径
//min_center_dist：找到的圆心之间的最小距离
//min_radius_dist：同心圆半径之间的最小差距
//max_circle_diff：阈值，圆周差分值低于此阈值，不是圆
//x：数组，存储所有的圆的中心点x坐标
//y：数组，存储所有的圆的中心点y坐标
//radius：数组，存储所有的圆的半径值
//circle_cnt：图像中找到的圆的数目
//max_circle：外部传入参数，圆的数目上限。如果图像中圆的数目超过此参数，根据差分值由大到小进行排序
//返回值：MY_OK或者MY_FAIL
int ustc_Find_Circles_By_Difference
(
	Mat colorImg, int min_radius, int max_radius,
	int min_center_dist, int min_radius_dist, int max_circle_diff,
	int*x, int*y, int*radius, int*circle_cnt, int max_circle
);

inline int AbsInt(int i)
{
	int j = i >> 31;
	return (i ^ j) - j;
}

int NonMaxSuppress
(
	int*xCenters, int*yCenters, int*radii, int*differences, int&nCircle,
	int min_center_dist, int min_radius_dist
)
{
	if (nCircle == 0) return -1;
	char*states = new char[nCircle]; //states[i]表示第i个圆的状态
	if (!states) return -1;
	memset(states, 'u', nCircle); //状态'u'表示不确定是否为极大值圆
	char finished; //循环结束的标志
	do
	{
		int m = -1;
		int diffMax = 0;
		for (int i = 0; i < nCircle; i++)
		{
			if (states[i] == 'u' && differences[i] > diffMax)
			{
				m = i;
				diffMax = differences[i];
			}
		} //这时的m为状态为'u'的圆中差分值最大的圆的序号
		states[m] = 'r'; //状态为'r'表示不进行抑制，留下该圆
		for (int i = 0; i < nCircle; i++)
		{
			if (states[i] == 'u'
				&& AbsInt(xCenters[i] - xCenters[m]) < min_center_dist
				&& AbsInt(yCenters[i] - yCenters[m]) < min_center_dist
				&& AbsInt(radii[i] - radii[m]) < min_radius_dist)
				states[i] = 's'; //状态为's'表示进行抑制
		} //抑制所有与具有极大差分值的圆过于接近的圆
		finished = 1;
		for (int i = 0; i < nCircle; i++) finished &= (states[i] != 'u');
		//如果还有圆的状态为'u'，则finished为0，将继续循环直到所有圆的状态为'r'或's'
	} while (!finished);
	int newNCircle = 0;
	for (int i = 0; i < nCircle; i++)
	{
		if (states[i] == 'r')
		{
			xCenters[newNCircle] = xCenters[i];
			yCenters[newNCircle] = yCenters[i];
			radii[newNCircle] = radii[i];
			differences[newNCircle] = differences[i];
			newNCircle++;
		}
	} //把留下的圆集中存放在数组低地址端
	nCircle = newNCircle;
	delete[]states;
	return 1;
}

int ustc_FindCircles1Channel
(
	Mat img, int min_radius, int max_radius, int dr,
	int min_center_dist, int min_radius_dist, int maxCircleDiff,
	int*xCenters, int*yCenters, int*radii, int*differences, int&nCircle, int nCircleMax
)
{
	if (!(img.data && img.depth() == CV_8U && img.channels() == 1
		&& min_radius > 0 && max_radius > min_radius && dr > 0
		&& min_center_dist > 0 && min_radius_dist > 0
		&& maxCircleDiff > 0 && maxCircleDiff < (256 << FIXPOINT_SHIFT)
		&& xCenters && yCenters && radii && differences
		&& nCircle >= 0 && nCircle < nCircleMax))
		return -1;
	int sine[360], cosine[360];
	for (int theta = 0; theta < 360; theta++)
	{
		sine[theta] = sin(theta / 180.0 * PI) * FIXPOINT_SCALE;
		cosine[theta] = cos(theta / 180.0 * PI) * FIXPOINT_SCALE;
	} //求出0~359度的正弦、余弦值，用定点小数表示
	int*sum = new int[img.cols];
	int*nSample = new int[img.cols];
	if (!(sum && nSample)) return -1;
	Mat average(max_radius + dr + 1, img.cols, CV_32SC1);
	for (int y = 0; y < img.rows; y++)
	{
		for (int r = min_radius - dr; r <= max_radius + dr; r++)
		{
			for (int x = 0; x < img.cols; x++)
			{
				sum[x] = 127;
				nSample[x] = 1;
			} //防止出现nSample[x]为0的情况导致除零错
			for (int theta = 0; theta < 360; theta++)
			{
				int offsetX = (r * cosine[theta] + FIXPOINT_HALF) >> FIXPOINT_SHIFT;
				int offsetY = (r * sine[theta] + FIXPOINT_HALF) >> FIXPOINT_SHIFT;
				//定点小数转换为定点整数
				if (y + offsetY >= 0 && y + offsetY < img.rows)
				{
					uchar*rowImg = img.ptr<uchar>(y + offsetY);
					int startX = offsetX >= 0 ? 0 : -offsetX;
					int endX = offsetX >= 0 ? img.cols - offsetX : img.cols;
					for (int x = startX; x < endX; x++)
					{
						sum[x] += rowImg[x + offsetX];
						nSample[x]++;
					}
				}
			}
			for (int x = 0; x < img.cols; x++)
				average.ptr<int>(r)[x] = (sum[x] << FIXPOINT_SHIFT) / nSample[x];
			//用定点除法代替浮点除法以提高效率，得到的平均像素值为定点小数
		}
		for (int r = min_radius; r <= max_radius; r++)
		{
			for (int x = 0; x < img.cols; x++)
			{
				int diff = AbsInt(average.ptr<int>(r + dr)[x] - average.ptr<int>(r - dr)[x]);
				if (diff > maxCircleDiff && nCircle < nCircleMax)
				{
					xCenters[nCircle] = x;
					yCenters[nCircle] = y;
					radii[nCircle] = r;
					differences[nCircle] = diff;
					nCircle++;
					if (nCircle == nCircleMax)
						NonMaxSuppress
						(
							xCenters, yCenters, radii, differences, nCircle,
							min_center_dist, min_radius_dist
						);
				}
			}
		}
	}
	NonMaxSuppress
	(
		xCenters, yCenters, radii, differences, nCircle,
		min_center_dist, min_radius_dist
	);
	delete[]sum;
	delete[]nSample;
	return 1;
}

int ustc_Find_Circles_By_Difference
(
	Mat colorImg, int min_radius, int max_radius,
	int min_center_dist, int min_radius_dist, int max_circle_diff,
	int*x, int*y, int*radius, int*circle_cnt, int max_circle
)
{
	if (!(colorImg.data && colorImg.depth() == CV_8U && colorImg.channels() == 3
		&& min_radius > 0 && max_radius > min_radius
		&& min_center_dist > 0 && min_radius_dist > 0
		&& max_circle_diff > 0 && max_circle_diff < 256
		&& x && y && radius && max_circle > 0))
		return -1;
	if (max_radius > colorImg.rows / 2) max_radius = colorImg.rows / 2;
	if (max_radius > colorImg.cols / 2) max_radius = colorImg.cols / 2;
	//图像中可能出现的最大的圆的直径为colorImg.rows和colorImg.cols中的较小者，没有必要搜寻太大的圆
	Mat channels[3];
	split(colorImg, channels);
	const int dr = 5;
	int nCircle = 0;
	int*xCenters = new int[max_circle];
	int*yCenters = new int[max_circle];
	int*radii = new int[max_circle];
	int*differences = new int[max_circle];
	if (!(xCenters && yCenters && radii && differences)) return -1;
	ustc_FindCircles1Channel
	(
		channels[2], min_radius, max_radius, dr,
		min_center_dist, min_radius_dist, max_circle_diff << FIXPOINT_SHIFT,
		xCenters, yCenters, radii, differences, nCircle, max_circle
	);
	cout << "channel red finished." << endl;
	ustc_FindCircles1Channel
	(
		channels[1], min_radius, max_radius, dr,
		min_center_dist, min_radius_dist, max_circle_diff << FIXPOINT_SHIFT,
		xCenters, yCenters, radii, differences, nCircle, max_circle
	);
	cout << "channel green finished." << endl;
	ustc_FindCircles1Channel
	(
		channels[0], min_radius, max_radius, dr,
		min_center_dist, min_radius_dist, max_circle_diff << FIXPOINT_SHIFT,
		xCenters, yCenters, radii, differences, nCircle, max_circle
	);
	cout << "channel blue finished." << endl;
	memcpy(x, xCenters, nCircle * sizeof(int));
	memcpy(y, yCenters, nCircle * sizeof(int));
	memcpy(radius, radii, nCircle * sizeof(int));
	*circle_cnt = nCircle;
	delete[]xCenters;
	delete[]yCenters;
	delete[]radii;
	delete[]differences;
	return 1;
}
