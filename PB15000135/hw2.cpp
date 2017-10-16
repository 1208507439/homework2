#include "opencv2/opencv.hpp"
#include <iostream>
#include <time.h>
#include<cstdlib>
using namespace std;
using namespace cv;
#define MY_OK 1
#define MY_FAIL 0
#define Lenth 100000
#define detaR 5
float Table_sin[360] = { 0 };
float Table_cos[360] = { 0 };
int diffOfcirlce[Lenth] = { 0 };
int xtemp[Lenth] = { 0 };
int ytemp[Lenth] = { 0 };
int radiustemp[Lenth] = { 0 };
int diff[Lenth] = { 0 };
int xt[Lenth] = { 0 };
int yt[Lenth] = { 0 };
int rt[Lenth] = { 0 };
int **R_sin;
int **R_cos;
int *index;
//得到sin和cos的两个表
void GetTable() {
	float temp = 0;
	for (int i = 360 - 1; i >= 0; --i) {
		Table_sin[i] = sin(temp);
		Table_cos[i] = cos(temp);
		temp += 0.01898;
	}
}

//得到sin和cos与r相乘后的两个表
void GetR_theta(int Rmax, int Rmin) {
	R_sin = new int*[Rmax + detaR + 1];
	R_cos = new int *[Rmax + detaR + 1];
	Rmax += detaR;
	Rmin -= detaR;
	for (int r = Rmin; r <= Rmax; r++) {
		R_sin[r] = new int[360];
		R_cos[r] = new int[360];
	}
	for (int r = Rmin; r <= Rmax; r++) {
		for (int theta = 0; theta < 360; theta++) {
			R_sin[r][theta] = r*Table_sin[theta];
			R_cos[r][theta] = r*Table_cos[theta];
		}
	}
}

void Getindex(int height, int width) {
	index = new int[height];
	for (int i = 0; i < height; i++) {
		index[i] = i*width;
	}
}

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
	int max_circle) {
	if (colorImg.data == NULL) {
		cout << "Image is NULL" << endl;
		return MY_FAIL;
	}

	int num = 0;
	int height = colorImg.rows;
	int width = colorImg.cols;
	//由于找整圆，所以当最大半径大于宽与长时，可以修正
	if (2 * max_radius > height) max_radius = height / 2;
	if (2 * max_radius > width)max_radius = width / 2;
	Mat RedImg(height, width, CV_8UC1);
	Mat GreenImg(height, width, CV_8UC1);
	Mat BlueImg(height, width, CV_8UC1);
	Mat out[] = { BlueImg,GreenImg,RedImg };
	split(colorImg, out);
	GetTable();
	GetR_theta(max_radius, min_radius);
	Getindex(height, width);
	int total = height*width;
	int *tempblue = new int[total];
	uchar *Imgdata[3] = { BlueImg.data,GreenImg.data,RedImg.data };
	for (int Imgnum = 0; Imgnum < 3; Imgnum++) {
		uchar *data = Imgdata[Imgnum];
		int r1 = max_radius >= 60 ? 60 : max_radius;
		for (int r = min_radius; r <= r1; r++) {
			memset(tempblue, 0, sizeof(int)*total);
			int r_inside = r - detaR;
			int r_outside = r + detaR;
			int heightup = height - r_outside;
			int widthup = width - r_outside;
			for (int theta = 0; theta < 180; theta++) {
				int temp0 = R_sin[r_outside][theta << 1];
				int temp1 = R_sin[r_inside][theta << 1];
				int temp2 = R_cos[r_outside][theta << 1];
				int temp3 = R_cos[r_inside][theta << 1];
				for (int row = r_outside; row < heightup; row++) {
					int i_outside = row + temp0;
					int i_inside = row + temp1;
					int indexrow = index[row] + r_outside;
					int indexioutside = index[i_outside] + r_outside + temp2;
					int indexiinside = index[i_inside] + r_outside + temp3;
					int *pblue = tempblue + indexrow;
					uchar *dataout = data + indexioutside;
					uchar *datain = data + indexiinside;
					int colmid = (widthup - r_outside) / 8;
					for (int i = 0; i < colmid; i++, pblue += 8, dataout += 8, datain += 8) {
						*(pblue) += *(dataout)-*(datain);
						*(pblue + 1) += *(dataout + 1) - *(datain + 1);
						*(pblue + 2) += *(dataout + 2) - *(datain + 2);
						*(pblue + 3) += *(dataout + 3) - *(datain + 3);
						*(pblue + 4) += *(dataout + 4) - *(datain + 4);
						*(pblue + 5) += *(dataout + 5) - *(datain + 5);
						*(pblue + 6) += *(dataout + 6) - *(datain + 6);
						*(pblue + 7) += *(dataout + 7) - *(datain + 7);
					}
					colmid = widthup - (widthup - r_outside) % 8;
					for (int col = colmid; col < widthup; col++) {
						*(pblue) += *(dataout)-*(datain);
						pblue += 1;
						dataout += 1;
						datain += 1;
					}
				}
			}
			for (int i = r_outside; i < height - r_outside; i++) {
				int tempindex_i = index[i];
				for (int j = r_outside; j < width - r_outside; j++) {
					int temp = tempblue[tempindex_i + j];
					temp = temp > 0 ? temp : -temp;
					if (temp > 180 * max_circle_diff) {
						xtemp[num] = i;
						ytemp[num] = j;
						radiustemp[num] = r;
						diffOfcirlce[num] = temp*0.56;//100/180
						num += 1;
						if (num == Lenth) {
							cout << "max_circle_diff is too low" << endl;
							return MY_FAIL;
						}
					}
				}
			}
		}

		int r2 = max_radius > 60 ? max_radius : 60;
		for (int r = 61; r <= r2; r++) {
			memset(tempblue, 0, sizeof(int)*total);
			int r_inside = r - detaR;
			int r_outside = r + detaR;
			int heightup = height - r_outside;
			int widthup = width - r_outside;
			for (int theta = 0; theta < 360; theta++) {
				int temp0 = R_sin[r_outside][theta];
				int temp1 = R_sin[r_inside][theta];
				int temp2 = R_cos[r_outside][theta];
				int temp3 = R_cos[r_inside][theta];
				for (int row = r_outside; row < heightup; row++) {
					int i_outside = row + temp0;
					int i_inside = row + temp1;
					int indexrow = index[row] + r_outside;
					int indexioutside = index[i_outside] + r_outside + temp2;
					int indexiinside = index[i_inside] + r_outside + temp3;
					int *pblue = tempblue + indexrow;
					uchar *dataout = data + indexioutside;
					uchar *datain = data + indexiinside;
					int colmid = (widthup - r_outside) / 8;
					for (int i = 0; i < colmid; i++, pblue += 8, dataout += 8, datain += 8) {
						*(pblue) += *(dataout)-*(datain);
						*(pblue + 1) += *(dataout + 1) - *(datain + 1);
						*(pblue + 2) += *(dataout + 2) - *(datain + 2);
						*(pblue + 3) += *(dataout + 3) - *(datain + 3);
						*(pblue + 4) += *(dataout + 4) - *(datain + 4);
						*(pblue + 5) += *(dataout + 5) - *(datain + 5);
						*(pblue + 6) += *(dataout + 6) - *(datain + 6);
						*(pblue + 7) += *(dataout + 7) - *(datain + 7);
					}
					colmid = widthup - (widthup - r_outside) % 8;
					for (int col = colmid; col < widthup; col++) {
						*(pblue) += *(dataout)-*(datain);
						pblue += 1;
						dataout += 1;
						datain += 1;
					}
				}
			}
			for (int i = r_outside; i < height - r_outside; i++) {
				int tempindex_i = index[i];
				for (int j = r_outside; j < width - r_outside; j++) {
					int temp = tempblue[tempindex_i + j];
					temp = temp > 0 ? temp : -temp;
					if (temp > 360 * max_circle_diff) {
						xtemp[num] = i;
						ytemp[num] = j;
						radiustemp[num] = r;
						diffOfcirlce[num] = temp *0.28;
						num += 1;
						if (num == Lenth) {
							cout << "max_circle_diff is too low" << endl;
							return MY_FAIL;
						}
					}
				}
			}
		}
	}


	//排除同圆
	int numafterdelete = 0;
	int count = 0;
	xt[count] = xtemp[numafterdelete];
	yt[count] = ytemp[numafterdelete];
	rt[count] = radiustemp[numafterdelete];
	diff[count] = diffOfcirlce[numafterdelete];
	count += 1;
	numafterdelete += 1;
	while (numafterdelete<num) {
		int flag = 1;
		for (int i = 0; i < count; i++) {
			int diffx = xt[i] - xtemp[numafterdelete];
			int diffy = yt[i] - ytemp[numafterdelete];
			if (diffx*diffx + diffy*diffy > min_center_dist*min_center_dist)continue;
			if (rt[i] - radiustemp[numafterdelete] > min_radius_dist || rt[i] - radiustemp[numafterdelete]<-min_radius_dist)continue;
			if (diff[i] < diffOfcirlce[numafterdelete]) {
				xt[i] = xtemp[numafterdelete];
				yt[i] = ytemp[numafterdelete];
				rt[i] = radiustemp[numafterdelete];
				diff[i] = diffOfcirlce[numafterdelete];
				flag = 0;
				continue;
			}
		}
		if (flag) {
			xt[count] = xtemp[numafterdelete];
			yt[count] = ytemp[numafterdelete];
			rt[count] = radiustemp[numafterdelete];
			diff[count] = diffOfcirlce[numafterdelete];
			count += 1;
		}
		numafterdelete += 1;
	}
	map<int, int>  mp;
	for (int i = 0; i < count; i++) {
		int temp = xt[i] * 1920000 + yt[i] * 1600 + rt[i];
		mp[temp] = diff[i];
	}
	map<int, int> mptemp;
	for (auto beg = mp.begin(); beg != mp.end(); beg++) {
		mptemp[beg->second] = beg->first;
	}

	if (mptemp.size() <= max_circle) {
		*circle_cnt = mptemp.size() - 1;
		int i = 0;
		for (auto beg = --mptemp.cend(); beg != mptemp.cbegin(); i++, beg--) {
			int temp = beg->second;
			xt[i] = temp / 1920000;
			temp -= x[i] * 1920000;
			y[i] = temp / 1600;
			radius[i] = temp - y[i] * 1600;
			//cout << x[i] << " " << y[i] << " " << radius[i] << " " << (beg->first) / 100.0 << endl;
		}
		return MY_OK;
	}
	else {
		*circle_cnt = max_circle;
		int i = 0;
		for (auto beg = --mptemp.cend(); i<max_circle; i++, beg--) {
			int temp = beg->second;
			x[i] = temp / 1920000;
			temp -= x[i] * 1920000;
			y[i] = temp / 1600;
			radius[i] = temp - y[i] * 1600;
			//cout << x[i] << " " << y[i] << " " << radius[i] << " " << (beg->first) / 100.0 << endl;
		}
		return MY_OK;
	}
}
