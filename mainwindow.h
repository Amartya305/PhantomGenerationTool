#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void create_sphere(int x,int y,int z,int r);

private slots:
    void on_Sphere_creator_clicked();
    void on_draw_image_clicked();

    void on_slider_z_valueChanged(int value);

    void on_Cylinder_creator_clicked();

    void on_write_image_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
