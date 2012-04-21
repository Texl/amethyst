//------------------------------------------------------------------------------
// File:    SceBox.cpp
//------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------
#include "SceObject.h"
#include "cinder/Ray.h"
#include "cinder/Vector.h"
//------------------------------------------------------------------------------
class SceBox: public SceObject
{
    public:
        void Precalculate       ();
        bool FindIntersection   ( Ray const & ray, float &t, Vec3f & point, Vec3f & normal );

        Vec3f v;
        Vec3f l;
        Vec3f w;
        Vec3f h;

        //precalculated variables
        Vec3f points[6];
        Vec3f normals[6];
};
//------------------------------------------------------------------------------
