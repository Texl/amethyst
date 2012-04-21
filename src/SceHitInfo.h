//------------------------------------------------------------------------------
// File:    SceHitInfo.h
//------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------
#include "Vec3f.h"
//------------------------------------------------------------------------------
class SceObject;
//------------------------------------------------------------------------------
typedef SceObject * SceObjectPtr
//------------------------------------------------------------------------------
class SceHitInfo
{
    public:
        explicit    SceHitInfo  ();

    private:
        SceObject * mpObject;
        Vec3f       mPosition;
        Vec3f       mNormal;
        Vec2f       mTexCoord1;
        Vec2f       mTexCoord2;
        
        float       mNi;
        float       mNt;
};
//------------------------------------------------------------------------------