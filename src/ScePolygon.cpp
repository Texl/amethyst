//------------------------------------------------------------------------------
// File:    ScePolygon.cpp
//------------------------------------------------------------------------------
#include "ScePolygon.h"

#include "cinder/app/AppBasic.h"
//------------------------------------------------------------------------------
ScePolygon::ScePolygon(vector<Vec3f> const & vertices, 
                       Material const & material)
: SceObject (material)
{
    for (unsigned int i = 0; i < vertices.size() - 2; ++i)
    {
        mTriangles.push_back(Triangle(vertices[0], vertices[i + 1], vertices[i + 2]));
    }
}
//------------------------------------------------------------------------------
bool
ScePolygon::RayCast(Ray const & ray,
                    float & t) const
{
    for (unsigned int i = 0; i < mTriangles.size(); ++i)
    {
        if (mTriangles[i].Raycast(ray, t))
        {
            return true;
        }
    }
    return false;
}
//------------------------------------------------------------------------------
bool
ScePolygon::RayCast(Ray const & ray, 
                    float & t, 
                    Vec3f & point, 
                    Vec3f & normal) const
{
    for (unsigned int i = 0; i < mTriangles.size(); ++i)
    {
        if (mTriangles[i].Raycast(ray, t, point, normal))
        {
            return true;
        }
    }
    return false;
}
//------------------------------------------------------------------------------
