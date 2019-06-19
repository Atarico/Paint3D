#include "mainwindow.h"
#include "ui_mainwindow.h"
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
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Initializing our 3D sculptor to internally deal with drawing stuff.
    vector<GeometricFigure*> figs;
    sculptor = new Sculptor(10, 15, 20);
    figs.push_back(new PutSphere(5, 5, 5, 3, 0.8, 0.1, 0.1, 1));
    figs.push_back(new PutSphere(10, 10, 10, 5, 0.1, 0.1, 0.9, 0.1));
    figs.push_back(new PutSphere(0, 10, 10, 5, 0.1, 0.1, 0.9, 0.1));
    figs.push_back(new PutSphere(10, 0, 10, 5, 0.1, 0.9, 0.1, 0.1));
    figs.push_back(new PutSphere(0, 0, 10, 5, 1, 1, 1, 0.1));
    for(int i = 0; i< figs.size(); i++){
        figs[i]->draw(*sculptor);
    }
    //End of 3D sculptor initialization

    ui->plotter_XY->paintMatrix( sculptor, XY, 50 );
    ui->plotter_XZ->paintMatrix( sculptor, XZ, 50 );
    ui->plotter_YZ->paintMatrix( sculptor, YZ, 50 );

    //connecting plotter dimensions to labels
    ui->label_XY_H->setText(QString::number(sculptor->getNx()));
    ui->label_XY_V->setText(QString::number(sculptor->getNy()));

    ui->label_XZ_H->setText(QString::number(sculptor->getNx()));
    ui->label_XZ_V->setText(QString::number(sculptor->getNz()));

    ui->label_YZ_H->setText(QString::number(sculptor->getNy()));
    ui->label_YZ_V->setText(QString::number(sculptor->getNz()));

    connect(ui->verticalSlider_XY,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(drawPlane()));

    connect(ui->verticalSlider_XZ,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(drawPlane()));

    connect(ui->verticalSlider_YZ,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(drawPlane()));

    ui->plotter_3D->paintMatrix3D(sculptor);


    //Connections from plotter to lcdNumber
    connect(ui->plotter_XY,
            SIGNAL(clickX(int)),
            ui->lcdNumberClickX,
            SLOT(display(int)));

    connect(ui->plotter_XY,
            SIGNAL(clickY(int)),
            ui->lcdNumberClickY,
            SLOT(display(int)));

    connect(ui->plotter_XZ,
            SIGNAL(clickX(int)),
            ui->lcdNumberClickX,
            SLOT(display(int)));

    connect(ui->plotter_XZ,
            SIGNAL(clickY(int)),
            ui->lcdNumberClickZ,
            SLOT(display(int)));

    connect(ui->plotter_YZ,
            SIGNAL(clickX(int)),
            ui->lcdNumberClickY,
            SLOT(display(int)));

    connect(ui->plotter_YZ,
            SIGNAL(clickY(int)),
            ui->lcdNumberClickZ,
            SLOT(display(int)));






    connect(ui->plotter_XY,
            SIGNAL(clickXY(int, int)),
            this,
            SLOT(XYXY(int, int)));

    connect(ui->plotter_XZ,
            SIGNAL(clickXY(int, int)),
            this,
            SLOT(drawSculptorXZ(int, int)));

    connect(ui->plotter_YZ,
            SIGNAL(clickXY(int, int)),
            this,
            SLOT(drawSculptorYZ(int, int)));

    //Connections from buttons to brush type
    connect(ui->pushButtonPutVoxel,
            SIGNAL(clicked(bool)),
            this,
            SLOT(selectPutVoxel()));
    connect(ui->pushButtonCutVoxel,
            SIGNAL(clicked(bool)),
            this,
            SLOT(selectCutVoxel()));
    connect(ui->pushButtonPutBox,
            SIGNAL(clicked(bool)),
            this,
            SLOT(selectPutBox()));
    connect(ui->pushButtonCutBox,
            SIGNAL(clicked(bool)),
            this,
            SLOT(selectCutBox()));
    connect(ui->pushButtonPutSphere,
            SIGNAL(clicked(bool)),
            this,
            SLOT(selectPutSphere()));
    connect(ui->pushButtonCutSphere,
            SIGNAL(clicked(bool)),
            this,
            SLOT(selectCutSphere()));
    connect(ui->pushButtonPutEllipsoid,
            SIGNAL(clicked(bool)),
            this,
            SLOT(selectPutEllipsoid()));
    connect(ui->pushButtonCutEllipsoid,
            SIGNAL(clicked(bool)),
            this,
            SLOT(selectCutEllipsoid()));
    connect(ui->pushButtonColor,
            SIGNAL(clicked(bool)),
            this,
            SLOT(mudaCor()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawPlane()
{
    ui->plotter_XY->paintMatrix(sculptor, XY, ui->verticalSlider_XY->value());
    ui->plotter_XZ->paintMatrix(sculptor, XZ, ui->verticalSlider_XZ->value());
    ui->plotter_YZ->paintMatrix(sculptor, YZ, ui->verticalSlider_YZ->value());
}

void MainWindow::drawSculptorXY(int x0, int y0)
{
    float sliderZ0 = float(ui->verticalSlider_XY->value())/100;
    int z0 = sliderZ0*sculptor->getNz();
    drawFigure(x0,y0,z0,brush);
    //sculptor->putVoxel(x0, y0, z0);
    //this->drawPlane();
}

void MainWindow::drawSculptorXZ(int x0, int z0)
{
    float sliderY0 = float(ui->verticalSlider_XZ->value())/100;
    int y0 = sliderY0*sculptor->getNy();
    drawFigure(x0,y0,z0,brush);
    //sculptor->putVoxel(x0, y0, z0);
    //this->drawPlane();
}

void MainWindow::drawSculptorYZ(int y0, int z0)
{
    float sliderX0 = float(ui->verticalSlider_YZ->value())/100;
    int x0 = sliderX0*sculptor->getNx();
    drawFigure(x0,y0,z0,brush);
    //sculptor->putVoxel(x0, y0, z0);
    //this->drawPlane();
}


void MainWindow::drawFigure(int x0, int y0, int z0, int brush)
{
    vector<GeometricFigure*> figs;

    if(brush == putvoxel){
        figs.push_back(new PutVoxel(x0,y0,z0,0,0,0,1)); //COLOR SYSTEM MISSING
    }
    if(brush == cutvoxel){
        figs.push_back(new CutVoxel(x0,y0,z0)); //COLOR SYSTEM MISSING
    }
    if(brush == putbox){
        figs.push_back(new PutBox(x0-2,x0+2,y0-2,y0+2,z0-2,z0+2,0,0,0,1)); //COLOR SYSTEM MISSING & RADIUS SYSTEM MISSING
    }
    if(brush == cutbox){
        figs.push_back(new CutBox(x0-2,x0+2,y0-2,y0+2,z0-2,z0+2)); //RADIUS SYSTEM MISSING
    }
    if(brush == putsphere){
        figs.push_back(new PutSphere(x0, y0, z0, 2, 0, 0, 0, 1)); //COLOR SYSTEM MISSING & RADIUS SYSTEM MISSING
    }
    if(brush == cutsphere){
        figs.push_back(new CutSphere(x0, y0, z0, 2)); //RADIUS SYSTEM MISSING
    }
    if(brush == putellipsoid){
        figs.push_back(new PutEllipsoid(x0,y0,z0,2,3,4,0,0,0,1)); //COLOR SYSTEM MISSING & RADIUS SYSTEM MISSING
    }
    if(brush == cutellipsoid){
        figs.push_back(new CutEllipsoid(x0, y0, z0, 2, 3, 4)); //RADIUS SYSTEM MISSING
    }
    for(int i = 0; i< figs.size(); i++){
        figs[i]->draw(*sculptor);
    }
    this->drawPlane();
}


//Selecting brush types
void MainWindow::selectPutVoxel()
{
    brush = putvoxel;
}
void MainWindow::selectCutVoxel()
{
    brush = cutvoxel;
}
void MainWindow::selectPutBox()
{
    brush = putbox;
}
void MainWindow::selectCutBox()
{
    brush = cutbox;
}
void MainWindow::selectPutSphere()
{
    brush = putsphere;
}
void MainWindow::selectCutSphere()
{
    brush = cutsphere;
}
void MainWindow::selectPutEllipsoid()
{
    brush = putellipsoid;
}
void MainWindow::selectCutEllipsoid()
{
    brush = cutellipsoid;
}

void MainWindow::mudaCor()
{
    QColorDialog d;
    d.exec();
    QColor color;
    color = d.selectedColor();
    r = color.red();
    g = color.green();
    b = color.blue();
    r=r/255.0;
    repaint();
}
