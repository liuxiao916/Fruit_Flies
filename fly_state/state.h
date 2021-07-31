#ifndef FLY_STATE_STATE_H
#define FLY_STATE_STATE_H
#include<opencv2/opencv.hpp>
#include <vector>
#include <iostream>
using namespace cv;
using namespace std;

// 状态机：状态：无反应阶段 求偶缓冲阶段 求偶阶段 交配缓冲阶段 交配阶段 结束
class State {
public:
    int fly_state;
    int courtship_time;
    int mate_time;
    int buff_time1,buff_time2;
    int stop_time1,stop_time2;
    void update_state(vector<Point> p);
    State();

private:
    Point fly1_now,fly2_now; //果蝇当前坐标
    int fly_move;
    vector<Point> fly1,fly2;

    bool chase_judge();
    bool stop_judge(vector<Point> fly);  //判断果蝇是否移动
    float dis(Point p1,Point p2);
};


#endif //FLY_STATE_STATE_H
