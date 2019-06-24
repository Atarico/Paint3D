#include "colordisplay.h"

#include <QPainter>
#include <QPen>
#include <QBrush>

colorDisplay::colorDisplay(QWidget *parent) : QWidget(parent)
{

}

void colorDisplay::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    QPen pen;
    QBrush brush;

    // preparando a caneta
    pen.setColor(QColor(150,150,150));
    pen.setWidth(4);
    p.setPen(pen);

    // preparando o pincel
    brush.setColor(QColor(this->r,this->g,this->b,this->a));
    brush.setStyle(Qt::SolidPattern);
    p.setBrush(brush);

    p.drawRect(0,0,width(),height()); //painting the background rectangle

}

void colorDisplay::changeColor(int r, int g, int b, int a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
    repaint();
}
