#include "plotter.h"
#include "sculptor.h"
#include "geometricfigure.h"
#include "putbox.h"
#include "cutbox.h"
#include "putsphere.h"
#include "cutsphere.h"
#include "putellipsoid.h"
#include "cutellipsoid.h"
#include "putvoxel.h"
#include "cutvoxel.h"

#include <vector>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QMouseEvent>

Plotter::Plotter(QWidget *parent) : QWidget(parent)
{
    planeXY;
    planeXZ;
    planeYZ;

    setMouseTracking(true);
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

void Plotter::paintMatrix(int depth){

    //Initializing our 3D sculptor to internally deal with drawing stuff.
    Sculptor *sculptor;
    vector<GeometricFigure*> figs;

    sculptor = new Sculptor(10, 10, 10);

    figs.push_back(new PutBox(3, 6, 3, 6, 3, 6, 0.1, 0.1, 0.9, 0.1));
    figs.push_back(new PutSphere(10, 10, 10, 3, 0.1, 0.1, 0.9, 0.1));

    for(int i = 0; i< figs.size(); i++){
        figs[i]->draw(*sculptor);
    }
    //End of 3D sculptor initialization

    //vector<vector<Voxel>> planeXY;
    planeXY = sculptor->planeXY(depth);
}

void Plotter::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    QPen pen;
    QBrush brush;

    // preparando o pincel
    brush.setColor(QColor(255,255,0));
    brush.setStyle(Qt::SolidPattern);
    // entregando o pincel ao pintor
    p.setBrush(brush);

    p.drawRect(0,0,width(),height());

    brush.setColor(QColor(0,0,255));
    brush.setStyle(Qt::SolidPattern);
    // entregando o pincel ao pintor
    p.setBrush(brush);

    int sizeX = planeXY.size();
    int sizeY = planeXY.size();
    float normSizeX = width()/sizeX;
    float normSizeY = height()/sizeY;

    for(int i=0; i<sizeX; i++)
    {
        for(int j=0; j<sizeY; j++)
        {
            if(planeXY[i][j].isOn){
                brush.setColor(QColor(planeXY[i][j].r*255,planeXY[i][j].g*255,planeXY[i][j].b*255));
                brush.setStyle(Qt::SolidPattern);
                p.setBrush(brush);
                p.drawRect(i*normSizeX, j*normSizeY,
                           i*normSizeX + normSizeX, j*normSizeY + normSizeY);
            }
            else{
                brush.setColor(QColor(255,255,255));
                brush.setStyle(Qt::SolidPattern);
                p.setBrush(brush);
                p.drawRect(i*normSizeX, j*normSizeY,
                           i*normSizeX + normSizeX, j*normSizeY + normSizeY);
            }

        }
    }
}
