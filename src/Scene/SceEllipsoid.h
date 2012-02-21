//------------------------------------------------------------------------------
// File:    SceEllipsoid.cpp
//------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------
#include "Math/MatRay.h"
#include "cinder/Vector.h"
#include "Scene/SceObject.h"
#include "cinder/Matrix.h"
//------------------------------------------------------------------------------
using namespace ci;
//------------------------------------------------------------------------------
class SceEllipsoid : public SceObject
{
    public:
        void Precalculate       ();
        bool FindIntersection   ( MatRay const & ray, float & t, Vec3f & point, Vec3f & normal );

        Vec3f c;
        Vec3f u;
        Vec3f v;
        Vec3f w;

        //precalculated variables
        Matrix33f m;
        Matrix33f mInv;
        Matrix33f mInvTInv;
};
//------------------------------------------------------------------------------
