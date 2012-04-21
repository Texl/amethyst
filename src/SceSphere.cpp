//------------------------------------------------------------------------------
// File:    SceSphere.cpp
//------------------------------------------------------------------------------
#include <cmath>

#include "SceSphere.h"
//------------------------------------------------------------------------------
void
SceSphere::Precalculate()
{
    SceObject::Precalculate();
}
//------------------------------------------------------------------------------
bool
SceSphere::FindIntersection( Ray const & ray, float & t, Vec3f & point, Vec3f & normal)
{
    Vec3f vectorCP = ray.getOrigin() - c;
    float pa = ray.getDirection().dot( ray.getDirection() );
    float pb = 2 * vectorCP.dot( ray.getDirection() );
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

    point = ray.getOrigin() + t * ray.getDirection();
    normal = ( point - c ) / r;
    normal.normalize();
    return true;
}
//------------------------------------------------------------------------------
