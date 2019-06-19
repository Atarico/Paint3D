#ifndef PLOTTER3D_H
#define PLOTTER3D_H

#include <QWidget>
#include <vector>
#include "sculptor.h"

class Plotter3d : public QWidget
{
    Q_OBJECT
private:
    vector<vector<vector<Voxel>>> plane3D;
public:
    explicit Plotter3d(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event);
    void paintMatrix3D(Sculptor *sculpt);
signals:

public slots:
};

#endif // PLOTTER3D_H
