//------------------------------------------------------------------------------
// File:    ScePolygon.cpp
//------------------------------------------------------------------------------
#include <cmath>

#include "Scene/ScePolygon.h"
//------------------------------------------------------------------------------
void ScePolygon::Precalculate()
{
    SceObject::Precalculate();

    for(int i = 0; i < n - 2; ++i)
    {
        vc.push_back(v[0]);
        va.push_back(v[i+2] - v[0]);
        vb.push_back(v[i+1] - v[0]);
        vn.push_back(vb[i].cross( va[i] ).normalized() );
        denom1Inv.push_back(va[i].dot( va[i] ) / ( va[i].dot( va[i] ) * vb[i].dot( vb[i] ) - pow( va[i].dot( vb[i]), 2)));
        denom2Inv.push_back(vb[i].dot( vb[i] ) / ( va[i].dot( va[i] ) * vb[i].dot( vb[i] ) - pow( va[i].dot( vb[i]), 2)));
        denom3Inv.push_back(va[i].dot( vb[i] ) / ( va[i].dot( va[i] ) * vb[i].dot( vb[i] ) - pow( va[i].dot( vb[i]), 2)));
    }
}
//------------------------------------------------------------------------------
bool ScePolygon::FindIntersection( MatRay const & ray, float &t, Vec3f &point, Vec3f &normal)
{
    for(int i = 0; i < n - 2; ++i)
    {
        float tint = - ( ray.mOrigin - vc[i] ).dot( vn[i] ) / ray.mDirection.dot( vn[i]);
        if(tint < 0)
            continue;

        Vec3f vpc = ray.mOrigin + ray.mDirection * tint - vc[i];
        float dotVpcVa = vpc.dot( va[i] );
        float dotVpcVb = vpc.dot( vb[i] );

        float alpha = dotVpcVa * denom2Inv[i] - dotVpcVb * denom3Inv[i];
        float beta  = dotVpcVb * denom1Inv[i] - dotVpcVa * denom3Inv[i];

        if(alpha >= 0 && beta >= 0 && alpha + beta <= 1)
        {
            t = tint;
            point = ray.mOrigin + t * ray.mDirection;
            normal = vn[i];
            return true;
        }
    }
    return false;
}
//------------------------------------------------------------------------------