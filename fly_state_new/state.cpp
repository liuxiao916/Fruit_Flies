#include "state.h"
#include<opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
void clear_queue(queue<Point>& q) {
    queue<Point> empty;
    swap(empty, q);
}
State::State() {
    size2_time = 0;
    mate_from_start = 0;
    mate_from_start_flag = 1;
    fly_state = 0;
    courtship_time = 0;
    mate_time = 0;
    buff_time1 = 0;
    buff_time2 = 0;
    average1_x = 0;
    average1_y = 0;
    average2_x = 0;
    average2_y = 0;
    size1_time =0;
    first_court = 0;
    first_court1 = true;
    court_start=0;
    mate_start=0;
    mate_end=0;
    may_mate = 0;
    num = 0;
    chasetimes = 0;
    clear_queue(av_center1);
    clear_queue(av_center2);
    clear_queue(fly1);
    clear_queue(fly2);
}
void State::set_fps(float video_fps) {
    fps = video_fps;
}
void State::update_scale(float scale) {
    sca = scale;
}
void State::Trajectory(vector<Point> p){
    float dis1,dis2;
    if (fly1.empty()){
        if (p.size() == 2){
            fly1.push(p[0]);
            fly2.push(p[1]);
        }
        if (p.size() == 1){
            fly1.push(p[0]);
            fly2.push(p[0]);
        }
        if (p.size() > 2){
            fly1.push(p[0]);
            fly2.push(p[1]);
        }
        return ;
    }
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
        fly1.push(fly1_now);
        fly2.push(fly2_now);
    }
    else if (p.size() == 1){ //两只果蝇接触
        fly1.push(p[0]);
        fly2.push(p[0]);
    }
    if (num >= fps){
        av_center1.push(Point(average1_x,average1_y));
        av_center2.push(Point(average2_x, average2_y));
        average1_x = 0;
        average1_y = 0;
        average2_x = 0;
        average2_y = 0;
        num=0;
    }
    average1_x = (average1_x*num+fly1.back().x)/(num+speed);
    average1_y = (average1_y*num+fly1.back().y)/(num+speed);
    average2_x = (average2_x*num+fly2.back().x)/(num+speed);
    average2_y = (average2_y*num+fly2.back().y)/(num+speed);
    num+= speed;
    if (fly1.size() >= 1000)
        fly1.pop();
    if (fly2.size() >= 1000)
        fly2.pop();
    if (av_center1.size() >= 1000)
        av_center1.pop();
    if (av_center2.size() >= 1000)
        av_center2.pop();
    return ;
}
void State::update_state(vector<Point> p,int index) {
    switch (fly_state){  //状态机
        case 0: {  //求偶前
            if (chase_judge() && p.size() == 2) {
                if (mate_from_start/fps > 100){
                    fly_state = 4;
                    mate_start = 0;
                    mate_end = index;
                    mate_time = mate_from_start;
                }
                else{
                    is_court = 1;
                    mate_from_start_flag = 0;
                    fly_state = 1;
                    first_court++;
                    stop_time1 = 0;
                    stop_time2 = 0;
                }
            }
            if (p.size() == 2){
                size2_time += speed;
                size1_time = 0;
            }
            if (p.size() == 1 && mate_from_start_flag)
                mate_from_start += speed;

            if (p.size() == 1 && size2_time/fps > 10){
                size1_time += speed;
            }
            if (size1_time/fps > 3){
                fly_state = 2;
                may_mate = index;
                buff_time2 = 0;
                buff_time3 = 0;
                fly_move = 0;
                size2_time=0;
            }
            break;
        }
        case 1: { //求偶状态
            if (p.size()==2){
                size2_time += speed;
                size1_time = 0;
                bool flag1 = true, flag2 = true;
                if (State::stop_judge(1)) {  //1号是否静止
                    stop_time1+=speed;
                    flag1 = false;
                } else  //静止时间清零
                    stop_time1 = 0;
                if (State::stop_judge(2)) { //2号是否静止
                    stop_time2+=speed;
                    flag2 = false;
                } else stop_time2 = 0;
                if ((flag1 || flag2)) { //至少有一个不静止且另外一个静止时间不超过5秒，就认为有可能还在求偶
                    if (first_court>=1&&courtship_time/fps > 2.5&&first_court1){
                        court_start = index-courtship_time;
                        first_court1 = false;
                    }
                    if (State::chase_judge()){//是否通过追逐检测
                        courtship_time=courtship_time + buff_time1+1;
                        buff_time1 = 0;
                        is_court = 1;
                    }
                    else{
                        buff_time1 +=speed;
                        is_court = 0;
                    }
                    if (buff_time1/fps > 6)  //连续3s没有通过追逐检测才清空缓冲时间，增加鲁棒性
                        buff_time1 = 0;
                }
                else{ //停止了超过2s，认为求偶停止，求偶时间不清空，与下一次求偶时间累积
                    fly_state = 0;
                    chasetimes = 0;
                    stop_time1 = 0;
                    stop_time2 = 0;
                    if (buff_time1/fps < 3) //求偶时间不足3s认为是误识别
                        buff_time1 = 0;
                }
            }
            else if (p.size() == 1){ //两只果蝇合在一起
                bool flag1 = true, flag2 = true;
                if (State::matestop_judge(1)) {  //1号是否静止
                    flag1 = true;
                }
                if (State::matestop_judge(2)) { //2号是否静止
                    flag2 = true;
                }
                if (flag1 || flag2){  //至少有一个通过静止判定认为静止，进入交配缓冲阶段
                    fly_state = 2;
                    may_mate = index;
                    buff_time2 = 0; //交配时间不累计
                    buff_time3 = 0;
                    fly_move = 0;size2_time=0;
                    once1 = 0;
                    once2 = 2;
                }
            }
            break;
        }
        case 2: {//交配缓冲阶段
//            if (State::matestop_judge(1)&& sca>1.5){
            if (p.size() == 1 ){
                buff_time2 +=speed;
                fly_move = 0;
                if (once2)
                    once1++;
            }
            else{
                fly_move +=speed;
                buff_time3 +=speed;
            }
            if (p.size()==2){
                size2_time+=speed;
                once2 += 1;
            }
            if (once1 && once2)
                if (once1/once2>6){
                    once1=0;
                    once2=0;
                    size2_time=0;
                }
            if (fly_move/fps  > 30 || size2_time/fps > 10){ //分离开或是持续30s动，返回求偶状态
                courtship_time =courtship_time + buff_time2 + buff_time3;
                size2_time = 0;
                buff_time2 = 0;
                fly_state = 1;
                stop_time1 = 0;
                stop_time2 = 0;
            }
            if (buff_time2/fps > 300){  //300秒未分开，说明进入了交配阶段
                mate_start = may_mate;
                mate_time = mate_time + buff_time2 + buff_time3;
                fly_state = 3;
                fly_move = 0; 
            }
            break;
        }
        case 3: {//交配阶段
            if (p.size() == 1){
                mate_time+=speed;
                fly_move = 0;
            }
            else
                fly_move+=speed;
            if (fly_move/fps > 9) //分开累计10秒认为交配已经结束
            {
                fly_state = 4;
                mate_end = index;
            }
            break;
        }
        case 4: //交配结束
            break;
    }

}
bool State::chase_judge() {
    float distance;
    if (!stop_judge(1)||!stop_judge(2)){
        distance = dis(fly1.back(), fly2.back());
        if (distance<30 && distance >= 5)
            chasetimes+=speed;
        else
            chasetimes -=1;
        if (chasetimes<0)
            chasetimes = 0;
        if (chasetimes > fps*2){
            chasetimes = (int)fps*2;
            return true;
        }
        return  true;
    }
    else
        return false;
}
bool State::stop_judge(int num) {
    float distance;
    if (av_center1.empty())
        return false;
    if (num==1){
        distance = dis(fly1.back(), av_center1.back());
//        cout<<"stop1=" <<distance<<endl;
        return distance <= 7;
    }
    else {
        distance = dis(fly2.back(), av_center2.back());
//        cout<<"stop2=" <<distance<<endl;
        return distance <= 7;
    }
}
bool State::matestop_judge(int num) {
    float distance;
    if (av_center1.empty())
        return false;
    if (num==1){
        distance = dis(fly1.back(), av_center1.back());
        return distance <= 10*speed;
    }
    else {
        distance = dis(fly2.back(), av_center2.back());
//        if (distance> 10*speed)
//            cout<<"dis = "<<distance<<endl;
        return distance <= 10*speed;
    }
}
float State::dis(Point p1, Point p2) {
    float disance;
    disance = sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
    return disance;
}
