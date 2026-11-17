
#include "engine/math/Vec3.h"
#include <cmath>
#include <stdexcept>

namespace Engine::Math
{
    Vec3::Vec3()
        : x(0.0f), y(0.0f), z(0.0f)
    {
    }

    Vec3::Vec3(float x, float y, float z)
        : x(x), y(y), z(z)
    {
    }

    Vec3 Vec3::operator+(const Vec3& other) const
    {
        return Vec3(
            x + other.x,
            y + other.y,
            z + other.z
        );
    }

    Vec3 Vec3::operator-(const Vec3& other) const
    {
        return Vec3(
            x - other.x,
            y - other.y,
            z - other.z
        );
    }

    Vec3 Vec3::operator*(float scalar) const
    {
        return Vec3(
            x * scalar,
            y * scalar,
            z * scalar
        );
    }

    Vec3 Vec3::operator/(float scalar) const
    {
        if (scalar == 0.0f)
            throw std::invalid_argument("Division by zero");

        return Vec3(
            x / scalar,
            y / scalar,
            z / scalar
        );
    }

    float Vec3::dot(const Vec3& other) const
    {
        return x * other.x +
               y * other.y +
               z * other.z;
    }

    Vec3 Vec3::cross(const Vec3& other) const
    {
        return Vec3(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }

    float Vec3::lengthSquared() const
    {
        return x * x + y * y + z * z;
    }

    float Vec3::length() const
    {
        return std::sqrt(lengthSquared());
    }

    Vec3 Vec3::normalized() const
    {
        const float magnitude = length();

        if (magnitude == 0.0f)
            throw std::invalid_argument("Cannot normalize zero vector");

        return *this / magnitude;
    }
    
    
    float Vec3::distanceTo(const Vec3& other) const
    {
        return (*this - other).length();
    }

    Vec3 Vec3::projectOnto(const Vec3& other) const
    {
        const float denominator = other.lengthSquared();

        if (denominator == 0.0f)
            throw std::invalid_argument(
                "Cannot project onto zero vector"
            );

        const float scalar = dot(other) / denominator;

        return other * scalar;
    }

    Vec3 Vec3::lerp(
        const Vec3& start,
        const Vec3& end,
        float t
    )
    {
        return start + (end - start) * t;
    }
}
