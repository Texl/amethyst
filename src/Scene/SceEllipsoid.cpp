//------------------------------------------------------------------------------
// File:    SceEllipsoid.cpp
//------------------------------------------------------------------------------
#include <cmath>

#include "Scene/SceEllipsoid.h"
//------------------------------------------------------------------------------
void SceEllipsoid::Precalculate()
{
    SceObject::Precalculate();

    m = Matrix33f( u, v, w );

    mInv = m.inverted();

    mInvTInv =  mInv.transposed() * mInv;
}
//------------------------------------------------------------------------------
bool SceEllipsoid::FindIntersection( MatRay const & ray, float & t, Vec3f & point, Vec3f & normal)
{
    MatRay const mInvRay( mInv * ( ray.mOrigin - c ), mInv * ray.mDirection );

    float const pa = mInvRay.mDirection.dot( mInvRay.mDirection );
    float const pb = 2 * mInvRay.mOrigin.dot( mInvRay.mDirection );
    float const pc = mInvRay.mOrigin.dot( mInvRay.mOrigin ) - 1.0f;

    float const discriminant = pb * pb - 4 * pa * pc;

    if( discriminant < 0 )
    {
        return false;
    }

    float const sqrtDiscriminant = sqrt( discriminant );

    float const tplus = -pb + sqrtDiscriminant;

    if( tplus < 0 )
    {
        return false;
    }

    float const tminus = -pb - sqrtDiscriminant;

    if( tminus < 0 )
    {
        t = (float)( 0.5 * tplus / pa );
    }
    else
    {
        t = (float)( 0.5f * tminus / pa );
    }

    point = ray.mOrigin + t * ray.mDirection;
    normal = ( mInvTInv * ( point - c ) ).normalized();
    return true;
}
//------------------------------------------------------------------------------
