#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sculptor.h"

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

private:
    Ui::MainWindow *ui;
    Sculptor *sculptor;
    int brush;
};

#endif // MAINWINDOW_H
