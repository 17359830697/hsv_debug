#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("hsv_Debug");

    //初始化范围
    ui->slider_h_max->setRange(0,180);
    ui->slider_s_max->setRange(0,255);
    ui->slider_v_max->setRange(0,255);
    ui->slider_h_min->setRange(0,180);
    ui->slider_s_min->setRange(0,255);
    ui->slider_v_min->setRange(0,255);

    QStringList list{"黑","灰","白","红","橙","黄","绿","青","蓝","紫"};
    ui->comboBox->addItems(list);

    connect(this,&MainWindow::slider_move,this,&MainWindow::hsv_slot);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionopen_triggered()//打开文件
{
     filepath = QFileDialog::getOpenFileName(nullptr,"选择文件","/home","*.*");
     if(filepath.isEmpty())
         return;
    QImage image(filepath);
    ui->lb_src->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::on_slider_h_min_valueChanged(int value)//h_min
{
    ui->h_min->setText(QString::number(value));
    emit slider_move();
}

void MainWindow::on_slider_s_min_valueChanged(int value)//s_min
{
    ui->s_min->setText(QString::number(value));
     emit slider_move();
}

void MainWindow::on_slider_v_min_valueChanged(int value)//v_min
{
    ui->v_min->setText(QString::number(value));
     emit slider_move();
}

void MainWindow::on_slider_h_max_valueChanged(int value)//h_max
{
    ui->h_max->setText(QString::number(value));
     emit slider_move();
}

void MainWindow::on_slider_s_max_valueChanged(int value)//s_max
{
    ui->s_max->setText(QString::number(value));
     emit slider_move();
}

void MainWindow::on_slider_v_max_valueChanged(int value)//v_max
{
    ui->v_max->setText(QString::number(value));
    emit slider_move();
}
QImage MainWindow::MatToImage(Mat &m) //Mat转QImage
{
    //判断m的类型，可能是CV_8UC1  CV_8UC2  CV_8UC3  CV_8UC4
    switch(m.type())
    { //QIamge 构造函数, ((const uchar *data, 宽(列),高(行), 一行共多少个（字节）通道，宽度*字节数，宏参数)
    case CV_8UC1:
    {
        QImage img((uchar *)m.data,m.cols,m.rows,m.cols * 1,QImage::Format_Grayscale8);
        return img;
    }
        break;
    case CV_8UC3:   //一个像素点由三个字节组成
    {
        //cvtColor(m,m,COLOR_BGR2RGB); BGR转RGB
        QImage img((uchar *)m.data,m.cols,m.rows,m.cols * 3,QImage::Format_RGB888);
        return img.rgbSwapped(); //opencv是BGR  Qt默认是RGB  所以RGB顺序转换
    }
        break;
    case CV_8UC4:
    {
        QImage img((uchar *)m.data,m.cols,m.rows,m.cols * 4,QImage::Format_RGBA8888);
        return img;
    }
        break;
    default:
    {
        QImage img; //如果遇到一个图片均不属于这三种，返回一个空的图片
        return img;
    }
    }
}
void MainWindow::hsv_slot()
{
    int h_min = ui->slider_h_min->value();
    int s_min = ui->slider_s_min->value();
    int v_min = ui->slider_v_min->value();
    int h_max = ui->slider_h_max->value();
    int s_max = ui->slider_s_max->value();
    int v_max = ui->slider_v_max->value();

    String cstr = String((const char *)filepath.toLocal8Bit());
    if(cstr.empty())
        return;
    Mat src = imread(cstr);
    Mat hsv_img;
    cvtColor(src, hsv_img, COLOR_BGR2HSV);
    Mat dstsrc = Mat::zeros(src.rows,src.cols,CV_8U);
    Scalar hsv_min(h_min,s_min,v_min);
    Scalar hsv_max(h_max,s_max,v_max);
    inRange(hsv_img,hsv_min,hsv_max,dstsrc);
    QImage dst = MatToImage(dstsrc);
    ui->lb_result->setPixmap(QPixmap::fromImage(dst));
}

void MainWindow::on_action_triggered()//打开hsv参数表
{
    form = new Formhsv;
    form->show();
}

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    if(arg1=="黑")
    {
        ui->slider_h_min->setValue(0);
        ui->slider_s_min->setValue(0);
        ui->slider_v_min->setValue(0);
        ui->slider_h_max->setValue(180);
        ui->slider_s_max->setValue(255);
        ui->slider_v_max->setValue(46);
    }
    else if(arg1=="灰")
    {
        ui->slider_h_min->setValue(0);
        ui->slider_s_min->setValue(0);
        ui->slider_v_min->setValue(46);
        ui->slider_h_max->setValue(180);
        ui->slider_s_max->setValue(43);
        ui->slider_v_max->setValue(220);
    }
    else if(arg1=="白")
    {
        ui->slider_h_min->setValue(0);
        ui->slider_s_min->setValue(0);
        ui->slider_v_min->setValue(221);
        ui->slider_h_max->setValue(180);
        ui->slider_s_max->setValue(30);
        ui->slider_v_max->setValue(255);
    }
    else if(arg1=="红")
    {
        ui->slider_h_min->setValue(156);
        ui->slider_s_min->setValue(43);
        ui->slider_v_min->setValue(46);
        ui->slider_h_max->setValue(180);
        ui->slider_s_max->setValue(255);
        ui->slider_v_max->setValue(255);
    }
    else if(arg1=="黄")
    {
        ui->slider_h_min->setValue(26);
        ui->slider_s_min->setValue(43);
        ui->slider_v_min->setValue(46);
        ui->slider_h_max->setValue(34);
        ui->slider_s_max->setValue(255);
        ui->slider_v_max->setValue(255);
    }
    else if(arg1=="橙")
    {
        ui->slider_h_min->setValue(11);
        ui->slider_s_min->setValue(43);
        ui->slider_v_min->setValue(46);
        ui->slider_h_max->setValue(25);
        ui->slider_s_max->setValue(255);
        ui->slider_v_max->setValue(255);
    }
    else if(arg1=="绿")
    {
        ui->slider_h_min->setValue(35);
        ui->slider_s_min->setValue(43);
        ui->slider_v_min->setValue(46);
        ui->slider_h_max->setValue(77);
        ui->slider_s_max->setValue(255);
        ui->slider_v_max->setValue(255);
    }
    else if(arg1=="青")
    {
        ui->slider_h_min->setValue(78);
        ui->slider_s_min->setValue(43);
        ui->slider_v_min->setValue(46);
        ui->slider_h_max->setValue(99);
        ui->slider_s_max->setValue(255);
        ui->slider_v_max->setValue(255);
    }
    else if(arg1=="蓝")
    {
        ui->slider_h_min->setValue(100);
        ui->slider_s_min->setValue(43);
        ui->slider_v_min->setValue(46);
        ui->slider_h_max->setValue(124);
        ui->slider_s_max->setValue(255);
        ui->slider_v_max->setValue(255);
    }
    else if(arg1=="紫")
    {
        ui->slider_h_min->setValue(125);
        ui->slider_s_min->setValue(43);
        ui->slider_v_min->setValue(46);
        ui->slider_h_max->setValue(155);
        ui->slider_s_max->setValue(255);
        ui->slider_v_max->setValue(255);
    }
}
