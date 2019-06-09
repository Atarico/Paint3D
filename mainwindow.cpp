#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->plotter_XY->paintMatrix( XY, 50);
    ui->plotter_XZ->paintMatrix( XZ, 50);
    ui->plotter_YZ->paintMatrix( YZ, 50);

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

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawPlane()
{
    ui->plotter_XY->paintMatrix(XY, ui->verticalSlider_XY->value());
    ui->plotter_XZ->paintMatrix(XZ, ui->verticalSlider_XZ->value());
    ui->plotter_YZ->paintMatrix(YZ, ui->verticalSlider_YZ->value());
}
