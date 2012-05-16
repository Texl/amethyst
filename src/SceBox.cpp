//------------------------------------------------------------------------------
// File:    SceBox.cpp
//------------------------------------------------------------------------------
#include "SceBox.h"
//------------------------------------------------------------------------------
SceBox::SceBox( Vec3f const & v, Vec3f const & l, Vec3f const & w, Vec3f const & h, Material const & material )
: SceObject ( material )
{
    points[0] = v;
    points[1] = v + w;
    points[2] = v;
    points[3] = v + l;
    points[4] = v;
    points[5] = v + h;

    normals[0] = l.cross( h ).normalized();
    normals[1] = normals[0] * -1;
    normals[2] = h.cross( w ).normalized();
    normals[3] = normals[2] * -1;
    normals[4] = w.cross( l ).normalized();
    normals[5] = normals[4] * -1;
}
//------------------------------------------------------------------------------
bool SceBox::FindIntersection( Ray const & ray, float &t, Vec3f &point, Vec3f &normal)
{
    float tmin = 0.0f;
    float tmax = FLT_MAX;

    int tminIndex, tmaxIndex, tIndex;

    for(int i = 0; i < 6 && tmin <= tmax; ++i)
    {
        float dotDN = ray.getDirection().dot(normals[i]);
        float dotPPN = ( ray.getOrigin() - points[i] ).dot( normals[i]);
        float tint = -dotPPN / dotDN;
        if(dotDN < 0)
        {
            if(tint > tmin)
            {
                tminIndex = i;
                tmin = tint;
            }
        }
        else if(dotDN > 0)
        {
            if(tint < tmax)
            {
                tmaxIndex = i;
                tmax = tint;
            }
        }
        else if(dotPPN > 0)
        {
            return false;
        }
    }

    if(tmin >= tmax)
        return false;
    
    if(tmin == 0)
    {
        t = tmax;
        tIndex = tmaxIndex;
    }
    else
    {
        t = tmin;
        tIndex = tminIndex;
    }

    point = ray.getOrigin() + t * ray.getDirection();
    normal = normals[tIndex];
    return true;
}
//------------------------------------------------------------------------------
