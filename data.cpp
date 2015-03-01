#include "data.h"
#include "structs.h"
#include "Vec3D.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

Data::Data()
{
}

Data::~Data()
{
}

void Data::getZdataFromString(std::string inputString)
{
  std::stringstream istringstrm(inputString);
  istringstrm >> zmatrixData.natoms; //TODO print error if natoms>nmaxatoms
  istringstrm.ignore(10000,'\n');
  istringstrm >> zmatrixData.comment;
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

void Data::getXyzdataFromString(std::string inputString)
{
  std::stringstream istringstrm(inputString);
  istringstrm >> xyzData.natoms; //TODO print error if natoms>nmaxatoms
  istringstrm.ignore(10000,'\n');
  istringstrm >> xyzData.comment;
  istringstrm.ignore(10000,'\n'); 
  for(int i=0;i<xyzData.natoms;i++)
  {
    istringstrm >> xyzData.entries[i].atomname;
    for(int j=0;j<3;j++)
    {
      istringstrm >> xyzData.entries[i].coords[j];
    }
    istringstrm.ignore(10000,'\n');
  }
};

std::string Data::outputXYZdataToString()
{
  std::ostringstream strs;
  strs << xyzData.natoms;
  std::string outputString=strs.str();
  outputString.append("\n");
  outputString.append(xyzData.comment);
  outputString.append(" Converted from z-matrix\n");
  for(int i=0;i<xyzData.natoms;i++)
  {
    std::string lineString;
    lineString=xyzData.entries[i].atomname;
    lineString.append(" ");
    for(int j=0;j<3;j++)
    {
      std::ostringstream strstream;
      strstream << xyzData.entries[i].coords[j];
      lineString.append(strstream.str());
      lineString.append(" ");
    }
    lineString.append("\n");
    outputString.append(lineString);
  }
  return outputString;
};

std::string Data::outputZdataToString()
{
  std::ostringstream strs;
  strs << zmatrixData.natoms;
  std::string outputString=strs.str();
  outputString.append("\n");
  outputString.append(zmatrixData.comment);
  outputString.append(" Converted from xyz-format data\n");
  //first line
  outputString.append(zmatrixData.entries[0].atomname);
  outputString.append("\n");
  //second line
  std::ostringstream strstream;
  strstream << zmatrixData.entries[1].atomname;  
  strstream << " ";
  strstream << zmatrixData.entries[1].atomindex[0];
  strstream << " ";
  strstream << zmatrixData.entries[1].value[0];
  strstream << "\n";
  outputString.append(strstream.str());
  //third line
  strstream.str("");
  strstream.clear();
  strstream << zmatrixData.entries[2].atomname;  
  strstream << " ";
  strstream << zmatrixData.entries[2].atomindex[0];
  strstream << " ";
  strstream << zmatrixData.entries[2].value[0];
  strstream << " ";
  strstream << zmatrixData.entries[2].atomindex[1];
  strstream << " ";
  strstream << zmatrixData.entries[2].value[1];
  strstream << "\n";
  outputString.append(strstream.str());
  //remaining lines
  for(int i=3;i<zmatrixData.natoms;i++)
  {
    strstream.str("");
    strstream.clear();
    strstream << zmatrixData.entries[i].atomname;  
    strstream << " ";
    for(int j=0;j<3;j++)
    {
      strstream << zmatrixData.entries[i].atomindex[j];
      strstream << " ";
      strstream << zmatrixData.entries[i].value[j];
      strstream << " ";
    }
    outputString.append(strstream.str());
    outputString.append("\n");
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
  xyzData.comment=zmatrixData.comment;

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
  theta=zmatrixData.entries[2].value[1]/180.0*constants::PI;
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
    theta=zmatrixData.entries[i].value[1]/180.0*constants::PI;
    phi=zmatrixData.entries[i].value[2]/180.0*constants::PI;
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
    double cosphi=normABC*normBCD/normABC.len()/normBCD.len();
    if (cosphi>1.0) {cosphi=1.0;} //numerical error
    phicurr=acos(cosphi); //TODO always 0?
    phi=phi-phicurr;
    vecBA=rotateVector(vecBA,vecBC,phi);
    Vec3D rA=vecBA+rB;

    xyzData.entries[indexBase].coords[0]=rA[0];
    xyzData.entries[indexBase].coords[1]=rA[1];
    xyzData.entries[indexBase].coords[2]=rA[2];
  }

};

void Data::convertXYZdataToZdata()
{
  Vec3D vecDist,vecAngle,vecDih;
  std::vector<Vec3D> xyzCoords;
  for(int i=0;i<xyzData.natoms;i++)
  {
    xyzCoords.push_back(Vec3D(xyzData.entries[i].coords[0],xyzData.entries[i].coords[1],xyzData.entries[i].coords[2]));
  }

  zmatrixData.natoms=xyzData.natoms;
  zmatrixData.comment=xyzData.comment;

  for(int i=0;i<xyzData.natoms;i++)
  {
    strncpy(zmatrixData.entries[i].atomname,xyzData.entries[i].atomname, sizeof zmatrixData.entries[i].atomname);
    if (i>0)
    {
      //dist
      zmatrixData.entries[i].atomindex[0]=i;
      vecDist=xyzCoords[i]-xyzCoords[i-1]; 
      zmatrixData.entries[i].value[0]=vecDist.len();
      if (i>1)
      {
        //angle
        zmatrixData.entries[i].atomindex[1]=i-1;
        vecAngle=xyzCoords[i-2]-xyzCoords[i-1];
        zmatrixData.entries[i].value[1]=acos(vecDist*vecAngle/(vecDist.len()*vecAngle.len()))*180.0/constants::PI;
        if (i>2)
        {
          //dihedral
          zmatrixData.entries[i].atomindex[2]=i-2;
          vecDih=xyzCoords[i-2]-xyzCoords[i-3];
          vecAngle=vecAngle*-1.0;
          Vec3D vecTemp1=vecDist.cross(vecAngle);
          Vec3D vecTemp2=vecAngle.cross(vecDih);
          double b=vecTemp1*vecTemp2/(vecTemp1.len()*vecTemp2.len());
          zmatrixData.entries[i].value[2]=acos(b)*180.0/constants::PI;
        }
      }
    }
  }
};

Vec3D Data::rotateVector(Vec3D vecin,Vec3D rotaxe,double theta) 
{
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

