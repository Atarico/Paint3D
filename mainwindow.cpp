#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    connect(ui->verticalSlider_XY,
//            SIGNAL(valueChanged(int)),
//            ui->plotter_XY,
//            SLOT(paintMatrix((int))));

    ui->plotter_XY->paintMatrix(5);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawPlaneXY()
{
    std::printf("fuck my life");
}
