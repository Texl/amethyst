//------------------------------------------------------------------------------
// File:    AppSettings.h"
//------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------
class Settings
{
    public:
        enum ShadowMode
        {
            kShadowMode_Hard,
            kShadowMode_None,
        };

    public:
        //application settings
        static bool         mPaused;
        static unsigned int mMaxWindowSize;

        static bool         mFisheye;

        //local illumination settings
        static bool         mUseAmbient;
        static bool         mUseDiffuse;
        static bool         mUseSpecular;
        static ShadowMode   mShadowMode;

        //global illumination settings
        static bool         mUseReflection;
        static bool         mUseRefraction;
        static bool         mUseAttenuation;
        static bool         mUseSceneRayDepth;
        static unsigned int mMaxRayDepth;
};
//------------------------------------------------------------------------------
