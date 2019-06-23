#ifndef PUTBOX_H
#define PUTBOX_H
#include "geometricfigure.h"

class PutBox : public GeometricFigure
{
protected:
    int x0, x1, y0, y1, z0, z1;
    float r, g, b, a;
public:
    /*!
     * \brief Ativa todos os voxels no intervalo x∈[x0,x1], y∈[y0,y1], z∈[z0,z1] e atribui aos mesmos a cor atual de desenho.
     * \param _x0 posição "x0" incial.
     * \param _x1 posição "x1" final.
     * \param _y0 posição "y0" incial.
     * \param _y1 posição "y1" final.
     * \param _z0 posição "z0" incial.
     * \param _z1 posição "z1" final.
     * \param _r define a cor vermelha.
     * \param _g define a cor verde.
     * \param _b define a cor azul.
     * \param _a define a opacidade.
     */
    PutBox(int _x0, int _x1, int _y0, int _y1, int _z0, int _z1, float _r, float _g, float _b, float _a);
    ~PutBox();
    /*!
     * \brief Ativa voxels selecionados no PutBox.
     * \param t
     */
    void draw(Sculptor &t);
};

#endif // PUTBOX_H
