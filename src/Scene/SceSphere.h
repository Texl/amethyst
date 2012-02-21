//------------------------------------------------------------------------------
// File:    SceSphere.cpp
//------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------
#include "Math/MatRay.h"
#include "cinder/Vector.h"
#include "Scene/SceObject.h"
//------------------------------------------------------------------------------
class SceSphere: public SceObject
{
    public:
        Vec3f c;
        float r;

        void Precalculate();
        bool FindIntersection( MatRay const & ray, float &t, Vec3f &point, Vec3f &normal);
};
//------------------------------------------------------------------------------
