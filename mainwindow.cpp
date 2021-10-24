#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <qinputdialog.h>
#include <string>

#define SCROLLBAR_MIN_VALUE 0
#define SCROLLBAR_MAX_VALUE 30

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(ProcessVideo()));
    setWindowTitle(tr("Fruit Flies"));

    m_isOpenFile = false;

    ui->horizontalSlider_X1->setMinimum(SCROLLBAR_MIN_VALUE);
    ui->horizontalSlider_X1->setMaximum(SCROLLBAR_MAX_VALUE);
    ui->horizontalSlider_X1->setValue(15);
    ui->label_xvalue1->setText(QString::number(0));

    ui->horizontalSlider_Y1->setMinimum(SCROLLBAR_MIN_VALUE);
    ui->horizontalSlider_Y1->setMaximum(SCROLLBAR_MAX_VALUE);
    ui->horizontalSlider_Y1->setValue(15);
    ui->label_yvalue1->setText(QString::number(0));

    ui->horizontalSlider_X2->setMinimum(SCROLLBAR_MIN_VALUE);
    ui->horizontalSlider_X2->setMaximum(SCROLLBAR_MAX_VALUE);
    ui->horizontalSlider_X2->setValue(15);
    ui->label_xvalue2->setText(QString::number(0));

    ui->horizontalSlider_Y2->setMinimum(SCROLLBAR_MIN_VALUE);
    ui->horizontalSlider_Y2->setMaximum(SCROLLBAR_MAX_VALUE);
    ui->horizontalSlider_Y2->setValue(15);
    ui->label_yvalue2->setText(QString::number(0));

    ui->horizontalSlider_X3->setMinimum(SCROLLBAR_MIN_VALUE);
    ui->horizontalSlider_X3->setMaximum(SCROLLBAR_MAX_VALUE);
    ui->horizontalSlider_X3->setValue(15);
    ui->label_xvalue3->setText(QString::number(0));

    ui->horizontalSlider_Y3->setMinimum(SCROLLBAR_MIN_VALUE);
    ui->horizontalSlider_Y3->setMaximum(SCROLLBAR_MAX_VALUE);
    ui->horizontalSlider_Y3->setValue(15);
    ui->label_yvalue3->setText(QString::number(0));

    ui->horizontalSlider_X4->setMinimum(SCROLLBAR_MIN_VALUE);
    ui->horizontalSlider_X4->setMaximum(SCROLLBAR_MAX_VALUE);
    ui->horizontalSlider_X4->setValue(15);
    ui->label_xvalue4->setText(QString::number(0));

    ui->horizontalSlider_Y4->setMinimum(SCROLLBAR_MIN_VALUE);
    ui->horizontalSlider_Y4->setMaximum(SCROLLBAR_MAX_VALUE);
    ui->horizontalSlider_Y4->setValue(15);
    ui->label_yvalue4->setText(QString::number(0));


    ui->progressBar->setValue(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QImage	Mat2QImage(cv::Mat mtx)
{
    switch (mtx.type())
    {
    case CV_8UC1:
        {
            QImage img((const unsigned char *)(mtx.data), mtx.cols, mtx.rows, mtx.cols, QImage::Format_Grayscale8);
            return img;
        }
        break;
    case CV_8UC3:
        {
            QImage img((const unsigned char *)(mtx.data), mtx.cols, mtx.rows, mtx.cols * 3, QImage::Format_RGB888);
            return img.rgbSwapped();
        }
        break;
    case CV_8UC4:
        {
            QImage img((const unsigned char *)(mtx.data), mtx.cols, mtx.rows, mtx.cols * 4, QImage::Format_ARGB32);
            return img;
        }
        break;
    default:
        {
            QImage img;
            return img;
        }
        break;
    }
}

void MainWindow::View1(Mat mtx)
{
    QImage disImage1 = Mat2QImage(mtx);

    ui->label_view1->setPixmap(QPixmap::fromImage(disImage1.scaled(ui->label_view1->width(),ui->label_view1->height(),Qt::KeepAspectRatio)));
}
void MainWindow::View2(Mat mtx)
{
    QImage disImage2 = Mat2QImage(mtx);

    ui->label_view2->setPixmap(QPixmap::fromImage(disImage2.scaled(ui->label_view2->width(),ui->label_view2->height(),Qt::KeepAspectRatio)));
}
void MainWindow::View3(Mat mtx)
{
    QImage disImage3 = Mat2QImage(mtx);

    ui->label_view3->setPixmap(QPixmap::fromImage(disImage3.scaled(ui->label_view3->width(),ui->label_view3->height(),Qt::KeepAspectRatio)));
}
void MainWindow::View4(Mat mtx)
{
    QImage disImage4 = Mat2QImage(mtx);

    ui->label_view4->setPixmap(QPixmap::fromImage(disImage4.scaled(ui->label_view4->width(),ui->label_view4->height(),Qt::KeepAspectRatio)));
}
void MainWindow::ViewDraw(int num){
    switch (num) {
        case 1:{
            View1(bo[0].Draw());
            break;
        }
        case 2:{
            View1(bo[0].Draw());
            View2(bo[1].Draw());
            break;
        }
        case 3:{
            View1(bo[0].Draw());
            View2(bo[1].Draw());
            View3(bo[2].Draw());
            break;
        }
        case 4:{
            View1(bo[0].Draw());
            View2(bo[1].Draw());
            View3(bo[2].Draw());
            View4(bo[3].Draw());
            break;
        }
        default:{
            View1(bo[0].Draw());
            break;
        }
    }
}
void MainWindow::ViewDst(int num){
    switch (num) {
        case 1:{
            View1(bo[0].dst);
            break;
        }
        case 2:{
            View1(bo[0].dst);
            View2(bo[1].dst);
            break;
        }
        case 3:{
            View1(bo[0].dst);
            View2(bo[1].dst);
            View3(bo[2].dst);
            break;
        }
        case 4:{
            View1(bo[0].dst);
            View2(bo[1].dst);
            View3(bo[2].dst);
            View4(bo[3].dst);
            break;
        }
        default:{
            View1(bo[0].dst);
            break;
        }
    }
}

void MainWindow::Writer(int index,String videoname){
    switch (index) {
        case 1:{
            writer1.open(videoname+"1.avi",CV_FOURCC('M','J','P','G'), 30.0, cv::Size(155*6, 270));
            break;
        }
        case 2:{
            writer1.open(videoname+"1.avi",CV_FOURCC('M','J','P','G'), 30.0, cv::Size(155*6, 270));
            writer2.open(videoname+"2.avi",CV_FOURCC('M','J','P','G'), 30.0, cv::Size(155*6, 270));
            break;
        }
        case 3:{
            writer1.open(videoname+"1.avi",CV_FOURCC('M','J','P','G'), 30.0, cv::Size(155*6, 270));
            writer2.open(videoname+"2.avi",CV_FOURCC('M','J','P','G'), 30.0, cv::Size(155*6, 270));
            writer3.open(videoname+"3.avi",CV_FOURCC('M','J','P','G'), 30.0, cv::Size(155*6, 270));
            break;
        }
        case 4:{
            writer1.open(videoname+"1.avi",CV_FOURCC('M','J','P','G'), 30.0, cv::Size(155*6, 270));
            writer2.open(videoname+"2.avi",CV_FOURCC('M','J','P','G'), 30.0, cv::Size(155*6, 270));
            writer3.open(videoname+"3.avi",CV_FOURCC('M','J','P','G'), 30.0, cv::Size(155*6, 270));
            writer4.open(videoname+"4.avi",CV_FOURCC('M','J','P','G'), 30.0, cv::Size(155*6, 270));
            break;
        }
        default:{
            writer1.open(videoname+"1.avi",CV_FOURCC('M','J','P','G'), 30.0, cv::Size(155*6, 270));
            writer2.open(videoname+"2.avi",CV_FOURCC('M','J','P','G'), 30.0, cv::Size(155*6, 270));
            writer3.open(videoname+"3.avi",CV_FOURCC('M','J','P','G'), 30.0, cv::Size(155*6, 270));
            writer4.open(videoname+"4.avi",CV_FOURCC('M','J','P','G'), 30.0, cv::Size(155*6, 270));
            break;
        }
    }
}


void MainWindow::SaveVideo(int index,cv::Mat dst){
    switch (index) {
        case 0:{
            writer1 << dst;
            break;
        }
        case 1:{
            writer2 << dst;
            break;
        }
        case 2:{
            writer3 << dst;
            break;
        }
        case 3:{
            writer4 << dst;
            break;
        }
        default:{
            break;
        }
    }
}


void MainWindow::on_pushButton_open_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open Video"),".",tr("Video File(*.avi *mp4 *h264)"));
    if (fileName.isEmpty())
    {
        return;
    }
    video.open(fileName.toStdString());
    video >> mid;

    //测试是否读取成功
    if (!mid.data)
    {
        m_isOpenFile = false;
        QMessageBox box(QMessageBox::Critical, "Open Image","Fail to opne image! Please Retry");
        box.setStandardButtons(QMessageBox::Ok);
        box.setButtonText(QMessageBox::Ok, QString("OK"));
        box.exec();
        return;
    }

    m_isOpenFile =true;

    //视频相关信息
    fps = (float)video.get(CV_CAP_PROP_FPS);
    all_length = video.get(CV_CAP_PROP_FRAME_COUNT);
    ui->progressBar->setRange(0,all_length);
    ui->progressBar->setValue(0);

    bool speedisok = false;
    speed = QInputDialog::getInt(this,
                                     "Input Speed",
                                     "请输入处理速率（1～10）",
                                     1,
                                     1,
                                     10,
                                     1,
                                     &speedisok);

    if(speedisok && speed>0){
        QString str1 = QString("将以%1的倍速处理视频" ).arg(speed);
        ui->statusbar->showMessage(str1);
    }


    for (int index=0;index<4;index++){  //初始化帧率
        for (int i=0;i<37;i++)
            bo[index].flies[i].set_fps(fps);
        bo[index].fps = fps;
        bo[index].set_speed(speed);
    }

    video >> mid;
    if (!(mid.rows==1280||mid.cols==1280)) //1080p就不用resize了
        resize_flag=true;
    if (mid.rows>mid.cols)
        dsize=Size(int(mid.cols*1280/mid.rows),1280);
    else
        dsize=Size(1280,int(mid.rows*1280/mid.cols));
    if (resize_flag)
        cv::resize(mid, src, dsize);
    else
        src = mid.clone();

    bool Inputisok = false;
    board_num = QInputDialog::getInt(this,
                                     "Input BoardNum",
                                     "请输入待处理板子的数量（不大于4）",
                                     1,
                                     1,
                                     4,
                                     1,
                                     &Inputisok);

    if(Inputisok && board_num>0){
        QString str1 = QString("输入视频中含有%1块实验板" ).arg(board_num);
        ui->statusbar->showMessage(str1);
    }

    for (int index = 0;index<board_num;index++){
        ui->statusbar->showMessage(tr("需要从左上角开始，顺时针依次点矩形的四个角！ "));
        bo[index].get_point(src);  //用鼠标点四个柱子
        bo[index].reset_matcher();  //初始化模板匹配
    }
    QString str1 = QString("输入视频中含有%1块实验板" ).arg(board_num);
    ui->statusbar->showMessage(str1);
    ViewDraw(board_num);
}


void MainWindow::on_pushButton_start_clicked()
{
    if(m_isOpenFile)
    {
        savevideo = QMessageBox::question(this,"提示","是否存储处理视频",QMessageBox::Yes|QMessageBox::No);
        if(savevideo == QMessageBox::Yes){
            ui->statusbar->showMessage(tr("指定视频存储路径"));
            QString fileName;
            fileName = QFileDialog::getSaveFileName(this,tr("Open Video"), "output.avi", tr("video Files (*.avi)"));
            string videoname = fileName.toStdString().substr(0,fileName.toStdString().find('.'));
            Writer(board_num,videoname);
        }
        timer->start(20);      //单位是毫秒
    }
}

void MainWindow::ProcessVideo(){
    if (video_count>=(all_length-2))
    {
        timer->stop();
        ui->statusbar->showMessage(tr("处理完成"));
        ui->progressBar->setValue(all_length);
    }
    for (int i = 0;i < speed ;i++ ) {
        video >> mid;
        video_count++;
        if (video_count%speed!=0){
            continue;
        }

        if (mid.empty())
            break;
        if (resize_flag)
            cv::resize(mid, src, dsize);
        else
            src = mid.clone();


        ui->progressBar->setValue(video_count);
        QString str2 = QString("已经处理了%1帧" ).arg(video_count);
        ui->statusbar->showMessage(str2);
        for (int index = 0;index<board_num;index++){
            bo[index].state(src,video_count);  //状态更新
            if(savevideo == QMessageBox::Yes){
                SaveVideo(index, bo[index].dst);
            }
        }
    }

    ViewDst(board_num);

}

void MainWindow::on_pushButton_out_clicked()
{
    if(m_isOpenFile){
        ui->statusbar->showMessage(tr("指定表格存储路径"));
        QString fileName;
        fileName = QFileDialog::getSaveFileName(this,tr("Open Csv"), "output.csv", tr("csv Files (*.csv)"));
        string csvname = fileName.toStdString().substr(0,fileName.toStdString().find('.'));
        for (int index=0;index<board_num;index++){
            bo[index].csv_output(csvname+to_string(index+1)+".csv"); //输出板子对应的结果
        }
        ui->statusbar->showMessage(tr("输出完成"));
        ui->progressBar->setValue(all_length);
    }
}


void MainWindow::on_horizontalSlider_X1_valueChanged(int value)
{
    if(m_isOpenFile){
        bo[0].s1 = value;
        ui->label_xvalue1->setText(QString::number(bo[0].s1-15));
        ViewDraw(board_num);
    }
}
void MainWindow::on_horizontalSlider_Y1_valueChanged(int value)
{
    if(m_isOpenFile){
        bo[0].s2 = value;
        ui->label_yvalue1->setText(QString::number(bo[0].s2-15));
        ViewDraw(board_num);
    }
}
void MainWindow::on_horizontalSlider_X2_valueChanged(int value)
{
    if(m_isOpenFile){
        bo[1].s1 = value;
        ui->label_xvalue2->setText(QString::number(bo[1].s1-15));
        ViewDraw(board_num);
    }
}
void MainWindow::on_horizontalSlider_Y2_valueChanged(int value)
{
    if(m_isOpenFile){
        bo[1].s2 = value;
        ui->label_yvalue2->setText(QString::number(bo[1].s2-15));
        ViewDraw(board_num);
    }
}
void MainWindow::on_horizontalSlider_X3_valueChanged(int value)
{
    if(m_isOpenFile){
        bo[2].s1 = value;
        ui->label_xvalue3->setText(QString::number(bo[2].s1-15));
        ViewDraw(board_num);
    }
}
void MainWindow::on_horizontalSlider_Y3_valueChanged(int value)
{
    if(m_isOpenFile){
        bo[2].s2 = value;
        ui->label_yvalue3->setText(QString::number(bo[2].s2-15));
        ViewDraw(board_num);
    }
}
void MainWindow::on_horizontalSlider_X4_valueChanged(int value)
{
    if(m_isOpenFile){
        bo[3].s1 = value;
        ui->label_xvalue4->setText(QString::number(bo[3].s1-15));
        ViewDraw(board_num);
    }
}
void MainWindow::on_horizontalSlider_Y4_valueChanged(int value)
{
    if(m_isOpenFile){
        bo[3].s2 = value;
        ui->label_yvalue4->setText(QString::number(bo[3].s2-15));
        ViewDraw(board_num);
    }
}
