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
    sculptor = new Sculptor(10, 15, 10);
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
