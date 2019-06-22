#ifndef DIALOGNEWCANVAS_H
#define DIALOGNEWCANVAS_H

#include <QDialog>

namespace Ui {
class DialogNewCanvas;
}

class DialogNewCanvas : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNewCanvas(QWidget *parent = 0);
    ~DialogNewCanvas();
    int getDimX();
    int getDimY();
    int getDimZ();

private:
    Ui::DialogNewCanvas *ui;
};

#endif // DIALOGNEWCANVAS_H
