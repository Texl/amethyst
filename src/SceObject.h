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
        explicit        SceObject           ( Material const & material );
        virtual         ~SceObject          ();

        virtual bool    FindIntersection    ( Ray const & ray, float & t, Vec3f & point, Vec3f & normal ) = 0;

        Material        mMaterial;
        Vec3f           mPosition;
        Quatf           mOrientation;
        Vec3f           mScale;
};
//------------------------------------------------------------------------------
