#ifndef PUTELLIPSOID_H
#define PUTELLIPSOID_H
#include "geometricfigure.h"

class PutEllipsoid : public GeometricFigure
{
protected:
    int xcenter, ycenter, zcenter, rx, ry, rz;
    float r, g, b, a;
public:
    /*!
     * \brief Ativa todos os voxels que satisfazem à equação da elipsoide e atribui aos mesmos a cor atual de desenho (r,g,b,a).
     * \param _xcenter centro da elipsoide na cordenada x.
     * \param _ycenter centro da elipsoide na cordenada y.
     * \param _zcenter centro da elipsoide na cordenada z.
     * \param _rx Semi-eixo principal x da elipsoide.
     * \param _ry Semi-eixo principal y da elipsoide.
     * \param _rz Semi-eixo principal z da elipsoide.
     * \param _r define a cor vermelha.
     * \param _g define a cor verde.
     * \param _b define a cor azul.
     * \param _a define a opacidade.
     */
    PutEllipsoid(int _xcenter, int _ycenter, int _zcenter, int _rx, int _ry, int _rz, float _r, float _g, float _b, float _a);
    ~PutEllipsoid();
    /*!
     * \brief Ativa voxels selecionados no PutEllipsoid.
     * \param t
     */
    void draw(Sculptor &t);
};

#endif // PUTELLIPSOID_H
