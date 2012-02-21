//------------------------------------------------------------------------------
#include "Application/AppSettings.h"
//------------------------------------------------------------------------------
bool                    Settings::mUseAmbient       = true;
bool                    Settings::mUseDiffuse       = true;
bool                    Settings::mUseSpecular      = true;
Settings::ShadowMode    Settings::mShadowMode       = Settings::kShadowMode_Hard;

bool                    Settings::mUseReflection    = false;
bool                    Settings::mUseRefraction    = false;
bool                    Settings::mUseAttenuation   = false;
bool                    Settings::mUseSceneRayDepth = false;
unsigned int            Settings::mMaxRayDepth      = 3;
//------------------------------------------------------------------------------
