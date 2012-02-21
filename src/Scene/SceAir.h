//------------------------------------------------------------------------------
// File:    SceAir.h
//------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------
#include "cinder/Color.h"
#include "cinder/Vector.h"
//------------------------------------------------------------------------------
using namespace ci;
//------------------------------------------------------------------------------
class SceAir
{
    public:
        explicit    SceAir  ();

        float   mPermittivity;
        float   mPermeability;
        float   mNt;
        Color   mC;
};
//-----------------------------------------------------------------------------