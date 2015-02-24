#ifndef DATA_H
#define DATA_H

#include "structs.h"
#include "Vec3D.h"
#include <iostream>

class Data
{
public:
  Data();
  ~Data();
  void getZdataFromString(std::string inputString);
  std::string outputXYZdataToString();
  void convertZdataToXYZdata();
  XyzStruct xyzData;
  ZmatrixStruct zmatrixData;
  double x;
  Vec3D rotateVector(Vec3D vecin,Vec3D rotaxe,double angle);
private:
};

#endif
