#include <ctime>
#include <cstdio>
#include <iostream>
#include <fstream>
using namespace std;
string key1="AK9WTG2GCB1H";
string key2="P9BNBQ8TNUQ1";
string key3="MNB8IA2RAC5Y";
struct times{
    int year,mon,mday;
};
int main()
{
    struct tm *local;
    time_t t;
    times time0,time_last;
    int year,mon,mday,hour;
    string key_now;
    ifstream input("/home/jf/.keyrc"); //在文件夹里面放了一个样例 第一行为最早运行时间，第二行为上一次运行时间，第三行为当前的密钥(查看隐藏文件按ctrl+H)
    input>>time0.year>>time0.mon>>time0.mday;
    input>>time_last.year>>time_last.mon>>time_last.mday;
    input>>key_now;
    input.close();
    //获取当前时间
    t=time(NULL);
    local=localtime(&t);
    year = 1900+local->tm_year;
    mon = local->tm_mon+1;
    mday = local->tm_mday;

    if (year<time0.year){  //判断日期的正确性
        cout<<"please update the time"<<endl;
        return 0;
    }
    else{
        if (year==time0.year){
            if (mon<time0.mon){
                cout<<"please update the time"<<endl;
                return 0;
            }
            else if (mon==time0.mon){
                if (mday<time0.mday){
                    cout<<"please update the time"<<endl;
                    return 0;
                }
            }
        }
    }
    int timedis = (year-time0.year)*365+30*(mon-time0.mon)+mday-time0.mday; //计算日期差
    if (key_now == key1){  //判断密钥
        if (timedis > 30){
            cout<<"please update the key"<<endl;
            return 0;
        }
    }
    else if (key_now == key2){ //70天密钥
        if (timedis > 70){
            cout<<"please update the key"<<endl;
            return 0;
        }
    }
    else if (key_now != key3){ //永久密钥
        cout<<"please input correct key"<<endl;
        return 0;
    }

    //如果更新密钥，可以加个输入按钮，不用每次运行都输入密钥
    cin >>key_now;

    //再写入文件更新日期
    ofstream output("/home/jf/.keyrc");
    output<<time0.year<<' '<<time0.mon<<' '<<time0.mday<<endl;
    output<<year<<' '<<mon<<' '<<mday<<endl;
    output<<key_now<<endl;
    output.close();
    return 0;
}
