#include<opencv2/opencv.hpp>
#include "state.h"
#include <fstream>
#include "board.h"
using namespace cv;
using namespace std;
int main() {
    board bo[4];
    VideoWriter writer("output.avi",  CV_FOURCC('M','J','P','G'), 30.0, cv::Size(155*6, 270));
    VideoCapture video("/media/jf/My Passport/SMD_exp._NachBac_0521.mp4");
    float fps = (float)video.get(CV_CAP_PROP_FPS);
    double all_length = video.get(CV_CAP_PROP_FRAME_COUNT);
    int index,i,board_num;
    int write = 0;
    int speed = 2;
    for (index=0;index<4;index++){  //初始化帧率
        for (i=0;i<37;i++)
            bo[index].flies[i].set_fps(fps);
        bo[index].fps = fps;
        bo[index].set_speed(speed);
    }
    Mat dst,src,gray;
    bool resize_flag=false;
    int video_count=0;
    Mat M,tempsrc;
    Mat mid;
    video >> mid;
    Size dsize;
    if (!(mid.rows==1280||mid.cols==1280)) //1080p就不用resize了
        resize_flag=true;
    if (mid.rows>mid.cols)
        dsize=Size(int(mid.cols*1280/mid.rows),1280);
    else
        dsize=Size(1280,int(mid.rows*1280/mid.cols));
    if (resize_flag)
        resize(mid, src, dsize);
    else
        src = mid.clone();
    cout<<src.size<<endl;
    tempsrc = src.clone();
    cout<<"input the num of board"<<endl;   //有几块板
    cin>>board_num;
    cout<<"choose write the video num"<<endl; //选择输出哪块板子的视频，输入0就是不输出视频
    cin>>write;
    for (index = 0;index<board_num;index++){
        bo[index].get_point(src);  //用鼠标点四个柱子
        bo[index].reset_matcher();  //初始化模板匹配
        bo[index].adjust_lines();  //调整网格
    }
//    cvNamedWindow("output3", 0);
//    resizeWindow("output3", 1280, 1080);
//    cvNamedWindow("output4", 0);
//    resizeWindow("output4", 1280, 1080);
    while (video_count<(all_length)) {
        video >> mid;
        if (mid.empty())
            break;
        if (resize_flag)
            resize(mid, src, dsize);
        else
            src = mid.clone();
        video_count++;
        if (video_count%speed!=0)
            continue;
        for (index = 0;index<board_num;index++){
            bo[index].state(src,video_count);  //状态更新
            string text = "ouput"+to_string(index);
            imshow(text,bo[index].dst);
            if (write)
                text = "ouput"+to_string(index)+".avi";
            if (index == write-1)
                writer<<bo[index].dst;
            waitKey(1);
        }
        cout<<"done="<<video_count/(all_length)*100<<"%"<<endl;
    }
    for (index=0;index<board_num;index++)
        bo[index].csv_output(index); //输出板子对应的结果
    return 0;
}