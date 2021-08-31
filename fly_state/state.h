#ifndef FLY_STATE_STATE_H
#define FLY_STATE_STATE_H
#include<opencv2/opencv.hpp>
#include <queue>
#include <iostream>
using namespace cv;
using namespace std;

// 状态机：状态：无反应阶段 求偶缓冲阶段 求偶阶段 交配缓冲阶段 交配阶段 结束
class State {
public:
    int fly_state;
    int courtship_time;
    int mate_time;
    int buff_time1,buff_time2,buff_time3;
    int stop_time1,stop_time2;
    int average1_x,average1_y,average2_x,average2_y,num;
    float fps;
    void update_state(vector<Point> p);
    void update_scale(float scale);
    void Trajectory(vector<Point> p);
    queue<Point> fly1,fly2;
    queue<Point> av_center2,av_center1;
    bool stop_judge(int num);  //判断果蝇是否移动
    bool matestop_judge(int num);
    int chasetimes=0;
    int is_court;
    int size2_time;
    int size1_time;
    float sca;
    State();
    void set_fps(float video_fps);

private:
    Point fly1_now,fly2_now; //果蝇当前坐标
    int fly_move;

    bool chase_judge();
    float dis(Point p1,Point p2);
};


#endif //FLY_STATE_STATE_H
