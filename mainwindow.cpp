#include <QFileDialog>
#include  <QByteArray>
#include <QString>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "setdimension.h"
#include "mousetracker.h"
#include "saveimage.h"
struct vec3d {
    int x, y ,z;
    vec3d(int x, int y,int z) : x(x), y(y) ,z(z) {}
};

QList<vec3d> vec3;

QImage *xycursor;
QImage *xzcursor;
QImage *yzcursor;

QImage *imagexy;
QImage *imagexz;
QImage *imageyz;

int x_pos,y_pos,z_pos;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    firstimgflag=0;

    ui->label_xy->setStyleSheet("QLabel{background-color : black}");
    ui->label_xz->setStyleSheet("QLabel{background-color :black}");
    ui->label_yz->setStyleSheet("QLabel{background-color : black}");
    ui->label_3d->setStyleSheet("QLabel{background-color : black}");

    connect(ui->xy_cursor,SIGNAL(Mouse_Pos()),this,SLOT(Mouse_Current_Pos()));
    connect(ui->xy_cursor,SIGNAL(Mouse_Pressed()),this,SLOT(Mouse_Pressed()));
    connect(ui->xy_cursor,SIGNAL(Mouse_Left()),this,SLOT(Mouse_Left()));
    connect(ui->xy_cursor,SIGNAL(Wheel_Moved()),this,SLOT(on_Wheel_rotated()));
    connect(ui->xy_cursor,SIGNAL(RightMouse_Pressed()),this,SLOT(on_RightMouse_Pressed()));

    connect(ui->xz_cursor,SIGNAL(Mouse_Pos()),this,SLOT(Mouse_Current_Pos()));
    connect(ui->xz_cursor,SIGNAL(Mouse_Pressed()),this,SLOT(Mouse_Pressed()));
    connect(ui->xz_cursor,SIGNAL(Mouse_Left()),this,SLOT(Mouse_Left()));
    connect(ui->xz_cursor,SIGNAL(Wheel_Moved()),this,SLOT(on_Wheel_rotated()));

    connect(ui->yz_cursor,SIGNAL(Mouse_Pos()),this,SLOT(Mouse_Current_Pos()));
    connect(ui->yz_cursor,SIGNAL(Mouse_Pressed()),this,SLOT(Mouse_Pressed()));
    connect(ui->yz_cursor,SIGNAL(Mouse_Left()),this,SLOT(Mouse_Left()));
    connect(ui->yz_cursor,SIGNAL(Wheel_Moved()),this,SLOT(on_Wheel_rotated()));

    ui->slider_x->setEnabled(false);
    ui->slider_y->setEnabled(false);
    ui->slider_z->setEnabled(false);
    ui->x_cur->setEnabled(false);
    ui->y_cur->setEnabled(false);
    ui->z_cur->setEnabled(false);

    QPalette pal = palette();
    pal.setColor(QPalette::Background, qRgb(200,200,200));
    ui->SphereBox->setAutoFillBackground(true);
    ui->SphereBox->setPalette(pal);
    ui->CylinderBox->setAutoFillBackground(true);
    ui->CylinderBox->setPalette(pal);
    ui->CurveBox->setAutoFillBackground(true);
    ui->CurveBox->setPalette(pal);
    ui->groupBox->setAutoFillBackground(true);
    ui->groupBox->setPalette(pal);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionCreate_Image_triggered()
{

  if(firstimgflag){

    for(int i=0;i<Xdim;i++){
        for(int j=0;j<Ydim;j++){
            delete[] Arr[i][j];
           }
        delete[] Arr[i];
       }
    delete[] Arr;

    for(int i=0;i<Xdim;i++){
        for(int j=0;j<Ydim;j++){
            delete[] temp_arr[i][j];
           }
        delete[] temp_arr[i];
       }
    delete[] temp_arr;

   }
  setdimension setdim_obj1;
  setdim_obj1.setModal(true);
  setdim_obj1.exec();

  Xdim=setdim_obj1.xdim;
  Ydim=setdim_obj1.ydim;
  Zdim=setdim_obj1.zdim;

  delete imagexy;
  delete imagexz;
  delete imageyz;
  delete xycursor;
  delete xzcursor;
  delete yzcursor;

   Arr= new unsigned short**[Xdim];
   for(int i=0;i<Xdim;i++){
       Arr[i]=new unsigned short*[Ydim];
       for(int j=0;j<Ydim;j++){
           Arr[i][j]=new unsigned short[Zdim];
       }
   }

   temp_arr= new unsigned short**[Xdim];
        for(int i=0;i<Xdim;i++){
            temp_arr[i]=new unsigned short*[Ydim];
            for(int j=0;j<Ydim;j++){
                temp_arr[i][j]=new unsigned short[Zdim];
            }
    }
    firstimgflag=1;

    for(int i=0;i<Xdim;i++){
        for(int j=0;j<Ydim;j++){
            for(int k=0;k<Zdim;k++){
                Arr[i][j][k]=0;
                temp_arr[i][j][k]=0;
            }
        }
    }    


    ui->xy_0->setText("0");
    ui->xz_0->setText("0");
    ui->yz_0->setText("0");


    ui->xy_xmax->setText(QString::number(Xdim));
    ui->xy_ymax->setText(QString::number(Ydim));
    ui->xz_xmax->setText(QString::number(Xdim));
    ui->xz_zmax->setText(QString::number(Zdim));
    ui->yz_ymax->setText(QString::number(Ydim));
    ui->yz_zmax->setText(QString::number(Zdim));


    if(Xdim>Ydim) xycursor=new QImage(300,(Ydim*300)/Xdim,QImage::Format_ARGB32);
    else xycursor=new QImage((Xdim*300)/Ydim,300,QImage::Format_ARGB32);
    if(Xdim>Zdim) xzcursor=new QImage(300,(Zdim*300)/Xdim,QImage::Format_ARGB32);
    else xzcursor=new QImage((Xdim*300)/Zdim,300,QImage::Format_ARGB32);
    if(Ydim>Zdim) yzcursor=new QImage(300,(Zdim*300)/Ydim,QImage::Format_ARGB32);
    else yzcursor=new QImage((Ydim*300)/Zdim,300,QImage::Format_ARGB32);

    imagexy=new QImage(Xdim,Ydim,QImage::Format_RGB888);
    imagexz=new QImage(Xdim,Zdim,QImage::Format_RGB888);
    imageyz=new QImage(Ydim,Zdim,QImage::Format_RGB888);

     for(int i=1;i<xycursor->width();i+=2) xycursor->setPixel(i,xycursor->height()/2,qRgb(0,255,255));
     for(int j=1;j<xycursor->height();j+=2) xycursor->setPixel(xycursor->width()/2,j,qRgb(0,255,255));
     for(int i=1;i<xzcursor->width();i+=2) xzcursor->setPixel(i,xzcursor->height()/2,qRgb(255,0,255));
     for(int k=1;k<xzcursor->height();k+=2) xzcursor->setPixel(xzcursor->width()/2,k,qRgb(255,0,255));
     for(int j=1;j<yzcursor->width();j+=2) yzcursor->setPixel(j,yzcursor->height()/2,qRgb(255,255,0));
     for(int k=1;k<yzcursor->height();k+=2) yzcursor->setPixel(yzcursor->width()/2,k,qRgb(255,255,0));

     ui->xy_cursor->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
     ui->xy_cursor->setPixmap(QPixmap::fromImage(*xycursor));
     ui->xz_cursor->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
     ui->xz_cursor->setPixmap(QPixmap::fromImage(*xzcursor));
     ui->yz_cursor->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
     ui->yz_cursor->setPixmap(QPixmap::fromImage(*yzcursor));

     for(int i=0;i<Xdim;i++){
         for(int j=0;j<Ydim;j++){
             imagexy->setPixel(i,j,qRgb(0,0,0));
         }
     }

     for(int i=0;i<Xdim;i++){
         for(int k=0;k<Zdim;k++){
             imagexz->setPixel(i,k,qRgb(0,0,0));
         }
     }

     for(int i=0;i<Xdim;i++){
         for(int j=0;j<Ydim;j++){
             imagexy->setPixel(i,j,qRgb(0,0,0));
         }
     }

     for(int j=0;j<Ydim;j++){
         for(int k=0;k<Zdim;k++){
             imageyz->setPixel(j,k,qRgb(0,0,0));
         }
     }

     ui->label_xy->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
     ui->label_xy->setPixmap(QPixmap::fromImage(imagexy->scaled(xycursor->width(),xycursor->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation)));
     ui->label_xz->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
     ui->label_xz->setPixmap(QPixmap::fromImage(imagexz->scaled(xzcursor->width(),xzcursor->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation)));
     ui->label_yz->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
     ui->label_yz->setPixmap(QPixmap::fromImage(imageyz->scaled(yzcursor->width(),yzcursor->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation)));


     ui->slider_x->setEnabled(true);
     ui->slider_y->setEnabled(true);
     ui->slider_z->setEnabled(true);

     ui->x_cur->setEnabled(true);
     ui->y_cur->setEnabled(true);
     ui->z_cur->setEnabled(true);



      ui->x_cur->setMaximum(Xdim-1);
      ui->y_cur->setMaximum(Ydim-1);
      ui->z_cur->setMaximum(Zdim-1);

      ui->slider_x->setMaximum(Xdim-1);
      ui->slider_y->setMaximum(Ydim-1);
      ui->slider_z->setMaximum(Zdim-1);

      ui->sp_x->setMaximum(Xdim-1);
      ui->sp_y->setMaximum(Ydim-1);
      ui->sp_z->setMaximum(Zdim-1);
      ui->sp_r->setMaximum(Zdim-1);

      ui->cy_x1->setMaximum(Xdim-1);
      ui->cy_y1->setMaximum(Ydim-1);
      ui->cy_z1->setMaximum(Zdim-1);
      ui->cy_x2->setMaximum(Xdim-1);
      ui->cy_y2->setMaximum(Ydim-1);
      ui->cy_z2->setMaximum(Zdim-1);
      ui->cy_r->setMaximum(Zdim-1);

      x_pos=Xdim/2;
      y_pos=Ydim/2;
      z_pos=Zdim/2;

     ui->x_cur->setValue(x_pos);
      ui->y_cur->setValue(y_pos);
     ui->z_cur->setValue(z_pos);
   // qDebug()<<x_pos<<" "<<y_pos<<" "<<z_pos<<endl;

     ui->slider_x->setValue(x_pos);
      ui->slider_y->setValue(y_pos);
      ui->slider_z->setValue(z_pos);


     // qDebug()<<Xdim<<" "<<Ydim<<" "<<Zdim<<endl;

      mouse=true;
      ui->listWidget->clear();
      vec3.clear();
}

void MainWindow::on_slider_z_valueChanged(int value)
{
    z_pos=value;
    for(int i=0;i<Xdim;i++){
        for(int j=0;j<Ydim;j++){
            if(Arr[i][j][value]){
                 imagexy->setPixel(i,j,qRgb(Arr[i][j][value],Arr[i][j][value],Arr[i][j][value]));
            }
            else imagexy->setPixel(i,j,qRgb(0,0,0));
        }
    }

    ui->label_xy->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->label_xy->setPixmap(QPixmap::fromImage(imagexy->scaled(xycursor->width(),xycursor->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation)));

    for(int i=0;i<xzcursor->width();i++){
        for(int j=0;j<xzcursor->height();j++){
             xzcursor->setPixel(i,j,qRgba(0,0,0,0));
            }
    }

    for(int i=0;i<yzcursor->width();i++){
        for(int j=0;j<yzcursor->height();j++){
             yzcursor->setPixel(i,j,qRgba(0,0,0,0));
            }
    }

    for(int i=1;i<xzcursor->width();i+=2) xzcursor->setPixel(i,(z_pos*xzcursor->height())/Zdim,qRgb(255,0,255));
    for(int k=1;k<xzcursor->height();k+=2) xzcursor->setPixel((x_pos*xzcursor->width())/Xdim,k,qRgb(255,0,255));
    for(int j=1;j<yzcursor->width();j+=2) yzcursor->setPixel(j,(z_pos*yzcursor->height())/Zdim,qRgb(255,255,0));
    for(int k=1;k<yzcursor->height();k+=2) yzcursor->setPixel((y_pos*yzcursor->width())/Ydim,k,qRgb(255,255,0));

    ui->xz_cursor->setPixmap(QPixmap::fromImage(*xzcursor));
    ui->yz_cursor->setPixmap(QPixmap::fromImage(*yzcursor));
}

void MainWindow::on_slider_y_valueChanged(int value)
{
   y_pos=value;

    for(int i=0;i<Xdim;i++){
        for(int k=0;k<Zdim;k++){
            if(Arr[i][value][k]){
                 imagexz->setPixel(i,k,qRgb(Arr[i][value][k],Arr[i][value][k],Arr[i][value][k]));
            }
            else imagexz->setPixel(i,k,qRgb(0,0,0));
        }
    }

   ui->label_xz->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
   ui->label_xz->setPixmap(QPixmap::fromImage(imagexz->scaled(xzcursor->width(),xzcursor->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation)));

    for(int i=0;i<yzcursor->width();i++){
        for(int j=0;j<yzcursor->height();j++){
             yzcursor->setPixel(i,j,qRgba(0,0,0,0));
            }
    }

    for(int i=0;i<xycursor->width();i++){
        for(int j=0;j<xycursor->height();j++){
             xycursor->setPixel(i,j,qRgba(0,0,0,0));
            }
    }

    for(int i=1;i<xycursor->width();i+=2) xycursor->setPixel(i,(y_pos*xycursor->height())/Ydim,qRgb(0,255,255));
    for(int j=1;j<xycursor->height();j+=2) xycursor->setPixel((x_pos*xycursor->width())/Xdim,j,qRgb(0,255,255));
    for(int j=1;j<yzcursor->width();j+=2) yzcursor->setPixel(j,(z_pos*yzcursor->height())/Zdim,qRgb(255,255,0));
    for(int k=1;k<yzcursor->height();k+=2) yzcursor->setPixel((y_pos*yzcursor->width())/Ydim,k,qRgb(255,255,0));

    ui->xy_cursor->setPixmap(QPixmap::fromImage(*xycursor));
    ui->yz_cursor->setPixmap(QPixmap::fromImage(*yzcursor));
}

void MainWindow::on_slider_x_valueChanged(int value)
{
    x_pos=value;

    for(int j=0;j<Ydim;j++){
        for(int k=0;k<Zdim;k++){
            if(Arr[value][j][k]){
                 imageyz->setPixel(j,k,qRgb(Arr[value][j][k],Arr[value][j][k],Arr[value][j][k]));
            }
            else imageyz->setPixel(j,k,qRgb(0,0,0));
        }
    }

    ui->label_yz->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->label_yz->setPixmap(QPixmap::fromImage(imageyz->scaled(yzcursor->width(),yzcursor->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation)));

    for(int i=0;i<xzcursor->width();i++){
        for(int j=0;j<xzcursor->height();j++){
             xzcursor->setPixel(i,j,qRgba(0,0,0,0));
            }
    }

    for(int i=0;i<xycursor->width();i++){
        for(int j=0;j<xycursor->height();j++){
             xycursor->setPixel(i,j,qRgba(0,0,0,0));
            }
    }

    for(int i=1;i<xycursor->width();i+=2) xycursor->setPixel(i,(y_pos*xycursor->height())/Ydim,qRgb(0,255,255));
    for(int j=1;j<xycursor->height();j+=2) xycursor->setPixel((x_pos*xycursor->width())/Xdim,j,qRgb(0,255,255));
    for(int j=1;j<xzcursor->width();j+=2) xzcursor->setPixel(j,(z_pos*xzcursor->height())/Zdim,qRgb(255,0,255));
    for(int k=1;k<xzcursor->height();k+=2) xzcursor->setPixel((x_pos*xzcursor->width())/Xdim,k,qRgb(255,0,255));

    ui->xy_cursor->setPixmap(QPixmap::fromImage(*xycursor));
    ui->xz_cursor->setPixmap(QPixmap::fromImage(*xzcursor));
}

void MainWindow::Mouse_Current_Pos()
{

 if(mouse){

    QObject* obj = sender();

    if(obj->objectName()=="xy_cursor"){

        if(ui->xy_cursor->x<150-xycursor->width()/2) ui->slider_x->setValue(0);
        else if(ui->xy_cursor->x>150+xycursor->width()/2) ui->slider_x->setValue(Xdim-1);
        else{
             ui->slider_x->setValue(((ui->xy_cursor->x-(150-xycursor->width()/2))*Xdim)/xycursor->width());
        }


        if(ui->xy_cursor->y<150-xycursor->height()/2)ui->slider_y->setValue(0);
        else if(ui->xy_cursor->y>150+xycursor->height()/2) ui->slider_y->setValue(Ydim-1);
        else{
            ui->slider_y->setValue(((ui->xy_cursor->y-(150-xycursor->height()/2))*Ydim)/xycursor->height());
        }

    }
    if(obj->objectName()=="xz_cursor"){

        if(ui->xz_cursor->x<150-xzcursor->width()/2)ui->slider_x->setValue(0);
        else if(ui->xz_cursor->x>150+xzcursor->width()/2) ui->slider_x->setValue(Xdim-1);
        else{
           ui->slider_x->setValue(((ui->xz_cursor->x-(150-xzcursor->width()/2))*Xdim)/xzcursor->width());

        }


        if(ui->xz_cursor->y<150-xzcursor->height()/2)ui->slider_z->setValue(0);
        else if(ui->xz_cursor->y>150+xzcursor->height()/2)ui->slider_z->setValue(Zdim-1);
        else{
           ui->slider_z->setValue(((ui->xz_cursor->y-(150-xzcursor->height()/2))*Zdim)/xzcursor->height());
        }

    }
    if(obj->objectName()=="yz_cursor"){

        if(ui->yz_cursor->x<150-yzcursor->width()/2) ui->slider_y->setValue(0);
        else if(ui->yz_cursor->x>150+yzcursor->width()/2)  ui->slider_y->setValue(Ydim-1);
        else{
          ui->slider_y->setValue(((ui->yz_cursor->x-(150-yzcursor->width()/2))*Ydim)/yzcursor->width());
        }


        if(ui->yz_cursor->y<150-yzcursor->height()/2)ui->slider_z->setValue(0);
        else if(ui->yz_cursor->y>150+yzcursor->height()/2)ui->slider_z->setValue(Zdim-1);
        else{
             ui->slider_z->setValue(((ui->yz_cursor->y-(150-yzcursor->height()/2))*Zdim)/yzcursor->height());
        }

    }
    }
}

void MainWindow::Mouse_Pressed()
{
    Mouse_Current_Pos();
}

void MainWindow::Mouse_Left()
{

}

void MainWindow::on_RightMouse_Pressed()
{

}

void MainWindow::on_Wheel_rotated()
{
    if(mouse){

        QObject* obj = sender();

        if(obj->objectName()=="xy_cursor"){
            ui->slider_z->setValue(ui->slider_z->value()+ui->xy_cursor->steps);
        }

        if(obj->objectName()=="xz_cursor"){
            ui->slider_y->setValue(ui->slider_y->value()+ui->xz_cursor->steps);
        }

        if(obj->objectName()=="yz_cursor"){
            ui->slider_x->setValue(ui->slider_x->value()+ui->yz_cursor->steps);
        }
    }
}

void MainWindow::on_setSphereCenter_clicked()
{
    ui->sp_x->setValue(ui->x_cur->value());
    ui->sp_y->setValue(ui->y_cur->value());
    ui->sp_z->setValue(ui->z_cur->value());
}

void MainWindow::on_SetCylendpt1_clicked()
{
    ui->cy_x1->setValue(ui->x_cur->value());
    ui->cy_y1->setValue(ui->y_cur->value());
    ui->cy_z1->setValue(ui->z_cur->value());
}

void MainWindow::on_SetCylendpt2_clicked()
{
    ui->cy_x2->setValue(ui->x_cur->value());
    ui->cy_y2->setValue(ui->y_cur->value());
    ui->cy_z2->setValue(ui->z_cur->value());
}
void MainWindow::create_sphere(int x,int y,int z,int r){
    int *radius_array=new int[Zdim];
    int i,j,k,a;
    int r_temp;
    float temp;
    i=r;
    j=0;
    for(a=0;a<=i;a++){
        Arr[x+a][y][z]=255;
        Arr[x-a][y][z]=255;
        Arr[x][y+a][z]=255;
        Arr[x][y-a][z]=255;

        temp_arr[x+a][y][z]=255;
        temp_arr[x-a][y][z]=255;
        temp_arr[x][y+a][z]=255;
        temp_arr[x][y-a][z]=255;
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
        Arr[x+a][y+j][z]=255;
        Arr[x-a][y+j][z]=255;
        Arr[x+a][y-j][z]=255;
        Arr[x-a][y-j][z]=255;
        Arr[x+j][y+a][z]=255;
        Arr[x-j][y+a][z]=255;
        Arr[x+j][y-a][z]=255;
        Arr[x-j][y-a][z]=255;

        temp_arr[x+a][y+j][z]=255;
        temp_arr[x-a][y+j][z]=255;
        temp_arr[x+a][y-j][z]=255;
        temp_arr[x-a][y-j][z]=255;
        temp_arr[x+j][y+a][z]=255;
        temp_arr[x-j][y+a][z]=255;
        temp_arr[x+j][y-a][z]=255;
        temp_arr[x-j][y-a][z]=255;
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
            Arr[x+a][y][z+k]=255;
            Arr[x-a][y][z+k]=255;
            Arr[x][y+a][z+k]=255;
            Arr[x][y-a][z+k]=255;
            Arr[x+a][y][z-k]=255;
            Arr[x-a][y][z-k]=255;
            Arr[x][y+a][z-k]=255;
            Arr[x][y-a][z-k]=255;

            temp_arr[x+a][y][z+k]=255;
            temp_arr[x-a][y][z+k]=255;
            temp_arr[x][y+a][z+k]=255;
            temp_arr[x][y-a][z+k]=255;
            temp_arr[x+a][y][z-k]=255;
            temp_arr[x-a][y][z-k]=255;
            temp_arr[x][y+a][z-k]=255;
            temp_arr[x][y-a][z-k]=255;
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
            Arr[x+a][y+j][z+k]=255;
            Arr[x-a][y+j][z+k]=255;
            Arr[x+a][y-j][z+k]=255;
            Arr[x-a][y-j][z+k]=255;
            Arr[x+j][y+a][z+k]=255;
            Arr[x-j][y+a][z+k]=255;
            Arr[x+j][y-a][z+k]=255;
            Arr[x-j][y-a][z+k]=255;
            Arr[x+a][y+j][z-k]=255;
            Arr[x-a][y+j][z-k]=255;
            Arr[x+a][y-j][z-k]=255;
            Arr[x-a][y-j][z-k]=255;
            Arr[x+j][y+a][z-k]=255;
            Arr[x-j][y+a][z-k]=255;
            Arr[x+j][y-a][z-k]=255;
            Arr[x-j][y-a][z-k]=255;

            temp_arr[x+a][y+j][z+k]=255;
            temp_arr[x-a][y+j][z+k]=255;
            temp_arr[x+a][y-j][z+k]=255;
            temp_arr[x-a][y-j][z+k]=255;
            temp_arr[x+j][y+a][z+k]=255;
            temp_arr[x-j][y+a][z+k]=255;
            temp_arr[x+j][y-a][z+k]=255;
            temp_arr[x-j][y-a][z+k]=255;
            temp_arr[x+a][y+j][z-k]=255;
            temp_arr[x-a][y+j][z-k]=255;
            temp_arr[x+a][y-j][z-k]=255;
            temp_arr[x-a][y-j][z-k]=255;
            temp_arr[x+j][y+a][z-k]=255;
            temp_arr[x-j][y+a][z-k]=255;
            temp_arr[x+j][y-a][z-k]=255;
            temp_arr[x-j][y-a][z-k]=255;
        }
      }
    }
 }
/*void MainWindow::create_sphere(int x0,int y0,int z0,int r){
int x,y,z,xa,ya,za,xb,yb,zb,xr,yr,zr,xx,yy,zz,rr=r*r,n=Xdim;
// bounding box
xa=x0-r; if (xa<0) xa=0; xb=x0+r; if (xb>n) xb=n;
ya=y0-r; if (ya<0) ya=0; yb=y0+r; if (yb>n) yb=n;
za=z0-r; if (za<0) za=0; zb=z0+r; if (zb>n) zb=n;
// project xy plane
for (x=xa,xr=x-x0,xx=xr*xr;x<xb;x++,xr++,xx=xr*xr)
 for (y=ya,yr=y-y0,yy=yr*yr;y<yb;y++,yr++,yy=yr*yr)
    {
    zz=rr-xx-yy; if (zz<0) continue; zr=sqrt(zz);
    z=z0-zr; if ((z>0)&&(z<n)) Arr[x][y][z]=255;
    z=z0+zr; if ((z>0)&&(z<n)) Arr[x][y][z]=255;
    }
// project xz plane
for (x=xa,xr=x-x0,xx=xr*xr;x<xb;x++,xr++,xx=xr*xr)
 for (z=za,zr=z-z0,zz=zr*zr;z<zb;z++,zr++,zz=zr*zr)
    {
    yy=rr-xx-zz; if (yy<0) continue; yr=sqrt(yy);
    y=y0-yr; if ((y>0)&&(y<n)) Arr[x][y][z]=255;
    y=y0+yr; if ((y>0)&&(y<n)) Arr[x][y][z]=255;
    }
// project yz plane
for (y=ya,yr=y-y0,yy=yr*yr;y<yb;y++,yr++,yy=yr*yr)
 for (z=za,zr=z-z0,zz=zr*zr;z<zb;z++,zr++,zz=zr*zr)
    {
    xx=rr-zz-yy; if (xx<0) continue; xr=sqrt(xx);
    x=x0-xr; if ((x>0)&&(x<n)) Arr[x][y][z]=255;
    x=x0+xr; if ((x>0)&&(x<n)) Arr[x][y][z]=255;
    }
}*/
void MainWindow::on_createSphere_clicked()
{
    for(int i=0;i<Xdim;i++){
        for(int j=0;j<Ydim;j++){
            for(int k=0;k<Zdim;k++){
                temp_arr[i][j][k]=0;
            }
        }
    }
     create_sphere(ui->sp_x->value(),ui->sp_y->value(),ui->sp_z->value(),ui->sp_r->value());
     on_slider_x_valueChanged(ui->sp_x->value());
     on_slider_y_valueChanged(ui->sp_y->value());
     on_slider_z_valueChanged(ui->sp_z->value());

}

void MainWindow::on_create_cylinder_clicked()
{
    int x1,y1,z1,x2,y2,z2,r,i;
    int dx, dy, dz, l, m, n, x_inc, y_inc, z_inc, err_1, err_2, dx2, dy2, dz2;
    int point[3];
    for(int i=0;i<Xdim;i++){
        for(int j=0;j<Ydim;j++){
            for(int k=0;k<Zdim;k++){
                temp_arr[i][j][k]=0;
            }
        }
    }
    x1=ui->cy_x1->value();
    y1=ui->cy_y1->value();
    z1=ui->cy_z1->value();
    x2=ui->cy_x2->value();
    y2=ui->cy_y2->value();
    z2=ui->cy_z2->value();
    r=ui->cy_r->value();
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
        on_slider_x_valueChanged(ui->cy_x2->value());
        on_slider_y_valueChanged(ui->cy_y2->value());
        on_slider_z_valueChanged(ui->cy_z2->value());
}

void MainWindow::on_SetCurcntrlpnt_clicked()
{
    vec3d tmp(ui->x_cur->value(),ui->y_cur->value(),ui->z_cur->value());
    vec3.append(tmp);
    ui->listWidget->addItem(QString("X=%1,Y=%2,Z=%3").arg(ui->x_cur->value()).arg(ui->y_cur->value()).arg(ui->z_cur->value()));
}
int MainWindow:: factorial(int n)
{
    if(n > 1)
        return n * factorial(n - 1);
    else
        return 1;
}

void MainWindow::on_create_curve_clicked()
{
    int n=vec3.length()-1,i;
    int xt,yt,zt;
    for(int i=0;i<Xdim;i++){
        for(int j=0;j<Ydim;j++){
            for(int k=0;k<Zdim;k++){
                temp_arr[i][j][k]=0;
            }
        }
    }
    for(double t=0;t<=1;t=t+0.01){
        xt=0;
        yt=0;
        zt=0;
        i=0;
        while(i<=n){
            xt=xt+(factorial(n)/(factorial(n-i)*factorial(i)))*pow(1-t,n-i)*pow(t,i)*vec3[i].x;
            yt=yt+(factorial(n)/(factorial(n-i)*factorial(i)))*pow(1-t,n-i)*pow(t,i)*vec3[i].y;
            zt=zt+(factorial(n)/(factorial(n-i)*factorial(i)))*pow(1-t,n-i)*pow(t,i)*vec3[i].z;
            i++;
        }
        create_sphere(xt,yt,zt,ui->curv_r->value());
    }
    on_slider_x_valueChanged(vec3.last().x);
    on_slider_y_valueChanged(vec3.last().y);
    on_slider_z_valueChanged(vec3.last().z);
    ui->listWidget->clear();
    vec3.clear();

}
void MainWindow::on_actionUndo_triggered()
{
    for(int i=0;i<Xdim;i++){
        for(int j=0;j<Ydim;j++){
            for(int k=0;k<Zdim;k++){
                if(temp_arr[i][j][k]){
                    Arr[i][j][k]=0;
                }
            }
        }
    }
    for(int i=0;i<Xdim;i++){
        for(int j=0;j<Ydim;j++){
            for(int k=0;k<Zdim;k++){
                temp_arr[i][j][k]=0;
            }
        }
    }
     on_slider_x_valueChanged(Xdim/2);
     on_slider_y_valueChanged(Ydim/2);
     on_slider_z_valueChanged(Zdim/2);
}
void MainWindow::on_actionSave_Image_triggered()
{
    /*int i,j,k;
    unsigned short *ptr;
    ptr=new unsigned short();
    *ptr=0;
    FILE *fo;
   saveImage s1;
    s1.setModal(true);
    s1.exec();
    const char *str;
    QString path=s1.name;
    QByteArray ba;
    ba = path.toLatin1();
    str = ba.data();
    fo=fopen(str,"wb+");
    //ui->test_label->setText(QString("%1,").arg(*ptr));
    for(k=0;k<Zdim;k++){
        for(j=0;j<Ydim;j++){
            for(i=0;i<Xdim;i++){
                if(Arr[i][j][k]){
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
    fclose(fo);*/
    QString temp;
    temp=QFileDialog::getSaveFileName(this,tr("Open File"), "",
                                      tr("Analyze Images (*.hdr);;MultiPage tiff Images (*.tif)"));
    QByteArray qb = temp.toLatin1();
    filename =  qb.data();
    if(filename.endsWith(".hdr"));
    if(filename.endsWith(".tif")) writeTiff();
}



void MainWindow::on_actionLoad_Image_triggered()
{
    QString temp;
    temp=QFileDialog::getOpenFileName(this,tr("Open File"), "",
                                      tr("Analyze Images (*.hdr);;MultiPage tiff Images (*.tif)"));
    QByteArray qb = temp.toLatin1();
    filename =  qb.data();

    if(firstimgflag){
     for(int i=0;i<Xdim;i++){
         for(int j=0;j<Ydim;j++){
             delete[] Arr[i][j];
            }
         delete[] Arr[i];
        }
     delete[] Arr;

     for(int i=0;i<Xdim;i++){
         for(int j=0;j<Ydim;j++){
             delete[] temp_arr[i][j];
            }
         delete[] temp_arr[i];
        }
     delete[] temp_arr;
    }

    if(filename.endsWith(".hdr"))histogram();
    if(filename.endsWith(".tif")) readTiff();

    ui->xy_0->setText("0");
    ui->xz_0->setText("0");
    ui->yz_0->setText("0");
    ui->xy_xmax->setText(QString::number(Xdim));
    ui->xy_ymax->setText(QString::number(Ydim));
    ui->xz_xmax->setText(QString::number(Xdim));
    ui->xz_zmax->setText(QString::number(Zdim));
    ui->yz_ymax->setText(QString::number(Ydim));
    ui->yz_zmax->setText(QString::number(Zdim));


    if(Xdim>Ydim) xycursor=new QImage(300,(Ydim*300)/Xdim,QImage::Format_ARGB32);
    else xycursor=new QImage((Xdim*300)/Ydim,300,QImage::Format_ARGB32);
    if(Xdim>Zdim) xzcursor=new QImage(300,(Zdim*300)/Xdim,QImage::Format_ARGB32);
    else xzcursor=new QImage((Xdim*300)/Zdim,300,QImage::Format_ARGB32);
    if(Ydim>Zdim) yzcursor=new QImage(300,(Zdim*300)/Ydim,QImage::Format_ARGB32);
    else yzcursor=new QImage((Ydim*300)/Zdim,300,QImage::Format_ARGB32);


    imagexy=new QImage(Xdim,Ydim,QImage::Format_RGB888);
    imagexz=new QImage(Xdim,Zdim,QImage::Format_RGB888);
    imageyz=new QImage(Ydim,Zdim,QImage::Format_RGB888);


     for(int i=1;i<xycursor->width();i+=2) xycursor->setPixel(i,xycursor->height()/2,qRgb(0,255,255));
     for(int j=1;j<xycursor->height();j+=2) xycursor->setPixel(xycursor->width()/2,j,qRgb(0,255,255));
     for(int i=1;i<xzcursor->width();i+=2) xzcursor->setPixel(i,xzcursor->height()/2,qRgb(255,0,255));
     for(int k=1;k<xzcursor->height();k+=2) xzcursor->setPixel(xzcursor->width()/2,k,qRgb(255,0,255));
     for(int j=1;j<yzcursor->width();j+=2) yzcursor->setPixel(j,yzcursor->height()/2,qRgb(255,255,0));
     for(int k=1;k<yzcursor->height();k+=2) yzcursor->setPixel(yzcursor->width()/2,k,qRgb(255,255,0));

     ui->xy_cursor->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
     ui->xy_cursor->setPixmap(QPixmap::fromImage(*xycursor));
     ui->xz_cursor->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
     ui->xz_cursor->setPixmap(QPixmap::fromImage(*xzcursor));
     ui->yz_cursor->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
     ui->yz_cursor->setPixmap(QPixmap::fromImage(*yzcursor));


     for(int i=0;i<Xdim;i++){
         for(int j=0;j<Ydim;j++){
             imagexy->setPixel(i,j,qRgb(0,0,0));
         }
     }
     for(int i=0;i<Xdim;i++){
         for(int k=0;k<Zdim;k++){
             imagexz->setPixel(i,k,qRgb(0,0,0));
         }
     }

     for(int j=0;j<Ydim;j++){
         for(int k=0;k<Zdim;k++){
             imageyz->setPixel(j,k,qRgb(0,0,0));
         }
     }

      ui->slider_x->setEnabled(true);
      ui->slider_y->setEnabled(true);
      ui->slider_z->setEnabled(true);
      ui->x_cur->setEnabled(true);
      ui->y_cur->setEnabled(true);
      ui->z_cur->setEnabled(true);

      ui->x_cur->setMaximum(Xdim-1);
      ui->y_cur->setMaximum(Ydim-1);
      ui->z_cur->setMaximum(Zdim-1);

      ui->slider_x->setMaximum(Xdim-1);
      ui->slider_y->setMaximum(Ydim-1);
      ui->slider_z->setMaximum(Zdim-1);

      ui->sp_x->setMaximum(Xdim-1);
      ui->sp_y->setMaximum(Ydim-1);
      ui->sp_z->setMaximum(Zdim-1);
      ui->sp_r->setMaximum(Zdim-1);

      ui->cy_x1->setMaximum(Xdim-1);
      ui->cy_y1->setMaximum(Ydim-1);
      ui->cy_z1->setMaximum(Zdim-1);
      ui->cy_x2->setMaximum(Xdim-1);
      ui->cy_y2->setMaximum(Ydim-1);
      ui->cy_z2->setMaximum(Zdim-1);
      ui->cy_r->setMaximum(Zdim-1);

      x_pos=Xdim/2;
      y_pos=Ydim/2;
      z_pos=Zdim/2;

      ui->x_cur->setValue(x_pos);
      ui->y_cur->setValue(y_pos);
      ui->z_cur->setValue(z_pos);

      ui->slider_x->setValue(x_pos);
      ui->slider_y->setValue(y_pos);
      ui->slider_z->setValue(z_pos);
      mouse=true;
      ui->listWidget->clear();
      vec3.clear();

}
void MainWindow::histogram()
{
    int i,j,k;
    unsigned short pixel;
    Xdim=0;
    Ydim=0;
    Zdim=0;
    FILE *fo;
    hdr=malloc(480);
    fo = fopen(filename,"rb");
    if(fo)
    {
        fread(hdr,348,1,fo);
        fseek(fo,42,SEEK_SET);
        Xdim=readShort(fo);
        Ydim=readShort(fo);
        Zdim=readShort(fo);
    }
    fclose(fo);

    Arr= new unsigned short**[Xdim];
    for(int i=0;i<Xdim;i++){
        Arr[i]=new unsigned short*[Ydim];
        for(int j=0;j<Ydim;j++){
            Arr[i][j]=new unsigned short[Zdim];
        }
    }
         temp_arr= new unsigned short**[Xdim];
         for(int i=0;i<Xdim;i++){
             temp_arr[i]=new unsigned short*[Ydim];
             for(int j=0;j<Ydim;j++){
                 temp_arr[i][j]=new unsigned short[Zdim];
             }
     }
    firstimgflag=1;

    filename.replace("hdr","img");
    fo = fopen(filename, "rb");
    if(fo)
    {
        for(k=0;k<Zdim;k++)
            for(j=0;j<Ydim;j++)
                for(i=0;i<Xdim;i++)
                {
                    if(fread(&pixel,sizeof(unsigned short),1,fo)==1)
                    {
                        Arr[i][j][k]=pixel;
                    }
                }
    }
    fclose(fo);
    //ui->label_3->setText(QString("%1,").arg(vol[index(7,35,41)]));
}

void MainWindow::readTiff()
{

  uint32* raster;
  TIFF* tif = TIFFOpen(filename, "r");
  TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &Xdim);           // uint32 width;
  TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &Ydim);// uint32 height;
  int dircount = 1;
  while (TIFFReadDirectory(tif))  dircount++;
  Zdim=dircount;
  raster = (uint32*)_TIFFmalloc(Xdim*Ydim * sizeof(uint32));

  Arr= new unsigned short**[Xdim];
  for(int i=0;i<Xdim;i++){
      Arr[i]=new unsigned short*[Ydim];
      for(int j=0;j<Ydim;j++){
          Arr[i][j]=new unsigned short[Zdim];
      }
  }
       temp_arr= new unsigned short**[Xdim];
       for(int i=0;i<Xdim;i++){
           temp_arr[i]=new unsigned short*[Ydim];
           for(int j=0;j<Ydim;j++){
               temp_arr[i][j]=new unsigned short[Zdim];
           }
   }
  firstimgflag=1;

  int k=1;
  int count=1;
  while(k<=Zdim){
  TIFFSetDirectory(tif,k);
    TIFFReadRGBAImage(tif,Xdim,Ydim, raster, 0);
    for (int j = 0; j < Ydim; j++){
         for (int i = 0; i <Xdim; i++){
                uint32& TiffPixel = raster[j*Xdim+i];
                //qDebug()<<count<<"."<<TiffPixel<<endl;
                Arr[i][Ydim-j-1][k-1]=(int)(0.1140*(float)TIFFGetB(TiffPixel)+0.2989*(float)TIFFGetR(TiffPixel)+0.5870*(float)TIFFGetG(TiffPixel));
                count++;
                }
          }
    //_TIFFfree(raster);
     k++;
    }//while (TIFFReadDirectory(tif));
  //qDebug()<<k<<endl;
}

void MainWindow::writeTiff(){
    TIFF *tif;
    tsize_t linebytes =4*Xdim;
    unsigned char *buf = NULL;
    buf =(unsigned char *)_TIFFmalloc(linebytes);

    for (int page = 0; page < Zdim;page++){

        if (page == 0)  tif = TIFFOpen(filename, "w");
        else  tif = TIFFOpen(filename, "a");

        TIFFSetField(tif,TIFFTAG_IMAGEWIDTH,Xdim);
        TIFFSetField(tif,TIFFTAG_IMAGELENGTH,Ydim);
        TIFFSetField(tif,TIFFTAG_SAMPLESPERPIXEL,4);
        TIFFSetField(tif,TIFFTAG_BITSPERSAMPLE,8);
        TIFFSetField(tif,TIFFTAG_SAMPLEFORMAT,SAMPLEFORMAT_UINT);
        TIFFSetField (tif, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
        TIFFSetField (tif, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
        TIFFSetField(tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_RGB);
        TIFFSetField(tif, TIFFTAG_COMPRESSION, COMPRESSION_NONE) ;

        TIFFSetField(tif, TIFFTAG_ROWSPERSTRIP, TIFFDefaultStripSize(tif,4*Xdim));
        for(int j=0;j<Ydim;j++){
           int k=0;
           for(int i=0;i<Xdim;i++){
               buf[k]=(unsigned char)Arr[i][j][page];
               buf[k+1]=(unsigned char)Arr[i][j][page];
               buf[k+2]=(unsigned char)Arr[i][j][page];
               buf[k+3]=(unsigned char)1;
               k+=4;
           }
           TIFFWriteScanline(tif,buf,j,0);
        }
        TIFFWriteDirectory(tif);
    }
   TIFFClose(tif);
}
unsigned short MainWindow:: readShort(FILE *inff)
{
    unsigned short ret;
    unsigned char lowByte, hiByte;

    hiByte = fgetc(inff);          // Read the high order byte
    lowByte = fgetc(inff);         // Read the low order byte (little endian form)


    // Pack together
    ret = lowByte;
    ret <<= 8;
    ret |= hiByte;

    return ret;
}
