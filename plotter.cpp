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
    //Initializing our 3D sculptor to internally deal with drawing stuff.
    vector<GeometricFigure*> figs;

    sculptor = new Sculptor(10, 10, 10);

    //figs.push_back(new PutBox(3, 6, 3, 6, 3, 6, 0.1, 0.1, 0.9, 0.1));
    figs.push_back(new PutSphere(5, 5, 5, 3, 0.8, 0.1, 0.1, 1));
    figs.push_back(new PutSphere(10, 10, 10, 5, 0.1, 0.1, 0.9, 0.1));
    figs.push_back(new PutSphere(0, 10, 10, 5, 0.1, 0.1, 0.9, 0.1));
    figs.push_back(new PutSphere(10, 0, 10, 5, 0.1, 0.1, 0.9, 0.1));
    figs.push_back(new PutSphere(0, 0, 10, 5, 0.1, 0.1, 0.9, 0.1));

    for(int i = 0; i< figs.size(); i++){
        figs[i]->draw(*sculptor);
    }
    //End of 3D sculptor initialization

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

void Plotter::paintMatrix(int plane, int depth){

    float depthNorm = float(depth)/100;

    if(plane == XY){
        planeXY = sculptor->planeXY(depthNorm);
    }
    else if(plane == XZ){
        planeXZ = sculptor->planeXZ(depthNorm);
    }
    else if(plane == YZ){
        planeYZ = sculptor->planeYZ(depthNorm);
    }

    repaint();
}

void Plotter::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    QPen pen;
    QBrush brush;

    // preparando a caneta
    // R, G, B
    pen.setColor(QColor(0,0,0));
    pen.setWidth(2);
    // entregando a caneta ao pintor
    p.setPen(pen);

    // preparando o pincel
    brush.setColor(QColor(255,255,255));
    brush.setStyle(Qt::SolidPattern);
    // entregando o pincel ao pintor
    p.setBrush(brush);

    p.drawRect(0,0,width(),height());

    //PAINTING XY MATRIX
    int sizeH = int(planeXY.size()); //horizontal size in pixels of our plotter
    int sizeV = int(planeXY[0].size()); //vertical size in pixels of our plotter
    float normSizeH = width()/sizeH;
    float normSizeV = height()/sizeV;

    for(int i=0; i<sizeH; i++)
    {
        for(int j=0; j<sizeV; j++)
        {
            if(planeXY[i][j].isOn){
                brush.setColor(QColor(planeXY[i][j].r*255,planeXY[i][j].g*255,planeXY[i][j].b*255));
                brush.setStyle(Qt::SolidPattern);
                p.setBrush(brush);
                p.drawRect(i*normSizeH, j*normSizeV,
                           i*normSizeH + normSizeH, j*normSizeV + normSizeV);
            }
            else{
                brush.setColor(QColor(255,255,255));
                brush.setStyle(Qt::SolidPattern);
                p.setBrush(brush);
                p.drawRect(i*normSizeH, j*normSizeV,
                           i*normSizeH + normSizeH, j*normSizeV + normSizeV);
            }

        }
    }


//    //PAINTING XZ MATRIX
//    sizeH = int(planeXZ.size());
//    sizeV = int(planeXZ[0].size());
//    normSizeH = width()/sizeH;
//    normSizeV = height()/sizeV;

//    for(int i=0; i<sizeH; i++)
//    {
//        for(int j=0; j<sizeV; j++)
//        {
//            if(planeXZ[i][j].isOn){
//                brush.setColor(QColor(planeXZ[i][j].r*255,planeXZ[i][j].g*255,planeXZ[i][j].b*255));
//                brush.setStyle(Qt::SolidPattern);
//                p.setBrush(brush);
//                p.drawRect(i*normSizeH, j*normSizeV,
//                           i*normSizeH + normSizeH, j*normSizeV + normSizeV);
//            }
//            else{
//                brush.setColor(QColor(255,255,255));
//                brush.setStyle(Qt::SolidPattern);
//                p.setBrush(brush);
//                p.drawRect(i*normSizeH, j*normSizeV,
//                           i*normSizeH + normSizeH, j*normSizeV + normSizeV);
//            }

//        }
//    }


//    //PAINTING YZ MATRIX
//    sizeH = int(planeYZ.size());
//    sizeV = int(planeYZ[0].size());
//    normSizeH = width()/sizeH;
//    normSizeV = height()/sizeV;

//    for(int i=0; i<sizeH; i++)
//    {
//        for(int j=0; j<sizeV; j++)
//        {
//            if(planeYZ[i][j].isOn){
//                brush.setColor(QColor(planeYZ[i][j].r*255,planeYZ[i][j].g*255,planeYZ[i][j].b*255));
//                brush.setStyle(Qt::SolidPattern);
//                p.setBrush(brush);
//                p.drawRect(i*normSizeH, j*normSizeV,
//                           i*normSizeH + normSizeH, j*normSizeV + normSizeV);
//            }
//            else{
//                brush.setColor(QColor(255,255,255));
//                brush.setStyle(Qt::SolidPattern);
//                p.setBrush(brush);
//                p.drawRect(i*normSizeH, j*normSizeV,
//                           i*normSizeH + normSizeH, j*normSizeV + normSizeV);
//            }

//        }
//    }
}
