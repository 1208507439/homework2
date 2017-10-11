//
//  CircleDiff.cpp
//  FindCircle_CircleDiff
//
//  Created by Lixian on 2017/9/26.
//  Copyright © 2017年 Lixian. All rights reserved.
//

/* Includes ------------------------------------------------------------------*/
#include <cv.hpp>
//#include "CircleDiff.hpp"
/* Namespace -----------------------------------------------------------------*/
using namespace cv;
/* Private define ------------------------------------------------------------*/
#define MY_OK 0
#define MY_FAIL -1
/* Private constant ----------------------------------------------------------*/
const float ANGLE_TO_PI = 0.0174532;
/* Private functions ---------------------------------------------------------*/

int ustc_Find_Circles_By_Difference(Mat colorImg, int min_radius, int max_radius,
                                    int min_center_dist, int min_radius_dist, int max_circle_diff,
                                    int *x, int *y, int *radius, int *circle_cnt,
                                    int max_circle) {
    //Protect
    if (nullptr == colorImg.data) {
        return MY_FAIL;
    }
    
    int rows = colorImg.rows;
    int cols = colorImg.cols;
    
    int rcmin = rows;
    if (rcmin > cols) rcmin = cols;
    
    if (rcmin < min_radius + 5) return MY_FAIL;
    if (min_radius - 5 < 0) min_radius = 5;
    rcmin /= 2;
    if (rcmin < max_radius + 5) max_radius = rcmin - 5;
    if (min_radius > max_radius) return MY_FAIL;
    
    //Start
    Mat srcImg;
    colorImg.convertTo(srcImg, CV_16UC3);
    
    Mat SumImg1[11], SumImg2[11], SumImg[11];
    for (int i = 0; i < 11; i++) {
        SumImg1[i] = Mat::zeros(rows, cols, CV_16UC3);
        SumImg2[i] = Mat::zeros(rows, cols, CV_16UC3);
    }
    
    int diffimg_lens = max_radius - min_radius + 10;
    Mat *diffimg = new Mat[diffimg_lens];
    for (int i = 0; i < 5; i++) diffimg[i] = Mat::zeros(rows, cols, CV_8UC1);
    for (int i = 0; i < 5; i++) diffimg[diffimg_lens - i - 1] = Mat::zeros(rows, cols, CV_8UC1);
    
    Mat max_circle_diff_img(rows, cols, CV_8UC3, Scalar(max_circle_diff, max_circle_diff, max_circle_diff));
    
    Mat srcImgROI, SumImgROI;
    
    
    //Initialization
    int subr[4];
    int top_point = 0, bottom_point;
    int radius_index, angle_index;
    
    for (radius_index = min_radius - 5; radius_index < min_radius + 5; radius_index++, top_point++) {
        angle_index = 0;
        
        for (; angle_index < 90; angle_index++) {
            subr[0] = (int) (radius_index * cos(angle_index * ANGLE_TO_PI)) + radius_index;
            subr[1] = (int) (radius_index * sin(angle_index * ANGLE_TO_PI)) + radius_index;
            subr[2] = cols - 2 * radius_index + subr[0];
            subr[3] = rows - 2 * radius_index + subr[1];
            srcImgROI = srcImg(Range(subr[1], subr[3]), Range(subr[0], subr[2]));
            SumImgROI = SumImg1[top_point](Range(radius_index, rows - radius_index),
                                           Range(radius_index, cols - radius_index));
            SumImgROI += srcImgROI;
        }
        for (; angle_index < 180; angle_index++) {
            subr[1] = (int) (radius_index * sin(angle_index * ANGLE_TO_PI)) + radius_index;
            subr[2] = (int) (cols + radius_index * cos(angle_index * ANGLE_TO_PI)) - radius_index;
            subr[0] = subr[2] - cols + 2 * radius_index;
            subr[3] = rows - 2 * radius_index + subr[1];
            srcImgROI = srcImg(Range(subr[1], subr[3]), Range(subr[0], subr[2]));
            SumImgROI = SumImg1[top_point](Range(radius_index, rows - radius_index),
                                           Range(radius_index, cols - radius_index));
            SumImgROI += srcImgROI;
            
        }
        
        for (; angle_index < 270; angle_index++) {
            subr[2] = (int) (cols + radius_index * cos(angle_index * ANGLE_TO_PI)) - radius_index;
            subr[3] = (int) (rows + radius_index * sin(angle_index * ANGLE_TO_PI)) - radius_index;
            subr[0] = subr[2] - cols + 2 * radius_index;
            subr[1] = subr[3] - rows + 2 * radius_index;
            srcImgROI = srcImg(Range(subr[1], subr[3]), Range(subr[0], subr[2]));
            SumImgROI = SumImg2[top_point](Range(radius_index, rows - radius_index),
                                           Range(radius_index, cols - radius_index));
            SumImgROI += srcImgROI;
        }
        for (; angle_index < 360; angle_index++) {
            subr[0] = (int) (radius_index * cos(angle_index * ANGLE_TO_PI)) + radius_index;
            subr[3] = (int) (rows + radius_index * sin(angle_index * ANGLE_TO_PI)) - radius_index;
            subr[1] = subr[3] - rows + 2 * radius_index;
            subr[2] = cols - 2 * radius_index + subr[0];
            srcImgROI = srcImg(Range(subr[1], subr[3]), Range(subr[0], subr[2]));
            SumImgROI = SumImg2[top_point](Range(radius_index, rows - radius_index),
                                           Range(radius_index, cols - radius_index));
            SumImgROI += srcImgROI;
        }
        
        // (16U+16U)/2 will not overflow? Insteresting!
        SumImg[top_point] = (SumImg1[top_point] + SumImg2[top_point]) / 360;
    }
    
    //Continue
    for (radius_index = min_radius + 5; radius_index <= max_radius + 5; radius_index++, top_point++, top_point %= 11) {
        angle_index = 0;
        
        for (; angle_index < 90; angle_index++) {
            subr[0] = (int) (radius_index * cos(angle_index * ANGLE_TO_PI)) + radius_index;
            subr[1] = (int) (radius_index * sin(angle_index * ANGLE_TO_PI)) + radius_index;
            subr[2] = cols - 2 * radius_index + subr[0];
            subr[3] = rows - 2 * radius_index + subr[1];
            srcImgROI = srcImg(Range(subr[1], subr[3]), Range(subr[0], subr[2]));
            SumImgROI = SumImg1[top_point](Range(radius_index, rows - radius_index),
                                           Range(radius_index, cols - radius_index));
            SumImgROI += srcImgROI;
        }
        for (; angle_index < 180; angle_index++) {
            subr[0] = (int) (radius_index * cos(angle_index * ANGLE_TO_PI)) + radius_index;
            subr[3] = (int) (rows + radius_index * sin(angle_index * ANGLE_TO_PI)) - radius_index;
            subr[1] = subr[3] - rows + 2 * radius_index;
            subr[2] = cols - 2 * radius_index + subr[0];
            srcImgROI = srcImg(Range(subr[1], subr[3]), Range(subr[0], subr[2]));
            SumImgROI = SumImg2[top_point](Range(radius_index, rows - radius_index),
                                           Range(radius_index, cols - radius_index));
            SumImgROI += srcImgROI;
            
        }
        
        for (; angle_index < 270; angle_index++) {
            subr[2] = (int) (cols + radius_index * cos(angle_index * ANGLE_TO_PI)) - radius_index;
            subr[3] = (int) (rows + radius_index * sin(angle_index * ANGLE_TO_PI)) - radius_index;
            subr[0] = subr[2] - cols + 2 * radius_index;
            subr[1] = subr[3] - rows + 2 * radius_index;
            srcImgROI = srcImg(Range(subr[1], subr[3]), Range(subr[0], subr[2]));
            SumImgROI = SumImg2[top_point](Range(radius_index, rows - radius_index),
                                           Range(radius_index, cols - radius_index));
            SumImgROI += srcImgROI;
        }
        for (; angle_index < 360; angle_index++) {
            subr[0] = (int) (radius_index * cos(angle_index * ANGLE_TO_PI)) + radius_index;
            subr[3] = (int) (rows + radius_index * sin(angle_index * ANGLE_TO_PI)) - radius_index;
            subr[1] = subr[3] - rows + 2 * radius_index;
            subr[2] = cols - 2 * radius_index + subr[0];
            srcImgROI = srcImg(Range(subr[1], subr[3]), Range(subr[0], subr[2]));
            SumImgROI = SumImg2[top_point](Range(radius_index, rows - radius_index),
                                           Range(radius_index, cols - radius_index));
            SumImgROI += srcImgROI;
        }
        
        bottom_point = (top_point + 1) % 11;
        
        Mat diffmat = Mat::zeros(rows, cols, CV_16UC3);
        SumImg[top_point] = (SumImg1[top_point] + SumImg2[top_point]) / 360;
        absdiff(SumImg[top_point](Range(radius_index, rows - radius_index), Range(radius_index, cols - radius_index)),
                SumImg[bottom_point](Range(radius_index, rows - radius_index),
                                     Range(radius_index, cols - radius_index)),
                diffmat(Range(radius_index, rows - radius_index), Range(radius_index, cols - radius_index)));
        
        diffmat.convertTo(diffmat, CV_8UC3);
        diffmat -= max_circle_diff_img;     //The value <= max_circle_diff will be set to zero
        
        std::vector <Mat> channels;
        split(diffmat, channels);
        diffimg[radius_index - min_radius] = max(max(channels.at(0), channels.at(1)), channels.at(2));
        
        SumImg1[bottom_point].setTo(0);
        SumImg2[bottom_point].setTo(0);
        
        
    }
    
    //Final(Select the circle)
    int circle_num = 0;
    int rows_index, cols_index;
    
    for (int r = 5; r < diffimg_lens - 5; r++) {
        int rc_index_start = r + min_radius - 5, r_index_end = rows - r - min_radius + 5, c_index_end =
        cols - r - min_radius + 5;
        uchar *ptr_diffimg = diffimg[r].data;
        for (rows_index = rc_index_start; rows_index < r_index_end; rows_index++) {
            for (cols_index = rc_index_start; cols_index < c_index_end; cols_index++) {
                int ptr_index = rows_index * cols + cols_index;
                int ROI_max = ptr_diffimg[ptr_index];
                if (ROI_max == 0) continue;
                
                int getflag = 1;
                
                int inner_r_begin = r - 5, inner_r_end = r + 5;
                int inner_rows_index_begin = rows_index - 5, inner_rows_index_end = rows_index + 5;
                int inner_cols_index_begin = cols_index - 5, inner_cols_index_end = cols_index + 5;
                for (int i = inner_r_begin; i < inner_r_end; i++) {
                    uchar *ptr_inner_diffimg = diffimg[i].data;
                    for (int j = inner_rows_index_begin; j < inner_rows_index_end; j++) {
                        for (int k = inner_cols_index_begin; k < inner_cols_index_end; k++) {
                            int temp_inner_value = ptr_inner_diffimg[j * cols + k];
                            if (ROI_max < temp_inner_value) {
                                //break three for-loop
                                k = inner_cols_index_end;
                                j = inner_rows_index_end;
                                i = inner_r_end;
                                
                                getflag = 0;
                            }
                        }
                    }
                }
                
                if (getflag == 1) {
                    ptr_diffimg[ptr_index] += 1;    //To solve the same max-value problem
                    x[circle_num] = cols_index;
                    y[circle_num] = rows_index;
                    radius[circle_num] = r + min_radius - 5;
                    circle_num++;
                }
            }
        }
    }
    
    (*circle_cnt) = circle_num;
    delete[] diffimg;
    return MY_OK;
}

