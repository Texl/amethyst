//------------------------------------------------------------------------------
#include "SceBox.h"
#include "SceEllipsoid.h"
#include "ScePolygon.h"
#include "SceScene.h"
#include "SceSphere.h"

#include "AppSettings.h"
//------------------------------------------------------------------------------
Scene::Scene()
: mCamera       ()
, mAmbientColor ()
, mAir          ()
, mMaxRayDepth  ()
, mSceneObjects ()
, mLights       ()
{
}
//------------------------------------------------------------------------------
Scene::~Scene()
{
    while( !mSceneObjects.empty() )
    {
        delete mSceneObjects[ mSceneObjects.size() - 1 ];
        mSceneObjects.pop_back();
    }

    while( !mLights.empty() )
    {
        delete mLights[ mLights.size() - 1 ];
        mLights.pop_back();
    }
}
//------------------------------------------------------------------------------
Color
Scene::GetPixelColor( int const screenWidth, int const screenHeight, int const screenX, int const screenY )
{
    float const windowAspect = (float)screenWidth / screenHeight;
    float const cameraAspect = mCamera.u.length() / mCamera.v.length();

    // Camera parameters
    Vec3f const eye = mCamera.c + mCamera.e;

    unsigned int const rayDepth = AppSettings::mUseSceneRayDepth ? mMaxRayDepth : AppSettings::mMaxRayDepth;

    Color color = Color::black();

    float const contribution = 1.0f / (AppSettings::mMultisampleCount * AppSettings::mMultisampleCount);

    for( unsigned int i = 0; i < AppSettings::mMultisampleCount; ++i )
    {
        for( unsigned int j = 0; j < AppSettings::mMultisampleCount; ++j )
        {
            float const screenSubX = screenX + i * 0.25f;
            float const screenSubY = screenY + j * 0.25f;

            float ndcX =    2 * (float)screenSubX / screenWidth - 1;
            float ndcY = -( 2 * (float)screenSubY / screenHeight - 1 );
            float ndcZ = 0;

            if( AppSettings::mFisheye )
            {
                float radius = math<float>::sqrt( ndcX * ndcX + ndcY * ndcY );
                float theta = radius * toRadians(90.f);
                ndcX = ndcX / radius * math<float>::sin( theta );
                ndcY = ndcY / radius * math<float>::sin( theta );
                ndcZ = math<float>::cos( theta );
            }

            Vec3f const target = mCamera.c + mCamera.u * windowAspect * ndcX + mCamera.v * ndcY - mCamera.e * ndcZ;

            // Construct the pixel's ray, then get its color.
            Vec3f const direction = ( target - eye ).normalized();

            color += _RayTrace( Ray( eye, direction ), mAir.mNt, rayDepth ) * contribution;
        }
    }

    return color;
}
//------------------------------------------------------------------------------
bool
Scene::Load()
{
    _Reset();

    {
        Material material;
        material.mColor                 = Color( 0.5f, 0.7f, 0.5f );
        material.mSpecularCoefficient   = 0.3f;
        material.mSpecularExponent      = 70.f;
        material.mAttenuation           = Color( 0.f, 0.f, 0.f );
        material.mPermittivity          = 1e6;
        material.mPermeability          = 1.f;
        mSceneObjects.push_back( new SceSphere( Vec3f( 0.5f, 0.25f, -0.5f ), 0.2f, material ) );
    }

    {
        Material material;
        material.mColor                 = Color( 0.3f, 0.3f, 0.5f );
        material.mSpecularCoefficient   = 0.3f;
        material.mSpecularExponent      = 20.f;
        material.mAttenuation           = Color( 0.5f, 0.5f, 0.5f );
        material.mPermittivity          = 1e6;
        material.mPermeability          = 1.f;
        mSceneObjects.push_back( new SceBox( Vec3f( -0.2623f, 0.001f, -0.7042f ), 
                                             Vec3f( 0.6495f, 0.f, -0.375f ),
                                             Vec3f( -0.125f, 0.f, -0.2165f ),
                                             Vec3f( 0.f, 0.75f, 0.f ),
                                             material ) );
    }

    {
        Material material;
        material.mColor                 = Color( 0.8f, 0.8f, 0.3f );
        material.mSpecularCoefficient   = 0.0f;
        material.mSpecularExponent      = 20.f;
        material.mAttenuation           = Color( 0.5f, 0.5f, 0.5f );
        material.mPermittivity          = 1e6;
        material.mPermeability          = 1.f;
        mSceneObjects.push_back( new SceBox( Vec3f( 0, 0.5f, -0.7042f ),
                                 Vec3f( 0, 0, 0.1f ),
                                 Vec3f( 0.1f, 0, 0),
                                 Vec3f( 0, 0.1f, 0 ),
                                 material ) );
    }

    {
        vector< Vec3f > v;
        v.push_back( Vec3f( 1.f, 0.f, 0.f ) );
        v.push_back( Vec3f( 1.f, 0.f, -2.f ) );
        v.push_back( Vec3f( -1.f, 0.f, -2.f ) );
        v.push_back( Vec3f( -1.f, 0.f, 0.f ) );
        Material material;
        material.mColor                 = Color( 0.6f, 0.6f, 0.6f );
        material.mSpecularCoefficient   = 0.4f;
        material.mSpecularExponent      = 20.f;
        material.mAttenuation           = Color( 0.f, 0.f, 0.f );
        material.mPermittivity          = 1e6;
        material.mPermeability          = 1.f;
        mSceneObjects.push_back( new ScePolygon( v, material) );
    }

    {
        Material material;
        material.mColor                 =  Color( 0.7f, 0.5f, 0.5f );
        material.mSpecularCoefficient   = 0.3f;
        material.mSpecularExponent      = 70.f;
        material.mAttenuation           = Color( 0.f, 0.f, 0.f );
        material.mPermittivity          = 1e6;
        material.mPermeability          = 1.f;
        mSceneObjects.push_back( new SceEllipsoid( Vec3f( -0.5f, 0.5f, -1.5f ),
                                                   Vec3f( 0.25f, 0.f, 0.f ),
                                                   Vec3f( 0.f, 0.5f, 0.f ),
                                                   Vec3f( 0.f, 0.f, 0.25f ),
                                                   material ) );
    }

    mCamera.c = Vec3f( 0.0267612f, 0.846193f, -0.14023f );
    mCamera.u = Vec3f( 0.343626f, -0.274153f, 0.238247f );
    mCamera.v = Vec3f( 0.362222f, 0.234501f, -0.252595f );
    mCamera.e = Vec3f( 0.0535224f, 0.692386f, 0.719539f );

    //mCamera.c = Vec3f( 0, 0.5f, 0.1f );
    //mCamera.u = Vec3f( 1, 0, 0 );
    //mCamera.v = Vec3f( 0, 1, 0 );
    //mCamera.e = Vec3f( 0, 0, 1 );


    {
        mLights.push_back( new SceLight(Vec3f( -1.f, 1.f, 0.f ),
                                        Color( 1.f, 1.f, 1.f ),
                                        0.1f ) );
    }

    {
        mLights.push_back( new SceLight(Vec3f( 0.75f, 0.5f, 0.f ),
                                        Color( 0.8f, 0.8f, 0.8f ),
                                        0.2f ) );
    }

    // Do any required scene precalculation.
    mAir.mNt = sqrt( mAir.mPermittivity * mAir.mPermeability );

    return true;
}
//------------------------------------------------------------------------------
void
Scene::_Reset()
{
    mAmbientColor       = Color( 0, 0, 0 );
    mAir.mAttenuation   = Color( 1, 1, 1 );
    mAir.mPermeability  = 1.0;
    mAir.mPermittivity  = 1.0;

    while( !mSceneObjects.empty() )
    {
        delete mSceneObjects[ mSceneObjects.size() - 1 ];
        mSceneObjects.pop_back();
    }
    while( !mLights.empty() )
    {
        delete mLights[ mLights.size() - 1 ];
        mLights.pop_back();
    }
}
//------------------------------------------------------------------------------
Color
Scene::_RayTrace( Ray const & ray, float const ni, int const depth )
{
    //find the nearest intersection's object index, intersection point, and surface normal
    unsigned int index;
    Vec3f point;
    Vec3f normal;

    if( depth < 0 || !_FindNearestIntersection( index, ray, point, normal ) )
    {
        return Color( 0, 0, 0 );
    }

//various other interesting display modes
//    return this->mSceneObjects[index]->color;
//    return Color( normal.x, normal.y, normal.z );

    //return value
    Color color;

    // refl/trans variables/vectors/rays
    float R = 1.0;
    float T = 0.0;
    Vec3f reflectionVector;
    Vec3f transmissionVector;

    //find the index of refraction and attenuation factor for the transmitting medium
    float const nt          = ni == mAir.mNt ? mSceneObjects[index]->mMaterial.mNt : mAir.mNt;
    Color const attenuation = ni == mAir.mNt ? mAir.mAttenuation : mSceneObjects[index]->mMaterial.mAttenuation;

    if( AppSettings::mUseReflection || AppSettings::mUseRefraction )
    {
        //calculate the incident vector
        Vec3f const incident = -ray.getDirection();

        //calculate R, T, and reflection/transmission vectors
        float const nRatio = ni / nt;
        float dotIN = incident.dot( normal );    //cos thetaI

        if( dotIN < 0 )
        {
            normal  = -normal;
            dotIN   = -dotIN;
        }

        float const radicand = 1 - nRatio * nRatio * ( 1 - dotIN * dotIN );

        if( radicand <= 0 )
        {
            //total internal reflection
            R = 1;
            T = 0;
            reflectionVector = ( 2 * normal * dotIN - incident ).normalized();
        }
        else
        {
            //reflection + refraction

            //calculate Fresnel equations
            float const cosThetaT = math<float>().sqrt( radicand );

            float muRatio;
            if( ni == mAir.mNt )
            {
                muRatio = mAir.mPermeability / mSceneObjects[index]->mMaterial.mPermeability;
            }
            else
            {
                muRatio = mSceneObjects[index]->mMaterial.mPermeability / mAir.mPermeability;
            }

            float const nRatioDotIN        = nRatio * dotIN;
            float const nRatioCosThetaT    = nRatio * cosThetaT;
            float const muRatioDotIN       = muRatio * dotIN;
            float const muRatioCosThetaT   = muRatio * cosThetaT;

            float const ErPerp = nRatioDotIN - muRatioCosThetaT;
            float const EiPerp = nRatioDotIN + muRatioCosThetaT;
            float const ErPara = muRatioDotIN - nRatioCosThetaT;
            float const EiPara = muRatioDotIN + nRatioCosThetaT;

            R = 0.5f * ( ( ErPerp * ErPerp ) / ( EiPerp * EiPerp ) + ( ErPara * ErPara ) / ( EiPara * EiPara ) );
            T = 1 - R;

            transmissionVector = ( ( -cosThetaT + nRatio * dotIN ) * normal - nRatio * incident ).normalized();
            reflectionVector = ( 2 * normal * dotIN - incident ).normalized();
        }

        R *= mSceneObjects[index]->mMaterial.mSpecularCoefficient;
        T *= mSceneObjects[index]->mMaterial.mSpecularCoefficient;
    }

    if( ni == mAir.mNt )
    {
        color = _GetLocalIllumination(index, ray, point, normal, R);
    }

    if( R != 0 && AppSettings::mUseReflection )
    {
        Ray const reflectionRay = Ray(point + (float)EPSILON * normal, reflectionVector);
        color += R * _RayTrace(reflectionRay, ni, depth - 1);
    }

    if( T != 0 && AppSettings::mUseRefraction )
    {
        Ray const transmissionRay = Ray(point - (float)EPSILON * normal, transmissionVector);
        color += T * _RayTrace(transmissionRay, nt, depth - 1);
    }

    if( attenuation != Color( 1, 1, 1 ) && AppSettings::mUseAttenuation )
    {
        float exponent = ( ray.getOrigin() - point ).length();
        color *= Color( math<float>().pow( attenuation.r, exponent ),
                        math<float>().pow( attenuation.g, exponent ),
                        math<float>().pow( attenuation.b, exponent ) );
    }

    return color;
}
//------------------------------------------------------------------------------
bool
Scene::_FindNearestIntersection( unsigned int & index, Ray const & ray, Vec3f & point, Vec3f & normal )
{
    bool result = false;
    float t;
    float tmin = FLT_MAX;
    Vec3f tminPoint, tminNormal;

    for( unsigned int i = 0; i < mSceneObjects.size(); ++i )
    {
        if( mSceneObjects[ i ]->FindIntersection( ray, t, tminPoint, tminNormal ) )
        {
            if( t < tmin )
            {
                tmin = t;
                index = i;
                result = true;
                point = tminPoint;
                normal = tminNormal;
            }
        }
    }

    if( !result || tmin < 0.0 )
    {
        return false;
    }

    return true;
}
//------------------------------------------------------------------------------
Color
Scene::_GetLocalIllumination( unsigned int index, Ray const & ray, Vec3f const & point, Vec3f const & normal, float setKs )
{
    Color ambient, diffuse, specular;

    //rename some longer identifiers/dereferences
    Color   Kd  = mSceneObjects[index]->mMaterial.mColor;
    float   Ks  = setKs > 0 ? setKs : mSceneObjects[index]->mMaterial.mSpecularCoefficient;
    float   ns  = mSceneObjects[index]->mMaterial.mSpecularExponent;

    Vec3f lightVector, viewVector, reflectionVector;

    if( AppSettings::mUseAmbient )
    {
        //ambient contribution
        ambient = mAmbientColor * mSceneObjects[ index ]->mMaterial.mColor;
    }

    //dummy values and occluder object contact point (for shadows)
    unsigned int uiDummy;
    Vec3f vDummy;
    Vec3f shadowPoint;

    for(unsigned int i = 0; i < mLights.size(); i++)
    {
        //calculate shadows

        //generate vector to current light
        lightVector = (mLights[i]->p - point).normalized();

        switch( AppSettings::mShadowMode )
        {
            case AppSettings::kShadowMode_Hard:
                //determine if pixel is shadowed entirely from current light
                if( _FindNearestIntersection( uiDummy, Ray( point + normal * (float)EPSILON, lightVector ), shadowPoint, Vec3f() ) )
                {
                    if( ( shadowPoint - point ).length() < ( mLights[i]->p - point ).length() )
                    {
                        //if the light is completely shadowed, don't count it in illumination at all
                        continue;
                    }
                }
                break;

            case AppSettings::kShadowMode_None:
            default:
                break;
        }

        //calculate diffuse contribution
        float dotNL = normal.dot( lightVector);
        if( dotNL < 0 )
        {
            continue;
        }

        if( AppSettings::mUseDiffuse )
        {
            diffuse += ( Kd * mLights[ i ]->c * dotNL );
        }

        if( AppSettings::mUseSpecular )
        {
            //calculate specular contribution
            reflectionVector = ( normal * 2.0f * dotNL - lightVector ).normalized();
            viewVector = ( ray.getDirection() * -1 ).normalized();

            float dotRV = reflectionVector.dot( viewVector );
            if(dotRV < 0.0)
                dotRV = 0.0;

            specular += ( mLights[ i ]->c * Ks * pow( dotRV, ns ) );
        }
    }

    return ambient + diffuse + specular;
}
//------------------------------------------------------------------------------
