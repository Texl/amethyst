//------------------------------------------------------------------------------
#include "Application/AppSettings.h"
//------------------------------------------------------------------------------
bool                    Settings::mFisheye          = true;

bool                    Settings::mUseAmbient       = true;
bool                    Settings::mUseDiffuse       = true;
bool                    Settings::mUseSpecular      = true;
Settings::ShadowMode    Settings::mShadowMode       = Settings::kShadowMode_Hard;

bool                    Settings::mUseReflection    = true;
bool                    Settings::mUseRefraction    = true;
bool                    Settings::mUseAttenuation   = true;
bool                    Settings::mUseSceneRayDepth = false;
unsigned int            Settings::mMaxRayDepth      = 3;
//------------------------------------------------------------------------------
