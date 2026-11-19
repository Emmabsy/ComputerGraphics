
#pragma once

#include "engine/math/Vec3.h"
#include "engine/math/Mat4.h"

namespace Engine::Math
{
    class Quaternion
    {
    public:
        float a;
        float b;
        float c;
        float d;

        Quaternion();
        Quaternion(float a, float b, float c, float d);

        static Quaternion identity();

        float magnitudeSquared() const;
        float magnitude() const;

        Quaternion normalized() const;
        Quaternion conjugated() const;
        Quaternion inversed() const;

        float dot(const Quaternion& other) const;

        Quaternion operator+(const Quaternion& other) const;
        Quaternion operator-(const Quaternion& other) const;

        Quaternion operator*(const Quaternion& other) const;
        Quaternion operator*(float scalar) const;
        Quaternion operator/(float scalar) const;

        static Quaternion fromAxisAngle(
            const Vec3& axis,
            float radians
        );

        static Quaternion slerp(
            const Quaternion& start,
            const Quaternion& end,
            float t
        );

        Vec3 rotate(const Vec3& vector) const;

        Mat4 toMatrix() const;
    };
}
