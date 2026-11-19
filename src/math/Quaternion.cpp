
#include "engine/math/Quaternion.h"

#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace Engine::Math
{
    namespace
    {
        constexpr float EPSILON = 1e-6f;
    }

    Quaternion::Quaternion()
        : a(0.0f), b(0.0f), c(0.0f), d(1.0f)
    {
    }

    Quaternion::Quaternion(float a, float b, float c, float d)
        : a(a), b(b), c(c), d(d)
    {
    }

    Quaternion Quaternion::identity()
    {
        return Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
    }

    float Quaternion::magnitudeSquared() const
    {
        return a*a + b*b + c*c + d*d;
    }

    float Quaternion::magnitude() const
    {
        return std::sqrt(magnitudeSquared());
    }

    Quaternion Quaternion::normalized() const
    {
        const float length = magnitude();

        if (length < EPSILON)
        {
            throw std::domain_error(
                "Cannot normalize a zero quaternion."
            );
        }

        return Quaternion(
            a / length,
            b / length,
            c / length,
            d / length
        );
    }

    Quaternion Quaternion::conjugated() const
    {
        return Quaternion(-a, -b, -c, d);
    }

    Quaternion Quaternion::inversed() const
    {
        const float lengthSquared = magnitudeSquared();

        if (lengthSquared < EPSILON * EPSILON)
        {
            throw std::domain_error(
                "Cannot invert a zero quaternion."
            );
        }

        return Quaternion(
            -a / lengthSquared,
            -b / lengthSquared,
            -c / lengthSquared,
            d / lengthSquared
        );
    }

    float Quaternion::dot(const Quaternion& other) const
    {
        return a * other.a +
               b * other.b +
               c * other.c +
               d * other.d;
    }

    Quaternion Quaternion::operator+(const Quaternion& other) const
    {
        return Quaternion(
            a + other.a,
            b + other.b,
            c + other.c,
            d + other.d
        );
    }

    Quaternion Quaternion::operator-(const Quaternion& other) const
    {
        return Quaternion(
            a - other.a,
            b - other.b,
            c - other.c,
            d - other.d
        );
    }

    Quaternion Quaternion::operator*(const Quaternion& other) const
    {
        // Hamilton product.

        return Quaternion(
            d * other.a + a * other.d +
            b * other.c - c * other.b,

            d * other.b - a * other.c +
            b * other.d + c * other.a,

            d * other.c + a * other.b -
            b * other.a + c * other.d,

            d * other.d - a * other.a -
            b * other.b - c * other.c
        );
    }

    Quaternion Quaternion::operator*(float scalar) const
    {
        return Quaternion(
            a * scalar,
            b * scalar,
            c * scalar,
            d * scalar
        );
    }

    Quaternion Quaternion::operator/(float scalar) const
    {
        if (std::abs(scalar) < EPSILON)
        {
            throw std::invalid_argument(
                "Cannot divide a quaternion by zero."
            );
        }

        return Quaternion(
            a / scalar,
            b / scalar,
            c / scalar,
            d / scalar
        );
    }

    Quaternion Quaternion::fromAxisAngle(
        const Vec3& axis,
        float radians
    )
    {
        const float axisLength = axis.length();

        if (axisLength < EPSILON)
        {
            throw std::invalid_argument(
                "Rotation axis cannot be zero."
            );
        }

        const Vec3 normalizedAxis = axis.normalized();

        const float halfAngle = radians * 0.5f;

        const float sinHalf = std::sin(halfAngle);
        const float cosHalf = std::cos(halfAngle);

        return Quaternion(
            normalizedAxis.x * sinHalf,
            normalizedAxis.y * sinHalf,
            normalizedAxis.z * sinHalf,
            cosHalf
        );
    }

    Quaternion Quaternion::slerp(
        const Quaternion& start,
        const Quaternion& end,
        float t
    )
    {
        Quaternion q1 = start.normalized();
        Quaternion q2 = end.normalized();

        float cosine = q1.dot(q2);

        // Choose the shortest rotation path.
        if (cosine < 0.0f)
        {
            q2 = q2 * -1.0f;
            cosine = -cosine;
        }

        cosine = std::clamp(cosine, -1.0f, 1.0f);

        // Nearly identical quaternions:
        // use normalized linear interpolation.
        if (cosine > 0.9995f)
        {
            Quaternion result =
                q1 * (1.0f - t) + q2 * t;

            return result.normalized();
        }

        const float angle = std::acos(cosine);
        const float sinAngle = std::sin(angle);

        const float weight1 =
            std::sin((1.0f - t) * angle) / sinAngle;

        const float weight2 =
            std::sin(t * angle) / sinAngle;

        Quaternion result =
            q1 * weight1 + q2 * weight2;

        return result.normalized();
    }

    Vec3 Quaternion::rotate(const Vec3& vector) const
    {
        const Quaternion rotation = normalized();

        // A vector becomes a pure quaternion:
        // vector components plus a zero scalar component.
        const Quaternion pureVector(
            vector.x,
            vector.y,
            vector.z,
            0.0f
        );

        // q * p * q^-1
        const Quaternion result =
            rotation * pureVector * rotation.conjugated();

        return Vec3(result.a, result.b, result.c);
    }

    Mat4 Quaternion::toMatrix() const
    {
        const Quaternion q = normalized();

        const float aa = q.a * q.a;
        const float ab = q.a * q.b;
        const float ac = q.a * q.c;

        const float bb = q.b * q.b;
        const float bc = q.b * q.c;
        const float cc = q.c * q.c;

        const float da = q.d * q.a;
        const float db = q.d * q.b;
        const float dc = q.d * q.c;

        Mat4 result = Mat4::identity();

        result.at(0, 0) = 1.0f - 2.0f * (bb + cc);
        result.at(0, 1) = 2.0f * (ab - dc);
        result.at(0, 2) = 2.0f * (ac + db);

        result.at(1, 0) = 2.0f * (ab + dc);
        result.at(1, 1) = 1.0f - 2.0f * (aa + cc);
        result.at(1, 2) = 2.0f * (bc - da);

        result.at(2, 0) = 2.0f * (ac - db);
        result.at(2, 1) = 2.0f * (bc + da);
        result.at(2, 2) = 1.0f - 2.0f * (aa + bb);

        return result;
    }
}
