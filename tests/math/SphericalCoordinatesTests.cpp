
#include "engine/math/SphericalCoordinates.h"

#include <cassert>
#include <cmath>
#include <iostream>

using namespace Engine::Math;

namespace
{
    constexpr float EPSILON = 1e-5f;
    constexpr float PI = 3.14159265358979323846f;

    bool equal(float a, float b)
    {
        return std::abs(a - b) < EPSILON;
    }

    bool equal(const Vec3& a, const Vec3& b)
    {
        return equal(a.x, b.x) &&
               equal(a.y, b.y) &&
               equal(a.z, b.z);
    }

    void testDefaultConstructor()
    {
        SphericalCoordinates spherical;

        assert(equal(spherical.theta, 0.0f));
        assert(equal(spherical.phi, 0.0f));
        assert(equal(spherical.radius, 0.0f));
    }

    void testSphericalToCartesianPositiveX()
    {
        SphericalCoordinates spherical(
            PI / 2.0f,
            0.0f,
            1.0f
        );

        Vec3 result = spherical.toCartesian();

        assert(equal(result, Vec3(1, 0, 0)));
    }

    void testSphericalToCartesianPositiveY()
    {
        SphericalCoordinates spherical(
            PI / 2.0f,
            PI / 2.0f,
            1.0f
        );

        Vec3 result = spherical.toCartesian();

        assert(equal(result, Vec3(0, 1, 0)));
    }

    void testSphericalToCartesianPositiveZ()
    {
        SphericalCoordinates spherical(
            0.0f,
            0.0f,
            1.0f
        );

        Vec3 result = spherical.toCartesian();

        assert(equal(result, Vec3(0, 0, 1)));
    }

    void testCartesianToSphericalPositiveX()
    {
        SphericalCoordinates result =
            SphericalCoordinates::fromCartesian(
                Vec3(1, 0, 0)
            );

        assert(equal(result.radius, 1.0f));
        assert(equal(result.theta, PI / 2.0f));
        assert(equal(result.phi, 0.0f));
    }

    void testCartesianToSphericalPositiveY()
    {
        SphericalCoordinates result =
            SphericalCoordinates::fromCartesian(
                Vec3(0, 1, 0)
            );

        assert(equal(result.radius, 1.0f));
        assert(equal(result.theta, PI / 2.0f));
        assert(equal(result.phi, PI / 2.0f));
    }

    void testCartesianToSphericalPositiveZ()
    {
        SphericalCoordinates result =
            SphericalCoordinates::fromCartesian(
                Vec3(0, 0, 1)
            );

        assert(equal(result.radius, 1.0f));
        assert(equal(result.theta, 0.0f));
    }

    void testZeroVector()
    {
        SphericalCoordinates result =
            SphericalCoordinates::fromCartesian(
                Vec3(0, 0, 0)
            );

        assert(equal(result.radius, 0.0f));
        assert(equal(result.theta, 0.0f));
        assert(equal(result.phi, 0.0f));
    }

    void testRoundTrip()
    {
        const Vec3 original(2, 3, 4);

        SphericalCoordinates spherical =
            SphericalCoordinates::fromCartesian(original);

        Vec3 recovered = spherical.toCartesian();

        assert(equal(recovered, original));
    }

    void testNegativeYAngle()
    {
        SphericalCoordinates result =
            SphericalCoordinates::fromCartesian(
                Vec3(0, -1, 0)
            );

        // Negative Y should produce an azimuth of 3*pi/2.
        assert(equal(result.phi, 3.0f * PI / 2.0f));
    }

    void testRadiusPreserved()
    {
        SphericalCoordinates result =
            SphericalCoordinates::fromCartesian(
                Vec3(3, 4, 0)
            );

        assert(equal(result.radius, 5.0f));
    }
}

int main()
{
    testDefaultConstructor();
    testSphericalToCartesianPositiveX();
    testSphericalToCartesianPositiveY();
    testSphericalToCartesianPositiveZ();
    testCartesianToSphericalPositiveX();
    testCartesianToSphericalPositiveY();
    testCartesianToSphericalPositiveZ();
    testZeroVector();
    testRoundTrip();
    testNegativeYAngle();
    testRadiusPreserved();

    std::cout << "All SphericalCoordinates tests passed.\n";

    return 0;
}
