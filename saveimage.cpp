#include "saveimage.h"
#include "ui_saveimage.h"

saveImage::saveImage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::saveImage)
{
    ui->setupUi(this);
}

saveImage::~saveImage()
{
    delete ui;
}

void saveImage::on_buttonBox_accepted()
{
    name=ui->textEdit->toPlainText();
}
