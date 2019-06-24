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
    /*!
     * \brief Emite o sinal clickX , clickY e clickXY para o plot em lcd number e para dar as coordenadas desenho no arrasto do mouse.
     * \param event
     */
    void mouseMoveEvent(QMouseEvent *event);
    /*!
     * \brief Emite o sinal clickX , clickY e clickXY para dar as coordenadas de início do desenho.
     * \param event
     */
    void mousePressEvent(QMouseEvent *event);
    /*!
     * \brief Sinaliza o ponto de  finalizar o desenho.
     * \param event
     */
    void mouseReleaseEvent(QMouseEvent *event);
    /*!
     * \brief  Prepara e desenha no plotter a imagem gerada de cada plano XY, XZ e YZ.
     * \param event
     */
    void paintEvent(QPaintEvent *event);
    /*!
     * \brief define onde deve ser desenhado cada plano nos plotter XY, XZ e YZ.
     * \param sculpt
     * \param plane
     * \param depth
     */
    void paintMatrix(Sculptor *sculpt, int plane, int depth);

signals:
    /*!
     * \brief Sinais de movimento dos eixos X e Y.
     */
    void moveXY(int, int);
    /*!
     * \brief Sinais de click do eixo X.
     */
    void clickX(int);
    /*!
     * \brief Sinais de click do eixo Y.
     */
    void clickY(int);
    /*!
     * \brief Sinais de click do eixo X e Y.
     */
    void clickXY(int, int);

public slots:

};

#endif // PLOTTER_H
