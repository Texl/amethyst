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
    explicit    SceSphere   (Vec3f const & center, 
                             float const radius, 
                             Material const & material);

    bool        RayCast     (Ray const & ray,
                             float & t) const;

    bool        RayCast     (Ray const & ray, 
                             float & t, 
                             Vec3f & point, 
                             Vec3f & normal) const;

private:
    Vec3f   mCenter;
    float   mRadius;
};
//------------------------------------------------------------------------------
