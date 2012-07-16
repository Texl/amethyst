//------------------------------------------------------------------------------
// File:    SceSphere.cpp
//------------------------------------------------------------------------------
#include <cmath>

#include "SceSphere.h"
//------------------------------------------------------------------------------
SceSphere::SceSphere(Vec3f const & center,
                     float const radius, 
                     Material const & material)
: SceObject (material)
, mCenter   (center)
, mRadius   (radius)
{
}
//------------------------------------------------------------------------------
bool
SceSphere::RayCast(Ray const & ray,
                   float & t) const
{
    Vec3f const vectorCP = ray.getOrigin() - mCenter;
    float const pa = ray.getDirection().lengthSquared();
    float const pb = 2 * vectorCP.dot(ray.getDirection());
    float const pc = vectorCP.lengthSquared() - mRadius * mRadius;

    float const discriminant = pb * pb - 4 * pa * pc;

    if (discriminant < 0)
    {
        return false;
    }

    float const sqrtDiscriminant = math<float>::sqrt(discriminant);

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
SceSphere::RayCast(Ray const & ray, 
                   float & t, 
                   Vec3f & point, 
                   Vec3f & normal) const
{
    float tIntersection;

    if (RayCast(ray, tIntersection))
    {
        t = tIntersection;
        point = ray.calcPosition(tIntersection);
        normal = (point - mCenter) / mRadius;
        return true;
    }

    return false;
}
//------------------------------------------------------------------------------
