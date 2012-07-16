//------------------------------------------------------------------------------
// File:    SceBox.cpp
//------------------------------------------------------------------------------
#include "SceBox.h"
//------------------------------------------------------------------------------
SceBox::SceBox(Vec3f const & origin, 
               Vec3f const & length, 
               Vec3f const & width,  
               Vec3f const & height, 
               Material const & material)
: SceObject (material)
{
    mPoints[0] = origin;
    mPoints[1] = origin + width;
    mPoints[2] = origin;
    mPoints[3] = origin + length;
    mPoints[4] = origin;
    mPoints[5] = origin + height;

    mNormals[0] = length.cross(height).normalized();
    mNormals[1] = -mNormals[0];
    mNormals[2] = height.cross(width).normalized();
    mNormals[3] = -mNormals[2];
    mNormals[4] = width.cross(length).normalized();
    mNormals[5] = -mNormals[4];
}
//------------------------------------------------------------------------------
bool
SceBox::RayCast(Ray const & ray,
                float & t) const
{
    float tIntersection;
    unsigned int index;

    if (_RayCast(ray, tIntersection, index))
    {
        t = tIntersection;
        return true;
    }

    return false;
}
//------------------------------------------------------------------------------
bool
SceBox::RayCast(Ray const & ray, 
                float & t, 
                Vec3f & point, 
                Vec3f & normal) const
{
    float tIntersection;
    unsigned int index;

    if (_RayCast(ray, tIntersection, index))
    {
        t = tIntersection;
        point = ray.calcPosition(tIntersection);
        normal = mNormals[index];
        return true;
    }

    return false;
}
//------------------------------------------------------------------------------
bool
SceBox::_RayCast(Ray const & ray,
                 float & t,
                 unsigned int & index) const
{
    float tMin = 0.0f;
    float tMax = FLT_MAX;

    int tMinIndex;
    int tMaxIndex;

    for (int i = 0; i < 6 && tMin <= tMax; ++i)
    {
        float dotDN = ray.getDirection().dot(mNormals[i]);
        float dotPPN = (ray.getOrigin() - mPoints[i]).dot(mNormals[i]);
        float tIntersection = -dotPPN / dotDN;

        if (dotDN < 0)
        {
            if (tIntersection > tMin)
            {
                tMinIndex = i;
                tMin = tIntersection;
            }
        }
        else if (dotDN > 0)
        {
            if (tIntersection < tMax)
            {
                tMaxIndex = i;
                tMax = tIntersection;
            }
        }
        else if (dotPPN > 0)
        {
            return false;
        }
    }

    if (tMin >= tMax)
    {
        return false;
    }
    
    if (tMin == 0)
    {
        t = tMax;
        index = tMaxIndex;
    }
    else
    {
        t = tMin;
        index = tMinIndex;
    }

    return true;
}
//------------------------------------------------------------------------------
