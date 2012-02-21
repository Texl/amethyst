//------------------------------------------------------------------------------
// File:    SceObject.cpp
//------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------
#include "cinder/Vector.h"
#include "Math/MatRay.h"
#include "cinder/Color.h"
//------------------------------------------------------------------------------
using namespace ci;
//------------------------------------------------------------------------------
class SceObject
{
    public:
        virtual         ~SceObject          ();

        virtual bool    FindIntersection    ( MatRay const & ray, float & t, Vec3f & point, Vec3f & normal ) = 0;
        virtual void    Precalculate        ();

        //surface properties
        Color   color;
        float   specularCoefficient;
        float   specularExponent;
        Color   attenuation;
        float   permittivity;
        float   permeability;
        float   nt;
};
//------------------------------------------------------------------------------
