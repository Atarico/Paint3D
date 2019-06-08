#include "sculptor.h"
#include <vector>

/*!
 * Construtor da classe para geração da matriz tridimensional.
 * \param _nx numero de linha
 * \param _ny numero de colunas
 * \param _nz numero de planos
 */

Sculptor::Sculptor()
{

}

Sculptor::Sculptor(int _nx, int _ny, int _nz)
{
    nx = _nx; ny = _ny; nz = _nz;

    if(nx < 0 or ny < 0 or nz < 0)
    {
        nx = 0; ny = 0; nz = 0;
    }

    //allocates X
    v = new Voxel**[nx];
    //verifies if X has been allocated
    if(v == nullptr)
    {
        cout<<"Error allocating the lines of the voxel matrix"<<endl;
        exit(0);
    }

    //allocates X's collumns
    v[0] = new Voxel*[nx*ny];
    //verifies if X[0] has been allocated
    if(v[0] == nullptr)
    {
        cout<<"Error allocating the columns of the voxel matrix"<<endl;
        exit(0);
    }

    //allocates X's planes
    v[0][0] = new Voxel[nx*ny*nz];
    //verifies if X[0] has been allocated
    if(v[0][0] == nullptr)
    {
        cout<<"Error allocating the planes of the voxel matrix"<<endl;
        exit(0);
    }


    //indexing X's collumns
    for(int i = 1; i<nx; i++){
        v[i] = v[i-1] + ny;
    }

    //indexing X's planes
    for(int i = 1; i<nx*ny; i++){
        v[0][i] = v[0][i-1] + nz;
    }

    //making every voxel invisible so we have a clean canvas
    for(int i = 0; i<nx; i++){
        for(int j = 0; j<ny; j++){
            for(int k = 0; k<nz; k++){
                v[i][j][k].isOn = false;
            }
        }
    }
}
/*!
 * Destrutor da classe
 */

Sculptor::~Sculptor()
{
    if(nx < 0 or ny < 0 or nz < 0)
    {
        return;
    }

    delete [] v[0][0];
    delete [] v[0];
    delete [] v;
}

/*!
 * Define a cor atual de desenho.
 * \param red  define a cor vermelha
 * \param green define a cor verde
 * \param blue define a cor azul
 * \param alpha define a opacidade
 */

void Sculptor::setColor(float red, float green, float blue, float alpha)
{
    r = red;
    g = green;
    b = blue;
    a = alpha;
}

/*!
 * Ativa o voxel na posição (x,y,z) e atribui ao mesmo a cor atual de desenho
 * \param x posição "x"
 * \param y posição "y"
 * \param z posição "z"
 */
void Sculptor::putVoxel(int x, int y, int z)
{
    if(x>=0 && x<nx &&
       y>=0 && y<ny &&
       z>=0 && z<nz){
        v[x][y][z].isOn = true;
        v[x][y][z].r = r;
        v[x][y][z].g = g;
        v[x][y][z].b = b;
        v[x][y][z].a = a;
    }
}

/*!
 * Desativa o voxel na posição (x,y,z)
 * \param x posição x
 * \param y posição y
 * \param z posição z
 */
void Sculptor::cutVoxel(int x, int y, int z)
{
    if(x>=0 && x<nx &&
       y>=0 && y<ny &&
       z>=0 && z<nz){
        v[x][y][z].isOn = false;
    }
}

/*!
 * Retorna uma matriz 2D (vetor de vetores) de Voxels do plano XY.
 * \param zFactor um fator de profundidade que varia de 0 a 1. Permite o retorno de diferentes planos desde o plano zero até o plano nz-1.
 */
vector<vector<Voxel>> Sculptor::planeXY(float zFactor)
{
    int z0 = int(nz*zFactor);

    vector<vector<Voxel>> plane;
    vector<Voxel> line;
    for(int i = 0; i<nx; i++){
        for(int j = 0; j<ny; j++){
            line.push_back(v[i][j][z0]);
        }
        plane.push_back(line);
        line.clear();
    }

    return plane;
}

/*!
 * Retorna uma matriz 2D (vetor de vetores) de Voxels do plano XZ.
 * \param yFactor um fator de profundidade que varia de 0 a 1. Permite o retorno de diferentes planos desde o plano zero até o plano ny-1.
 */
vector<vector<Voxel>> Sculptor::planeXZ(float yFactor)
{
    int y0 = int(nz*yFactor);

    vector<vector<Voxel>> plane;
    vector<Voxel> line;
    for(int i = 0; i<nx; i++){
        for(int k = 0; k<nz; k++){
            line.push_back(v[i][y0][k]);
        }
        plane.push_back(line);
        line.clear();
    }

    return plane;
}

/*!
 * Retorna uma matriz 2D (vetor de vetores) de Voxels do plano YZ.
 * \param xFactor um fator de profundidade que varia de 0 a 1. Permite o retorno de diferentes planos desde o plano zero até o plano nx-1.
 */
vector<vector<Voxel>> Sculptor::planeYZ(float xFactor)
{
    int x0 = int(nz*xFactor);

    vector<vector<Voxel>> plane;
    vector<Voxel> line;
    for(int j = 0; j<ny; j++){
        for(int k = 0; k<nz; k++){
            line.push_back(v[x0][j][k]);
        }
        plane.push_back(line);
        line.clear();
    }

    return plane;
}

/*!
 * Escreve um arquivo "filename".off no diretório do arquivo .exe com uma representação de nossa matriz 3D de voxels, 
 * permitindo a visualização da matriz em um software externo de representação 3D, como o 
	<a href="http://www.meshlab.net" target="_blank">Meshlab</a>(Windows) ou o 
	<a href="http://www.geomview.org/" target="_blank">Geomview</a>(Linux).
 * \param filename string que será usada como nome do arquivo na hora de escreve-lo na memória.
 */
void Sculptor::writeOFF(string filename)
{
    ofstream fout;


    fout.open("./"+filename+".off");
    if(fout.is_open() == false)
    {
        cout << "arquivo nao foi aberto\n";
        exit(1);
    }

    fout<<"OFF"<<endl;

    int nvoxels = 0;
    for(int i = 0; i<nx; i++){
        for(int j = 0; j<ny; j++){
            for(int k = 0; k<nz; k++){
                if(v[i][j][k].isOn){
                    nvoxels = nvoxels+1;
                }
            }
        }
    }
    fout<<nvoxels*8<<" "<<nvoxels*6<<" 0"<<endl;

    //printing the (x,y,z) position of every vertex (there will be 8 vertices for each voxel)
    //the position of each vertex is shifted by a factor defined below (vRadius)
    //so that the total lenght of one side of the voxel is defined by vRadius*2
    //In the end, we will have each of our voxels separated by a 0.10 length gap from eachother
    float vRadius=0.5f;
    for(int i = 0; i<nx; i++){
        for(int j = 0; j<ny; j++){
            for(int k = 0; k<nz; k++){
                if(v[i][j][k].isOn){
                    fout<<(float)i-vRadius<<" "<<(float)j+vRadius<<" "<<(float)k-vRadius<<endl;
                    fout<<(float)i-vRadius<<" "<<(float)j-vRadius<<" "<<(float)k-vRadius<<endl;
                    fout<<(float)i+vRadius<<" "<<(float)j-vRadius<<" "<<(float)k-vRadius<<endl;
                    fout<<(float)i+vRadius<<" "<<(float)j+vRadius<<" "<<(float)k-vRadius<<endl;
                    fout<<(float)i-vRadius<<" "<<(float)j+vRadius<<" "<<(float)k+vRadius<<endl;
                    fout<<(float)i-vRadius<<" "<<(float)j-vRadius<<" "<<(float)k+vRadius<<endl;
                    fout<<(float)i+vRadius<<" "<<(float)j-vRadius<<" "<<(float)k+vRadius<<endl;
                    fout<<(float)i+vRadius<<" "<<(float)j+vRadius<<" "<<(float)k+vRadius<<endl;
                }
            }
        }
    }

    fout << std::setprecision(1) << fixed;

    //printing the order of connection of 4 vertices to define a face (there will be 6 faces for each voxel)
    int vcn = 0; //vertex count for each activated vertex
    for(int i = 0; i<nx; i++){
        for(int j = 0; j<ny; j++){
            for(int k = 0; k<nz; k++){
                if(v[i][j][k].isOn){
                    //int vcn = vc*8; //vertex count multipled by 8, so that we jump 8 vertices in our printing every time we change voxel

                    fout<<"4 "<<vcn+0<<" "<<vcn+3<<" "<<vcn+2<<" "<<vcn+1<<" "<<v[i][j][k].r<<" "<<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl;
                    fout<<"4 "<<vcn+4<<" "<<vcn+5<<" "<<vcn+6<<" "<<vcn+7<<" "<<v[i][j][k].r<<" "<<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl;
                    fout<<"4 "<<vcn+0<<" "<<vcn+1<<" "<<vcn+5<<" "<<vcn+4<<" "<<v[i][j][k].r<<" "<<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl;
                    fout<<"4 "<<vcn+0<<" "<<vcn+4<<" "<<vcn+7<<" "<<vcn+3<<" "<<v[i][j][k].r<<" "<<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl;
                    fout<<"4 "<<vcn+3<<" "<<vcn+7<<" "<<vcn+6<<" "<<vcn+2<<" "<<v[i][j][k].r<<" "<<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl;
                    fout<<"4 "<<vcn+1<<" "<<vcn+2<<" "<<vcn+6<<" "<<vcn+5<<" "<<v[i][j][k].r<<" "<<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl;

                    vcn = vcn+8;
                }
            }
        }
    }
}

/*!
 * Escreve um arquivo "filename".vect no diretório do arquivo .exe com uma representação de nossa matriz 3D de voxels, 
 * permitindo a visualização da matriz em um software externo de representação 3D, como o 
	<a href="http://www.meshlab.net" target="_blank">Meshlab</a>(Windows) ou o 
	<a href="http://www.geomview.org/" target="_blank">Geomview</a>(Linux).
 * \param filename string que será usada como nome do arquivo na hora de escreve-lo na memória.
 */
void Sculptor::writeVECT(string filename)
{
    ofstream fout;

    fout.open("./"+filename+".vect");
    if(fout.is_open() == false)
    {
        cout << "arquivo nao foi aberto\n";
        exit(1);
    }

    fout<<"VECT"<<endl;

    int nvoxels = 0;
    for(int i = 0; i<nx; i++){
        for(int j = 0; j<ny; j++){
            for(int k = 0; k<nz; k++){
                if(v[i][j][k].isOn){
                    nvoxels = nvoxels+1;
                }
            }
        }
    }
    fout<<nvoxels<<" "<<nvoxels<<" "<<nvoxels<<endl;

    for(int i = 1; i<nvoxels; i++){
        fout<<"1 ";
    }
    fout<<"1"<<endl;

    for(int i = 1; i<nvoxels; i++){
        fout<<"1 ";
    }
    fout<<"1"<<endl;

    for(int i = 0; i<nx; i++){
        for(int j = 0; j<ny; j++){
            for(int k = 0; k<nz; k++){
                if(v[i][j][k].isOn){
                    fout<<i<<" "<<j<<" "<<k<<endl;
                }
            }
        }
    }

    for(int i = 0; i<nx; i++){
        for(int j = 0; j<ny; j++){
            for(int k = 0; k<nz; k++){
                if(v[i][j][k].isOn){
                    fout<<v[i][j][k].r<<" "<<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl;
                }
            }
        }
    }

}
