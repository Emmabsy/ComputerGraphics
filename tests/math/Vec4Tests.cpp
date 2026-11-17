#include "engine/math/Vec4.h"

#include <cassert>
#include <cmath>
#include <iostream>
#include <stdexcept>

using Engine::Math::Vec3;
using Engine::Math::Vec4;

bool approximatelyEqual(float a, float b)
{
    return std::abs(a - b) < 0.0001f;
}

bool approximatelyEqual(const Vec4& a, const Vec4& b)
{
    return approximatelyEqual(a.x, b.x) &&
           approximatelyEqual(a.y, b.y) &&
           approximatelyEqual(a.z, b.z) &&
           approximatelyEqual(a.w, b.w);
}

bool approximatelyEqual(const Vec3& a, const Vec3& b)
{
    return approximatelyEqual(a.x, b.x) &&
           approximatelyEqual(a.y, b.y) &&
           approximatelyEqual(a.z, b.z);
}

int main()
{
    // 1. Default constructor
    {
        Vec4 v;

        assert(approximatelyEqual(v.x, 0.0f));
        assert(approximatelyEqual(v.y, 0.0f));
        assert(approximatelyEqual(v.z, 0.0f));
        assert(approximatelyEqual(v.w, 0.0f));
    }

    // 2. Four-component constructor
    {
        Vec4 v(1.0f, 2.0f, 3.0f, 4.0f);

        assert(approximatelyEqual(v.x, 1.0f));
        assert(approximatelyEqual(v.y, 2.0f));
        assert(approximatelyEqual(v.z, 3.0f));
        assert(approximatelyEqual(v.w, 4.0f));
    }

    // 3. Construct from Vec3
    {
        Vec3 v(1.0f, 2.0f, 3.0f);
        Vec4 point(v, 1.0f);

        assert(approximatelyEqual(
            point, Vec4(1.0f, 2.0f, 3.0f, 1.0f)
        ));
    }

    // 4. Addition
    {
        Vec4 a(1.0f, 2.0f, 3.0f, 4.0f);
        Vec4 b(5.0f, 6.0f, 7.0f, 8.0f);

        assert(approximatelyEqual(
            a + b, Vec4(6.0f, 8.0f, 10.0f, 12.0f)
        ));
    }

    // 5. Subtraction
    {
        Vec4 a(5.0f, 6.0f, 7.0f, 8.0f);
        Vec4 b(1.0f, 2.0f, 3.0f, 4.0f);

        assert(approximatelyEqual(
            a - b, Vec4(4.0f, 4.0f, 4.0f, 4.0f)
        ));
    }

    // 6. Scalar multiplication
    {
        Vec4 v(1.0f, 2.0f, 3.0f, 4.0f);

        assert(approximatelyEqual(
            v * 2.0f, Vec4(2.0f, 4.0f, 6.0f, 8.0f)
        ));
    }

    // 7. Scalar division
    {
        Vec4 v(2.0f, 4.0f, 6.0f, 8.0f);

        assert(approximatelyEqual(
            v / 2.0f, Vec4(1.0f, 2.0f, 3.0f, 4.0f)
        ));
    }

    // 8. Division by zero throws
    {
        bool exceptionThrown = false;

        try
        {
            Vec4(1.0f, 2.0f, 3.0f, 4.0f) / 0.0f;
        }
        catch (const std::invalid_argument&)
        {
            exceptionThrown = true;
        }

        assert(exceptionThrown);
    }

    // 9. Dot product
    {
        Vec4 a(1.0f, 2.0f, 3.0f, 4.0f);
        Vec4 b(5.0f, 6.0f, 7.0f, 8.0f);

        // 5 + 12 + 21 + 32 = 70
        assert(approximatelyEqual(a.dot(b), 70.0f));
    }

    // 10. Squared length
    {
        Vec4 v(1.0f, 2.0f, 3.0f, 4.0f);

        // 1 + 4 + 9 + 16 = 30
        assert(approximatelyEqual(v.lengthSquared(), 30.0f));
    }

    // 11. Length
    {
        Vec4 v(1.0f, 2.0f, 2.0f, 0.0f);

        assert(approximatelyEqual(v.length(), 3.0f));
    }

    // 12. Normalization
    {
        Vec4 v(0.0f, 3.0f, 0.0f, 4.0f);

        Vec4 result = v.normalized();

        assert(approximatelyEqual(
            result, Vec4(0.0f, 0.6f, 0.0f, 0.8f)
        ));

        assert(approximatelyEqual(result.length(), 1.0f));
    }

    // 13. Normalizing zero vector throws
    {
        bool exceptionThrown = false;

        try
        {
            Vec4().normalized();
        }
        catch (const std::invalid_argument&)
        {
            exceptionThrown = true;
        }

        assert(exceptionThrown);
    }

    // 14. Perspective divide
    {
        Vec4 homogeneous(8.0f, 6.0f, 4.0f, 2.0f);

        Vec3 result = homogeneous.perspectiveDivide();

        assert(approximatelyEqual(
            result, Vec3(4.0f, 3.0f, 2.0f)
        ));
    }

    // 15. Perspective divide with w = 0 throws
    {
        bool exceptionThrown = false;

        try
        {
            Vec4(1.0f, 2.0f, 3.0f, 0.0f).perspectiveDivide();
        }
        catch (const std::domain_error&)
        {
            exceptionThrown = true;
        }

        assert(exceptionThrown);
    }

    // 16. Point and direction representations
    {
        Vec3 position(2.0f, 3.0f, 4.0f);

        Vec4 point(position, 1.0f);
        Vec4 direction(position, 0.0f);

        assert(approximatelyEqual(point.w, 1.0f));
        assert(approximatelyEqual(direction.w, 0.0f));
    }

    std::cout << "All Vec4 tests passed!\n";

    return 0;
}