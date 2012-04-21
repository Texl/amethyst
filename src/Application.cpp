//------------------------------------------------------------------------------
// File:    Application.cpp
//------------------------------------------------------------------------------
#include "cinder/app/AppBasic.h"
#include "cinder/CinderMath.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/Surface.h"
#include "cinder/Thread.h"

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

        void    prepareSettings ( Settings * settings );
        void    setup           ();
        void    resize          ( ResizeEvent event );
        void    update          ();
        void    draw            ();

        void    RenderScreen    ();
        void    DrawLine        ( int const row );
        void    DrawArea        ( Area const & area );

        Scene	            mScene;
        Surface8u           mSurface;
        gl::Texture         mTexture;

        mutex               mSurfaceMutex;
        thread              mThread;
};
//------------------------------------------------------------------------------
Application::Application()
: mScene        ()
, mSurface      ()
, mTexture      ()
, mSurfaceMutex ()
, mThread       ()
{
}
//------------------------------------------------------------------------------
Application::~Application()
{
    mThread.interrupt();
    mThread.join();
}
//------------------------------------------------------------------------------
void
Application::prepareSettings( Settings * settings )
{
    settings->setTitle( "amethyst" );
}
//------------------------------------------------------------------------------
void Application::setup()
{
    setFrameRate( 60.0f );

    mScene.Load();

    mSurface = Surface8u( getWindowWidth(), getWindowHeight(), false );
    mTexture = gl::Texture( mSurface );

    mThread = thread(&Application::RenderScreen, this);
}
//------------------------------------------------------------------------------
void
Application::resize( ResizeEvent event )
{
    int height, width;

    mScene.CalculateViewSize( width, height, getWindowWidth() );

    setWindowSize( width, height );

    // Stop render thread
    mThread.interrupt();
    mThread.join();

    // Recreate surface
    mSurface = Surface8u( getWindowWidth(), getWindowHeight(), false );
    mTexture = gl::Texture( mSurface );

    // Start render thread
    mThread = thread(&Application::RenderScreen, this);
}
//------------------------------------------------------------------------------
void Application::update()
{
    mutex::scoped_lock lock( mSurfaceMutex );
    mTexture.update( (Surface &)mSurface );
}
//------------------------------------------------------------------------------
void Application::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );

    gl::draw( mTexture );
}
//------------------------------------------------------------------------------
void
Application::RenderScreen()
{
    try
    {
        for( int i = 0; i < mSurface.getHeight(); ++i )
        {
            boost::this_thread::sleep( boost::posix_time::milliseconds( 1 ) );
            mutex::scoped_lock lock( mSurfaceMutex );
            DrawLine( i );
        }
    }
    catch( boost::thread_interrupted const & )
    {
        return;
    }
}
//------------------------------------------------------------------------------
void 
Application::DrawArea(Area const & area)
{
    Surface8u::Iter iter = mSurface.getIter( Area( area.x1, area.y1, area.getWidth() - 1, area.getHeight() - 1 ) );

    while( iter.line() )
    {
        while( iter.pixel() )
        {
            Color color = mScene.GetPixelColor( mSurface.getWidth(), mSurface.getHeight(), iter.x(), iter.y() );

            iter.r() = (uint8_t)(math<float>().clamp( color.r, 0, 1 ) * 255);
            iter.g() = (uint8_t)(math<float>().clamp( color.g, 0, 1 ) * 255);
            iter.b() = (uint8_t)(math<float>().clamp( color.b, 0, 1 ) * 255);
        }
    }
}
//------------------------------------------------------------------------------

void 
Application::DrawLine( int const row )
{
    Surface8u::Iter iter = mSurface.getIter( Area( 0, row, mSurface.getWidth() - 1, row + 1 - 1) );

    while( iter.pixel() )
    {
        Color color = mScene.GetPixelColor( mSurface.getWidth(), mSurface.getHeight(), iter.x(), iter.y() );

        iter.r() = (uint8_t)(math<float>().clamp( color.r, 0, 1 ) * 255);
        iter.g() = (uint8_t)(math<float>().clamp( color.g, 0, 1 ) * 255);
        iter.b() = (uint8_t)(math<float>().clamp( color.b, 0, 1 ) * 255);
    }
}
//------------------------------------------------------------------------------
CINDER_APP_BASIC( Application, RendererGl )
//------------------------------------------------------------------------------
