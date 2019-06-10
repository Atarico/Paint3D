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

#include <algorithm>
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
    figs.push_back(new PutSphere(10, 0, 10, 5, 0.1, 0.9, 0.1, 0.1));
    figs.push_back(new PutSphere(0, 0, 10, 5, 1, 1, 1, 0.1));

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
        plane2D = sculptor->planeXY(depthNorm);
    }
    else if(plane == XZ){
        plane2D = sculptor->planeXZ(depthNorm);
    }
    else if(plane == YZ){
        plane2D = sculptor->planeYZ(depthNorm);
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
    pen.setColor(QColor(150,150,150));
    pen.setWidth(4);
    // entregando a caneta ao pintor
    p.setPen(pen);

    // preparando o pincel
    brush.setColor(QColor(250,250,250));
    brush.setStyle(Qt::SolidPattern);
    // entregando o pincel ao pintor
    p.setBrush(brush);

    p.drawRect(0,0,width(),height()); //painting the background rectangle

    //defining our dashed line pattern after the background has been painted
    QVector<qreal> dashes;
    qreal space = 4;
    dashes << 9 << space << 9 << space;
    pen.setDashPattern(dashes);
    pen.setDashOffset(3);
    p.setPen(pen);


    //PAINTING 2D MATRIX
    int sizeH = int(plane2D.size()); //horizontal size of our matrix in voxels
    int sizeV = int(plane2D[0].size()); //vertical size of our matrix in voxels
    int smallerAxisPixels; //longest axis in relation to our plotter pixels
    if(width() <= height()){
        smallerAxisPixels = width();
    }
    else{
        smallerAxisPixels = height();
    }
    int biggerAxisVoxels; //the longest axis in relation to our voxel matrix
    if(sizeH >= sizeV){
        biggerAxisVoxels = sizeH;
    }
    else{
        biggerAxisVoxels = sizeV;
    }
    float normSize = smallerAxisPixels/biggerAxisVoxels; //a relation betwen our smaller pixel axis and our longest voxel axis to be used as a drawing unit.

    QPoint *plottingStart = new QPoint(width()/2 - smallerAxisPixels/2, height()/2 - smallerAxisPixels/2); //defines the 2D point at which we will start painting our voxels.

    for(int i=0; i<sizeH; i++)
    {
        for(int j=0; j<sizeV; j++)
        {
            if(!plane2D[i][j].isOn){
                brush.setColor(QColor(240,240,240));
                brush.setStyle(Qt::SolidPattern);
                p.setBrush(brush);

                pen.setColor(QColor(150,150,150));
                pen.setWidth(1);
                //pen.setStyle(Qt::DashLine);
                p.setPen(pen);

                p.drawRect(i*normSize + plottingStart->x(), j*normSize + plottingStart->y(),
                           normSize, normSize);
            }

        }
    }

    for(int i=0; i<sizeH; i++)
    {
        for(int j=0; j<sizeV; j++)
        {
            if(plane2D[i][j].isOn){
                brush.setColor(QColor(plane2D[i][j].r*255,plane2D[i][j].g*255,plane2D[i][j].b*255));
                brush.setStyle(Qt::SolidPattern);
                p.setBrush(brush);

                pen.setColor(QColor(0,0,0));
                pen.setWidth(2);
                pen.setStyle(Qt::SolidLine);
                p.setPen(pen);

                p.drawRect(i*normSize + plottingStart->x(), j*normSize + plottingStart->y(),
                           normSize, normSize);
            }

        }
    }
}
