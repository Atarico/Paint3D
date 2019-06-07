#include "plotterxy.h"

#include <QPainter>
#include <QPen>
#include <QBrush>

plotterXY::plotterXY(QWidget *parent) : QWidget(parent)
{

}

void Plotter::mouseMoveEvent(QMouseEvent *event){
  emit moveX(event->x());
  emit moveY(event->y());
}

void Plotter::mousePressEvent(QMouseEvent *event){
  if(event->button() == Qt::LeftButton ){
    emit clickX(event->x());
    emit clickY(event->y());
  }
}

void Plotter::paintMatrix(vector<vector<Voxel>> matrix){
    QPainter p(this);
    QPen pen;
    QBrush brush;

    // preparando o pincel
    brush.setColor(QColor(cor,cor,0));
    brush.setStyle(Qt::SolidPattern);
    // entregando o pincel ao pintor
    p.setBrush(brush);

    int sizeX = width();
    int sizeY = height();

    for(int i=0; i<matrix.size(); i++)
    {
        for(int j=0; j<matrix[i].size(); j++)
        {
            p.drawRect(i, j,
                       i+width()/matrix[i].size(), j+height()/matrix.size()
                       );
        }
    }
}
