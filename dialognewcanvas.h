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
    /*!
     * \brief Retorna o numero da dimensão X digitada pelo usuário.
     */
    int getDimX();
    /*!
     * \brief Retorna o numero da dimensão Y digitada pelo usuário.
     */
    int getDimY();
    /*!
     * \brief  Retorna o numero da dimensão Z digitada pelo usuário.
     */
    int getDimZ();

private:
    Ui::DialogNewCanvas *ui;
};

#endif // DIALOGNEWCANVAS_H
