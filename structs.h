#ifndef STRUCTS_H
#define STRUCTS_H

#include <string>
#include <qmath.h>

struct CoordEntry
{
  char atomname[4];
  double coords[3];
};

struct XyzStruct
{
  static const int nmaxatoms=50;
  int natoms;
  std::string comment;
  CoordEntry entries[nmaxatoms];
};

struct ZmatrixEntry
{
  char atomname[4];
  int  atomindex[3];
  double value[3];
};

struct ZmatrixStruct
{
  static const int nmaxatoms=50;
  int natoms;
  std::string comment;
  ZmatrixEntry entries[nmaxatoms];
};

namespace constants
{
  const double PI = atan(1.0)*4;
}

#endif
