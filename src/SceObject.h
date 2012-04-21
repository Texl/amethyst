//------------------------------------------------------------------------------
// File:    SceObject.cpp
//------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------
#include "cinder/Color.h"
#include "cinder/Vector.h"
#include "cinder/Ray.h"
//------------------------------------------------------------------------------
using namespace ci;
//------------------------------------------------------------------------------
class SceObject
{
    public:
        explicit        SceObject           ();
        explicit        SceObject           ( float const permittivity, float const permeability );
        virtual         ~SceObject          ();

        virtual bool    FindIntersection    ( Ray const & ray, float & t, Vec3f & point, Vec3f & normal ) = 0;
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
