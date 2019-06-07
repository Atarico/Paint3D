#ifndef PLOTTERXY_H
#define PLOTTERXY_H

#include <QWidget>
#include <vector>
#include "sculptor.h"

class plotterXY : public QWidget
{
    Q_OBJECT

private:

public:
    explicit plotterXY(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

signals:
    void moveX(int);
    void moveY(int);
    void clickX(int);
    void clickY(int);

public slots:
    void paintMatrix(vector<vector<Voxel>> matrix);
};

#endif // PLOTTERXY_H
