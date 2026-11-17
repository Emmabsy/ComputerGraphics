
#include "engine/math/Mat4.h"

#include <cassert>
#include <cmath>
#include <iostream>
#include <stdexcept>

using Engine::Math::Mat4;
using Engine::Math::Vec3;

bool approximatelyEqual(float a, float b)
{
    return std::abs(a - b) < 0.0001f;
}

bool approximatelyEqual(const Vec3& a, const Vec3& b)
{
    return approximatelyEqual(a.x, b.x) &&
           approximatelyEqual(a.y, b.y) &&
           approximatelyEqual(a.z, b.z);
}

bool approximatelyEqual(const Mat4& a, const Mat4& b)
{
    for (int row = 0; row < 4; ++row)
    {
        for (int column = 0; column < 4; ++column)
        {
            if (!approximatelyEqual(
                a.m[row][column],
                b.m[row][column]))
            {
                return false;
            }
        }
    }

    return true;
}

int main()
{
    // 1. Default constructor creates a zero matrix.
    {
        Mat4 matrix;

        for (int row = 0; row < 4; ++row)
        {
            for (int column = 0; column < 4; ++column)
            {
                assert(approximatelyEqual(
                    matrix.m[row][column], 0.0f));
            }
        }
    }

    // 2. Identity matrix.
    {
        Mat4 matrix = Mat4::identity();

        for (int row = 0; row < 4; ++row)
        {
            for (int column = 0; column < 4; ++column)
            {
                const float expected =
                    row == column ? 1.0f : 0.0f;

                assert(approximatelyEqual(
                    matrix.m[row][column], expected));
            }
        }
    }

    // 3. Matrix addition.
    {
        Mat4 a = Mat4::identity();
        Mat4 b = Mat4::identity();

        Mat4 result = a + b;

        assert(approximatelyEqual(result.m[0][0], 2.0f));
        assert(approximatelyEqual(result.m[1][1], 2.0f));
        assert(approximatelyEqual(result.m[2][2], 2.0f));
        assert(approximatelyEqual(result.m[3][3], 2.0f));
    }

    // 4. Matrix subtraction.
    {
        Mat4 a = Mat4::identity();
        Mat4 b = Mat4::identity();

        Mat4 result = a - b;

        assert(approximatelyEqual(result, Mat4()));
    }

    // 5. Scalar multiplication.
    {
        Mat4 result = Mat4::identity() * 3.0f;

        assert(approximatelyEqual(result.m[0][0], 3.0f));
        assert(approximatelyEqual(result.m[1][1], 3.0f));
        assert(approximatelyEqual(result.m[2][2], 3.0f));
        assert(approximatelyEqual(result.m[3][3], 3.0f));
    }

    // 6. Matrix multiplication.
    {
        Mat4 a = Mat4::scaling(2.0f, 3.0f, 4.0f);
        Mat4 b = Mat4::scaling(5.0f, 2.0f, 3.0f);

        Mat4 result = a * b;

        assert(approximatelyEqual(result.m[0][0], 10.0f));
        assert(approximatelyEqual(result.m[1][1], 6.0f));
        assert(approximatelyEqual(result.m[2][2], 12.0f));
        assert(approximatelyEqual(result.m[3][3], 1.0f));
    }

    // 7. Matrix multiplied by identity.
    {
        Mat4 matrix = Mat4::translation(5.0f, 2.0f, 1.0f);

        assert(approximatelyEqual(
            matrix * Mat4::identity(), matrix));

        assert(approximatelyEqual(
            Mat4::identity() * matrix, matrix));
    }

    // 8. Element access.
    {
        Mat4 matrix;

        matrix.at(1, 2) = 7.0f;

        assert(approximatelyEqual(matrix.at(1, 2), 7.0f));

        bool exceptionThrown = false;

        try
        {
            matrix.at(4, 0);
        }
        catch (const std::out_of_range&)
        {
            exceptionThrown = true;
        }

        assert(exceptionThrown);
    }

    // 9. Transpose.
    {
        Mat4 matrix;

        matrix.m[0][1] = 2.0f;
        matrix.m[1][2] = 3.0f;
        matrix.m[2][3] = 4.0f;

        Mat4 result = matrix.transposed();

        assert(approximatelyEqual(result.m[1][0], 2.0f));
        assert(approximatelyEqual(result.m[2][1], 3.0f));
        assert(approximatelyEqual(result.m[3][2], 4.0f));
    }

    // 10. Determinant of identity.
    {
        assert(approximatelyEqual(
            Mat4::identity().determinant(), 1.0f));
    }

    // 11. Determinant of a scaling matrix.
    {
        Mat4 matrix = Mat4::scaling(2.0f, 3.0f, 4.0f);

        // 2 * 3 * 4 * 1 = 24.
        assert(approximatelyEqual(
            matrix.determinant(), 24.0f));
    }

    // 12. Determinant of a singular matrix.
    {
        Mat4 matrix = Mat4::scaling(2.0f, 3.0f, 0.0f);

        assert(approximatelyEqual(
            matrix.determinant(), 0.0f));
    }

    // 13. Inverse of a scaling matrix.
    {
        Mat4 matrix = Mat4::scaling(2.0f, 4.0f, 5.0f);

        Mat4 inverse = matrix.inversed();

        assert(approximatelyEqual(inverse.m[0][0], 0.5f));
        assert(approximatelyEqual(inverse.m[1][1], 0.25f));
        assert(approximatelyEqual(inverse.m[2][2], 0.2f));
        assert(approximatelyEqual(inverse.m[3][3], 1.0f));

        assert(approximatelyEqual(
            matrix * inverse, Mat4::identity()));
    }

    // 14. Inverse of a translation matrix.
    {
        Mat4 matrix = Mat4::translation(5.0f, 3.0f, 2.0f);

        Mat4 inverse = matrix.inversed();

        assert(approximatelyEqual(inverse.m[0][3], -5.0f));
        assert(approximatelyEqual(inverse.m[1][3], -3.0f));
        assert(approximatelyEqual(inverse.m[2][3], -2.0f));

        assert(approximatelyEqual(
            matrix * inverse, Mat4::identity()));
    }

    // 15. Inverse of a combined transformation.
    {
        Mat4 matrix =
            Mat4::translation(5.0f, 3.0f, 2.0f) *
            Mat4::rotationZ(0.5f) *
            Mat4::scaling(2.0f, 3.0f, 4.0f);

        Mat4 inverse = matrix.inversed();

        assert(approximatelyEqual(
            matrix * inverse, Mat4::identity()));

        assert(approximatelyEqual(
            inverse * matrix, Mat4::identity()));
    }

    // 16. Inverting a singular matrix must throw.
    {
        Mat4 matrix = Mat4::scaling(2.0f, 3.0f, 0.0f);

        bool exceptionThrown = false;

        try
        {
            matrix.inversed();
        }
        catch (const std::domain_error&)
        {
            exceptionThrown = true;
        }

        assert(exceptionThrown);
    }

    // 17. Translation transforms a point.
    {
        Mat4 matrix = Mat4::translation(5.0f, 2.0f, 1.0f);

        Vec3 point(2.0f, 3.0f, 4.0f);

        Vec3 result = matrix.transformPoint(point);

        assert(approximatelyEqual(result, Vec3(7.0f, 5.0f, 5.0f)));
    }

    // 18. Translation does not affect a direction.
    {
        Mat4 matrix = Mat4::translation(5.0f, 2.0f, 1.0f);

        Vec3 direction(1.0f, 2.0f, 3.0f);

        Vec3 result = matrix.transformDirection(direction);

        assert(approximatelyEqual(result, direction));
    }

    // 19. Scaling transforms a point.
    {
        Mat4 matrix = Mat4::scaling(2.0f, 3.0f, 4.0f);

        Vec3 point(1.0f, 2.0f, 3.0f);

        Vec3 result = matrix.transformPoint(point);

        assert(approximatelyEqual(result, Vec3(2.0f, 6.0f, 12.0f)));
    }

    // 20. Rotation around Z.
    {
        constexpr float halfPi = 1.57079632679f;

        Mat4 matrix = Mat4::rotationZ(halfPi);

        Vec3 result = matrix.transformPoint(Vec3(1.0f, 0.0f, 0.0f));

        assert(approximatelyEqual(result, Vec3(0.0f, 1.0f, 0.0f)));
    }

    // 21. Transforming a point with resulting w = 0 throws.
    {
        Mat4 matrix;

        bool exceptionThrown = false;

        try
        {
            matrix.transformPoint(Vec3(1.0f, 2.0f, 3.0f));
        }
        catch (const std::domain_error&)
        {
            exceptionThrown = true;
        }

        assert(exceptionThrown);
    }
    
    //
    // Test 22: Look-at camera facing negative Z.
    {
        const Vec3 eye(0.0f, 0.0f, 5.0f);
        const Vec3 target(0.0f, 0.0f, 0.0f);
        const Vec3 worldUp(0.0f, 1.0f, 0.0f);

        const Mat4 view = Mat4::lookAt(eye, target, worldUp);

        const Vec3 result = view.transformPoint(target);

        assert(approximatelyEqual(result.x, 0.0f));
        assert(approximatelyEqual(result.y, 0.0f));
        assert(approximatelyEqual(result.z, -5.0f));
    }

    // Test 23: Look-at camera positioned on the X axis.
    {
        const Vec3 eye(5.0f, 0.0f, 0.0f);
        const Vec3 target(0.0f, 0.0f, 0.0f);
        const Vec3 worldUp(0.0f, 1.0f, 0.0f);

        const Mat4 view = Mat4::lookAt(eye, target, worldUp);

        const Vec3 result = view.transformPoint(target);

        assert(approximatelyEqual(result.x, 0.0f));
        assert(approximatelyEqual(result.y, 0.0f));
        assert(approximatelyEqual(result.z, -5.0f));
    }

    // Test 24: Look-at rejects identical eye and target positions.
    {
        bool exceptionThrown = false;

        try
        {
            Mat4::lookAt(
                Vec3(0.0f, 0.0f, 5.0f),
                Vec3(0.0f, 0.0f, 5.0f),
                Vec3(0.0f, 1.0f, 0.0f)
            );
        }
        catch (const std::invalid_argument&)
        {
            exceptionThrown = true;
        }

        assert(exceptionThrown);
    }

    // Test 25: Look-at rejects a world-up vector parallel to forward.
    {
        bool exceptionThrown = false;

        try
        {
            Mat4::lookAt(
                Vec3(0.0f, 0.0f, 5.0f),
                Vec3(0.0f, 0.0f, 0.0f),
                Vec3(0.0f, 0.0f, -1.0f)
            );
        }
        catch (const std::invalid_argument&)
        {
            exceptionThrown = true;
        }

        assert(exceptionThrown);
    }
    std::cout << "All Mat4 tests passed!\n";

    return 0;
}
