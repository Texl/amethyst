//------------------------------------------------------------------------------
// File:    Triangle.h
//------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------
#include "cinder/Ray.h"
#include "cinder/Vector.h"
//------------------------------------------------------------------------------
using namespace ci;
//------------------------------------------------------------------------------
class Triangle
{
public:
    explicit    Triangle    (Vec3f const & a, 
                             Vec3f const & b, 
                             Vec3f const & c);

    bool        Raycast     (Ray const & ray) const;

    bool        Raycast     (Ray const & ray,
                             float & t) const;

    bool        Raycast     (Ray const & ray,
                             float & t, 
                             Vec3f & point, 
                             Vec3f & normal) const;

private:
    Vec3f   mA;
    Vec3f   mB;
    Vec3f   mC;
    Vec3f   mNormal;
    Vec3f   mAB;
    Vec3f   mAC;
    float   mDot00;
    float   mDot01;
    float   mDot11;
    float   mInvDenom;
};
//------------------------------------------------------------------------------