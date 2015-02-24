#include "Vec3D.h"

Vec3D::Vec3D() {}

Vec3D::Vec3D(double x, double y, double z) {
  data[0] = x;
  data[1] = y;
  data[2] = z;
}

double &Vec3D::operator[](int i)
{ return data[i]; }

Vec3D &Vec3D::operator=(const Vec3D &v) {
    data[0] = v.data[0];
    data[1] = v.data[1];
    data[2] = v.data[2];
    return *this;
}

Vec3D Vec3D::operator+(const Vec3D& v)
{
  Vec3D temp(0.0,0.0,0.0);
  temp.data[0]=data[0]+v.data[0];
  temp.data[1]=data[1]+v.data[1];
  temp.data[2]=data[2]+v.data[2];
  return temp;
}

Vec3D Vec3D::operator-(const Vec3D& v)
{
  Vec3D temp(0.0,0.0,0.0);
  temp.data[0]=data[0]-v.data[0];
  temp.data[1]=data[1]-v.data[1];
  temp.data[2]=data[2]-v.data[2];
  return temp;
}

Vec3D Vec3D::operator*(const double s) const
{
  Vec3D temp(0.0,0.0,0.0);
  temp.data[0]=data[0]*s;
  temp.data[1]=data[1]*s;
  temp.data[2]=data[2]*s;
  return temp;
}

Vec3D Vec3D::operator/(const double s) const
{
  Vec3D temp(0.0,0.0,0.0);
  temp.data[0]=data[0]/s;
  temp.data[1]=data[1]/s;
  temp.data[2]=data[2]/s;
  return temp;
}

double Vec3D::operator* (const Vec3D& v) const
{ return data[0]*v.data[0] + data[1]*v.data[1] + data[2]*v.data[2]; }


double Vec3D::sqr() const
{ return data[0]*data[0] + data[1]*data[1] + data[2]*data[2]; }

double Vec3D::len() const
{ return sqrt(Vec3D::sqr()); }

Vec3D Vec3D::cross(const Vec3D& v) const
{
  return Vec3D(data[1]*v.data[2] - data[2]*v.data[1],
               data[2]*v.data[0] - data[0]*v.data[2],
               data[0]*v.data[1] - data[1]*v.data[0]);
}

