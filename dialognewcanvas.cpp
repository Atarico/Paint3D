#include "dialognewcanvas.h"
#include "ui_dialognewcanvas.h"

DialogNewCanvas::DialogNewCanvas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNewCanvas)
{
    ui->setupUi(this);
}

DialogNewCanvas::~DialogNewCanvas()
{
    delete ui;
}

int DialogNewCanvas::getDimX()
{
    return (ui->lineEditDimX->text()).toInt();
}

int DialogNewCanvas::getDimY()
{
    return (ui->lineEditDimY->text()).toInt();
}

int DialogNewCanvas::getDimZ()
{
    return (ui->lineEditDimZ->text()).toInt();
}
