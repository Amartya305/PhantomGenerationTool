#ifndef MOUSETRACKER_H
#define MOUSETRACKER_H
#include<QLabel>
#include <QWidget>
#include<QMouseEvent>
#include<QEvent>
#include<QDebug>
class mousetracker : public QLabel
{
    Q_OBJECT
public:
    explicit mousetracker(QWidget *parent = nullptr);
    void mouseMoveEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void leaveEvent(QEvent *ev);
    void wheelEvent(QWheelEvent *ev);
    int x,y;
    int steps=0;
    int zoom=0;
signals:
    void Mouse_Pressed();
    void RightMouse_Pressed();
    void Mouse_Pos();
    void Mouse_Left();
    void Wheel_Moved();
public slots:
};

#endif // MOUSETRACKER_H
