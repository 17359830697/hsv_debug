#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma execution_character_set("utf-8")
#include <QMainWindow>
#include<opencv2/opencv.hpp>
#include<QFileDialog>
#include"formhsv.h"
using namespace cv;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QImage MatToImage(Mat &m);
signals:
    void slider_move();

private slots:
    void on_actionopen_triggered();

    void on_slider_h_min_valueChanged(int value);

    void on_slider_s_min_valueChanged(int value);

    void on_slider_v_min_valueChanged(int value);

    void on_slider_h_max_valueChanged(int value);

    void on_slider_s_max_valueChanged(int value);

    void on_slider_v_max_valueChanged(int value);

    void hsv_slot();


    void on_action_triggered();

    void on_comboBox_currentTextChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QString filepath;
    Formhsv* form;
};
#endif // MAINWINDOW_H
