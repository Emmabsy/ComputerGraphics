
#include "engine/math/SphericalCoordinates.h"

#include <algorithm>
#include <cmath>

namespace Engine::Math
{
    namespace
    {
        constexpr float PI = 3.14159265358979323846f;
        constexpr float TWO_PI = 2.0f * PI;
        constexpr float EPSILON = 1e-6f;
    }

    SphericalCoordinates::SphericalCoordinates()
        : theta(0.0f), phi(0.0f), radius(0.0f)
    {
    }

    SphericalCoordinates::SphericalCoordinates(
        float theta,
        float phi,
        float radius
    )
        : theta(theta), phi(phi), radius(radius)
    {
    }

    SphericalCoordinates SphericalCoordinates::fromCartesian(
        const Vec3& vector
    )
    {
        // Step 1: Calculate the distance from the origin.
        const float radius = std::sqrt(
            vector.x * vector.x +
            vector.y * vector.y +
            vector.z * vector.z
        );

        // The angles are undefined for the zero vector.
        if (radius < EPSILON)
        {
            return SphericalCoordinates(0.0f, 0.0f, 0.0f);
        }

        // Step 2: Calculate theta.
        // Clamp the value to protect acos from floating-point
        // rounding errors outside the range [-1, 1].
        const float cosTheta = std::clamp(
            vector.z / radius,
            -1.0f,
            1.0f
        );

        const float theta = std::acos(cosTheta);

        // Step 3: Calculate phi using atan2.
        float phi = std::atan2(vector.y, vector.x);

        // Convert negative angles into the range [0, 2*pi).
        if (phi < 0.0f)
        {
            phi += TWO_PI;
        }

        return SphericalCoordinates(theta, phi, radius);
    }

    Vec3 SphericalCoordinates::toCartesian() const
    {
        const float sinTheta = std::sin(theta);
        const float cosTheta = std::cos(theta);

        const float sinPhi = std::sin(phi);
        const float cosPhi = std::cos(phi);

        const float x = radius * sinTheta * cosPhi;
        const float y = radius * sinTheta * sinPhi;
        const float z = radius * cosTheta;

        return Vec3(x, y, z);
    }
}
