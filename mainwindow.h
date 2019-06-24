#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sculptor.h"

enum { putvoxel, cutvoxel, putbox, cutbox, putsphere, cutsphere, putellipsoid, cutellipsoid };

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief Conecta os Botões, sliders, plotters.
     */
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    /*!
     * \brief Determina o tamanho das dimensões digitadas pelo usuário.
     */
    void setDimSculptor();
    /*!
     * \brief Desenha plano e modifica o label do tamanho das dimensões de acordo com o vertical slider.
     */
    void drawPlane();
    /*!
     * \brief Desenha plano XY no Plotter_XY de acordo com o movimento do vertical slider que representa a coordenada Z.
     */
    void drawSculptorXY(int, int);
    /*!
     * \brief Desenha plano XZ no Plotter_XZ de acordo com o movimento do vertical slider que representa a coordenada Y.
     */
    void drawSculptorXZ(int, int);
    /*!
     * \brief Desenha plano YZ no Plotter_YZ de acordo com o movimento do vertical slider que representa a coordenada X.
     */
    void drawSculptorYZ(int, int);
    /*!
     * \brief Desenha a figura selecionada pelo Botões localizado na esquerda do layout.
     * \param x0 Cordenada X selecionada pelo click do usuário.
     * \param y0 Cordenada Y selecionada pelo click do usuário.
     * \param z0 Cordenada Z selecionada pelo click do usuário.
     * \param brush Tipo de Figura selecionada pelo usuário nos Botões.
     */
    void drawFigure(int x0, int y0, int z0, int brush);
    /*!
     * \brief Seleciona o método PutVoxel para o desenho.
     */
    void selectPutVoxel();
    /*!
     * \brief Seleciona o método CutVoxel para o desenhado.
     */
    void selectCutVoxel();
    /*!
     * \brief Seleciona o método PutBox para o desenhado.
     */
    void selectPutBox();
    /*!
     * \brief Seleciona o método CutBox para o desenhado.
     */
    void selectCutBox();
    /*!
     * \brief Seleciona o método PutSphere para o desenhado.
     */
    void selectPutSphere();
    /*!
     * \brief Seleciona o método CutSphere para o desenhado.
     */
    void selectCutSphere();
    /*!
     * \brief Seleciona o método PutEllipsoid para o desenhado.
     */
    void selectPutEllipsoid();
    /*!
     * \brief Seleciona o método CutEllipsoid para o desenhado.
     */
    void selectCutEllipsoid();
    /*!
     * \brief Seleciona a cor das figuras que serão desenhadas.
     */
    void mudaCor();
    /*!
     * \brief Seleciona a cor vermelha da figura usando o slider.
     */
    void redSliderChangeColor(int);
    /*!
     * \brief Seleciona a cor verde da figura usando o slider.
     */
    void greenSliderChangeColor(int);
    /*!
     * \brief Seleciona a cor azul da figura usando o slider.
     */
    void blueSliderChangeColor(int);
    /*!
     * \brief Seleciona o alpha da figura usando o slider.
     */
    void alphaSliderChangeColor(int);

    /*!
     * \brief Escreve a matriz de voxels em um arquivo .off de visualização 3D.
     */
    void writeOFF();

private:
    Ui::MainWindow *ui;
    Sculptor *sculptor;
    int brush = putvoxel;
    int color;
    float r = 1,g = 1,b = 1, a = 1;

};

#endif // MAINWINDOW_H
