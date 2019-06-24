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
#include <QFileDialog>
#include <QSysInfo>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Initializing our 3D sculptor with a standard dimension of 10x10x10.
    sculptor = new Sculptor(10, 10, 10);
    //End of 3D sculptor initialization


    ui->plotter_XY->paintMatrix( sculptor, XY, 50 );
    ui->plotter_XZ->paintMatrix( sculptor, XZ, 50 );
    ui->plotter_YZ->paintMatrix( sculptor, YZ, 50 );

    //Connecting plotter dimensions to labels
    ui->label_XY_H->setText("X: "+QString::number(sculptor->getNx()));
    ui->label_XY_V->setText("Y: "+QString::number(sculptor->getNy()));

    ui->label_XZ_H->setText("X: "+QString::number(sculptor->getNx()));
    ui->label_XZ_V->setText("Z: "+QString::number(sculptor->getNz()));

    ui->label_YZ_H->setText("Y: "+QString::number(sculptor->getNy()));
    ui->label_YZ_V->setText("Z: "+QString::number(sculptor->getNz()));

    //Connecting brush colors to labels
    ui->label_Red->setText("Red: "+QString::number(r*255));
    ui->label_Green->setText("Green: "+QString::number(g*255));
    ui->label_Blue->setText("Blue: "+QString::number(b*255));
    ui->label_Alpha->setText("Alpha: "+QString::number(a*255));

    //Connections from the RGBA sliders
    connect(ui->horizontalSliderRed,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(redSliderChangeColor(int)));
    connect(ui->horizontalSliderGreen,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(greenSliderChangeColor(int)));
    connect(ui->horizontalSliderBlue,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(blueSliderChangeColor(int)));
    connect(ui->horizontalSliderAlpha,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(alphaSliderChangeColor(int)));


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
    connect(ui->actionputvoxel,
            SIGNAL(triggered(bool)),
            this,
            SLOT(selectPutVoxel()));
    connect(ui->actioncutvoxel,
            SIGNAL(triggered(bool)),
            this,
            SLOT(selectCutVoxel()));
    connect(ui->actionputbox,
            SIGNAL(triggered(bool)),
            this,
            SLOT(selectPutBox()));
    connect(ui->actioncutbox,
            SIGNAL(triggered(bool)),
            this,
            SLOT(selectCutBox()));
    connect(ui->actionputsphere,
            SIGNAL(triggered(bool)),
            this,
            SLOT(selectPutSphere()));
    connect(ui->actioncutsphere,
            SIGNAL(triggered(bool)),
            this,
            SLOT(selectCutSphere()));
    connect(ui->actionputellipsoid,
            SIGNAL(triggered(bool)),
            this,
            SLOT(selectPutEllipsoid()));
    connect(ui->actioncutellipsoid,
            SIGNAL(triggered(bool)),
            this,
            SLOT(selectCutEllipsoid()));

    //Connecting the color picking button to it's popup
    connect(ui->pushButtonColor,
            SIGNAL(clicked(bool)),
            this,
            SLOT(mudaCor()));

    //Connecting the actions to SLOTS
    connect(ui->actionNew_3D_Canvas,
            SIGNAL(triggered(bool)),
            this,
            SLOT(setDimSculptor()));

    connect(ui->actionwriteOFF,
            SIGNAL(triggered(bool)),
            this,
            SLOT(writeOFF()));

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

    ui->plotter_3D->paintMatrix3D(sculptor);

    ui->slider_XY->setText(QString::number(int(ui->verticalSlider_XY->value()/(100.0/sculptor->getNz()))));
    ui->slider_XZ->setText(QString::number(int(ui->verticalSlider_XZ->value()/(100.0/sculptor->getNy()))));
    ui->slider_YZ->setText(QString::number(int(ui->verticalSlider_YZ->value()/(100.0/sculptor->getNx()))));

    //connecting plotter dimensions to labels
    ui->label_XY_H->setText("X: "+QString::number(sculptor->getNx()));
    ui->label_XY_V->setText("Y: "+QString::number(sculptor->getNy()));

    ui->label_XZ_H->setText("X: "+QString::number(sculptor->getNx()));
    ui->label_XZ_V->setText("Z: "+QString::number(sculptor->getNz()));

    ui->label_YZ_H->setText("Y: "+QString::number(sculptor->getNy()));
    ui->label_YZ_V->setText("Z: "+QString::number(sculptor->getNz()));
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
        figs.push_back(new PutVoxel(x0,y0,z0,r,g,b,a));
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
                                  r,g,b,a));
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
        figs.push_back(new PutSphere(x0, y0, z0, (ui->lineEditSphereRadius->text()).toInt(), r, g, b, a));
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
                                        r,g,b,a));
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
    a = color.alpha();

    ui->displayColor->changeColor(r,g,b,a);

    r=r/255.0;
    g=g/255.0;
    b=b/255.0;
    a=a/255.0;

    //Connecting brush colors to labels and sliders
    ui->label_Red->setText("Red: "+QString::number(r*255));
    ui->horizontalSliderRed->setValue(r*100);

    ui->label_Green->setText("Green: "+QString::number(g*255));
    ui->horizontalSliderGreen->setValue(g*100);

    ui->label_Blue->setText("Blue: "+QString::number(b*255));
    ui->horizontalSliderBlue->setValue(b*100);

    ui->label_Alpha->setText("Alpha: "+QString::number(a*255));
    ui->horizontalSliderAlpha->setValue(a*100);
}

void MainWindow::redSliderChangeColor(int slider)
{
    float aux = slider/100.0;
    r = aux;
    ui->displayColor->changeColor(r*255,g*255,b*255,a*255);
    ui->label_Red->setText("Red: "+QString::number(r*255));
}

void MainWindow::greenSliderChangeColor(int slider)
{
    float aux = slider/100.0;
    g = aux;
    ui->displayColor->changeColor(r*255,g*255,b*255,a*255);
    ui->label_Green->setText("Green: "+QString::number(g*255));
}

void MainWindow::blueSliderChangeColor(int slider)
{
    float aux = slider/100.0;
    b = aux;
    ui->displayColor->changeColor(r*255,g*255,b*255,a*255);
    ui->label_Blue->setText("Blue: "+QString::number(b*255));
}

void MainWindow::alphaSliderChangeColor(int slider)
{
    float aux = slider/100.0;
    a = aux;
    ui->displayColor->changeColor(r*255,g*255,b*255,a*255);
    ui->label_Alpha->setText("Alpha: "+QString::number(a*255));
}

void MainWindow::writeOFF()
{
    QString fileName;

    std::cout<<QSysInfo::productType().toStdString();

    qDebug("OS: " + QSysInfo::productType().toLatin1() + "\n");

    if(QSysInfo::productType() == "windows"){
        fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                   "./untitled.off",
                                   tr("OFF (*.off)"));
    }
    else if(QSysInfo::productType() == "ubuntu"){
        fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                   "./untitled.off",
                                   tr("OFF (*.off)"));
    }

    (*sculptor).writeOFF(fileName.toStdString());
}
