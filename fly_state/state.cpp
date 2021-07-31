#include "state.h"
#include<opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
State::State() {
    fly_state = 0;
    courtship_time = 0;
    mate_time = 0;
    buff_time1 = 0;
    buff_time2 = 0;
}
void State::update_state(vector<Point> p) {
    float dis1,dis2;
    if (p.size() == 2){ //两只果蝇未接触
        for (int i=0;i<2;i++){  //轨迹匹配
            dis1 = dis(p[i], fly1_now);
            dis2 = dis(p[i], fly2_now);
            if (dis1<dis2){
                fly1_now = p[i];
                fly2_now = p[1-i];
            }
            else{
                fly2_now = p[i];
                fly1_now = p[1-i];
            }
        }
        fly1.emplace_back(fly1_now);
        fly2.emplace_back(fly2_now);
    }
    else if (p.size() == 1){ //两只果蝇接触
        fly1.emplace_back(p[0]);
        fly2.emplace_back(p[0]);
    }
    switch (fly_state){  //状态机
        case 0: {  //求偶前
            if (State::chase_judge()) {
                fly_state = 1;
                stop_time1 = 0;
                stop_time2 = 0;
            }
            break;
        }
        case 1: { //求偶状态
            if (p.size()==2){
                bool flag1 = true, flag2 = true;
                if (State::stop_judge(fly1)) {  //1号是否静止
                    stop_time1++;
                    flag1 = false;
                } else  //静止时间清零
                    stop_time1 = 0;
                if (State::stop_judge(fly2)) { //2号是否静止
                    stop_time2++;
                    flag2 = false;
                } else stop_time2 = 0;
                if ((flag1 || flag2) && flag1 / 30 < 5 && flag2 / 30 < 5) { //至少有一个不静止且另外一个静止时间不超过5秒，就认为有可能还在求偶
                    if (State::chase_judge()){//是否通过追逐检测
                        courtship_time=courtship_time + buff_time1+1;
                        buff_time1 = 0;
                    }
                    else
                        buff_time1 ++;
                    if (buff_time1/30 > 10)  //连续10s没有通过追逐检测才清空缓冲时间，增加鲁棒性
                        buff_time1 = 0;
                }
                if (stop_time1 / 30 > 20 && stop_time2 / 30 > 20) { //停止了超过20s，认为求偶停止，求偶时间不清空，与下一次求偶时间累积
                    fly_state = 0;
                    stop_time1 = 0;
                    stop_time2 = 0;
                }
            }
            else if (p.size() == 1){ //两只果蝇合在一起
                bool flag1 = true, flag2 = true;
                if (State::stop_judge(fly1)) {  //1号是否静止
                    flag1 = false;
                }
                if (State::stop_judge(fly2)) { //2号是否静止
                    flag2 = false;
                }
                if (flag1 || flag2){  //至少有一个通过静止判定认为静止，进入交配缓冲阶段
                    fly_state = 2;
                    buff_time2 = 0; //交配时间不累计
                    fly_move = 0;
                }
            }
            break;
        }
        case 2: {//交配缓冲阶段
            if (State::stop_judge(fly1) && State::stop_judge(fly2)){
                buff_time2++;
                fly_move = 0;
            }
            else
                fly_move ++;
            if (fly_move/30  > 10 || p.size() == 2){ //分离开或是持续10s还在动，返回求偶状态
                courtship_time += buff_time2;
                buff_time2 = 0;
                fly_state = 1;
                stop_time1 = 0;
                stop_time2 = 0;
            }
            if (buff_time2/30 > 40){  //40秒未分开，说明进入了交配阶段
                mate_time += buff_time2;
                fly_state = 3;
                fly_move = 0;
            }
            break;
        }
        case 3: {//交配阶段
            if (p.size() == 1){
                mate_time++;
                fly_move = 0;
            }
            else
                fly_move++;
            if (fly_move/30 > 10) //分开累计五秒认为交配已经结束
                fly_state = 4;
            break;
        }
        case 4: //交配结束
            break;
    }


}
bool State::chase_judge() {
}
bool State::stop_judge(vector<Point> fly) {
}
float State::dis(Point p1, Point p2) {
    float disance;
    disance = sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
    return disance;
}