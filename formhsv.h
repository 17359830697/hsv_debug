#ifndef FORMHSV_H
#define FORMHSV_H

#include <QWidget>

namespace Ui {
class Formhsv;
}

class Formhsv : public QWidget
{
    Q_OBJECT

public:
    explicit Formhsv(QWidget *parent = nullptr);
    ~Formhsv();

private:
    Ui::Formhsv *ui;
};

#endif // FORMHSV_H
