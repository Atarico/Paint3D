#ifndef CUTBOX_H
#define CUTBOX_H
#include "geometricfigure.h"

class CutBox : public GeometricFigure
{
protected:
    int x0, x1, y0, y1, z0, z1;
public:
    /*!
     * \brief Desativa todos os voxels no intervalo x∈[x0,x1], y∈[y0,y1], z∈[z0,z1].
     * \param _x0 posição "x0" incial.
     * \param _x1 posição "x1" final.
     * \param _y0 posição "y0" incial.
     * \param _y1 posição "y1" final.
     * \param _z0 posição "z0" incial.
     * \param _z1 posição "z1" final.
     */
    CutBox(int _x0, int _x1, int _y0, int _y1, int _z0, int _z1);
    ~CutBox();
    /*!
     * \brief Desativa voxels selecionados no CutBox.
     * \param t
     */
    void draw(Sculptor &t);
};

#endif // CUTBOX_H
