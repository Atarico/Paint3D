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
    vector<vector<Voxel>> plane2D;
    QPoint *plotStart;
    int normalizao;
    bool lmbPressed = false;
public:
    explicit Plotter(QWidget *parent = nullptr);

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void paintMatrix(Sculptor *sculpt, int plane, int depth);

signals:
    void moveX(int);
    void moveY(int);
    void clickX(int);
    void clickY(int);
    void clickXY(int, int);

public slots:

};

#endif // PLOTTER_H
