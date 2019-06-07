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

    Sculptor *sculptor;
    vector<GeometricFigure*> figs;

    figs.push_back(new PutBox(10, 20, 10, 20, 10, 20, 0.1, 0.1, 0.9, 0.1));
    figs.push_back(new PutSphere(30, 30, 30, 5, 0.1, 0.1, 0.9, 0.1));

    for(int i = 0; i< figs.size(); i++){
        figs[i]->draw(*sculptor);
    }

    (*sculptor).writeOFF("OFF_file");

    return a.exec();
}
