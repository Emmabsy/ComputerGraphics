#pragma once

#include "engine/math/Vec3.h"

namespace Engine::Math
{
    class Vec4
    {
    public:
        float x;
        float y;
        float z;
        float w;

        // Constructors
        Vec4();
        Vec4(float x, float y, float z, float w);
        Vec4(const Vec3& vector, float w);

        // Arithmetic
        Vec4 operator+(const Vec4& other) const;
        Vec4 operator-(const Vec4& other) const;

        Vec4 operator*(float scalar) const;
        Vec4 operator/(float scalar) const;

        // Vector operations
        float dot(const Vec4& other) const;

        float lengthSquared() const;
        float length() const;

        Vec4 normalized() const;

        // Homogeneous coordinate conversion
        Vec3 perspectiveDivide() const;
    };
}