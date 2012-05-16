//------------------------------------------------------------------------------
// File:    SceEllipsoid.cpp
//------------------------------------------------------------------------------
#include <cmath>

#include "SceEllipsoid.h"
//------------------------------------------------------------------------------
SceEllipsoid::SceEllipsoid( Vec3f const & c, Vec3f const & u, Vec3f const & v, Vec3f const & w, Material const & material )
: SceObject ( material )
, c         ( c )
, u         ( u )
, v         ( v )
, w         ( w )
{
    m = Matrix33f( u, v, w );

    mInv = m.inverted();

    mInvTInv =  mInv.transposed() * mInv;
}
//------------------------------------------------------------------------------
bool SceEllipsoid::FindIntersection( Ray const & ray, float & t, Vec3f & point, Vec3f & normal)
{
    Ray const mInvRay( mInv * ( ray.getOrigin() - c ), mInv * ray.getDirection() );

    float const pa = mInvRay.getDirection().lengthSquared();
    float const pb = 2 * mInvRay.getOrigin().dot( mInvRay.getDirection() );
    float const pc = mInvRay.getOrigin().lengthSquared() - 1;

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
        t = tplus / ( 2 * pa );
    }
    else
    {
        t = tminus / ( 2 * pa );
    }

    point = ray.calcPosition( t );
    normal = ( mInvTInv * ( point - c ) ).normalized();
    return true;
}
//------------------------------------------------------------------------------
