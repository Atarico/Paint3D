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
#include "dialognewcanvas.h"
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Initializing our 3D sculptor with a standard dimension of 10x10x10.
    vector<GeometricFigure*> figs;
    sculptor = new Sculptor(10, 10, 10);
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

    //Connections from the depth sliders to the SLOT that draws our matrixes on their plotters
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

    //Connections from clicking in the plotting widgets to the SLOT that draws the selected figure on our sculptor
    connect(ui->plotter_XY,
            SIGNAL(clickXY(int, int)),
            this,
            SLOT(drawSculptorXY(int, int)));

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

    //Connecting the actions to SLOTS
    connect(ui->actionNew_3D_Canvas,
            SIGNAL(triggered(bool)),
            this,
            SLOT(setDimSculptor()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setDimSculptor()
{
    DialogNewCanvas dialog;

    if(dialog.exec() == QDialog::Accepted){
        int nx, ny, nz;
        nx = dialog.getDimX();
        ny = dialog.getDimY();
        nz = dialog.getDimZ();

        sculptor = new Sculptor(nx, ny, nz);
        drawPlane();
    }
}

void MainWindow::drawPlane()
{
    ui->plotter_XY->paintMatrix(sculptor, XY, ui->verticalSlider_XY->value());
    ui->plotter_XZ->paintMatrix(sculptor, XZ, ui->verticalSlider_XZ->value());
    ui->plotter_YZ->paintMatrix(sculptor, YZ, ui->verticalSlider_YZ->value());

    ui->slider_XY->setText(QString::number(int(ui->verticalSlider_XY->value()/(100.0/sculptor->getNz()))));
    ui->slider_XZ->setText(QString::number(int(ui->verticalSlider_XZ->value()/(100.0/sculptor->getNy()))));
    ui->slider_YZ->setText(QString::number(int(ui->verticalSlider_YZ->value()/(100.0/sculptor->getNx()))));

    //connecting plotter dimensions to labels
    ui->label_XY_H->setText(QString::number(sculptor->getNx()));
    ui->label_XY_V->setText(QString::number(sculptor->getNy()));

    ui->label_XZ_H->setText(QString::number(sculptor->getNx()));
    ui->label_XZ_V->setText(QString::number(sculptor->getNz()));

    ui->label_YZ_H->setText(QString::number(sculptor->getNy()));
    ui->label_YZ_V->setText(QString::number(sculptor->getNz()));
}

void MainWindow::drawSculptorXY(int x0, int y0)
{
    float sliderZ0 = float(ui->verticalSlider_XY->value())/100;
    int z0 = sliderZ0*sculptor->getNz();
    drawFigure(x0,y0,z0,brush);
}

void MainWindow::drawSculptorXZ(int x0, int z0)
{
    float sliderY0 = float(ui->verticalSlider_XZ->value())/100;
    int y0 = sliderY0*sculptor->getNy();
    drawFigure(x0,y0,z0,brush);
}

void MainWindow::drawSculptorYZ(int y0, int z0)
{
    float sliderX0 = float(ui->verticalSlider_YZ->value())/100;
    int x0 = sliderX0*sculptor->getNx();
    drawFigure(x0,y0,z0,brush);
}


void MainWindow::drawFigure(int x0, int y0, int z0, int brush)
{
    vector<GeometricFigure*> figs;

    if(brush == putvoxel){
        figs.push_back(new PutVoxel(x0,y0,z0,r,g,b,1));
    }
    if(brush == cutvoxel){
        figs.push_back(new CutVoxel(x0,y0,z0));
    }
    if(brush == putbox){
        figs.push_back(new PutBox(x0-((ui->lineEditRectangleSizeX->text()).toInt()/2),
                                  x0+((ui->lineEditRectangleSizeX->text()).toInt()/2),
                                  y0-((ui->lineEditRectangleSizeY->text()).toInt()/2),
                                  y0+((ui->lineEditRectangleSizeY->text()).toInt()/2),
                                  z0-((ui->lineEditRectangleSizeZ->text()).toInt()/2),
                                  z0+((ui->lineEditRectangleSizeZ->text()).toInt()/2),
                                  r,g,b,1));
    }
    if(brush == cutbox){
        figs.push_back(new CutBox(x0-((ui->lineEditRectangleSizeX->text()).toInt()/2),
                                  x0+((ui->lineEditRectangleSizeX->text()).toInt()/2),
                                  y0-((ui->lineEditRectangleSizeY->text()).toInt()/2),
                                  y0+((ui->lineEditRectangleSizeY->text()).toInt()/2),
                                  z0-((ui->lineEditRectangleSizeZ->text()).toInt()/2),
                                  z0+((ui->lineEditRectangleSizeZ->text()).toInt()/2)));
    }
    if(brush == putsphere){
        figs.push_back(new PutSphere(x0, y0, z0, (ui->lineEditSphereRadius->text()).toInt(), r, g, b, 1));
    }
    if(brush == cutsphere){
        figs.push_back(new CutSphere(x0, y0, z0, (ui->lineEditSphereRadius->text()).toInt()));
    }
    if(brush == putellipsoid){
        figs.push_back(new PutEllipsoid(x0,
                                        y0,
                                        z0,
                                        (ui->lineEditElipsoidRadiusX->text()).toInt(),
                                        (ui->lineEditElipsoidRadiusY->text()).toInt(),
                                        (ui->lineEditElipsoidRadiusZ->text()).toInt(),
                                        r,g,b,1));
    }
    if(brush == cutellipsoid){
        figs.push_back(new CutEllipsoid(x0, y0, z0,
                                        (ui->lineEditElipsoidRadiusX->text()).toInt(),
                                        (ui->lineEditElipsoidRadiusY->text()).toInt(),
                                        (ui->lineEditElipsoidRadiusZ->text()).toInt()));
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

    QColor previousColor(r*255, g*255, b*255);
    d.setCurrentColor(previousColor);
    d.exec();

    QColor color;
    color= d.selectedColor();

    r = color.red();
    g = color.green();
    b = color.blue();
    r=r/255.0;
    g=g/255.0;
    b=b/255.0;
}
