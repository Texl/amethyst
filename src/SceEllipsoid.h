//------------------------------------------------------------------------------
// File:    SceEllipsoid.cpp
//------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------
#include "cinder/Ray.h"
#include "cinder/Vector.h"
#include "SceObject.h"
#include "cinder/Matrix.h"
//------------------------------------------------------------------------------
using namespace ci;
//------------------------------------------------------------------------------
class SceEllipsoid : public SceObject
{
public:
    explicit    SceEllipsoid    (Vec3f const & c, 
                                 Vec3f const & u, 
                                 Vec3f const & v, 
                                 Vec3f const & w, 
                                 Material const & material);

    bool        RayCast         (Ray const & ray,
                                 float & t) const;

    bool        RayCast         (Ray const & ray, 
                                 float & t, 
                                 Vec3f & point, 
                                 Vec3f & normal) const;

private:
    Vec3f       mCenter;
    Matrix33f   mMatrixInv;
    Matrix33f   mMatrixInvTInv;
};
//------------------------------------------------------------------------------
