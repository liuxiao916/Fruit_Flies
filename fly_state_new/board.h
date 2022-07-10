//
// Created by jf on 2021/9/30.
//

#ifndef FLY_STATE_NEW_BOARD_H
#define FLY_STATE_NEW_BOARD_H
#include<opencv2/opencv.hpp>
#include "state.h"
#include <fstream>
using namespace cv;
using namespace std;
struct callbackP
{
    Mat src;
    int clickTimes = 0;        //在图像上单击次数
    vector<Point2f> srcTri;
};
class board {
public:
    board();
    Mat img;
    vector<Mat> matchimg;
    vector<Point> matchcenter;
    State flies[37];
    vector<Point> P[37];
    vector<Point2f> dstTri;
    float scale[37];
    void get_point(Mat &img);
    void adjust_lines();
    void reset_matcher();
    void reset_threshold();
    void state(Mat &img, int time);
    void csv_output(int pos);
    void set_speed(int speed);
    float fps;
    Mat dst,M;
private:
    callbackP utsc;
    callbackP utsc1;
    int set_threshold;
    int length = 155*6;
    int height = 45*6;
    char key;
};


#endif //FLY_STATE_NEW_BOARD_H
