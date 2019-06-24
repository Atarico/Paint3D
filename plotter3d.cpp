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

const double cos45 = 0.70710678118;

Plotter3d::Plotter3d(QWidget *parent) : QWidget(parent)
{

}

void Plotter3d::paintMatrix3D(Sculptor *sculpt)
{
    plane3D = sculpt->plane3D();
    repaint();
}

void Plotter3d::drawCube(QPainter *painter,  QBrush *brush, QPen *pen, int x, int y, int size)
{
    painter->setBrush(*brush);
    painter->setPen(*pen);

    QPainterPath pathTop, pathSide, pathFront;
    QPolygon cubeTop, cubeSide, cubeFront;
    QPoint E, F, G, H, A, B, C, D;

    E = QPoint(x, y);
    F = QPoint(E.x()+size, E.y());
    G = QPoint(F.x(), F.y()+size);
    H = QPoint(G.x()-size, G.y());

    A = QPoint(x-size*cos45/2, y+size*cos45/2);
    B = QPoint(A.x()+size, A.y());
    C = QPoint(B.x(), B.y()+size);
    D = QPoint(C.x()-size, C.y());

    cubeTop<<QPoint(A.x(),A.y()-1)<<E<<F<<QPoint(B.x(),B.y()-1)<<QPoint(A.x(),A.y()-1);
    cubeSide<<QPoint(B.x()+1,B.y())<<F<<G<<QPoint(C.x()+1,C.y())<<QPoint(B.x()+1,B.y());
    cubeFront<<A<<B<<C<<D<<A;

    pathTop.addPolygon(cubeTop);
    pathSide.addPolygon(cubeSide);
    pathFront.addPolygon(cubeFront);

    painter->drawPolygon(cubeTop);
    painter->drawPolygon(cubeSide);
    painter->drawPolygon(cubeFront);

    painter->fillPath(pathTop, *brush);
    painter->fillPath(pathSide, *brush);
    painter->fillPath(pathFront, *brush);
}

void Plotter3d::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    QPen pen;
    QBrush brush;

    p.setRenderHint(QPainter::Antialiasing);

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

    //Defining the sizes of our voxel matrix
    int sizeX = int(plane3D.size());
    int sizeY = int(plane3D[0].size());
    int sizeZ = int(plane3D[0][0].size());

    //A bunch of calculations to determine where to start drawing, the size of our cubes, etc.
    double totalVoxelSizeH =double(sizeZ+double(sizeX*cos45/2));
    double totalVoxelSizeV =double(sizeZ+double(sizeX*cos45/2));

    double normSizeH = width()/totalVoxelSizeH;
    double normSizeV = height()/totalVoxelSizeV;
    double normSize;

    if(normSizeH <= normSizeV){
        normSize = normSizeH;
    }
    else{
        normSize = normSizeV;
    }

    double voxelSizeH = normSize*sizeZ;

    //Starting point to our plotting
    QPoint *plottingStart = new QPoint(width()/2 - normSize*totalVoxelSizeH/2 + (normSize*totalVoxelSizeH-voxelSizeH), height()/2 - normSize*totalVoxelSizeV/2); //defines the 2D point at which we will start painting our voxels.


    for(int i=0; i<sizeX; i++)
    {
        //This if statement makes plottingStart jump between each layer of our 3D painting,
        //so that the layers in front have a displacement in relation to the layer behind it,
        //creating the illusion of three dimensional space.
        if(i!=0){
            plottingStart->setX(plottingStart->x() - normSize*cos45/2);
            plottingStart->setY(plottingStart->y() + normSize*cos45/2);
        }

        for(int j=0; j<sizeY; j++)
        {
            for(int k=sizeZ-1; k>=0; k--)
            {
                if(plane3D[i][j][k].isOn){
                    brush.setColor(QColor(plane3D[i][j][k].r*255,plane3D[i][j][k].g*255,plane3D[i][j][k].b*255,plane3D[i][j][k].a*255));
                    brush.setStyle(Qt::SolidPattern);
                    p.setBrush(brush);

                    pen.setColor(QColor(0,0,0));
                    pen.setWidth(2);
                    pen.setStyle(Qt::SolidLine);
                    p.setPen(pen);

                    drawCube(&p, &brush, &pen, j*normSize + plottingStart->x(), k*normSize + plottingStart->y(), normSize);
                }
            }
        }
    }
}
