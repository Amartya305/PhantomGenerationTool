#include "mousetracker.h"

mousetracker::mousetracker(QWidget *parent) : QLabel(parent)
{

}

void mousetracker::mouseMoveEvent(QMouseEvent *ev)
{
    this->x=ev->x();
    this->y=ev->y();
    emit Mouse_Pos();
}

void mousetracker::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button()==Qt::LeftButton){
        this->x=ev->x();
        this->y=ev->y();
        emit Mouse_Pressed();
    }
    else if(ev->button()==Qt::RightButton){
        this->zoom++;
        qDebug()<<this->zoom<<endl;
        emit RightMouse_Pressed();
    }
}

void mousetracker::leaveEvent(QEvent *ev)
{
    emit Mouse_Left();
}

void mousetracker::wheelEvent(QWheelEvent *ev)
{
   this->steps= ev->delta()/120;
   qDebug()<<this->steps<<endl;
   emit Wheel_Moved();
}
