//------------------------------------------------------------------------------
// File:    ScePolygon.cpp
//------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------
#include <vector>

#include "cinder/Ray.h"
#include "cinder/Vector.h"
#include "SceObject.h"
#include "Triangle.h"
//------------------------------------------------------------------------------
using namespace std;
//------------------------------------------------------------------------------
class ScePolygon : public SceObject
{
public:
    explicit    ScePolygon  (vector<Vec3f> const & vertices, 
                             Material const & material);

    bool        RayCast     (Ray const & ray,
                             float & t) const;

    bool        RayCast     (Ray const & ray, 
                             float & t, 
                             Vec3f & point, 
                             Vec3f & normal) const;

private:
    vector<Triangle>    mTriangles;
};
//------------------------------------------------------------------------------
