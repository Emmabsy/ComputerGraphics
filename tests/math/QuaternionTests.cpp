
#include "engine/math/Quaternion.h"

#include <cassert>
#include <cmath>
#include <iostream>
#include <stdexcept>

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
        Quaternion q;

        assert(equal(q.a, 0));
        assert(equal(q.b, 0));
        assert(equal(q.c, 0));
        assert(equal(q.d, 1));
    }

    void testMagnitude()
    {
        Quaternion q(1, 2, 3, 4);

        assert(equal(q.magnitudeSquared(), 30));
        assert(equal(q.magnitude(), std::sqrt(30.0f)));
    }

    void testNormalization()
    {
        Quaternion q(0, 0, 0, 5);
        Quaternion result = q.normalized();

        assert(equal(result.magnitude(), 1));
        assert(equal(result.d, 1));
    }

    void testZeroNormalizationThrows()
    {
        bool threw = false;

        try
        {
            Quaternion(0, 0, 0, 0).normalized();
        }
        catch (const std::domain_error&)
        {
            threw = true;
        }

        assert(threw);
    }

    void testConjugate()
    {
        Quaternion q(1, 2, 3, 4);
        Quaternion result = q.conjugated();

        assert(equal(result.a, -1));
        assert(equal(result.b, -2));
        assert(equal(result.c, -3));
        assert(equal(result.d, 4));
    }

    void testInverse()
    {
        Quaternion q(1, 2, 3, 4);

        Quaternion result = q * q.inversed();

        assert(equal(result.a, 0));
        assert(equal(result.b, 0));
        assert(equal(result.c, 0));
        assert(equal(result.d, 1));
    }

    void testDotProduct()
    {
        Quaternion q1(1, 2, 3, 4);
        Quaternion q2(2, 3, 4, 5);

        assert(equal(q1.dot(q2), 40));
    }

    void testAddition()
    {
        Quaternion result =
            Quaternion(1, 2, 3, 4) +
            Quaternion(5, 6, 7, 8);

        assert(equal(result.a, 6));
        assert(equal(result.b, 8));
        assert(equal(result.c, 10));
        assert(equal(result.d, 12));
    }

    void testSubtraction()
    {
        Quaternion result =
            Quaternion(5, 6, 7, 8) -
            Quaternion(1, 2, 3, 4);

        assert(equal(result.a, 4));
        assert(equal(result.b, 4));
        assert(equal(result.c, 4));
        assert(equal(result.d, 4));
    }

    void testHamiltonProduct()
    {
        Quaternion result =
            Quaternion(1, 2, 3, 4) *
            Quaternion(5, 6, 7, 8);

        assert(equal(result.a, 24));
        assert(equal(result.b, 48));
        assert(equal(result.c, 48));
        assert(equal(result.d, -6));
    }

    void testAxisAngle()
    {
        Quaternion q = Quaternion::fromAxisAngle(
            Vec3(0, 0, 1),
            PI / 2.0f
        );

        assert(equal(q.a, 0));
        assert(equal(q.b, 0));
        assert(equal(q.c, std::sin(PI / 4.0f)));
        assert(equal(q.d, std::cos(PI / 4.0f)));
    }

    void testZeroAxisThrows()
    {
        bool threw = false;

        try
        {
            Quaternion::fromAxisAngle(
                Vec3(0, 0, 0),
                PI / 2.0f
            );
        }
        catch (const std::invalid_argument&)
        {
            threw = true;
        }

        assert(threw);
    }

    void testRotateVector()
    {
        Quaternion rotation = Quaternion::fromAxisAngle(
            Vec3(0, 0, 1),
            PI / 2.0f
        );

        Vec3 result = rotation.rotate(Vec3(1, 0, 0));

        assert(equal(result, Vec3(0, 1, 0)));
    }

  
    void testSlerpEndpoints()
    {
        Quaternion start = Quaternion::identity();

        Quaternion end = Quaternion::fromAxisAngle(
            Vec3(0, 0, 1),
            PI
        );

        Quaternion first = Quaternion::slerp(start, end, 0);
        Quaternion last = Quaternion::slerp(start, end, 1);

        // q and -q represent the same rotation.
        // Therefore, compare using the absolute dot product.
        assert(equal(std::abs(first.dot(start)), 1.0f));
        assert(equal(std::abs(last.dot(end)), 1.0f));
    }

   
    void testSlerpMidpoint()
    {
        Quaternion start = Quaternion::identity();

        // Use a 90-degree destination rotation.
        // Its midpoint is an unambiguous 45-degree rotation.
        Quaternion end = Quaternion::fromAxisAngle(
            Vec3(0, 0, 1),
            PI / 2.0f
        );

        Quaternion middle = Quaternion::slerp(start, end, 0.5f);

        Vec3 result = middle.rotate(Vec3(1, 0, 0));

        const float expected = std::sqrt(0.5f);

        assert(equal(result.x, expected));
        assert(equal(result.y, expected));
        assert(equal(result.z, 0.0f));
    }


    void testToMatrix()
    {
        Quaternion q = Quaternion::fromAxisAngle(
            Vec3(0, 0, 1),
            PI / 2.0f
        );

        Mat4 matrix = q.toMatrix();

        Vec3 result = matrix.transformDirection(Vec3(1, 0, 0));

        assert(equal(result, Vec3(0, 1, 0)));
    }
}

int main()
{
    testDefaultConstructor();
    testMagnitude();
    testNormalization();
    testZeroNormalizationThrows();
    testConjugate();
    testInverse();
    testDotProduct();
    testAddition();
    testSubtraction();
    testHamiltonProduct();
    testAxisAngle();
    testZeroAxisThrows();
    testRotateVector();
    testSlerpEndpoints();
    testSlerpMidpoint();
    testToMatrix();

    std::cout << "All Quaternion tests passed.\n";

    return 0;
}
