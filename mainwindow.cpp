#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

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

    ui->horizontalSlider_X->setMinimum(SCROLLBAR_MIN_VALUE);
    ui->horizontalSlider_X->setMaximum(SCROLLBAR_MAX_VALUE);
    ui->horizontalSlider_X->setValue(15);
    ui->label_xvalue->setText(QString::number(0));

    ui->horizontalSlider_Y->setMinimum(SCROLLBAR_MIN_VALUE);
    ui->horizontalSlider_Y->setMaximum(SCROLLBAR_MAX_VALUE);
    ui->horizontalSlider_Y->setValue(15);
    ui->label_yvalue->setText(QString::number(0));

    ui->progressBar->setValue(0);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::View(Mat mtx)
{
    QImage disImage1 = Mat2QImage(mtx);

    ui->label_view->setPixmap(QPixmap::fromImage(disImage1.scaled(ui->label_view->width(),ui->label_view->height(),Qt::KeepAspectRatio)));
}

Mat MainWindow::Draw(Mat mtx)
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
    img2 = mtx.clone();
    for (int i=0;i<4;i++)
       line(img2,Point(0, y[i]),Point(155*6, y[i]),Scalar(0,0,255),2);
    for (int i=0;i<15;i++)
       line(img2,Point(x[i], 0),Point(x[i], 270),Scalar(0,0,255),2);
    cv::imwrite("output1.jpg", img2);
    return img2;
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

    Mat temp;
    for (int i=0;i<37;i++)
       flies[i].set_fps(fps);
    dstTri.resize(4);
    callbackP utsc;
    char key;

    if (mid.rows>mid.cols)
       dsize=Size(int(mid.cols*1280/mid.rows),1280);
    else
       dsize=Size(1280,int(mid.rows*1280/mid.cols));
    cv::resize(mid, utsc.src, dsize);
    //cout<<utsc.src.size<<endl;
    tempsrc = utsc.src.clone();
    namedWindow("src", 0);
    resizeWindow("src", 1280, 1080);

    bool process1=true;
    while(process1) {
        imshow("src", utsc.src);
        setMouseCallback("src", onMouse, (void *) &utsc);  //类型转换
        if (utsc.clickTimes == 4) {
            dstTri[0].x = 0;
            dstTri[0].y = 0;
            dstTri[1].x = length;
            dstTri[1].y = 0;
            dstTri[2].x = length;
            dstTri[2].y = height;
            dstTri[3].x = 0;
            dstTri[3].y = height;

            //计算透视矩阵
            M = findHomography(utsc.srcTri, dstTri, RANSAC);
            //图像透视变换
            warpPerspective(utsc.src, dst, M,Size((length), (height)));
            ui->statusbar->showMessage(tr("透视变换完成"));
            cv::imwrite("output.jpg", dst);
            process1 = false;
        } else {
            QString str1 = QString("需要从左上角开始，顺时针依次点矩形的四个角！ 现在点击了%1次" ).arg(utsc.clickTimes);
            ui->statusbar->showMessage(str1);
        }
        key = waitKey(1);
        if (key == 'q')
            break;
    }

    for (int i=0;i<4;i++){
        center = utsc.srcTri[i];
        if (center.x>3 && center.y>3){
            matchimg.emplace_back(tempsrc(Rect(center.x-3,center.y-3,6,6)).clone());
            matchcenter.emplace_back(center);
        }
    }

    cv::destroyAllWindows();
    img = dst.clone();
    View(Draw(img));
}


void MainWindow::on_horizontalSlider_X_valueChanged(int value)
{
    if(m_isOpenFile){
        s1 = value;
        ui->label_xvalue->setText(QString::number(s1-15));
        View(Draw(img));
    }
}


void MainWindow::on_horizontalSlider_Y_valueChanged(int value)
{
    if(m_isOpenFile){
        s2 = value;
        ui->label_yvalue->setText(QString::number(s2-15));
        View(Draw(img));
    }
}


void MainWindow::on_pushButton_start_clicked()
{
    if(m_isOpenFile)
    {
        timer->start(25);
    }
}


void MainWindow::on_pushButton_out_clicked()
{
    if(m_isOpenFile){
        outcsv(flies, 37);
        ui->statusbar->showMessage(tr("输出完成"));
    }
}

void MainWindow::ProcessVideo()
{
    if (video_count>=(all_length-2))
    {
        timer->stop();
        ui->progressBar->setValue(all_length);
    }
        ui->progressBar->setValue(video_count);
        video >> mid;

        cv::resize(mid, img, dsize);
        video_count++;

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
            if (dis_judge(location, matchcenter[i]))
                matchcenter[i]=location;
//            rectangle(img,leftup,Point(leftup.x+wid,leftup.y+heigh),Scalar(0,255,0),2);
//            circle(img,center,2,Scalar(255,0,0),2);
//            rectangle(img, Point(matchLocate.x+leftup.x,matchLocate.y+leftup.y),Point(matchLocate.x+matchimg[i].cols+leftup.x,matchLocate.y+matchimg[i].rows+leftup.y),Scalar(0,0,255),2);
        }
        M = findHomography(matchcenter, dstTri, RANSAC);
        warpPerspective(img, dst, M,
                        Size((length), (height)));
        for (int i=0;i<37;i++){
            P[i].clear();
            scale[i] = 0;
        }
        cvtColor(dst,img_gray,CV_BGR2GRAY);
        threshold(img_gray,img_black,160,255,CV_THRESH_BINARY);
        dilate(img_black, img_black, kernel);
        findContours(img_black, contours, hierarchy, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);
        vector<RotatedRect> boundRect(contours.size());
        for (size_t i = 0; i < contours.size(); i++)
        {
            //approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);
            boundRect[i] = minAreaRect(Mat(contours[i]));
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
                        if (t_area>=13)
                        {
                            Scalar color = Scalar(0, 0, 255);
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
                        if (t_area>=13)
                        {
                            Scalar color = Scalar(0, 0, 255);
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
                        if (t_area>=13)
                        {
                            Scalar color = Scalar(0, 0, 255);
                            drawContours(dst, contours, i, color, 1);
                            P[index_num].emplace_back(boundRect[i].center);
                            boundRect[i].points(rect);
                            float ca = calc(rect);
                            scale[index_num] = ca;
                        }
                    }
                }
        }
        for (int i=0;i<37;i++){
            if (!P[i].empty() && P[i].size()<3){ //有2个果蝇才处理
                flies[i].Trajectory(P[i]);
                flies[i].update_state(P[i]);
                flies[i].update_scale(scale[i]);
                string text =" ";
                string text1 = to_string(i);
                if (flies[i].fly_state == 1)
                {
                    if (flies[i].is_court || flies[i].buff_time1/fps>3){
                        text = "Court";
                    }else{
                        text = "MayCourt";
                    }
                }
                if (flies[i].fly_state == 2)
                    text = "3";
                if (flies[i].fly_state == 3)
                    text = "4";
                putText(dst, text, flies[i].fly2.back(), cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(0, 120, 255), 2);
                if (i==32){
                    text=to_string(scale[i]);
                    putText(dst, text, flies[i].fly2.back(), cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(0, 255, 0), 2);
                }
//                if (flies[i].stop_judge(1))
//                    putText(dst, "stop", flies[i].fly1.back(), cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(0, 255, 255), 2);
//                else
//                    putText(dst, "move", flies[i].fly1.back(), cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(0, 255, 255), 2);
            }
        }


        View(dst);
        writer<<dst;
        QString str2 = QString("已经处理了%1帧" ).arg(video_count);
        ui->statusbar->showMessage(str2);


}

