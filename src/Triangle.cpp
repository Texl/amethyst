//------------------------------------------------------------------------------
// File:    Triangle.cpp
//------------------------------------------------------------------------------
#include "Triangle.h"
//------------------------------------------------------------------------------
Triangle::Triangle(Vec3f const & a, 
                   Vec3f const & b, 
                   Vec3f const & c)
: mA        (a)
, mB        (b)
, mC        (c)
, mNormal   ((c - a).cross(b - a).normalized())
, mAB       (mB - mA)
, mAC       (mC - mA)
, mDot00    (mAB.dot(mAB))
, mDot01    (mAB.dot(mAC))
, mDot11    (mAC.dot(mAC))
, mInvDenom (1.0f / (mDot00 * mDot11 - mDot01 * mDot01))
{
}
//------------------------------------------------------------------------------
bool
Triangle::Raycast(Ray const & ray) const
{
    float tIntersection;

    return Raycast(ray, tIntersection);
}
//------------------------------------------------------------------------------
bool
Triangle::Raycast(Ray const & ray,
                  float & t) const
{
    float const tIntersection = (mA - ray.getOrigin()).dot(mNormal) / ray.getDirection().dot(mNormal);

    if (tIntersection < 0)
    {
        return false;
    }

    Vec3f const p = ray.calcPosition(tIntersection);

    Vec3f const ap = p - mA;

    float const dot02 = mAB.dot(ap);
    float const dot12 = mAC.dot(ap);

    float u = (mDot11 * dot02 - mDot01 * dot12) * mInvDenom;
    float v = (mDot00 * dot12 - mDot01 * dot02) * mInvDenom;
        
    if (u >= 0 && v >= 0 && u + v <= 1.0f)
    {
        t = tIntersection;
        return true;
    }

    return false;
}
//------------------------------------------------------------------------------
bool
Triangle::Raycast(Ray const & ray, 
                  float & t, 
                  Vec3f & point, 
                  Vec3f & normal) const
{
    float tIntersection;

    if (Raycast(ray, tIntersection))
    {
        t = tIntersection;
        point = ray.calcPosition(t);
        normal = mNormal;
        return true;
    }

    return false;
}
//------------------------------------------------------------------------------