#ifndef SCULPTOR_H
#define SCULPTOR_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;

//definition of our voxel type
struct Voxel {
  float r,g,b; // Colors
  float a; // Transparency
  bool isOn; // Included or not
};


//definition of our sculptor class
class Sculptor {
protected:
  int nx, ny, nz; // Dimensions
  Voxel ***v; // 3D matrix
  float r,g,b,a; // Current drawing color
public:
  Sculptor();
  Sculptor(int _nx, int _ny, int _nz);
  ~Sculptor();
  void setColor(float red, float green, float blue, float alpha);
  void putVoxel(int x, int y, int z);
  void cutVoxel(int x, int y, int z);
  vector<vector<Voxel>> planeXY(float zFactor);
  vector<vector<Voxel>> planeXZ(float yFactor);
  vector<vector<Voxel>> planeYZ(float xFactor);
  vector<vector<vector<Voxel>>> plane3D();
  void writeOFF(string filename);
  void writeVECT(string filename);
};

#endif // SCULPTOR_H
