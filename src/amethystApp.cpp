//------------------------------------------------------------------------------
// File:    AmethystApp.cpp
//------------------------------------------------------------------------------
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Surface.h"
#include "cinder/gl/Texture.h"
#include "cinder/CinderMath.h"
#include "Scene/SceScene.h"
//------------------------------------------------------------------------------
using namespace ci;
using namespace ci::app;
using namespace std;
//------------------------------------------------------------------------------
class amethystAppApp : public AppBasic
{
    public:
        void prepareSettings( Settings * settinga );
        void setup();
        void mouseDown( MouseEvent event );	
        void resize( ResizeEvent event );
        void update();
        void draw();

        void drawLine();

        Scene	        mScene;
        Surface8u       mSurface;
        gl::Texture     mTexture;
};
//------------------------------------------------------------------------------
void
amethystAppApp::prepareSettings( Settings * settings )
{
    settings->setTitle( "test title" );
}
//------------------------------------------------------------------------------
void amethystAppApp::setup()
{
	mScene.Load();

    mSurface = Surface8u( getWindowWidth(), getWindowHeight(), false );
    mTexture = gl::Texture( mSurface );
}
//------------------------------------------------------------------------------
void
amethystAppApp::resize( ResizeEvent event )
{
    int height, width;

    mScene.CalculateViewSize( width, height, getWindowWidth() );

    setWindowSize( width, height );

    mSurface = Surface8u( getWindowWidth(), getWindowHeight(), false );
    mTexture = gl::Texture( mSurface );
}
//------------------------------------------------------------------------------
void amethystAppApp::mouseDown( MouseEvent event )
{
    drawLine();
}
//------------------------------------------------------------------------------
void amethystAppApp::update()
{
    mTexture.update( (Surface &)mSurface );
}
//------------------------------------------------------------------------------
void amethystAppApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );

    gl::draw( mTexture );
}
//------------------------------------------------------------------------------
void 
amethystAppApp::drawLine()
{
    //Surface8u::Iter iter = mSurface.getIter( Area( 0, mLine, mSurface.getWidth() - 1, mLine + 1 - 1) );

    //while( iter.pixel() )
    //{
    //    Color color = mScene.GetPixelColor( mSurface.getWidth(), mSurface.getHeight(), iter.x(), iter.y() );
    //    iter.r() = (uint8_t)(math<float>().clamp( color.r, 0, 1 ) * 255);
    //    iter.g() = (uint8_t)(math<float>().clamp( color.g, 0, 1 ) * 255);
    //    iter.b() = (uint8_t)(math<float>().clamp( color.b, 0, 1 ) * 255);
    //}

    Surface8u::Iter iter = mSurface.getIter();

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
CINDER_APP_BASIC( amethystAppApp, RendererGl )
//------------------------------------------------------------------------------
