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
    // Camera parameters
    Vec3f const eye = mCamera.c + mCamera.e;

    unsigned int const rayDepth = Settings::mUseSceneRayDepth ? mMaxRayDepth : Settings::mMaxRayDepth;

    Color color = Color::black();

    float const contribution = 1.0f / (Settings::mMultisampleCount * Settings::mMultisampleCount);

    for( unsigned int i = 0; i < Settings::mMultisampleCount; ++i )
    {
        for( unsigned int j = 0; j < Settings::mMultisampleCount; ++j )
        {
            float const screenSubX = screenX + i * 0.25f;
            float const screenSubY = screenY + j * 0.25f;

            float ndcX =    2 * (float)screenSubX / screenWidth - 1;
            float ndcY = -( 2 * (float)screenSubY / screenHeight - 1 );
            float ndcZ = 0;

            if( Settings::mFisheye )
            {
                float radius = math<float>::sqrt( ndcX * ndcX + ndcY * ndcY );
                float theta = radius * toRadians(90.f);
                ndcX = ndcX / radius * math<float>::sin( theta );
                ndcY = ndcY / radius * math<float>::sin( theta );
                ndcZ = math<float>::cos( theta );
            }

            Vec3f const target = mCamera.c + mCamera.u * ndcX + mCamera.v * ndcY - mCamera.e * ndcZ;

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
        SceObject * pObject = new SceSphere();
        ( ( SceSphere * )pObject )->c = Vec3f( 0.5f, 0.25f, -0.5f );
        ( ( SceSphere * )pObject  )->r = 0.25f;
        pObject->color                  = Color( 0.5f, 0.7f, 0.5f );
        pObject->specularCoefficient    = 0.3f;
        pObject->specularExponent       = 70.f;
        pObject->attenuation            = Color( 0.f, 0.f, 0.f );
        pObject->permittivity           = 1e6;
        pObject->permeability           = 1.f;

        pObject->Precalculate();
        mSceneObjects.push_back( pObject );
    }

    {
        SceObject * pObject = new SceBox();
        ( ( SceBox * )pObject )->v   = Vec3f( -0.2623f, 0.001f, -0.7042f );
        ( ( SceBox * )pObject )->l   = Vec3f( 0.6495f, 0.f, -0.375f );
        ( ( SceBox * )pObject )->w   = Vec3f( -0.125f, 0.f, -0.2165f );
        ( ( SceBox * )pObject )->h   = Vec3f( 0.f, 0.75f, 0.f );
        pObject->color                  = Color( 0.3f, 0.3f, 0.5f );
        pObject->specularCoefficient    = 0.8f;
        pObject->specularExponent       = 20.f;
        pObject->attenuation            = Color( 0.5f, 0.5f, 0.5f );
        pObject->permittivity           = 2.3716f;
        pObject->permeability           = 1.f;

        pObject->Precalculate();
        mSceneObjects.push_back( pObject );
    }

    {
        SceObject * pObject = new SceBox();
        ( ( SceBox * )pObject )->v   = Vec3f( 0, 0.5f, -0.7042f );
        ( ( SceBox * )pObject )->l   = Vec3f( 0, 0, 0.1f );
        ( ( SceBox * )pObject )->w   = Vec3f( 0.1f, 0, 0);
        ( ( SceBox * )pObject )->h   = Vec3f( 0, 0.1f, 0 );
        pObject->color                  = Color( 0.8f, 0.8f, 0.3f );
        pObject->specularCoefficient    = 0.0f;
        pObject->specularExponent       = 20.f;
        pObject->attenuation            = Color( 0.5f, 0.5f, 0.5f );
        pObject->permittivity           = 1e6;
        pObject->permeability           = 1.f;

        pObject->Precalculate();
        mSceneObjects.push_back( pObject );
    }

    {
        SceObject * pObject = new ScePolygon();
        ( ( ScePolygon * )pObject )->n = 4;
        ( ( ScePolygon * )pObject )->v.push_back( Vec3f( 1.f, 0.f, 0.f ) );
        ( ( ScePolygon * )pObject )->v.push_back( Vec3f( 1.f, 0.f, -2.f ) );
        ( ( ScePolygon * )pObject )->v.push_back( Vec3f( -1.f, 0.f, -2.f ) );
        ( ( ScePolygon * )pObject )->v.push_back( Vec3f( -1.f, 0.f, 0.f ) );
        pObject->color                  = Color( 0.6f, 0.6f, 0.6f );
        pObject->specularCoefficient    = 0.4f;
        pObject->specularExponent       = 20.f;
        pObject->attenuation            = Color( 0.f, 0.f, 0.f );
        pObject->permittivity           = 1e6;
        pObject->permeability           = 1.f;

        pObject->Precalculate();
        mSceneObjects.push_back( pObject );
    }

    {
        SceObject * pObject = new SceEllipsoid();
        ( ( SceEllipsoid * )pObject )->c    = Vec3f( -0.5f, 0.5f, -1.5f );
        ( ( SceEllipsoid * )pObject )->u    = Vec3f( 0.25f, 0.f, 0.f );
        ( ( SceEllipsoid * )pObject )->v    = Vec3f( 0.f, 0.5f, 0.f );
        ( ( SceEllipsoid * )pObject )->w    = Vec3f( 0.f, 0.f, 0.25f );

        pObject->color                  = Color( 0.7f, 0.5f, 0.5f );
        pObject->specularCoefficient    = 0.3f;
        pObject->specularExponent       = 70.f;
        pObject->attenuation            = Color( 0.f, 0.f, 0.f );
        pObject->permittivity           = 1e6;
        pObject->permeability           = 1.f;

        pObject->Precalculate();
        mSceneObjects.push_back( pObject );
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
        SceLight * pLight = new SceLight();
        pLight->p = Vec3f( -1.f, 1.f, 0.f );
        pLight->c = Color(1.f, 1.f, 1.f);
        pLight->r = 0.1f;

        mLights.push_back( pLight );
    }

    {
        SceLight * pLight = new SceLight();
        pLight->p = Vec3f( 0.75f, 0.5f, 0.f );
        pLight->c = Color( 0.8f, 0.8f, 0.8f );
        pLight->r = 0.2f;

        mLights.push_back( pLight );
    }

    // Do any required scene precalculation.
    mAir.mNt = sqrt( mAir.mPermittivity * mAir.mPermeability );

    return true;
}
//------------------------------------------------------------------------------
void
Scene::CalculateViewSize(int & width, int & height, int const maxDimension)
{
    float const aspect = mCamera.u.length() / mCamera.v.length();

    if( aspect > 1.0 )
    {
        width = maxDimension;
        height = (int)( width / aspect );
    }
    else
    {
        height = maxDimension;
        width = (int)( height * aspect );
    }
}
//------------------------------------------------------------------------------
void
Scene::_Reset()
{
    mAmbientColor       = Color( 0, 0, 0 );
    mAir.mC             = Color( 1, 1, 1 );
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
    float const nt          = ni == mAir.mNt ? mSceneObjects[index]->nt : mAir.mNt;
    Color const attenuation = ni == mAir.mNt ? mAir.mC : mSceneObjects[index]->attenuation;

    if( Settings::mUseReflection || Settings::mUseRefraction )
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
                muRatio = mAir.mPermeability / mSceneObjects[index]->permeability;
            }
            else
            {
                muRatio = mSceneObjects[index]->permeability / mAir.mPermeability;
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

        R *= mSceneObjects[index]->specularCoefficient;
        T *= mSceneObjects[index]->specularCoefficient;
    }

    if( ni == mAir.mNt )
    {
        color = _GetLocalIllumination(index, ray, point, normal, R);
    }

    if( R != 0 && Settings::mUseReflection )
    {
        Ray const reflectionRay = Ray(point + (float)EPSILON * normal, reflectionVector);
        color += R * _RayTrace(reflectionRay, ni, depth - 1);
    }

    if( T != 0 && Settings::mUseRefraction )
    {
        Ray const transmissionRay = Ray(point - (float)EPSILON * normal, transmissionVector);
        color += T * _RayTrace(transmissionRay, nt, depth - 1);
    }

    if( attenuation != Color( 1, 1, 1 ) && Settings::mUseAttenuation )
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
    Color   Kd  = mSceneObjects[index]->color;
    float   Ks  = setKs > 0 ? setKs : mSceneObjects[index]->specularCoefficient;
    float   ns  = mSceneObjects[index]->specularExponent;

    Vec3f lightVector, viewVector, reflectionVector;

    if( Settings::mUseAmbient )
    {
        //ambient contribution
        ambient = mAmbientColor * mSceneObjects[ index ]->color;
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

        switch( Settings::mShadowMode )
        {
            case Settings::kShadowMode_Hard:
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

            case Settings::kShadowMode_None:
            default:
                break;
        }

        //calculate diffuse contribution
        float dotNL = normal.dot( lightVector);
        if( dotNL < 0 )
        {
            continue;
        }

        if( Settings::mUseDiffuse )
        {
            diffuse += ( Kd * mLights[ i ]->c * dotNL );
        }

        if( Settings::mUseSpecular )
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
