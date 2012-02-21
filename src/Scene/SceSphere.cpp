//------------------------------------------------------------------------------
// File:    SceSphere.cpp
//------------------------------------------------------------------------------
#include <cmath>

#include "Scene/SceSphere.h"
//------------------------------------------------------------------------------
void
SceSphere::Precalculate()
{
    SceObject::Precalculate();
}
//------------------------------------------------------------------------------
bool
SceSphere::FindIntersection( MatRay const & ray, float & t, Vec3f & point, Vec3f & normal)
{
    Vec3f vectorCP = ray.mOrigin - c;
    float pa = ray.mDirection.dot( ray.mDirection );
    float pb = 2 * vectorCP.dot( ray.mDirection );
    float pc = vectorCP.dot( vectorCP ) - r * r;

    float discriminant = pb * pb - 4 * pa * pc;

    if(discriminant < 0)
        return false;

    float sqrtDiscriminant = sqrt(discriminant);

    float tplus = -pb + sqrtDiscriminant;

    if(tplus < 0)
        return false;

    float tminus = -pb - sqrtDiscriminant;
    if(tminus < 0)
        t = tplus / (2 * pa);
    else
        t = tminus / (2 * pa);

    point = ray.mOrigin + t * ray.mDirection;
    normal = ( point - c ) / r;
    normal.normalize();
    return true;
}
//------------------------------------------------------------------------------
