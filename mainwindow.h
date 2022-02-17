#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTimer>
#include <opencv2/opencv.hpp>
#include "state.h"
#include "board.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void View1(cv::Mat mtx);
    void View2(cv::Mat mtx);
    void View3(cv::Mat mtx);
    void View4(cv::Mat mtx);
    void ViewDraw(int num);
    void ViewDst(int num);
    void SaveVideo(int index,cv::Mat dst);
    void Writer(int index,String videoname);
    void saveall(string filepath, int num);
    ~MainWindow();

private slots:
    void on_pushButton_open_clicked();

    void on_pushButton_start_clicked();

    void on_pushButton_out_clicked();

    void on_horizontalSlider_X1_valueChanged(int value);

    void on_horizontalSlider_Y1_valueChanged(int value);

    void on_horizontalSlider_X2_valueChanged(int value);

    void on_horizontalSlider_Y2_valueChanged(int value);

    void on_horizontalSlider_X3_valueChanged(int value);

    void on_horizontalSlider_Y3_valueChanged(int value);

    void on_horizontalSlider_X4_valueChanged(int value);

    void on_horizontalSlider_Y4_valueChanged(int value);

    void ProcessVideo();

private:
    Ui::MainWindow *ui;
    QTimer *timer;

    board bo[4];
    int board_num = 1;          //处理板子的数目
    int speed =2;               //处理速度


    bool m_isOpenFile;
    cv::VideoCapture video;
    cv::Mat mid;            //处理中的图片
    float fps;
    double all_length;

    cv::Mat dst,src,gray;   //意义不明的图片
    bool resize_flag=false;
    int video_count=0;
    cv::Size dsize;

    QMessageBox::StandardButton savevideo;
    cv::VideoWriter writer1;
    cv::VideoWriter writer2;
    cv::VideoWriter writer3;
    cv::VideoWriter writer4;

};
#endif // MAINWINDOW_H
