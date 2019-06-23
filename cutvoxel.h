#ifndef CUTVOXEL_H
#define CUTVOXEL_H
#include "geometricfigure.h"

class CutVoxel : public GeometricFigure
{
protected:
    int x, y, z;
public:
    /*!
     * \brief Desativa o voxel na posição (x,y,z).
     * \param _x  coordenada x.
     * \param _y  coordenada y.
     * \param _z  coordenada z.
     */
    CutVoxel(int _x, int _y, int _z);
    ~CutVoxel();
    /*!
     * \brief Desativa voxels selecionados no CutVoxel.
     * \param t
     */
    void draw(Sculptor &t);
};

#endif // CUTVOXEL_H
