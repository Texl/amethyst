//------------------------------------------------------------------------------
// File:    Triangle.h
//------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------
#include "cinder/Vector.h"
//------------------------------------------------------------------------------
using namespace ci;
//------------------------------------------------------------------------------
template <class T>
class Triangle
{
    public:
        explicit    Triangle    ( Vec3<T> const & a, Vec3<T> const & b, Vec3<T> const & c );

        bool        Raycast     ( Ray const & ray );

        Vec3<T>     mA;
        Vec3<T>     mB;
        Vec3<T>     mC;
};
//------------------------------------------------------------------------------
inline
template <class T>
Triangle<T>::Triangle( Vec3<T> const & a, Vec3<T> const & b, Vec3<T> const & c )
: mA    ( a )
, mB    ( b )
, mC    ( c )
{
}
//------------------------------------------------------------------------------
inline
template <class T>
Triangle<T>::Raycast( Ray const & ray )
{
    float t;
    bool const hit = ray.calcTriangleIntersection(mA, mB, mC, &t);

    return hit;
}
//------------------------------------------------------------------------------