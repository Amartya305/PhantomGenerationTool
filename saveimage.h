#ifndef SAVEIMAGE_H
#define SAVEIMAGE_H

#include <QDialog>
#include <QString>
namespace Ui {
class saveImage;
}

class saveImage : public QDialog
{
    Q_OBJECT

public:
    QString name;
    explicit saveImage(QWidget *parent = 0);
    ~saveImage();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::saveImage *ui;
};

#endif // SAVEIMAGE_H
