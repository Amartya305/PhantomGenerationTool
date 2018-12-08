#include "setdimension.h"
#include "ui_setdimension.h"
setdimension::setdimension(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setdimension)
{
    ui->setupUi(this);
    ui->sp_xdim->setMinimum(0);
    ui->sp_ydim->setMinimum(0);
    ui->sp_zdim->setMinimum(0);
    ui->sp_xdim->setMaximum(1000);
    ui->sp_ydim->setMaximum(1000);
    ui->sp_zdim->setMaximum(1000);
    ui->sp_xdim->setValue(100);
    ui->sp_ydim->setValue(100);
    ui->sp_zdim->setValue(100);
    //arr=NULL;
}

setdimension::~setdimension()
{
    delete ui;
}

void setdimension::on_buttonBox_accepted()
{
    if(ui->sp_xdim->value() && ui->sp_ydim->value() && ui->sp_zdim->value()){
                xdim=ui->sp_xdim->value();
                ydim=ui->sp_ydim->value();
                zdim=ui->sp_zdim->value();
               }

}
