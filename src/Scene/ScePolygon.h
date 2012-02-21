//------------------------------------------------------------------------------
// File:    ScePolygon.cpp
//------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------
#include <vector>

#include "Math/MatRay.h"
#include "cinder/Vector.h"
#include "Scene/SceObject.h"
//------------------------------------------------------------------------------
class ScePolygon : public SceObject
{
    public:
        void Precalculate();
        bool FindIntersection( MatRay const & ray, float &t, Vec3f &point, Vec3f &normal);

        int n;
        std::vector< Vec3f > v;

        //precalculated variables
        std::vector< Vec3f >    vc;
        std::vector< Vec3f >    va;
        std::vector< Vec3f >    vb;
        std::vector< Vec3f >    vn;
        std::vector< float >    denom1Inv;
        std::vector< float >    denom2Inv;
        std::vector< float >    denom3Inv;
};
//------------------------------------------------------------------------------
