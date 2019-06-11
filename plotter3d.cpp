#include "plotter3d.h"
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

Plotter3d::Plotter3d(QWidget *parent) : QWidget(parent)
{

}

void Plotter3d::paintMatrix3D(Sculptor *sculpt)
{
    plane3D = sculpt->plane3D();
    repaint();
}

void Plotter3d::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    QPen pen;
    QBrush brush;

    // preparando a caneta
    pen.setColor(QColor(150,150,150));
    pen.setWidth(4);
    p.setPen(pen);

    // preparando o pincel
    brush.setColor(QColor(250,250,250));
    brush.setStyle(Qt::SolidPattern);
    p.setBrush(brush);

    p.drawRect(0,0,width(),height()); //painting the background rectangle

    //defining our dashed line pattern after the background has been painted
    QVector<qreal> dashes;
    qreal space = 4;
    dashes << 9 << space << 9 << space;
    pen.setDashPattern(dashes);
    pen.setDashOffset(3);
    p.setPen(pen);

    int sizeZ = int(plane3D.size());
    int sizeY = int(plane3D[0].size());
    int sizeX = int(plane3D[0][0].size());

    int smallerAxisPixels;
    if(width() <= height()){
        smallerAxisPixels = width();
    }
    else{
        smallerAxisPixels = height();
    }
    int biggerAxisVoxels; //the longest axis in relation to our voxel matrix
    if(sizeX >= sizeY){
        biggerAxisVoxels = sizeX;
    }
    else{
        biggerAxisVoxels = sizeY;
    }
    float normSize = smallerAxisPixels/biggerAxisVoxels; //a relation betwen our smaller pixel axis and our longest voxel axis to be used as a drawing unit.

    QPoint *plottingStart = new QPoint(width()/2 - smallerAxisPixels/2, height()/2 - smallerAxisPixels/2); //defines the 2D point at which we will start painting our voxels.


    //PAINTING 3D MATRIX
    for(int i=0; i<sizeX; i++)
    {
        for(int j=0; j<sizeY; j++)
        {
            for(int k=0; k<sizeZ; k++)
            {
                if(!plane3D[i][j][k].isOn){
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
    }
}
