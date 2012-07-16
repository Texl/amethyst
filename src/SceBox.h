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
    explicit    SceBox      (Vec3f const & origin, 
                             Vec3f const & length, 
                             Vec3f const & width, 
                             Vec3f const & height, 
                             Material const & material);

    bool        RayCast     (Ray const & ray,
                             float & t) const;

    bool        RayCast     (Ray const & ray, 
                             float & t, 
                             Vec3f & point, 
                             Vec3f & normal) const;

private:
    bool        _RayCast    (Ray const & ray,
                             float & t,
                             unsigned int & index) const;

    Vec3f	    mPoints[6];
    Vec3f	    mNormals[6];
};
//------------------------------------------------------------------------------
