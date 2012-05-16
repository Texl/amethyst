//------------------------------------------------------------------------------
// File:    Material.h
//------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------
#include "cinder/Color.h"
#include "cinder/Vector.h"
//------------------------------------------------------------------------------
using namespace ci;
//------------------------------------------------------------------------------
class Material
{
    public:
        Material();
        Material( float const permittivity, float const permeability, Color const & color );

        bool operator==( Material const & rhs ) const;

    public:
        Color   mColor;
        float   mSpecularCoefficient;
        float   mSpecularExponent;
        Color   mAttenuation;
        float   mPermittivity;
        float   mPermeability;
        float   mNt;
};
//-----------------------------------------------------------------------------
inline
Material::Material()
: mColor                ()
, mSpecularCoefficient  ()
, mSpecularExponent     ()
, mAttenuation          ()
, mPermittivity         ()
, mPermeability         ()
, mNt                   ()
{
}
//-----------------------------------------------------------------------------
inline
Material::Material( float const permittivity, float const permeability, Color const & color )
: mColor                ()
, mSpecularCoefficient  ()
, mSpecularExponent     ()
, mAttenuation          ( color )
, mPermittivity         ( permittivity )
, mPermeability         ( permeability )
, mNt                   ()
{
}
//-----------------------------------------------------------------------------
inline
bool
Material::operator==( Material const & rhs ) const
{
    return mColor == rhs.mColor &&
           mSpecularCoefficient == rhs.mSpecularCoefficient &&
           mSpecularExponent == rhs.mSpecularExponent &&
           mAttenuation == rhs.mAttenuation &&
           mPermittivity == rhs.mPermittivity &&
           mPermeability == rhs.mPermeability &&
           mNt == rhs.mNt;
}
//-----------------------------------------------------------------------------
