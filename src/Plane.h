//------------------------------------------------------------------------------
// File:    Plane.h
//------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------
#include "cinder/Ray.h"
#include "cinder/Vector.h"
//------------------------------------------------------------------------------
using namespace ci;
//------------------------------------------------------------------------------
class Plane
{
public:
    explicit    Plane   (Vec3f const & point, 
                         Vec3f const & normal);

    bool        Raycast (Ray const & ray,
                         float & t, 
                         Vec3f & point, 
                         Vec3f & normal) const;

private:
    // mPoint.dot(mNormal) + mD = 0
    Vec3f   mPoint;
    Vec3f   mNormal;
};
//------------------------------------------------------------------------------
inline
Plane::Plane(Vec3f const & point, 
             Vec3f const & normal)
: mPoint    (point)
, mNormal   (normal)
{
}
//------------------------------------------------------------------------------
inline
bool
Plane::Raycast(Ray const & ray,
               float & t, 
               Vec3f & point, 
               Vec3f & normal) const
{
    float const tIntersection = (mPoint - ray.getOrigin()).dot(mNormal) / ray.getDirection().dot(mNormal);

    if (tIntersection < 0)
    {
        return false;
    }

    t = tIntersection;
    point = ray.calcPosition(tIntersection);
    normal = mNormal;
    return true;
}
//------------------------------------------------------------------------------