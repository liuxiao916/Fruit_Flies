#include<opencv2/opencv.hpp>
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
int main(int argc, char *argv[])
{
    vector<Point2f> dstTri(4);
    Mat dst,src,gray;
    int center_x[12];
    int center_y[3];
    callbackP utsc;
    char key;
    int length = 155*6;
    int height = 45*6;
    bool process1=true,process2=true;
    utsc.src = imread("1.jpg");
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
            Mat M = findHomography(utsc.srcTri, dstTri, RANSAC);
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
    cvNamedWindow("output2", CV_WINDOW_AUTOSIZE);
    first();
    while (process2){
        createTrackbar("diffx", "output2", &s1, 30, trackBar);
        createTrackbar("diffy", "output2", &s2, 30, trackBar);
        key = waitKey(1);
        if (key == 'q')
            break;
    }
    Mat img_gray,img_black;
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
    cvtColor(img,img_gray,CV_BGR2GRAY);
//    threshold(img_gray,img_black,0,255,CV_THRESH_BINARY|CV_THRESH_OTSU);
    threshold(img_gray,img_black,160,255,CV_THRESH_BINARY);
    dilate(img_black, img_black, kernel);
//    erode(img_black, img_black, kernel);
    vector<vector<cv::Point>> contours;
    vector<cv::Vec4i> hierarchy;
    findContours(img_black, contours, hierarchy, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);
    vector<RotatedRect> boundRect(contours.size());
    for (size_t i = 0; i < contours.size(); i++)
    {
        //approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);
        boundRect[i] = minAreaRect(Mat(contours[i]));
    }
    vector<Point> max_contour;
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
//                    cout <<"area="<<t_area<<endl;
                    if (t_area>=20)
                    {
                        Scalar color = Scalar(0, 0, 255);
                        drawContours(dst, contours, i, color, 1);
                        string text = to_string(index_num);
                        putText(dst, text, boundRect[i].center, cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(0, 255, 255), 2);
                    }
                }
            }
        add = 12;
        for (int j=0;j<3;j++)
            for (int k=5;k<9;k++){
                if ((t_x>x[k]&&t_x<x[k+1])&&(t_y>y[j]&&t_y<y[j+1])){
                    int index_num = j*4+k+1+add;
//                    cout <<"area="<<t_area<<endl;
                    if (t_area>=20)
                    {
                        Scalar color = Scalar(0, 0, 255);
                        drawContours(dst, contours, i, color, 1);
                        string text = to_string(index_num);
                        putText(dst, text, boundRect[i].center, cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(0, 255, 255), 2);
                    }
                }
            }
        add = 24;
        for (int j=0;j<3;j++)
            for (int k=10;k<14;k++){
                if ((t_x>x[k]&&t_x<x[k+1])&&(t_y>y[j]&&t_y<y[j+1])){
                    int index_num = j*4+k+1+add;
//                    cout <<"area="<<t_area<<endl;
                    if (t_area>=20)
                    {
                        Scalar color = Scalar(0, 0, 255);
                        drawContours(dst, contours, i, color, 1);
                        string text = to_string(index_num);
                        putText(dst, text, boundRect[i].center, cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(0, 255, 255), 2);
                    }
                }
            }

    }
//    morphologyEx(img_black, img_black, CV_MOP_OPEN, kernel);
//    dilate(img_black,img_black,getStructuringElement(cv::MORPH_RECT, cv::Size(2,2)));
    imshow("output3", img_black);
//    imshow("output4", img_gray);
    imshow("output5", dst);
    waitKey(0);
    return 0;
}