//------------------------------------------------------------------------------
// File:    SceEllipsoid.cpp
//------------------------------------------------------------------------------
#include <cmath>

#include "SceEllipsoid.h"
//------------------------------------------------------------------------------
void SceEllipsoid::Precalculate()
{
    SceObject::Precalculate();

    m = Matrix33f( u, v, w );

    mInv = m.inverted();

    mInvTInv =  mInv.transposed() * mInv;
}
//------------------------------------------------------------------------------
bool SceEllipsoid::FindIntersection( Ray const & ray, float & t, Vec3f & point, Vec3f & normal)
{
    Ray const mInvRay( mInv * ( ray.getOrigin() - c ), mInv * ray.getDirection() );

    float const pa = mInvRay.getDirection().dot( mInvRay.getDirection() );
    float const pb = 2 * mInvRay.getOrigin().dot( mInvRay.getDirection() );
    float const pc = mInvRay.getOrigin().dot( mInvRay.getOrigin() ) - 1.0f;

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

    point = ray.getOrigin() + t * ray.getDirection();
    normal = ( mInvTInv * ( point - c ) ).normalized();
    return true;
}
//------------------------------------------------------------------------------
