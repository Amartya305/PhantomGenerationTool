#ifndef SETDIMENSION_H
#define SETDIMENSION_H

#include <QDialog>
namespace Ui {
class setdimension;
}

class setdimension : public QDialog
{
    Q_OBJECT

public:
    int xdim,ydim,zdim;
   // bool ***arr;
    explicit setdimension(QWidget *parent = 0);
    ~setdimension();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::setdimension *ui;
};
#endif
