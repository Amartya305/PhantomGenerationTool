#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QList>
//#include<tiff.h>
//#include<tiffvers.h>
#include<tiffio.h>
//#include<tiffconf.vc.h>
//#include<tif_dir.h>
//#include<tiffiop.h>
//#include<tiffconf.wince.h>
//#include<tif_predict.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void *hdr;
    int Xdim,Ydim,Zdim,firstimgflag;
    unsigned short ***Arr,***temp_arr;
    bool mouse=false;     QByteArray filename;
    bool xzflag=false;
    bool yzflag=false;
    explicit MainWindow(QWidget *parent = 0);
    void create_sphere(int x0, int y0, int z0, int r);
    unsigned short readShort(FILE* );
    void histogram();
    void readTiff();
    void writeTiff();
    int factorial(int n);
    ~MainWindow();

private slots:

    void on_actionCreate_Image_triggered();

    void on_slider_z_valueChanged(int value);

    void on_slider_y_valueChanged(int value);

    void on_slider_x_valueChanged(int value);

    void Mouse_Current_Pos();

    void Mouse_Pressed();

    void Mouse_Left();

    void on_RightMouse_Pressed();

    void on_Wheel_rotated();

    void on_setSphereCenter_clicked();

    void on_SetCylendpt1_clicked();

    void on_SetCylendpt2_clicked();

    void on_createSphere_clicked();

    void on_create_cylinder_clicked();

    void on_SetCurcntrlpnt_clicked();

    void on_create_curve_clicked();

    void on_actionSave_Image_triggered();

    void on_actionUndo_triggered();

    void on_actionLoad_Image_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
