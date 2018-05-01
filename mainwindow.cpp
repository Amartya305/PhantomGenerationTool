#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "global.h"
QImage imagexy(Xdim,Ydim,QImage::Format_RGB888);
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
   int i,j,k;
    ui->setupUi(this);
    for(i=0;i<Xdim;i++){
        for(j=0;j<Ydim;j++){
            imagexy.setPixel(i,j,qRgb(0,0,0));
        }
    }
    imagexy.setDevicePixelRatio(float(imagexy.width())/float(ui->Label->width()));
    ui->Label->setPixmap(QPixmap::fromImage(imagexy));
    ui->sp_x_in->setMaximum(Xdim);
    ui->sp_y_in->setMaximum(Ydim);
    ui->sp_z_in->setMaximum(Zdim);
    ui->sp_r_in->setMaximum(Zdim);
    ui->c_x1_in->setMaximum(Xdim);
    ui->c_y1_in->setMaximum(Ydim);
    ui->c_z1_in->setMaximum(Zdim);
    ui->c_x2_in->setMaximum(Xdim);
    ui->c_y2_in->setMaximum(Ydim);
    ui->c_z2_in->setMaximum(Zdim);
    ui->c_r_in->setMaximum(Zdim);
    ui->slider_z->setMaximum(Zdim);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::create_sphere(int x,int y,int z,int r){
    int radius_array[Zdim];
    int i,j,k,a;
    int r_temp;
    float temp;
    i=r;
    j=0;
    for(a=0;a<=i;a++){
        arr[x+a][y][z]=100;
        arr[x-a][y][z]=100;
        arr[x][y+a][z]=100;
        arr[x][y-a][z]=100;
    }
    while(i>j){
              temp=(i-0.5)*(i-0.5)+(j+1)*(j+1)-r*r;
              if(temp<0){
                  radius_array[i-1]=j;
                  j=j+1;
                   }
              else{
                  radius_array[i-1]=j;
                  i=i-1;
                  j=j+1;
                  }
    for(a=0;a<=i;a++){
        arr[x+a][y+j][z]=100;
        arr[x-a][y+j][z]=100;
        arr[x+a][y-j][z]=100;
        arr[x-a][y-j][z]=100;
        arr[x+j][y+a][z]=100;
        arr[x-j][y+a][z]=100;
        arr[x+j][y-a][z]=100;
        arr[x-j][y-a][z]=100;
    }
    }
    j=r;
    i=0;
    while(j>i){
              temp=(j-0.5)*(j-0.5)+(i+1)*(i+1)-r*r;
              if(temp<0){
                  radius_array[i]=j;
                  i=i+1;
              }
              else{

                  radius_array[i]=j;
                  j=j-1;
                  i=i+1;
              }

    }
    for(k=1;k<r;k++){
        r_temp=radius_array[k];
        i=r_temp;
        j=0;
        for(a=0;a<=i;a++){
            arr[x+a][y][z+k]=100;
            arr[x-a][y][z+k]=100;
            arr[x][y+a][z+k]=100;
            arr[x][y-a][z+k]=100;
            arr[x+a][y][z-k]=100;
            arr[x-a][y][z-k]=100;
            arr[x][y+a][z-k]=100;
            arr[x][y-a][z-k]=100;
        }
        while(i>j){
                  temp=(i-0.5)*(i-0.5)+(j+1)*(j+1)-r_temp*r_temp;
                  if(temp<0){
                      j=j+1;
                       }
                  else{
                      i=i-1;
                      j=j+1;
                      }
        for(a=0;a<=i;a++){
            arr[x+a][y+j][z+k]=100;
            arr[x-a][y+j][z+k]=100;
            arr[x+a][y-j][z+k]=100;
            arr[x-a][y-j][z+k]=100;
            arr[x+j][y+a][z+k]=100;
            arr[x-j][y+a][z+k]=100;
            arr[x+j][y-a][z+k]=100;
            arr[x-j][y-a][z+k]=100;
            arr[x+a][y+j][z-k]=100;
            arr[x-a][y+j][z-k]=100;
            arr[x+a][y-j][z-k]=100;
            arr[x-a][y-j][z-k]=100;
            arr[x+j][y+a][z-k]=100;
            arr[x-j][y+a][z-k]=100;
            arr[x+j][y-a][z-k]=100;
            arr[x-j][y-a][z-k]=100;
        }
      }
    }
 }

void MainWindow::on_Sphere_creator_clicked()
{
    create_sphere(ui->sp_x_in->value(),ui->sp_y_in->value(),ui->sp_z_in->value(),ui->sp_r_in->value());
}

void MainWindow::on_draw_image_clicked()
{
    int i,j;
    ui->slider_z->setValue(50);
    ui->z_value->setValue(50);
    for(i=0;i<Xdim;i++){
        for(j=0;j<Ydim;j++){
            if(arr[i][j][50]==100){
                 imagexy.setPixel(i,j,qRgb(255,255,255));
            }
        }
    }
    imagexy.setDevicePixelRatio(float(imagexy.width())/float(ui->Label->width()));
    ui->Label->setPixmap(QPixmap::fromImage(imagexy));
  }


void MainWindow::on_slider_z_valueChanged(int value)
{
    int i,j;
    for(i=0;i<Xdim;i++){
        for(j=0;j<Ydim;j++){
            if(arr[i][j][value]==100){
                 imagexy.setPixel(i,j,qRgb(255,255,255));
            }
            else imagexy.setPixel(i,j,qRgb(0,0,0));
        }
    }
    imagexy.setDevicePixelRatio(float(imagexy.width())/float(ui->Label->width()));
    ui->Label->setPixmap(QPixmap::fromImage(imagexy));
}

void MainWindow::on_Cylinder_creator_clicked()
{
    int x1,y1,z1,x2,y2,z2,r,i;
    int dx, dy, dz, l, m, n, x_inc, y_inc, z_inc, err_1, err_2, dx2, dy2, dz2;
    int point[3];
    x1=ui->c_x1_in->value();
    y1=ui->c_y1_in->value();
    z1=ui->c_z1_in->value();
    x2=ui->c_x2_in->value();
    y2=ui->c_y2_in->value();
    z2=ui->c_z2_in->value();
    r=ui->c_r_in->value();
    point[0] = x1;
    point[1] = y1;
    point[2] = z1;
    dx = x2 - x1;
    dy = y2 - y1;
    dz = z2 - z1;
    x_inc = (dx < 0) ? -1 : 1;
    l = abs(dx);
    y_inc = (dy < 0) ? -1 : 1;
    m = abs(dy);
    z_inc = (dz < 0) ? -1 : 1;
    n = abs(dz);
    dx2 = l << 1;
    dy2 = m << 1;
    dz2 = n << 1;

        if ((l >= m) && (l >= n)) {
            err_1 = dy2 - l;
            err_2 = dz2 - l;
            for (i = 0; i < l; i++) {
                create_sphere(point[0], point[1], point[2],r);
                if(err_1>0){
                    point[1] += y_inc;
                    err_1 -= dx2;
                }
                if (err_2 > 0) {
                    point[2] += z_inc;
                    err_2 -= dx2;
                }
                err_1 += dy2;
                err_2 += dz2;
                point[0] += x_inc;
            }
         }
        else if((m >= l) && (m >= n)) {
            err_1 = dx2 - m;
            err_2 = dz2 - m;
            for (i = 0; i < m; i++) {
                create_sphere(point[0], point[1], point[2],r);
                if (err_1 > 0) {
                    point[0] += x_inc;
                    err_1 -= dy2;
                }
                if (err_2 > 0) {
                    point[2] += z_inc;
                    err_2 -= dy2;
                }
                err_1 += dx2;
                err_2 += dz2;
                point[1] += y_inc;
            }
        }
        else {
            err_1 = dy2 - n;
            err_2 = dx2 - n;
            for (i = 0; i < n; i++) {
                create_sphere(point[0], point[1], point[2],r);
                if (err_1 > 0) {
                    point[1] += y_inc;
                    err_1 -= dz2;
                }
                if (err_2 > 0) {
                    point[0] += x_inc;
                    err_2 -= dz2;
                }
                err_1 += dy2;
                err_2 += dx2;
                point[2] += z_inc;
            }
        }
    }
void MainWindow::on_write_image_clicked()
{
    int i,j,k;
    unsigned short *ptr;
    ptr=new unsigned short();
    *ptr=0;
    FILE *fo;
    fo=fopen("MyImage","wb+");
    //ui->test_label->setText(QString("%1,").arg(*ptr));
    for(k=0;k<Zdim;k++){
        for(j=0;j<Ydim;j++){
            for(i=0;i<Xdim;i++){
                if(arr[i][j][k]==100){
                    *ptr=100;
                    fwrite(ptr,1,1,fo);
                    //ui->test_label->setText(QString("%1,").arg(*ptr));
                }
                else{
                    fwrite(ptr,1,1,fo);
                   // ui->test_label->setText(QString("%1,").arg(*ptr));
                }
               *ptr=0;
            }
        }
    }
    fclose(fo);
}
