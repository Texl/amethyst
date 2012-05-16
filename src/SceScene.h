//------------------------------------------------------------------------------
// File:    SceScene.h
//------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------
#include <string>
#include <vector>
#include "cinder/Color.h"
#include "cinder/Ray.h"
#include "cinder/Vector.h"

#include "SceCamera.h"
#include "SceLight.h"
#include "SceObject.h"
//------------------------------------------------------------------------------
using namespace ci;
//------------------------------------------------------------------------------
typedef std::vector< SceObject * >  SceObjectPtrVector;
typedef std::vector< SceLight * >   SceLightPtrVector;
//------------------------------------------------------------------------------
class Scene
{
    public:
        explicit            Scene                       ();
                            ~Scene                      ();

        Color               GetPixelColor               ( int const width, int const height, int const x, int const y );
        bool                Load                        ();

    private:
        void                _Reset                      ();
        Color               _RayTrace                   ( Ray const & ray, float ni, int const depth );
        bool                _FindNearestIntersection    ( unsigned int & index, Ray const & ray, Vec3f & point, Vec3f & normal );
        Color               _GetLocalIllumination       ( unsigned int index, Ray const & ray, Vec3f const & point, Vec3f const & normal, float setKs = -1 );

        SceCamera           mCamera;
        Color               mAmbientColor;
        Material            mAir;
        int                 mMaxRayDepth;
        SceObjectPtrVector  mSceneObjects;
        SceLightPtrVector   mLights;
};
//------------------------------------------------------------------------------
