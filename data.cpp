#include "data.h"
#include "structs.h"
#include "Vec3D.h"
#include <iostream>
#include <string>
#include <sstream>

Data::Data()
{
  //xyzData = new XyzStruct();
  //zmatrixData = new ZmatrixStruct();
}

Data::~Data()
{
  //delete xyzData;
  //delete zmatrixData;
}

void Data::getZdataFromString(std::string inputString)
{
  std::stringstream istringstrm(inputString);
  istringstrm >> zmatrixData.natoms;
//TODO print error if natoms>nmaxatoms
  istringstrm.ignore(10000,'\n');
  //first line
  istringstrm >> zmatrixData.entries[0].atomname;
  istringstrm.ignore(10000,'\n');
  //second line
  istringstrm >> zmatrixData.entries[1].atomname;
  istringstrm >> zmatrixData.entries[1].atomindex[0]; //TODO check validity of z-matrix, eg is this =1?
  istringstrm >> zmatrixData.entries[1].value[0];
  istringstrm.ignore(10000,'\n');
  //third line
  istringstrm >> zmatrixData.entries[2].atomname;
  istringstrm >> zmatrixData.entries[2].atomindex[0];
  istringstrm >> zmatrixData.entries[2].value[0];
  istringstrm >> zmatrixData.entries[2].atomindex[1];
  istringstrm >> zmatrixData.entries[2].value[1];
  istringstrm.ignore(10000,'\n');
  //remaining lines
  for(int i=3;i<zmatrixData.natoms;i++)
  {
     istringstrm >> zmatrixData.entries[i].atomname;
     for(int j=0;j<3;j++)
     {
       istringstrm >> zmatrixData.entries[i].atomindex[j];
       istringstrm >> zmatrixData.entries[i].value[j];
     }
     istringstrm.ignore(10000,'\n');
  }
};

std::string Data::outputXYZdataToString()
{
  std::ostringstream strs;
  strs << xyzData.natoms;
  //std::string outputString=std::to_string(xyzData.natoms);
  std::string outputString=strs.str();
  outputString.append("\n");
  outputString.append("Converted from z-matrix\n");
  for(int i=0;i<xyzData.natoms;i++)
  {
     std::string lineString;
     lineString=xyzData.entries[i].atomname;
     lineString.append(" ");
     for(int j=0;j<3;j++)
     {
       std::ostringstream strstream;
       strstream << xyzData.entries[i].coords[j];
       //lineString.append(std::to_string(xyzData.entries[i].coords[j]));
       lineString.append(strstream.str());
       lineString.append(" ");
     }
     lineString.append("\n");
     outputString.append(lineString);
  }
  return outputString;
};

void Data::convertZdataToXYZdata()
{
     //A-B-C-D is indexBase-indexDist-indexAngl-indexDihe
     //dist=|AB|
     //theta=angle(ABC)
     //phi=dihedral-angle(ABCD)

     double dist,theta,costheta,sintheta,phi;
     int natoms = zmatrixData.natoms;
     int indexBase,indexDist,indexAngl,indexDihe;

     xyzData.natoms=zmatrixData.natoms;

     //first entry
     strncpy(xyzData.entries[0].atomname,zmatrixData.entries[0].atomname, sizeof xyzData.entries[0].atomname);
     xyzData.entries[0].coords[0]=0.0;
     xyzData.entries[0].coords[1]=0.0;
     xyzData.entries[0].coords[2]=0.0;

     //second entry
     strncpy(xyzData.entries[1].atomname,zmatrixData.entries[1].atomname, sizeof xyzData.entries[1].atomname);
     xyzData.entries[1].coords[0]=0.0;
     xyzData.entries[1].coords[1]=0.0;
     xyzData.entries[1].coords[2]=zmatrixData.entries[1].value[0]; //assumes zmatrix[1].atomindex[0]=1, check previously TODO

     //third entry
     dist=zmatrixData.entries[2].value[0];
     theta=zmatrixData.entries[2].value[1]/180.0*3.14159;
     costheta=cos(theta);
     sintheta=sin(theta);

     indexBase=2;
     indexDist=zmatrixData.entries[2].atomindex[0]-1;
     indexAngl=zmatrixData.entries[2].atomindex[1]-1;

     //vector from B to C
     Vec3D rB=Vec3D(xyzData.entries[indexDist].coords[0],xyzData.entries[indexDist].coords[1],xyzData.entries[indexDist].coords[2]);
     Vec3D rC=Vec3D(xyzData.entries[indexAngl].coords[0],xyzData.entries[indexAngl].coords[1],xyzData.entries[indexAngl].coords[2]);
     Vec3D vecBC=rC-rB;

     //rotate vecBC by angle theta
     Vec3D vecBA=Vec3D(0.0,vecBC[1]*costheta+vecBC[2]*sintheta,vecBC[2]*costheta-vecBC[1]*sintheta);
     vecBA=vecBA*dist/vecBC.len();
     
     Vec3D rA = vecBA+rB;

     strncpy(xyzData.entries[2].atomname,zmatrixData.entries[2].atomname, sizeof xyzData.entries[2].atomname);
     xyzData.entries[indexBase].coords[0]=0.0;
     xyzData.entries[indexBase].coords[1]=rA[1];
     xyzData.entries[indexBase].coords[2]=rA[2];

     for (int i=3;i<natoms;i++) 
     {
       strncpy(xyzData.entries[i].atomname,zmatrixData.entries[i].atomname, sizeof xyzData.entries[i].atomname);

       indexBase=i;
       indexDist=zmatrixData.entries[i].atomindex[0]-1;
       indexAngl=zmatrixData.entries[i].atomindex[1]-1;
       indexDihe=zmatrixData.entries[i].atomindex[2]-1;
       dist=zmatrixData.entries[i].value[0];
       theta=zmatrixData.entries[i].value[1]/180.0*3.14159;
       phi=zmatrixData.entries[i].value[2]/180.0*3.14159;
       costheta=cos(theta);
       sintheta=sin(theta);

       //vector from B to C
       Vec3D rB=Vec3D(xyzData.entries[indexDist].coords[0],xyzData.entries[indexDist].coords[1],xyzData.entries[indexDist].coords[2]);
       Vec3D rC=Vec3D(xyzData.entries[indexAngl].coords[0],xyzData.entries[indexAngl].coords[1],xyzData.entries[indexAngl].coords[2]);
       Vec3D vecBC=rC-rB;

       //rotate vecBC by angle theta
       Vec3D vecBA=Vec3D(0.0,vecBC[1]*costheta+vecBC[2]*sintheta,vecBC[2]*costheta-vecBC[1]*sintheta);
       vecBA=vecBA*dist/vecBC.len();

       //vector from C to D
       Vec3D rD=Vec3D(xyzData.entries[indexDihe].coords[0],xyzData.entries[indexDihe].coords[1],xyzData.entries[indexDihe].coords[2]);
       Vec3D vecDC=rC-rD;
       Vec3D normBCD=vecBC.cross(vecDC);
       Vec3D normABC=vecBA.cross(vecBC);

       //rotate vecBA around vecBC until angle between planes is phi
       vecBC=vecBC/vecBC.len();
       double phicurr; //current angle between planes
       phicurr=acos((normABC*normBCD)/normABC.len()/normBCD.len());
       phi=phi-phicurr;
       vecBA=rotateVector(vecBA,vecBC,phi);
       Vec3D rA=vecBA+rB;

       xyzData.entries[indexBase].coords[0]=rA[0];
       xyzData.entries[indexBase].coords[1]=rA[1];
       xyzData.entries[indexBase].coords[2]=rA[2];
     }
   
};

Vec3D Data::rotateVector(Vec3D vecin,Vec3D rotaxe,double theta) {
      //rotaxe should be normalised
      Vec3D vecout;
      double costheta=cos(theta);
      double invcostheta=1.0-costheta;
      double sintheta=sin(theta);

      vecout[0]=(rotaxe[0]*rotaxe[0]*invcostheta+costheta)*vecin[0] + (rotaxe[0]*rotaxe[1]*invcostheta-rotaxe[2]*sintheta)*vecin[1] + (rotaxe[0]*rotaxe[2]*invcostheta+rotaxe[1]*sintheta)*vecin[2];
      vecout[1]=(rotaxe[1]*rotaxe[0]*invcostheta+rotaxe[2]*sintheta)*vecin[0] + (costheta+rotaxe[1]*rotaxe[1]*invcostheta)*vecin[1] + (rotaxe[1]*rotaxe[2]*invcostheta-rotaxe[0]*sintheta)*vecin[2];
      vecout[2]=(rotaxe[2]*rotaxe[0]*invcostheta-rotaxe[1]*sintheta)*vecin[0] + (rotaxe[2]*rotaxe[1]*invcostheta+rotaxe[0]*sintheta)*vecin[1] + (costheta+rotaxe[2]*rotaxe[2]*invcostheta)*vecin[2];
      return vecout;
};

