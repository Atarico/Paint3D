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

    /*!
     * \brief Cria um objeto QPolygon que desenha um cubo translucido e o retorna.
     * \param x
     * \param y
     * \param size
     */
    void drawCube(QPainter *painter,  QBrush *brush, QPen *pen,  int x, int y, int size);
signals:

public slots:
};

#endif // PLOTTER3D_H
