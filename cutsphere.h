#ifndef CUTSPHERE_H
#define CUTSPHERE_H
#include "geometricfigure.h"

class CutSphere : public GeometricFigure
{
protected:
    int xcenter, ycenter, zcenter, radius;
public:
    /*!
     * \brief Desativa todos os voxels que satisfazem à equação da esfera.
     * \param _xcenter centro da esfera na cordenada x.
     * \param _ycenter centro da esfera na cordenada y.
     * \param _zcenter centro da esfera na cordenada z.
     * \param _radius raio da esfera.
     */
    CutSphere(int _xcenter, int _ycenter, int _zcenter, int _radius);
    ~CutSphere();
    /*!
     * \brief Desativa voxels selecionados no CutSphere.
     * \param t
     */
    void draw(Sculptor &t);
};

#endif // CUTSPHERE_H
