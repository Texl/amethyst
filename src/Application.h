//------------------------------------------------------------------------------
// File:    Application.cpp
//------------------------------------------------------------------------------
#include "cinder/app/AppBasic.h"
#include "cinder/CinderMath.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/Surface.h"
#include "cinder/Thread.h"

#include "AppSettings.h"
#include "SceScene.h"
//------------------------------------------------------------------------------
using namespace ci;
using namespace ci::app;
using namespace std;
//------------------------------------------------------------------------------
typedef shared_ptr<thread>  threadPtr;
//------------------------------------------------------------------------------
class Application : public AppBasic
{
public:
            Application     ();
            ~Application    ();

private:
    void    prepareSettings (Settings * settings);

    void    setup           ();

    void    resize          (ResizeEvent event);

    void    update          ();

    void    draw            ();

    void    _StartThreads   ();

    void    _StopThreads    ();

    void    _SetJobs        ();

    void    _ProcessJobs    ();

    void    _DrawArea       (Area const & area);

    Scene	            mScene;
    Surface8u           mSurface;
    gl::Texture         mTexture;

    mutex               mSurfaceMutex;
    condition_variable  mCond;
    vector<threadPtr>   mThreads;
    list<Area>          mJobs;
};
//------------------------------------------------------------------------------