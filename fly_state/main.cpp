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

int s1=15,s2=15;
int diffx_up = 0,diffx_down = 0,diffy_up = 0,diffy_down = 0;
int diffx = 0;
int diffy = 0;
int x[15],y[4];
Mat img;

void trackBar(int, void*)
{
    diffx = s1 - 15;
    diffy = s2 - 15;
    x[0] = 0;
    y[0] = 36;
    for (int i=1;i<5;i++)
        x[i] = x[i-1]+66;
    x[5] = 333;
    for (int i=6;i<10;i++)
        x[i] = x[i-1]+66;
    x[10] = 666;
    for (int i=11;i<15;i++)
        x[i] = x[i-1]+66;
    for (int i=1;i<4;i++)
        y[i] = y[i-1]+66;
    for (int i=1;i<15;i++)
        x[i] +=diffx;
    for (int i=0;i<4;i++)
        y[i] +=diffy;
    Mat img2;
    img2 = img.clone();
    for (int i=0;i<4;i++)
        line(img2,Point(0, y[i]),Point(155*6, y[i]),Scalar(0,0,255),1);
    for (int i=0;i<15;i++)
        line(img2,Point(x[i], 0),Point(x[i], 270),Scalar(0,0,255),1);
    imshow("output2", img2);
}
void first(){
    diffx = s1 - 15;
    diffy = s2 - 15;
    x[0] = 0;
    y[0] = 36;
    for (int i=1;i<5;i++)
        x[i] = x[i-1]+66;
    x[5] = 333;
    for (int i=6;i<10;i++)
        x[i] = x[i-1]+66;
    x[10] = 666;
    for (int i=11;i<15;i++)
        x[i] = x[i-1]+66;
    for (int i=1;i<4;i++)
        y[i] = y[i-1]+66;
    for (int i=1;i<15;i++)
        x[i] +=diffx;
    for (int i=0;i<4;i++)
        y[i] +=diffy;
    Mat img2;
    img2 = img.clone();
    for (int i=0;i<4;i++)
        line(img2,Point(0, y[i]),Point(155*6, y[i]),Scalar(0,0,255),1);
    for (int i=0;i<15;i++)
        line(img2,Point(x[i], 0),Point(x[i], 270),Scalar(0,0,255),1);
    imshow("output2", img2);
}
void onMouse(int event, int x, int y, int flags, void *utsc)
{
    callbackP cp = *(callbackP*)utsc;  // 先转换类型，再取数据

    if (event == EVENT_LBUTTONUP)      //响应鼠标左键事件
    {
        circle((*(callbackP*)utsc).src, Point(x, y), 2, Scalar(0, 0, 255), 2);  //标记选中点
//        imshow("wait ", (*(callbackP*)utsc).src);
        (*(callbackP*)utsc).srcTri.push_back(Point2f(x, y));
        cout << "x:" << x << " " << "y:" << y << endl;
        (*(callbackP*)utsc).clickTimes++;

        if ((*(callbackP*)utsc).clickTimes == 4)
        {
            cout << "按任意键继续！" << endl;
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
    cout<<"output to csv"<<endl;
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
float calc(Point2f rect[4]){
    float length,width;
    length = sqrt((rect[0].x-rect[1].x)*(rect[0].x-rect[1].x)+(rect[0].y-rect[1].y)*(rect[0].y-rect[1].y));
    width = sqrt((rect[2].x-rect[1].x)*(rect[2].x-rect[1].x)+(rect[2].y-rect[1].y)*(rect[2].y-rect[1].y));
    if (width/length < 1.0)
        return length/width*1.0;
    return width/length*1.0;
}
bool dis_judge(Point p1,Point p2){
    float dis;
    dis = sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
    if (dis>12.0)
        cout<<"dis="<<dis<<endl;
    return dis <= 12.0;
}
int main(int argc, char *argv[])
{
    vector<Point> P[37];
    float scale[37];
    VideoWriter writer("output.avi",  CV_FOURCC('M','J','P','G'), 30.0, cv::Size(155*6, 270));
    VideoCapture video("/media/jf/TOSHIBA EXT/fly video/SMD_Naive_NachBac_0521.mp4");
//    VideoCapture video("test3.mp4");
    float fps = (float)video.get(CV_CAP_PROP_FPS);
//    State test1(fps);
    State flies[37];
    Mat temp;
    for (int i=0;i<37;i++)
        flies[i].set_fps(fps);
    double all_length = video.get(CV_CAP_PROP_FRAME_COUNT);
    vector<Point2f> dstTri(4);
    Mat dst,src,gray;
    int center_x[12];
    int center_y[3];
    callbackP utsc;
    char key;
    int length = 155*6;
    int height = 45*6;
    Mat M,tempsrc;
    bool process1=true,process2=true;
//    for (int i=0;i<60*fps;i++)
//        video>>temp;
    Mat mid;
//    video >> utsc.src;
    video >> mid;
//    Size dsize=Size(1280,int(mid.rows*1280/mid.cols));
    Size dsize;
    if (mid.rows>mid.cols)
        dsize=Size(int(mid.cols*1280/mid.rows),1280);
    else
        dsize=Size(1280,int(mid.rows*1280/mid.cols));
    resize(mid, utsc.src, dsize);
    cout<<utsc.src.size<<endl;
    tempsrc = utsc.src.clone();
    namedWindow("src", 0);
    resizeWindow("src", 1280, 1080);
    int flag = 2;
    while(process1) {
        imshow("src", utsc.src);
        setMouseCallback("src", onMouse, (void *) &utsc);  //类型转换
        if (utsc.clickTimes == 4) {
            dstTri[0].x = 0;
            dstTri[0].y = 0;
            dstTri[1].x = length;
            dstTri[1].y = 0;
            dstTri[2].x = length;
            dstTri[2].y = height;
            dstTri[3].x = 0;
            dstTri[3].y = height;
            //计算透视矩阵
            M = findHomography(utsc.srcTri, dstTri, RANSAC);
            //图像透视变换
            warpPerspective(utsc.src, dst, M,
                            Size((length), (height)));
            imwrite("output.jpg", dst);
            process1 = false;
        } else {
            cout << "需要从左上角开始，顺时针依次点矩形的四个角！" << endl;
            cout << "现在点击了" << utsc.clickTimes << "次" << endl;
        }
        key = waitKey(1);
        if (key == 'q')
            break;
    }
    img = dst.clone();
    cvNamedWindow("output2", 0);
    resizeWindow("output2", 1280, 1080);
    first();
    Mat srcimg,dstimg;
    vector<Mat> matchimg;
    vector<Point> matchcenter;
    Point leftup,rightdown,center;
    for (int i=0;i<4;i++){
        center = utsc.srcTri[i];
        if (center.x>3 && center.y>3){
            matchimg.emplace_back(tempsrc(Rect(center.x-3,center.y-3,6,6)).clone());
            matchcenter.emplace_back(center);
        }
    }
    while (process2){
        createTrackbar("diffx", "output2", &s1, 30, trackBar);
        createTrackbar("diffy", "output2", &s2, 30, trackBar);
        key = waitKey(1);
        if (key == 'q')
            break;
    }
    Mat img_gray,img_black;
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
    vector<vector<cv::Point>> contours;
    vector<cv::Vec4i> hierarchy;
    Point2f rect[4];
    int video_count=0,wid,heigh;
    cvNamedWindow("output3", 0);
    resizeWindow("output3", 1280, 1080);
    cvNamedWindow("output4", 0);
    resizeWindow("output4", 1280, 1080);
    while (video_count<(all_length)){
        video >> mid;
        if (mid.empty())
            break;
        resize(mid, img, dsize);
        video_count++;
//        if (video_count%5 !=0)
//            continue;
        for (int i=0;i<4;i++){
            center = matchcenter[i];
            if (center.x>20)
                leftup.x=center.x-20;
            else
                leftup.x = 0;
            if (center.y>20)
                leftup.y=center.y-20;
            else
                leftup.y = 0;
            if (center.x+20>img.cols)
                rightdown.x = img.cols;
            else
                rightdown.x = center.x+20;
            if (center.y+20>img.rows)
                rightdown.y = img.rows;
            else
                rightdown.y = center.y+20;
            wid = rightdown.x-leftup.x;
            heigh = rightdown.y - leftup.y;
            srcimg = img(Rect(leftup.x,leftup.y,wid,heigh)).clone();
            matchTemplate(srcimg, matchimg[i], dstimg, TM_SQDIFF);
            normalize(dstimg,dstimg,0, 1, NORM_MINMAX, -1, Mat());
            double minvalue,maxvalue;
            Point minLocat,maxLocat;
            Point matchLocate,location;
            minMaxLoc(dstimg, &minvalue, &maxvalue, &minLocat, &maxLocat, Mat());
            matchLocate = minLocat;
            location.x = matchLocate.x+leftup.x+(int)matchimg[i].cols/2;
            location.y = matchLocate.y+leftup.y+(int)matchimg[i].rows/2;
            if (dis_judge(location, matchcenter[i]))
                matchcenter[i]=location;
//            rectangle(img,leftup,Point(leftup.x+wid,leftup.y+heigh),Scalar(0,255,0),2);
//            circle(img,center,2,Scalar(255,        0,0),2);
//            rectangle(img, Point(matchLocate.x+leftup.x,matchLocate.y+leftup.y),Point(matchLocate.x+matchimg[i].cols+leftup.x,matchLocate.y+matchimg[i].rows+leftup.y),Scalar(0,0,255),2);
        }
        M = findHomography(matchcenter, dstTri, RANSAC);
        warpPerspective(img, dst, M,
                        Size((length), (height)));
        for (int i=0;i<37;i++){
            P[i].clear();
            scale[i] = 0;
        }
        cvtColor(dst,img_gray,CV_BGR2GRAY);
        medianBlur(img_gray,img_gray,3);
        threshold(img_gray,img_black,150,255,CV_THRESH_BINARY);
        dilate(img_black, img_black, kernel);
        findContours(img_black, contours, hierarchy, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);
        vector<RotatedRect> boundRect(contours.size());
        for (size_t i = 0; i < contours.size(); i++)
        {
            //approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);
            boundRect[i] = minAreaRect(Mat(contours[i]));
        }
        for (size_t i = 0; i < contours.size(); i++)
        {
            int t_area = boundRect[i].size.area();
            int t_x = boundRect[i].center.x;
            int t_y = boundRect[i].center.y;
            int add = 0;
            for (int j=0;j<3;j++)
                for (int k=0;k<4;k++){
                    if ((t_x>x[k]&&t_x<x[k+1])&&(t_y>y[j]&&t_y<y[j+1])){
                        int index_num = j*4+k+1;
                        if (t_area>=14)
                        {
                            Scalar color = Scalar(0, 0, 255);
                            drawContours(dst, contours, i, color, 1);
                            P[index_num].emplace_back(boundRect[i].center);
                            boundRect[i].points(rect);
                            float ca = calc(rect);
                            scale[index_num] = ca;
//                            cout<<"长宽比"<<ca<<endl;
                        }
                    }
                }
            add = 12;
            for (int j=0;j<3;j++)
                for (int k=5;k<9;k++){
                    if ((t_x>x[k]&&t_x<x[k+1])&&(t_y>y[j]&&t_y<y[j+1])){
                        int index_num = j*4+(k-5)+1+add;
                        if (t_area>=14)
                        {
                            Scalar color = Scalar(0, 0, 255);
                            drawContours(dst, contours, i, color, 1);
                            P[index_num].emplace_back(boundRect[i].center);
                            boundRect[i].points(rect);
                            float ca = calc(rect);
                            scale[index_num] = ca;
                        }
                    }
                }
            add = 24;
            for (int j=0;j<3;j++)
                for (int k=10;k<14;k++){
                    if ((t_x>x[k]&&t_x<x[k+1])&&(t_y>y[j]&&t_y<y[j+1])){
                        int index_num = j*4+(k-10)+1+add;
                        if (t_area>=14)
                        {
                            Scalar color = Scalar(0, 0, 255);
                            drawContours(dst, contours, i, color, 1);
                            P[index_num].emplace_back(boundRect[i].center);
                            boundRect[i].points(rect);
                            float ca = calc(rect);
                            scale[index_num] = ca;
                        }
                    }
                }
        }
        for (int i=0;i<37;i++){
            if (!P[i].empty() && P[i].size()<3){ //有2个果蝇才处理
                flies[i].Trajectory(P[i]);
                flies[i].update_state(P[i]);
                flies[i].update_scale(scale[i]);
                string text =" ";
                string text1 = to_string(i);
                if (flies[i].fly_state == 1)
                    if (flies[i].is_court || flies[i].buff_time1/fps>3)
                        text = "Court";
                    else
                        text = "MayCourt";
                if (flies[i].fly_state == 2)
                    text = "3";
                if (flies[i].fly_state == 3)
                    text = "4";
                putText(dst, text, flies[i].fly2.back(), cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(0, 120, 255), 2);
                if (i==32){
                    text=to_string(scale[i]);
                    putText(dst, text, flies[i].fly2.back(), cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(0, 255, 0), 2);
                }
//                if (flies[i].stop_judge(1))
//                    putText(dst, "stop", flies[i].fly1.back(), cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(0, 255, 255), 2);
//                else
//                    putText(dst, "move", flies[i].fly1.back(), cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(0, 255, 255), 2);
            }
        }

//        imshow("output3", img);
//        imshow("output4", dst);
        writer<<dst;
        cout<<"done="<<video_count/(all_length)*100<<"%"<<endl;
//        key = waitKey(1);
//        if (key == 'q')
//            break;
    }

    outcsv(flies, 37);

//    ofstream outfile("Test5.txt");  //保存果蝇坐标
//    for (int i=0;i<flies[32].fly1.size();i++){
//        outfile << flies[32].fly1.front().x <<' '<<flies[32].fly1.front().y<<' '<<flies[32].fly2.front().x<<' '<<flies[32].fly2.front().y<<endl;
//        flies[32].fly1.push(flies[32].fly1.front());
//        flies[32].fly1.pop();
//        flies[32].fly2.push(flies[32].fly2.front());
//        flies[32].fly2.pop();
//    }
//    outfile.close();
//    cout<<"Write done"<<endl;
//    waitKey(0);
    return 0;
}