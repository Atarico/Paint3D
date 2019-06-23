#ifndef PUTSPHERE_H
#define PUTSPHERE_H
#include "geometricfigure.h"

class PutSphere : public GeometricFigure
{
protected:
    int xcenter, ycenter, zcenter, radius;
    float r, g, b, a;
public:
    /*!
     * \brief Ativa todos os voxels que satisfazem à equação da esfera e atribui aos mesmos a cor atual de desenho (r,g,b,a).
     * \param _xcenter Centro da esfera na coordenada x.
     * \param _ycenter Centro da esfera na coordenada y.
     * \param _zcenter Centro da esfera na coordenada z.
     * \param _radius raio da esfera
     * \param _r define a cor vermelha.
     * \param _g define a cor verde.
     * \param _b define a cor azul.
     * \param _a define a opacidade.
     */
    PutSphere(int _xcenter, int _ycenter, int _zcenter, int _radius, float _r, float _g, float _b, float _a);
    ~PutSphere();
    /*!
     * \brief Ativa voxels selecionados no PutSphere.
     * \param t
     */
    void draw(Sculptor &t);
};

#endif // PUTSPHERE_H
