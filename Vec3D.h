#ifndef VEC3D_HPP
#define VEC3D_HPP

#include <qmath.h> 

class Vec3D
{
  private:
    double data[3];

  public:
    Vec3D();
    Vec3D(double x, double y, double z);

    Vec3D& operator=(const Vec3D& v);
    double& operator[](int i);

    double operator* (const Vec3D& v) const;
    Vec3D operator* (const double s) const;
    Vec3D operator/ (const double s) const;
    Vec3D operator+ (const Vec3D& v);
    Vec3D operator- (const Vec3D& v);

    double sqr() const;
    double len() const;

    Vec3D cross(const Vec3D& v) const;

};

#endif
