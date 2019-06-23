#ifndef PUTVOXEL_H
#define PUTVOXEL_H
#include "geometricfigure.h"

class PutVoxel : public GeometricFigure
{
protected:
    int x, y, z;
    float r, g, b, a;
public:
    /*!
     * \brief Ativa o voxel na posição (x,y,z) e atribui ao mesmo a cor atual de desenho.
     * \param _x coordenada x.
     * \param _y coordenada y.
     * \param _z coordenada z.
     * \param _radius raio da esfera
     * \param _r define a cor vermelha.
     * \param _g define a cor verde.
     * \param _b define a cor azul.
     * \param _a define a opacidade.
     */
    PutVoxel(int _x, int _y, int _z, float _r, float _g, float _b, float _a);
    ~PutVoxel();
    /*!
     * \brief Ativa voxels selecionados no PutVoxel.
     * \param t
     */
    void draw(Sculptor &t);
};

#endif // PUTVOXEL_H
