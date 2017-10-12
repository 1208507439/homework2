#include "opencv2/opencv.hpp"
#define MY_OK 1
#define MY_FAIL -1

#define SCALE_FACTOR 0.6
#define MAX_COUNTER 350
#define INCREMENT 3
//#define SHOW
//#define SHOW_S

using namespace cv;
const float COS[360] = { 1.0F,0.999848F,0.999391F,0.99863F,0.997564F,0.996195F,0.994522F,
0.992546F,0.990268F,0.987688F,0.984808F,0.981627F,0.978148F,0.97437F,0.970296F,
0.965926F,0.961262F,0.956305F,0.951057F,0.945519F,0.939693F,0.93358F,0.927184F,
0.920505F,0.913545F,0.906308F,0.898794F,0.891007F,0.882948F,0.87462F,0.866025F,
0.857167F,0.848048F,0.838671F,0.829038F,0.819152F,0.809017F,0.798636F,0.788011F,
0.777146F,0.766044F,0.75471F,0.743145F,0.731354F,0.71934F,0.707107F,0.694658F,
0.681998F,0.669131F,0.656059F,0.642788F,0.62932F,0.615661F,0.601815F,0.587785F,
0.573576F,0.559193F,0.544639F,0.529919F,0.515038F,0.5F,0.48481F,0.469472F,0.45399F,
0.438371F,0.422618F,0.406737F,0.390731F,0.374607F,0.358368F,0.34202F,0.325568F,
0.309017F,0.292372F,0.275637F,0.258819F,0.241922F,0.224951F,0.207912F,0.190809F,
0.173648F,0.156434F,0.139173F,0.121869F,0.104528F,0.0871558F,0.0697565F,0.0523359F,
0.0348994F,0.0174524F,-4.63605e-008F,-0.0174525F,-0.0348995F,-0.052336F,-0.0697565F,
-0.0871559F,-0.104528F,-0.121869F,-0.139173F,-0.156434F,-0.173648F,-0.190809F,
-0.207912F,-0.224951F,-0.241922F,-0.258819F,-0.275637F,-0.292372F,-0.309017F,
-0.325568F,-0.34202F,-0.358368F,-0.374607F,-0.390731F,-0.406737F,-0.422618F,
-0.438371F,-0.453991F,-0.469472F,-0.48481F,-0.5F,-0.515038F,-0.529919F,-0.544639F,
-0.559193F,-0.573577F,-0.587785F,-0.601815F,-0.615662F,-0.62932F,-0.642788F,
-0.656059F,-0.669131F,-0.681998F,-0.694658F,-0.707107F,-0.71934F,-0.731354F,
-0.743145F,-0.75471F,-0.766045F,-0.777146F,-0.788011F,-0.798636F,-0.809017F,
-0.819152F,-0.829038F,-0.838671F,-0.848048F,-0.857167F,-0.866025F,-0.87462F,
-0.882948F,-0.891007F,-0.898794F,-0.906308F,-0.913545F,-0.920505F,-0.927184F,
-0.93358F,-0.939693F,-0.945519F,-0.951057F,-0.956305F,-0.961262F,-0.965926F,
-0.970296F,-0.97437F,-0.978148F,-0.981627F,-0.984808F,-0.987688F,-0.990268F,
-0.992546F,-0.994522F,-0.996195F,-0.997564F,-0.99863F,-0.999391F,-0.999848F,
-1.0F,-0.999848F,-0.999391F,-0.99863F,-0.997564F,-0.996195F,-0.994522F,
-0.992546F,-0.990268F,-0.987688F,-0.984808F,-0.981627F,-0.978148F,-0.97437F,
-0.970296F,-0.965926F,-0.961262F,-0.956305F,-0.951057F,-0.945519F,-0.939693F,
-0.93358F,-0.927184F,-0.920505F,-0.913545F,-0.906308F,-0.898794F,-0.891006F,
-0.882948F,-0.87462F,-0.866025F,-0.857167F,-0.848048F,-0.838671F,-0.829038F,
-0.819152F,-0.809017F,-0.798635F,-0.788011F,-0.777146F,-0.766044F,-0.75471F,
-0.743145F,-0.731354F,-0.71934F,-0.707107F,-0.694658F,-0.681998F,-0.669131F,
-0.656059F,-0.642787F,-0.62932F,-0.615662F,-0.601815F,-0.587785F,-0.573576F,
-0.559193F,-0.544639F,-0.529919F,-0.515038F,-0.5F,-0.48481F,-0.469471F,-0.45399F,
-0.438371F,-0.422618F,-0.406737F,-0.390731F,-0.374607F,-0.358368F,-0.34202F,
-0.325568F,-0.309017F,-0.292372F,-0.275637F,-0.258819F,-0.241922F,-0.224951F,
-0.207911F,-0.190809F,-0.173648F,-0.156434F,-0.139173F,-0.121869F,-0.104528F,
-0.0871555F,-0.0697562F,-0.052336F,-0.0348995F,-0.0174523F,1.39081e-007F,
0.0174526F,0.0348997F,0.0523362F,0.0697565F,0.0871558F,0.104529F,0.121869F,
0.139173F,0.156435F,0.173648F,0.190809F,0.207912F,0.224951F,0.241922F,0.258819F,
0.275638F,0.292372F,0.309017F,0.325568F,0.34202F,0.358368F,0.374607F,0.390731F,
0.406737F,0.422618F,0.438371F,0.453991F,0.469472F,0.48481F,0.5F,0.515038F,0.529919F,
0.544639F,0.559193F,0.573577F,0.587785F,0.601815F,0.615661F,0.62932F,0.642788F,
0.656059F,0.669131F,0.681999F,0.694659F,0.707107F,0.71934F,0.731354F,0.743145F,
0.75471F,0.766045F,0.777146F,0.788011F,0.798636F,0.809017F,0.819152F,0.829037F,
0.838671F,0.848048F,0.857167F,0.866025F,0.87462F,0.882948F,0.891007F,0.898794F,
0.906308F,0.913546F,0.920505F,0.927184F,0.933581F,0.939693F,0.945519F,0.951057F,
0.956305F,0.961262F,0.965926F,0.970296F,0.97437F,0.978148F,0.981627F,0.984808F,
0.987688F,0.990268F,0.992546F,0.994522F,0.996195F,0.997564F,0.99863F,0.999391F,0.999848F };
const float SIN[360] = { 0.0F,0.0174524F,0.0348995F,0.052336F,0.0697565F,0.0871557F,0.104528F,0.121869F,
0.139173F,0.156434F,0.173648F,0.190809F,0.207912F,0.224951F,0.241922F,0.258819F,
0.275637F,0.292372F,0.309017F,0.325568F,0.34202F,0.358368F,0.374607F,0.390731F,
0.406737F,0.422618F,0.438371F,0.453991F,0.469472F,0.48481F,0.5F,0.515038F,0.529919F,
0.544639F,0.559193F,0.573576F,0.587785F,0.601815F,0.615661F,0.62932F,0.642788F,
0.656059F,0.669131F,0.681998F,0.694658F,0.707107F,0.71934F,0.731354F,0.743145F,
0.75471F,0.766044F,0.777146F,0.788011F,0.798636F,0.809017F,0.819152F,0.829038F,
0.838671F,0.848048F,0.857167F,0.866025F,0.87462F,0.882948F,0.891007F,0.898794F,
0.906308F,0.913545F,0.920505F,0.927184F,0.93358F,0.939693F,0.945519F,0.951057F,
0.956305F,0.961262F,0.965926F,0.970296F,0.97437F,0.978148F,0.981627F,0.984808F,
0.987688F,0.990268F,0.992546F,0.994522F,0.996195F,0.997564F,0.99863F,0.999391F,0.999848F,
1.0F,0.999848F,0.999391F,0.99863F,0.997564F,0.996195F,0.994522F,0.992546F,0.990268F,
0.987688F,0.984808F,0.981627F,0.978148F,0.97437F,0.970296F,0.965926F,0.961262F,
0.956305F,0.951056F,0.945519F,0.939693F,0.93358F,0.927184F,0.920505F,0.913545F,
0.906308F,0.898794F,0.891007F,0.882948F,0.87462F,0.866025F,0.857167F,0.848048F,
0.838671F,0.829038F,0.819152F,0.809017F,0.798636F,0.788011F,0.777146F,0.766044F,
0.75471F,0.743145F,0.731354F,0.71934F,0.707107F,0.694658F,0.681998F,0.669131F,
0.656059F,0.642787F,0.62932F,0.615661F,0.601815F,0.587785F,0.573576F,0.559193F,
0.544639F,0.529919F,0.515038F,0.5F,0.48481F,0.469472F,0.45399F,0.438371F,0.422618F,
0.406737F,0.390731F,0.374607F,0.358368F,0.34202F,0.325568F,0.309017F,0.292372F,
0.275637F,0.258819F,0.241922F,0.224951F,0.207912F,0.190809F,0.173648F,0.156434F,
0.139173F,0.121869F,0.104528F,0.0871556F,0.0697562F,0.052336F,0.0348995F,0.0174524F,
-9.2721e-008F,-0.0174525F,-0.0348997F,-0.0523362F,-0.0697564F,-0.0871557F,-0.104529F,
-0.121869F,-0.139173F,-0.156435F,-0.173648F,-0.190809F,-0.207912F,-0.224951F,-0.241922F,
-0.258819F,-0.275638F,-0.292372F,-0.309017F,-0.325568F,-0.34202F,-0.358368F,-0.374607F,
-0.390731F,-0.406737F,-0.422618F,-0.438371F,-0.453991F,-0.469472F,-0.48481F,-0.5F,
-0.515038F,-0.529919F,-0.544639F,-0.559193F,-0.573577F,-0.587785F,-0.601815F,
-0.615661F,-0.62932F,-0.642788F,-0.656059F,-0.669131F,-0.681998F,-0.694659F,
-0.707107F,-0.71934F,-0.731354F,-0.743145F,-0.75471F,-0.766045F,-0.777146F,-0.788011F,
-0.798636F,-0.809017F,-0.819152F,-0.829038F,-0.838671F,-0.848048F,-0.857167F,-0.866025F,
-0.87462F,-0.882948F,-0.891007F,-0.898794F,-0.906308F,-0.913545F,-0.920505F,-0.927184F,
-0.93358F,-0.939693F,-0.945519F,-0.951057F,-0.956305F,-0.961262F,-0.965926F,-0.970296F,
-0.97437F,-0.978148F,-0.981627F,-0.984808F,-0.987688F,-0.990268F,-0.992546F,-0.994522F,
-0.996195F,-0.997564F,-0.99863F,-0.999391F,-0.999848F,-1.0F,-0.999848F,-0.999391F,-0.99863F,
-0.997564F,-0.996195F,-0.994522F,-0.992546F,-0.990268F,-0.987688F,-0.984808F,-0.981627F,
-0.978148F,-0.97437F,-0.970296F,-0.965926F,-0.961262F,-0.956305F,-0.951057F,-0.945519F,
-0.939693F,-0.93358F,-0.927184F,-0.920505F,-0.913545F,-0.906308F,-0.898794F,-0.891006F,
-0.882948F,-0.87462F,-0.866025F,-0.857167F,-0.848048F,-0.838671F,-0.829038F,-0.819152F,
-0.809017F,-0.798635F,-0.788011F,-0.777146F,-0.766044F,-0.754709F,-0.743145F,-0.731354F,
-0.71934F,-0.707107F,-0.694658F,-0.681998F,-0.669131F,-0.656059F,-0.642787F,-0.62932F,
-0.615661F,-0.601815F,-0.587785F,-0.573576F,-0.559193F,-0.544639F,-0.529919F,-0.515038F,
-0.5F,-0.48481F,-0.469471F,-0.45399F,-0.438371F,-0.422618F,-0.406736F,-0.390731F,-0.374606F,
-0.358367F,-0.34202F,-0.325568F,-0.309017F,-0.292372F,-0.275637F,-0.258819F,-0.241922F,
-0.224951F,-0.207911F,-0.190809F,-0.173648F,-0.156434F,-0.139173F,-0.12187F,-0.104529F,
-0.0871558F,-0.0697565F,-0.0523359F,-0.0348994F,-0.0174523F };

//整数求绝对值函数
int ABS(int x)
{
	int i = x >> 31;
	return ((x ^ i) - i);
}

//三通道融合
int Channel_Fusion(
	int* b_x, int* b_y, int* b_r, float* b_diff, int b_len,
	int* g_x, int* g_y, int* g_r, float* g_diff, int g_len,
	int* r_x, int* r_y, int* r_r, float* r_diff, int r_len,
	int* x, int* y, int* r, float* diff, int &len,
	int min_center_dist, int min_radius_dist)
{
	len = 0;
	//逐通道融合
	for (int i = 0; i < b_len; i++)
	{
		int flag = 1;
		for (int j = 0; j < len; j++)
		{
			int center_dist_x = ABS(x[j] - b_x[i]);
			int center_dist_y = ABS(y[j] - b_y[i]);
			int radius_dist = ABS(r[j] - b_r[i]);
			if (center_dist_x <= min_center_dist
				&& center_dist_y <= min_center_dist
				&& radius_dist <= min_radius_dist)
			{
				flag = 0;
				x[j] = b_x[i];
				y[j] = b_y[i];
				r[j] = b_r[i];
				diff[j] = b_diff[i];
				break;
			}
		}
		x[len] = b_x[i];
		y[len] = b_y[i];
		r[len] = b_r[i];
		diff[len] = b_diff[i];
		len += flag;
	}

	for (int i = 0; i < g_len; i++)
	{
		int flag = 1;
		for (int j = 0; j < len; j++)
		{
			int center_dist_x = ABS(x[j] - g_x[i]);
			int center_dist_y = ABS(y[j] - g_y[i]);
			int radius_dist = ABS(r[j] - g_r[i]);
			if (center_dist_x <= min_center_dist
				&& center_dist_y <= min_center_dist
				&& radius_dist <= min_radius_dist)
			{
				flag = 0;
				x[j] = g_x[i];
				y[j] = g_y[i];
				r[j] = g_r[i];
				diff[j] = g_diff[i];
				break;
			}
		}
		x[len] = g_x[i];
		y[len] = g_y[i];
		r[len] = g_r[i];
		diff[len] = g_diff[i];
		len += flag;
	}

	for (int i = 0; i < r_len; i++)
	{
		int flag = 1;
		for (int j = 0; j < len; j++)
		{
			int center_dist_x = ABS(x[j] - r_x[i]);
			int center_dist_y = ABS(y[j] - r_y[i]);
			int radius_dist = ABS(r[j] - r_r[i]);
			if (center_dist_x <= min_center_dist
				&& center_dist_y <= min_center_dist
				&& radius_dist <= min_radius_dist)
			{
				flag = 0;
				x[j] = r_x[i];
				y[j] = r_y[i];
				r[j] = r_r[i];
				diff[j] = r_diff[i];
				break;
			}
		}
		x[len] = r_x[i];
		y[len] = r_y[i];
		r[len] = r_r[i];
		diff[len] = r_diff[i];
		len += flag;
	}


	return MY_OK;
}

//快速排序，并取前max_circle个圆
int Partition(
	int* x, int* y, int* r, float* diff,
    int low, int high)
{
	int i, k = low;
	float pivot = diff[low];
	int pivot_x = x[low];
	int pivot_y = y[low];
	int pivot_r = r[low];

	for(i = low + 1; i <= high; i++)
	{
		if (diff[i] > pivot)
		{
			k++;
			if (k != i)
			{
				int t = x[i];
				x[i] = x[k];
				x[k] = t;

				t = y[i];
				y[i] = y[k];
				y[k] = t;

				t = r[i];
				r[i] = r[k];
				r[k] = t;

				float ft = diff[i];
				diff[i] = diff[k];
				diff[k] = ft;
			}
		}
	}
	x[low] = x[k];
	x[k] = pivot_x;

	r[low] = r[k];
	r[k] = pivot_r;

	y[low] = y[k];
	y[k] = pivot_y;

	diff[low] = diff[k];
	diff[k] = pivot;

	return k;
}
void QuickSort(
	int* x, int* y, int* r, float* diff,
    int left, int right)
{
	if (left < right)
	{
		int pivotpos = Partition(x, y, r, diff, left, right);
		
		QuickSort(x, y, r, diff, left, pivotpos - 1);
		QuickSort(x, y, r, diff, pivotpos + 1, right);
	}
	
}

//灰度图找圆
int ustc_Find_Circles_By_Difference_In_GrayImg(
	Mat grayImg,             //用来搜索圆形目标的单通道灰度图像
	int min_radius,          //需要搜索的圆的最小半径
	int max_radius,          //需要搜索的圆的最大半径
	int min_center_dist,     //找到的圆心之间的最小距离
	int min_radius_dist,     //同心圆半径之间的最小差距
	int max_circle_diff,     //阈值，圆周差分值低于此阈值，不是圆
	int* x,                  //数组，存储所有的圆的中心点x坐标
	int* y,                  //数组，存储所有的圆的中心点y坐标
	int* radius,             //数组，存储所有的圆的半径值
	float* circle_diff,      //数组，存储所有圆的差分值
	int* len)                //圆的数目
{
	/*判断图像读入是否正常*/
	if (NULL == grayImg.data)
	{
		std::cout << "image is NULL." << std::endl;
		return MY_FAIL;
	}
	//图像尺寸
	int width = grayImg.cols;
	int height = grayImg.rows;


	/*制表，计算圆上点的偏移坐标*/
	//确定半径范围，跨度
	int max_r = max_radius + 5;
	int min_r = min_radius - 5;
	int r_len = max_r - min_r + 1;
	//申请二维数组：r * angle
	int** dx = new int*[r_len];
	int** dy = new int*[r_len];
	for (int i = 0; i < r_len; i++)
	{
		dx[i] = new int[360];
		dy[i] = new int[360];
	}

	//写入数组
	for (int r = min_r; r <= max_r; r++) 
	{
		int indx_r = r - min_r;
		for (int angle = 0; angle < 360; angle++)
		{
			dx[indx_r][angle] = (int)(r * COS[angle]);
			dy[indx_r][angle] = (int)(r * SIN[angle]);
		}
	}

	//遍历图像每个像素点，找圆
	*len = 0;//圆的个数清零
	float max_diff = max_circle_diff * SCALE_FACTOR;
	for (int i_row = 0; i_row < height; i_row++)
	{
		for (int j_col = 0; j_col < width; j_col++)
		{
			for (int r = min_radius; r <= max_radius; r++)
			{
				//半径转换成数组下标
				int indx_r = r - min_r;
				int out_indx_r = indx_r + 5;
				int in_indx_r = indx_r - 5;

				//定义像素值处理参数
				int sum_out = 0;
				int sum_in = 0;
				int counter = 0;
				for (int angle = 0; angle < 360; angle++)
				{
					//外圆上点的坐标
					int out_indx_x = j_col + dx[out_indx_r][angle];
					int out_indx_y = i_row + dy[out_indx_r][angle];
					//内圆上点的坐标
					int in_indx_x = j_col + dx[in_indx_r][angle];
					int in_indx_y = i_row + dy[in_indx_r][angle];

					//越界检测
					if (out_indx_x >= 0 && out_indx_x < width && out_indx_y >= 0 && out_indx_y < height)
					{
						//取像素值
						int out_pix = grayImg.data[out_indx_y * width + out_indx_x];
						int in_pix = grayImg.data[in_indx_y * width + in_indx_x];
						int diff = ABS(out_pix - in_pix);

						//逐点判断
						if (diff > max_diff)
				    	{
							sum_in += in_pix;
							sum_out += out_pix;
							counter++;
						}
					}
				}

				//整圆检测
				if (counter > MAX_COUNTER)
				{  
					int id = *len;     //当前长度
					float avg_in = (float)sum_in / counter;
					float avg_out = (float)sum_out / counter; 
					circle_diff[id] = abs(avg_in - avg_out);
					
					//阈值判断
					if (circle_diff[id] > max_circle_diff)
					{
						int flag = 1;  //同圆标识
						for (int i = 0; i < id; i++)
						{
							int center_dist_x = ABS(x[i] - j_col);
							int center_dist_y = ABS(y[i] - i_row);
							int radius_dist = ABS(r - radius[i]);
							//同圆检测
							if (center_dist_x <= min_center_dist + INCREMENT 
								&& center_dist_y <= min_center_dist + INCREMENT
								&& radius_dist <= min_radius_dist + INCREMENT)
							{
								flag = 0;
								if (circle_diff[id] > circle_diff[i])
								{
									//替换掉圆心定位不准确的圆
									x[i] = j_col;
									y[i] = i_row;
									radius[i] = r;
									circle_diff[i] = circle_diff[id];
									break;
								}
							}
						}
						//检测到新圆
						x[id] = j_col;
						y[id] = i_row;
						radius[id] = r;
						(*len) += flag;
						if (*len >= 10000)
						{
							std::cout << "本通道中圆的数目超过函数功能极限，提前结束对此通道的搜索" << std::endl;
							return MY_OK;
						}
					}
				}
			}
		}
	}


#ifdef SHOW
	//图像显示
	Mat CircleImg(height, width, CV_8UC1);
	CircleImg = grayImg.clone();
	//CircleImg.setTo(255);

	for (int i = 0; i < *len; i++)
	{
		for (int angle = 0; angle < 360; angle++)
		{
			int indx_x = x[i] + dx[radius[i] - min_r][angle];
			int indx_y = y[i] + dy[radius[i] - min_r][angle];

			//越界检查
			if (indx_x >= 0 && indx_x < width && indx_y >= 0 && indx_y < height)
			{
				CircleImg.data[indx_y * width + indx_x] = 128;
			}
		}
	}

	imshow("圆提取图", CircleImg);
	waitKey();
#endif // SHOW

	return MY_OK;
}

//最终找圆函数
int ustc_Find_Circles_By_Difference(
	Mat colorImg,            //用来搜索圆形目标的彩色图像
	int min_radius,          //需要搜索的圆的最小半径
	int max_radius,          //需要搜索的圆的最大半径
	int min_center_dist,     //找到的圆心之间的最小距离
	int min_radius_dist,     //同心圆半径之间的最小差距
	int max_circle_diff,     //阈值，圆周差分值低于此阈值，不是圆
	int* x,                  //数组，存储所有的圆的中心点x坐标
	int* y,                  //数组，存储所有的圆的中心点y坐标
	int* radius,             //数组，存储所有的圆的半径值
	int* circle_cnt,         //图像中找到的圆的数目
	int max_circle)        //外部传入参数，圆的数目上限。如果图像中圆的数目超过此参数，根据差分值由大到小进行排序
{
	if (NULL == colorImg.data)
	{
		std::cout << "image is NULL." << std::endl;
		return MY_FAIL;
	}

	if (min_center_dist < 5 || min_radius_dist < 5)
	{
		std::cout << "最小圆心间距和最小半径差距不得小于5" << std::endl;
		return MY_FAIL;
	}

	if (max_circle_diff < 10)
	{
		std::cout << "差分阈值设置过小" << std::endl;
		return MY_FAIL;
	}

	if (min_radius < 5 || max_radius < 5 || max_radius < min_radius)
	{
		std::cout << "关于半径的阈值参数设置不恰当" << std::endl;
		return MY_FAIL;
	}

	if (NULL == x || NULL == y || NULL == radius || NULL == circle_cnt)
	{
		std::cout << "x or y or r or circle_len is NULL" << std::endl;
		return MY_FAIL;
	}

	if (max_circle < 0)
	{
		std::cout << "圆的数目上限设置不当" << std::endl;
		return MY_FAIL;
	}

	//图像大小
	int width = colorImg.cols;
	int height = colorImg.rows;

	Mat BlueImg(height, width, CV_8UC1);
	Mat GreenImg(height, width, CV_8UC1);
	Mat RedImg(height, width, CV_8UC1);
	Mat channel[3];

	//图像分离
	split(colorImg, channel);
	BlueImg = channel[0];
	GreenImg = channel[1];
	RedImg = channel[2];

	//分通道找圆
	//Blue channel
	int* B_x = new int[10000];       //数组，存储所有的圆的中心点x坐标
	int* B_y = new int[10000];       //数组，存储所有的圆的中心点y坐标
	int* B_radius = new int[10000];  //数组，存储所有的圆的半径值
	float* B_diff = new float[10000];//数组，存储所有的圆的差分值
	int B_len = 0;         //圆的数目

	int BLUE = ustc_Find_Circles_By_Difference_In_GrayImg(
		       BlueImg, min_radius, max_radius,
		       min_center_dist, min_radius_dist, max_circle_diff,
		       B_x, B_y, B_radius, B_diff, &B_len);
	if (MY_FAIL == BLUE)
	{
		std::cout << "blue channel error" << std::endl;
	}

	//Green channel
	int* G_x = new int[10000];       //数组，存储所有的圆的中心点x坐标
	int* G_y = new int[10000];       //数组，存储所有的圆的中心点y坐标
	int* G_radius = new int[10000];  //数组，存储所有的圆的半径值
	float* G_diff = new float[10000];//数组，存储所有的圆的差分值
	int G_len = 0;         //圆的数目

	int GREEN = ustc_Find_Circles_By_Difference_In_GrayImg(
		        GreenImg, min_radius, max_radius,
		        min_center_dist, min_radius_dist, max_circle_diff,
		        G_x, G_y, G_radius, G_diff, &G_len);
	if (MY_FAIL == GREEN)
	{
		std::cout << "green channel error" << std::endl;
	}

	//Blue channel
	int* R_x = new int[10000];       //数组，存储所有的圆的中心点x坐标
	int* R_y = new int[10000];       //数组，存储所有的圆的中心点y坐标
	int* R_radius = new int[10000];  //数组，存储所有的圆的半径值
	float* R_diff = new float[10000];//数组，存储所有的圆的差分值
	int R_len = 0;         //圆的数目

	int RED = ustc_Find_Circles_By_Difference_In_GrayImg(
		RedImg, min_radius, max_radius,
		min_center_dist, min_radius_dist, max_circle_diff,
		R_x, R_y, R_radius, R_diff, &R_len);
	if (MY_FAIL == RED)
	{
		std::cout << "red channel error" << std::endl;
	}

	//通道融合
	float* circle_diff = new float[10000];
    Channel_Fusion(
    B_x, B_y, B_radius, B_diff, B_len,
    G_x, G_y, G_radius, G_diff, G_len,
	R_x, R_y, R_radius, R_diff, R_len,
	x, y, radius, circle_diff, *circle_cnt,
	min_center_dist, min_radius_dist);

	//圆个数抑制
	if (*circle_cnt > max_circle)
	{
		QuickSort(x, y, radius, circle_diff,
			      0, *circle_cnt - 1);
		*circle_cnt = max_circle;
	}

#ifdef SHOW_S
	//图像显示
	Mat CircleImg(height, width, CV_8UC3);
	CircleImg = colorImg.clone();
	//CircleImg.setTo(255);

	for (int i = 0; i < *circle_cnt; i++)
	{
		for (int angle = 0; angle < 360; angle++)
		{
			int indx_x = x[i] + radius[i] * COS[angle];
			int indx_y = y[i] + radius[i] * SIN[angle];

			//越界检查
			if (indx_x >= 0 && indx_x < width && indx_y >= 0 && indx_y < height)
			{
				CircleImg.data[(indx_y * width + indx_x) * 3 + 0] = 0;
				CircleImg.data[(indx_y * width + indx_x) * 3 + 1] = 0;
				CircleImg.data[(indx_y * width + indx_x) * 3 + 2] = 255;
			}
		}
	}

	imshow("圆提取图", CircleImg);
	waitKey();
#endif // SHOW_S

	return MY_OK;
}
