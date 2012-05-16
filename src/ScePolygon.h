//------------------------------------------------------------------------------
// File:    ScePolygon.cpp
//------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------
#include <vector>

#include "cinder/Ray.h"
#include "cinder/Vector.h"
#include "SceObject.h"
//------------------------------------------------------------------------------
using namespace std;
//------------------------------------------------------------------------------
class ScePolygon : public SceObject
{
    public:
        explicit    ScePolygon          ( vector< Vec3f > const & vertices, Material const & material );
        bool        FindIntersection    ( Ray const & ray, float & t, Vec3f & point, Vec3f & normal );

    private:
        int             n;
        vector< Vec3f > v;

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
