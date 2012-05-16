//------------------------------------------------------------------------------
// File:    SceEllipsoid.cpp
//------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------
#include "cinder/Ray.h"
#include "cinder/Vector.h"
#include "SceObject.h"
#include "cinder/Matrix.h"
//------------------------------------------------------------------------------
using namespace ci;
//------------------------------------------------------------------------------
class SceEllipsoid : public SceObject
{
    public:
        explicit    SceEllipsoid        ( Vec3f const & c, Vec3f const & u, Vec3f const & v, Vec3f const & w, Material const & material );
        bool        FindIntersection    ( Ray const & ray, float & t, Vec3f & point, Vec3f & normal );

    private:
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
