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
  void getXyzdataFromString(std::string inputString);
  std::string outputXYZdataToString();
  std::string outputZdataToString();
  void convertZdataToXYZdata();
  void convertXYZdataToZdata();
  XyzStruct xyzData;
  ZmatrixStruct zmatrixData;
  double x;
  Vec3D rotateVector(Vec3D vecin,Vec3D rotaxe,double angle); //should be in some kind of vectorManipulation class, not a member of data
private:
};

#endif
