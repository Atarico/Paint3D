#include "mainwindow.h"
#include <QApplication>

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


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
