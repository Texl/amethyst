//------------------------------------------------------------------------------
// File:    SceObject.cpp
//------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------
#include "cinder/Color.h"
#include "cinder/Vector.h"
#include "cinder/Quaternion.h"
#include "cinder/Ray.h"

#include "Material.h"
//------------------------------------------------------------------------------
using namespace ci;
//------------------------------------------------------------------------------
class SceObject
{
public:
    explicit        SceObject   (Material const & material);

    virtual         ~SceObject  ();

    virtual bool    RayCast     (Ray const & ray,
                                 float & t) const = 0;

    virtual bool    RayCast     (Ray const & ray, 
                                 float & t, 
                                 Vec3f & point, 
                                 Vec3f & normal) const = 0;

    Material        mMaterial;
};
//------------------------------------------------------------------------------
