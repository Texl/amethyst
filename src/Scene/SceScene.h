//------------------------------------------------------------------------------
// File:    SceScene.h
//------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------
#include <string>
#include <vector>
#include "Scene/SceAir.h"
#include "Scene/SceCamera.h"
#include "Scene/SceLight.h"
#include "Scene/SceObject.h"
#include "Math/MatRay.h"

#include "cinder/app/AppBasic.h"
#include "cinder/Vector.h"

#include "cinder/Color.h"
//------------------------------------------------------------------------------
using namespace ci;
using namespace ci::app;
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
        void                CalculateViewSize           ( int & width, int & height, int minDimension );

    private:
        void                _Reset                      ();
        Color               _RayTrace                   ( MatRay const & ray, float ni, int const depth );
        bool                _FindNearestIntersection    ( unsigned int & index, MatRay const & ray, Vec3f & point, Vec3f & normal );
        Color               _GetLocalIllumination       ( unsigned int index, MatRay const & ray, Vec3f const & point, Vec3f const & normal, float setKs = -1 );

        SceCamera           mCamera;
        Color               mAmbientColor;
        SceAir              mAir;
        int                 mMaxRayDepth;
        SceObjectPtrVector  mSceneObjects;
        SceLightPtrVector   mLights;
};
//------------------------------------------------------------------------------
