#ifndef CUTELLIPSOID_H
#define CUTELLIPSOID_H
#include "geometricfigure.h"

class CutEllipsoid : public GeometricFigure
{
protected:
    int xcenter, ycenter,  zcenter,  rx,  ry, rz;
public:
    /*!
     * \brief Desativa todos os voxels que satisfazem à equação da elipsoide.
     * \param _xcenter centro da elipsoide na cordenada x.
     * \param _ycenter centro da elipsoide na cordenada y.
     * \param _zcenter centro da elipsoide na cordenada z.
     * \param _rx 	Semi-eixo principal x da elipsoide.
     * \param _ry   Semi-eixo principal y da elipsoide.
     * \param _rz   Semi-eixo principal z da elipsoide.
     */
    CutEllipsoid(int _xcenter, int _ycenter, int _zcenter, int _rx, int _ry, int _rz);
    ~CutEllipsoid();
    /*!
     * \brief Desativa voxels selecionados no CutEllipsoid.
     * \param t
     */
    void draw(Sculptor &t);
};

#endif // CUTELLIPSOID_H
