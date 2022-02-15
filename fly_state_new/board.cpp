#include "board.h"
int s1=15,s2=15;
int diffx = 0;
int diffy = 0;
int x[15],y[4];
Mat image;
board::board() {
    dstTri.emplace_back(Point2f(0,0));
    dstTri.emplace_back(Point2f(length,0));
    dstTri.emplace_back(Point2f(length,height));
    dstTri.emplace_back(Point2f(0,height));
}
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
    img2 = image.clone();
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
    img2 = image.clone();
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
        (*(callbackP*)utsc).srcTri.emplace_back(Point2f(x, y));
        cout << "x:" << x << " " << "y:" << y << endl;
        (*(callbackP*)utsc).clickTimes++;

        if ((*(callbackP*)utsc).clickTimes == 4)
        {
            cout << "按任意键继续！" << endl;
        }
    }
}
void board::set_speed(int speed) {
    for (int i=0;i<37;i++)
        flies[i].speed = speed;
}
void board::get_point(Mat &img) {
    namedWindow("src",0);

    cvResizeWindow("src", 1080, 1080);
    bool process1 = true;
    utsc.src = img.clone();
    while(process1) {
        imshow("src", utsc.src);
        setMouseCallback("src", onMouse, (void *) &utsc);  //类型转换
        if (utsc.clickTimes == 4) {
            //计算透视矩阵
            M = findHomography(utsc.srcTri, dstTri, RANSAC);
            //图像透视变换
            warpPerspective(utsc.src, dst, M,
                            Size((length), (height)));
            imwrite("output.jpg", dst);
            break;
        } else {
            cout << "需要从左上角开始，顺时针依次点矩形的四个角！" << endl;
            cout << "现在点击了" << utsc.clickTimes << "次" << endl;
        }
        key = waitKey(1);
        if (key == 'q')
            break;
    }
    image = dst.clone();
    destroyWindow("src");
}
void board::adjust_lines() {
    cvNamedWindow("output2", 0);
    resizeWindow("output2", 1280, 1080);
    bool process2 = true;
    first();
    while (process2){
        createTrackbar("diffx", "output2", &s1, 30, trackBar);
        createTrackbar("diffy", "output2", &s2, 30, trackBar);
        key = waitKey(1);
        if (key == 'q')
            break;
    }
    destroyWindow("output2");
}
void board::reset_matcher() {
    Mat tempsrc = utsc.src.clone();
    Point center;
    for (int i=0;i<4;i++){
        center = utsc.srcTri[i];
        if (center.x>8 && center.y>8){
            matchimg.emplace_back(tempsrc(Rect(center.x-8,center.y-8,16,16)).clone());
            matchcenter.emplace_back(center);
        }
    }
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
//    if (dis>8.0)
//        cout<<"dis="<<dis<<endl;
    return dis <= 8.0;
}
void board::state(Mat &img, int time) {
    int wid,heigh;
    Mat img_gray,img_black;
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
    vector<vector<cv::Point>> contours;
    vector<cv::Vec4i> hierarchy;
    Point2f rect[4];
    Point leftup,rightdown,center;
    Mat srcimg,dstimg;
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
        if (dis_judge(location, matchcenter[i])){
            matchcenter[i]=location;
//            matchimg[i]=img(Rect(location.x-3,location.y-3,6,6)).clone();
        }
            rectangle(img,leftup,Point(leftup.x+wid,leftup.y+heigh),Scalar(0,255,0),2);
            circle(img,center,2,Scalar(255,        0,0),2);
            rectangle(img, Point(matchLocate.x+leftup.x,matchLocate.y+leftup.y),Point(matchLocate.x+matchimg[i].cols+leftup.x,matchLocate.y+matchimg[i].rows+leftup.y),Scalar(0,0,255),2);
    }
    imshow("test",img);
    imwrite ("img.jpg",img);
    waitKey(1);
    M = findHomography(matchcenter, dstTri, RANSAC);
    warpPerspective(img, dst, M,
                    Size((length), (height)));
    for (int i=0;i<37;i++){
        P[i].clear();
        scale[i] = 0;
    }
    cvtColor(dst,img_gray,CV_BGR2GRAY);
    medianBlur(img_gray,img_gray,3);
    threshold(img_gray,img_black,152,255,CV_THRESH_BINARY);
    dilate(img_black, img_black, kernel);
    findContours(img_black, contours, hierarchy, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);
    imshow ("test2", img_black);
    imwrite ("black.jpg",img_black);
    waitKey(1);
    vector<RotatedRect> boundRect(contours.size());
    vector<double> contArea(contours.size());
    for (size_t i = 0; i < contours.size(); i++)
    {
        //approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);
        boundRect[i] = minAreaRect(Mat(contours[i]));
        contArea[i] = contourArea(contours[i]);
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
                    if (t_area>=14 &&  contArea[i]>12 && contArea[i]<8000)
                    {
                        Scalar color = Scalar(0, 255, 255);
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
                    if (t_area>=14 &&  contArea[i]>12 && contArea[i]<8000)
                    {
                        Scalar color = Scalar(0, 255, 255);
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
                    if (t_area>=14 &&  contArea[i]>12 && contArea[i]<8000)
                    {
                        Scalar color = Scalar(0, 255, 255);
                        drawContours(dst, contours, i, color, 1);
                        P[index_num].emplace_back(boundRect[i].center);
                        boundRect[i].points(rect);
                        float ca = calc(rect);
                        scale[index_num] = ca;
                    }
                }
            }
    }

    imshow ("test3", dst);
    imwrite ("dst.jpg",dst);
    waitKey(1);
    for (int i=0;i<37;i++){
        if (!P[i].empty() && P[i].size()<3){ //有2个果蝇才处理
            flies[i].Trajectory(P[i]);
            flies[i].update_state(P[i],time);
            flies[i].update_scale(scale[i]);
            string text =" ";
            string text1 = to_string(i);
//            if (flies[i].fly_state == 0)
//                text = "0";
            if (flies[i].fly_state == 1)
                if (flies[i].is_court || flies[i].buff_time1/fps>3)
                    text = "Court";
                else
                    text = "MCourt";
            if (flies[i].fly_state == 2)
                text = "MMate";
            if (flies[i].fly_state == 3)
                text = "Mate";
            putText(dst, text, flies[i].fly2.back(), cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(0, 120, 255), 2);
//            if (i==32){
//                text=to_string(scale[i]);
//                putText(dst, text, flies[i].fly2.back(), cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(0, 255, 0), 2);
//            }
//                if (flies[i].stop_judge(1))
//                    putText(dst, "stop", flies[i].fly1.back(), cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(0, 255, 255), 2);
//                else
//                    putText(dst, "move", flies[i].fly1.back(), cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(0, 255, 255), 2);
        }
    }
}
void board::csv_output(int pos) {
    cout<<"output to csv"<<endl;
    string file = "output_"+to_string(pos+1)+".csv";
    float CI;
    std::ofstream myfile;
    myfile.open (file);
    myfile << " ," << "courtship_duration(min),"<<"mate_duration(min),"<<"CI,"<<"court start time(min),"<<"mate start time(min),"<<"mate end time(min)"<<endl;
    for (int i = 0; i< 37; i++)
    {
        if (flies[i].mate_start == 0)
            CI = 0;
        else
            CI = (float)flies[i].courtship_time/(flies[i].mate_start-flies[i].court_start);
        myfile << i<< ","<< flies[i].courtship_time/flies[i].fps/60<< ","<<flies[i].mate_time/flies[i].fps/60 << "," << CI <<","<<flies[i].court_start/flies[i].fps/60<<","<<flies[i].mate_start/flies[i].fps/60<<","<<(flies[i].mate_start+flies[i].mate_time)/flies[i].fps/60<<endl;
    }
    myfile.close();
}