#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <opencv2/opencv.hpp>
#include "state.h"
#include "util.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void View(cv::Mat mtx);
    cv::Mat Draw(cv::Mat mtx);

private slots:
    void on_pushButton_open_clicked();

    void on_horizontalSlider_X_valueChanged(int value);

    void on_horizontalSlider_Y_valueChanged(int value);

    void on_pushButton_start_clicked();

    void on_pushButton_out_clicked();

    void ProcessVideo();

private:
    Ui::MainWindow *ui;

    QTimer *timer;

    bool m_isOpenFile;

    Mat img;
    cv::VideoCapture video;
    cv::VideoWriter writer;
    float fps;
    double all_length;
    vector<Point2f> dstTri;
    State flies[37];

    int s1=15,s2=15;
    int diffx_up = 0,diffx_down = 0,diffy_up = 0,diffy_down = 0;
    int diffx = 0;
    int diffy = 0;
    int x[15],y[4];

    int length = 155*6;
    int height = 45*6;
    vector<Point> P[37];
    float scale[37];

    Mat mid;
    Mat srcimg,dstimg;
    Mat dst,src,gray;
    Mat M,tempsrc;
    vector<Mat> matchimg;
    vector<Point> matchcenter;
    Point leftup,rightdown,center;
    Size dsize;

    Mat img_gray,img_black;
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
    vector<vector<cv::Point>> contours;
    vector<cv::Vec4i> hierarchy;
    Point2f rect[4];
    int video_count=0,wid,heigh;

};
#endif // MAINWINDOW_H
