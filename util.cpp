#include <util.h>
#include <opencv2/opencv.hpp>
#include <QImage>

using namespace cv;
using namespace std;


void onMouse(int event, int x, int y, int flags, void *utsc)
{
    callbackP cp = *(callbackP*)utsc;  // 先转换类型，再取数据

    if (event == EVENT_LBUTTONUP)      //响应鼠标左键事件
    {
        circle((*(callbackP*)utsc).src, Point(x, y), 2, Scalar(0, 0, 255), 2);  //标记选中点
//        imshow("wait ", (*(callbackP*)utsc).src);
        (*(callbackP*)utsc).srcTri.push_back(Point2f(x, y));
       // cout << "x:" << x << " " << "y:" << y << endl;
        (*(callbackP*)utsc).clickTimes++;

        if ((*(callbackP*)utsc).clickTimes == 4)
        {
         //   cout << "按任意键继续！" << endl;
        }
    }
}


void outcsv(State *flies, int size)
/*
    This function is used to generate a csv file which contains all infomation
    Input:
        flies: The State class
        size: The size of input flies
*/
{
    //cout<<"output to csv"<<endl;
    std::ofstream myfile;
    myfile.open ("output.csv");
    myfile << " ," << "courtship_time,"<<"mate_time ,"<<"indicator"<<endl;
    for (int i = 0; i< size; i++)
    {
        if ((flies[i].courtship_time/flies[i].fps)||(flies[i].mate_time/flies[i].fps))
            myfile << i<< ","<< flies[i].courtship_time/flies[i].fps<< ","<<flies[i].mate_time/flies[i].fps  << "," << (float)flies[i].courtship_time/(flies[i].courtship_time+flies[i].mate_time) <<endl;
    }
    myfile.close();
}

bool dis_judge(Point p1,Point p2){
    float dis;
    dis = sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
    if (dis>12.0)
        cout<<"dis="<<dis<<endl;
    return dis <= 12.0;
}

float calc(Point2f rect[4]){
    float length,width;
    length = sqrt((rect[0].x-rect[1].x)*(rect[0].x-rect[1].x)+(rect[0].y-rect[1].y)*(rect[0].y-rect[1].y));
    width = sqrt((rect[2].x-rect[1].x)*(rect[2].x-rect[1].x)+(rect[2].y-rect[1].y)*(rect[2].y-rect[1].y));
    if (width/length < 1.0)
        return length/width*1.0;
    return width/length*1.0;
}

QImage	Mat2QImage(cv::Mat mtx)
{
    switch (mtx.type())
    {
    case CV_8UC1:
        {
            QImage img((const unsigned char *)(mtx.data), mtx.cols, mtx.rows, mtx.cols, QImage::Format_Grayscale8);
            return img;
        }
        break;
    case CV_8UC3:
        {
            QImage img((const unsigned char *)(mtx.data), mtx.cols, mtx.rows, mtx.cols * 3, QImage::Format_RGB888);
            return img.rgbSwapped();
        }
        break;
    case CV_8UC4:
        {
            QImage img((const unsigned char *)(mtx.data), mtx.cols, mtx.rows, mtx.cols * 4, QImage::Format_ARGB32);
            return img;
        }
        break;
    default:
        {
            QImage img;
            return img;
        }
        break;
    }
}


