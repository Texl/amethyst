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
        explicit    SceBox              ( Vec3f const & v, Vec3f const & l, Vec3f const & w, Vec3f const & h, Material const & material );
        bool        FindIntersection    ( Ray const & ray, float & t, Vec3f & point, Vec3f & normal );

    private:
        Vec3f v;
        Vec3f l;
        Vec3f w;
        Vec3f h;

        Vec3f points[6];
        Vec3f normals[6];
};
//------------------------------------------------------------------------------
