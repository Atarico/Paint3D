#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sculptor.h"

enum { putvoxel, cutvoxel, putbox, cutbox, putsphere, cutsphere, putellipsoid, cutellipsoid };

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void drawPlane();
    void drawSculptorXY(int, int);
    void drawSculptorXZ(int, int);
    void drawSculptorYZ(int, int);

    void drawFigure(int x0, int y0, int z0, int brush);

    void selectPutVoxel();
    void selectCutVoxel();
    void selectPutBox();
    void selectCutBox();
    void selectPutSphere();
    void selectCutSphere();
    void selectPutEllipsoid();
    void selectCutEllipsoid();

    void mudaCor();

private:
    Ui::MainWindow *ui;
    Sculptor *sculptor;
    int brush = putvoxel;
    int color;
    float r = 1,g = 1,b = 1;

};

#endif // MAINWINDOW_H
