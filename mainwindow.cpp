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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Initializing our 3D sculptor to internally deal with drawing stuff.
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

    connect(ui->plotter_XY,
            SIGNAL(clickX(int)),
            ui->lcdNumberClickX,
            SLOT(display(int)));

    connect(ui->plotter_XY,
            SIGNAL(clickY(int)),
            ui->lcdNumberClickY,
            SLOT(display(int)));

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
    sculptor->putVoxel(x0, y0, z0);
    this->drawPlane();
}

void MainWindow::drawSculptorXZ(int x0, int z0)
{
    float sliderY0 = float(ui->verticalSlider_XZ->value())/100;
    int y0 = sliderY0*sculptor->getNy();
    sculptor->putVoxel(x0, y0, z0);
    this->drawPlane();
}

void MainWindow::drawSculptorYZ(int y0, int z0)
{
    float sliderX0 = float(ui->verticalSlider_YZ->value())/100;
    int x0 = sliderX0*sculptor->getNx();
    sculptor->putVoxel(x0, y0, z0);
    this->drawPlane();
}
