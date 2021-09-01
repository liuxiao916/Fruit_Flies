#ifndef UTIL_H
#define UTIL_H

#include <opencv2/opencv.hpp>
#include <state.h>
#include <QImage>

using namespace cv;
using namespace std;

struct callbackP
{
    Mat src;
    int clickTimes = 0;        //在图像上单击次数
    vector<Point2f> srcTri;
};

void onMouse(int event, int x, int y, int flags, void *utsc);
void outcsv(State *flies,string filepath, int size);
bool dis_judge(Point p1,Point p2);
float calc(Point2f rect[4]);
QImage	Mat2QImage(cv::Mat mtx);


#endif // UTIL_H
