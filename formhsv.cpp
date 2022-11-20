#include "formhsv.h"
#include "ui_formhsv.h"

Formhsv::Formhsv(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Formhsv)
{
    ui->setupUi(this);
    this->setWindowTitle("hsv");
    QImage image(":/new/prefix1/hsv.png");
    ui->label->setPixmap(QPixmap::fromImage(image));
}

Formhsv::~Formhsv()
{
    delete ui;
}
