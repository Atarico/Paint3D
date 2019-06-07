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
    Sculptor *sculptor;
    vector<GeometricFigure*> figs;

    sculptor = new Sculptor(30, 30, 30);

    figs.push_back(new PutBox(10, 20, 10, 20, 10, 20, 0.1, 0.1, 0.9, 0.1));
    figs.push_back(new PutSphere(30, 30, 30, 5, 0.1, 0.1, 0.9, 0.1));

    for(int i = 0; i< figs.size(); i++){
        figs[i]->draw(*sculptor);
    }
    //End of 3D sculptor initialization

    vector<vector<Voxel>> planeXY;
    planeXY = sculptor->planeXY(15);
    std::printf("test");
}

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow::drawPlaneXY()
{

}
