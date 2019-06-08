#ifndef PLOTTER_H
#define PLOTTER_H

#include <QWidget>
#include <vector>
#include "sculptor.h"

enum { XY, XZ, YZ };

class Plotter : public QWidget
{
    Q_OBJECT

private:
    vector<vector<Voxel>> planeXY;
    vector<vector<Voxel>> planeXZ;
    vector<vector<Voxel>> planeYZ;
    Sculptor *sculptor;

public:
    explicit Plotter(QWidget *parent = nullptr);

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void paintMatrix(int plane, int depth);

signals:
    void moveX(int);
    void moveY(int);
    void clickX(int);
    void clickY(int);

public slots:

};

#endif // PLOTTER_H
