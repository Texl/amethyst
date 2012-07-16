//------------------------------------------------------------------------------
// File:    SceEllipsoid.cpp
//------------------------------------------------------------------------------
#include <cmath>

#include "SceEllipsoid.h"
//------------------------------------------------------------------------------
SceEllipsoid::SceEllipsoid(Vec3f const & center, 
                           Vec3f const & u, 
                           Vec3f const & v, 
                           Vec3f const & w, 
                           Material const & material)
: SceObject         (material)
, mCenter           (center)
, mMatrixInv        (Matrix33f(u, v, w).inverted())
, mMatrixInvTInv    (mMatrixInv.transposed() * mMatrixInv)
{
}
//------------------------------------------------------------------------------
bool
SceEllipsoid::RayCast(Ray const & ray,
                      float & t) const
{
    Ray const invRay(mMatrixInv * (ray.getOrigin() - mCenter), mMatrixInv * ray.getDirection());

    float const pa = invRay.getDirection().lengthSquared();
    float const pb = 2 * invRay.getOrigin().dot(invRay.getDirection());
    float const pc = invRay.getOrigin().lengthSquared() - 1;

    float const discriminant = pb * pb - 4 * pa * pc;

    if (discriminant < 0)
    {
        return false;
    }

    float const sqrtDiscriminant = sqrt(discriminant);

    float const tplus = -pb + sqrtDiscriminant;

    if (tplus < 0)
    {
        return false;
    }

    float const tminus = -pb - sqrtDiscriminant;

    if (tminus < 0)
    {
        t = tplus / (2 * pa);
    }
    else
    {
        t = tminus / (2 * pa);
    }

    return true;
}
//------------------------------------------------------------------------------
bool
SceEllipsoid::RayCast(Ray const & ray, 
                      float & t, 
                      Vec3f & point, 
                      Vec3f & normal) const
{
    float tIntersection;

    if (RayCast(ray, tIntersection))
    {
        t = tIntersection;
        point = ray.calcPosition(tIntersection);
        normal = (mMatrixInvTInv * (point - mCenter)).normalized();
        return true;
    }

    return false;
}
//------------------------------------------------------------------------------
