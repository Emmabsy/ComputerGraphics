#include "engine/math/Vec4.h"

#include <cmath>
#include <stdexcept>

namespace Engine::Math
{
    // Default constructor
    Vec4::Vec4()
        : x(0.0f), y(0.0f), z(0.0f), w(0.0f)
    {
    }

    // Four-component constructor
    Vec4::Vec4(float x, float y, float z, float w)
        : x(x), y(y), z(z), w(w)
    {
    }

    // Construct from Vec3 and a homogeneous component
    Vec4::Vec4(const Vec3& vector, float w)
        : x(vector.x),
          y(vector.y),
          z(vector.z),
          w(w)
    {
    }

    // Addition
    Vec4 Vec4::operator+(const Vec4& other) const
    {
        return Vec4(
            x + other.x,
            y + other.y,
            z + other.z,
            w + other.w
        );
    }

    // Subtraction
    Vec4 Vec4::operator-(const Vec4& other) const
    {
        return Vec4(
            x - other.x,
            y - other.y,
            z - other.z,
            w - other.w
        );
    }

    // Scalar multiplication
    Vec4 Vec4::operator*(float scalar) const
    {
        return Vec4(
            x * scalar,
            y * scalar,
            z * scalar,
            w * scalar
        );
    }

    // Scalar division
    Vec4 Vec4::operator/(float scalar) const
    {
        if (scalar == 0.0f)
        {
            throw std::invalid_argument(
                "Division by zero"
            );
        }

        return Vec4(
            x / scalar,
            y / scalar,
            z / scalar,
            w / scalar
        );
    }

    // Dot product
    float Vec4::dot(const Vec4& other) const
    {
        return x * other.x +
               y * other.y +
               z * other.z +
               w * other.w;
    }

    // Squared magnitude
    float Vec4::lengthSquared() const
    {
        return x * x +
               y * y +
               z * z +
               w * w;
    }

    // Magnitude
    float Vec4::length() const
    {
        return std::sqrt(lengthSquared());
    }

    // Normalization
    Vec4 Vec4::normalized() const
    {
        const float magnitude = length();

        if (magnitude == 0.0f)
        {
            throw std::invalid_argument(
                "Cannot normalize zero vector"
            );
        }

        return *this / magnitude;
    }

    // Convert homogeneous coordinates into Cartesian coordinates
    Vec3 Vec4::perspectiveDivide() const
    {
        if (std::abs(w) < 1e-6f)
        {
            throw std::domain_error(
                "Cannot perform perspective divide when w is zero"
            );
        }

        return Vec3(
            x / w,
            y / w,
            z / w
        );
    }
}