//------------------------------------------------------------------------------
// File:    Application.cpp
//------------------------------------------------------------------------------
#include "Application.h"
//------------------------------------------------------------------------------
Application::Application()
: mScene        ()
, mSurface      ()
, mTexture      ()
, mSurfaceMutex ()
, mCond         ()
, mThreads      ()
, mJobs         ()
{
    for (unsigned int i = 0; i < AppSettings::mThreadCount; ++i)
    {
        mThreads.push_back(threadPtr(new thread));
    }
}
//------------------------------------------------------------------------------
Application::~Application()
{
    _StopThreads();
}
//------------------------------------------------------------------------------
void
Application::prepareSettings(Settings * settings)
{
    settings->setTitle("amethyst");
}
//------------------------------------------------------------------------------
void
Application::setup()
{
    setFrameRate(60.0f);

    mScene.Load();
}
//------------------------------------------------------------------------------
void
Application::resize(ResizeEvent event)
{
    // Stop render threads
    _StopThreads();

    // Recreate surface
    mSurface = Surface8u(getWindowWidth(), getWindowHeight(), false);
    memset(mSurface.getData(), 0, 3 * mSurface.getWidth() * mSurface.getHeight() * sizeof(mSurface.getData()[0]));
    mTexture = gl::Texture(mSurface);

    // Set up jobs
    _SetJobs();

    // Start render threads
    _StartThreads();
}
//------------------------------------------------------------------------------
void
Application::update()
{
    mTexture.update((Surface &)mSurface);
}
//------------------------------------------------------------------------------
void
Application::draw()
{
	// clear out the window with black
	gl::clear(Color(0, 0, 0));

    gl::draw(mTexture);
}
//------------------------------------------------------------------------------
void
Application::_StartThreads()
{
    for (unsigned int i = 0; i < mThreads.size(); ++i)
    {
        *mThreads[i] = thread(&Application::_ProcessJobs, this);
    }
}
//------------------------------------------------------------------------------
void
Application::_StopThreads()
{
    for (unsigned int i = 0; i < mThreads.size(); ++i)
    {
        mThreads[i]->interrupt();
        mThreads[i]->join();
    }
}
//------------------------------------------------------------------------------
void
Application::_SetJobs()
{
    mSurfaceMutex.lock();

    mJobs.clear();
    int areaWidth = 64;
    int areaHeight = 64;
    int heightSegments = (int)math<float>::ceil((float)getWindowHeight() / areaHeight);
    int widthSegments = (int)math<float>::ceil((float)getWindowWidth() / areaWidth);

    for (int j = 0; j < heightSegments; ++j)
    {
        for (int i = 0; i < widthSegments; ++i)
        {
            mJobs.push_front(Area(i * areaWidth, 
                                  j * areaHeight, 
                                  math<int>::clamp((i + 1) * areaWidth, 0, getWindowWidth()), 
                                  math<int>::clamp((j + 1) * areaHeight, 0, getWindowHeight())));
        }
    }
    mCond.notify_all();
    mSurfaceMutex.unlock();
}
//------------------------------------------------------------------------------
void
Application::_ProcessJobs()
{
    try
    {
        while(1)
        {
            // Lock job queue
            mutex::scoped_lock lock(mSurfaceMutex);
            while(mJobs.empty())
            {
                // Wait on a job
                mCond.wait(lock);
            }

            // There's a job; get it and relinquish the lock
            Area area = mJobs.back();
            mJobs.pop_back();
            lock.unlock();

            // Draw the job
            _DrawArea(area);
        }
    }
    catch(boost::thread_interrupted const &)
    {
        // If we're interrupted, just return
        return;
    }
}
//------------------------------------------------------------------------------
void 
Application::_DrawArea(Area const & area)
{
    Surface8u::Iter iter = mSurface.getIter(area);

    while(iter.line())
    {
        while(iter.pixel())
        {
            boost::this_thread::interruption_point();

            Color color = mScene.GetPixelColor(mSurface.getWidth(), mSurface.getHeight(), iter.x(), iter.y());

            iter.r() = (unsigned char)(math<float>().clamp(color.r, 0, 1) * 255);
            iter.g() = (unsigned char)(math<float>().clamp(color.g, 0, 1) * 255);
            iter.b() = (unsigned char)(math<float>().clamp(color.b, 0, 1) * 255);
        }
    }
}
//------------------------------------------------------------------------------
CINDER_APP_BASIC(Application, RendererGl)
//------------------------------------------------------------------------------
