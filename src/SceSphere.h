//------------------------------------------------------------------------------
// File:    SceSphere.cpp
//------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------
#include "cinder/Ray.h"
#include "cinder/Vector.h"
#include "SceObject.h"
//------------------------------------------------------------------------------
class SceSphere: public SceObject
{
    public:
        Vec3f c;
        float r;

        void Precalculate();
        bool FindIntersection( Ray const & ray, float &t, Vec3f &point, Vec3f &normal);
};
//------------------------------------------------------------------------------
