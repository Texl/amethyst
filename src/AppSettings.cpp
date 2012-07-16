//------------------------------------------------------------------------------
#include "AppSettings.h"
//------------------------------------------------------------------------------
bool                    AppSettings::mFisheye           = true;

bool                    AppSettings::mUseAmbient        = true;
bool                    AppSettings::mUseDiffuse        = true;
bool                    AppSettings::mUseSpecular       = true;
AppSettings::ShadowMode AppSettings::mShadowMode        = AppSettings::kShadowMode_Hard;

bool                    AppSettings::mUseReflection     = true;
bool                    AppSettings::mUseRefraction     = true;
bool                    AppSettings::mUseAttenuation    = true;
bool                    AppSettings::mUseSceneRayDepth  = false;
unsigned int            AppSettings::mMaxRayDepth       = 3;

unsigned int            AppSettings::mMultisampleCount  = 4;

unsigned int            AppSettings::mThreadCount       = 8;
//------------------------------------------------------------------------------
