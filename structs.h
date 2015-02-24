#ifndef STRUCTS_H
#define STRUCTS_H

struct CoordEntry
{
    char atomname[4];
    double coords[3];
};

struct XyzStruct
{
    static const int nmaxatoms=50;
    int natoms;
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
    ZmatrixEntry entries[nmaxatoms];
};

#endif
