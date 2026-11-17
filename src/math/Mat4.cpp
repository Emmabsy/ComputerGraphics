
#include "engine/math/Mat4.h"

#include <cmath>
#include <stdexcept>
#include <algorithm>

namespace Engine::Math
{
    namespace
    {
        constexpr float epsilon = 1e-6f;
    }

    // ---------------------------------------------------------
    // CONSTRUCTOR
    // ---------------------------------------------------------

    Mat4::Mat4()
    {
        for (int row = 0; row < 4; ++row)
        {
            for (int column = 0; column < 4; ++column)
            {
                m[row][column] = 0.0f;
            }
        }
    }

    // ---------------------------------------------------------
    // IDENTITY
    // ---------------------------------------------------------

    Mat4 Mat4::identity()
    {
        Mat4 result;

        for (int i = 0; i < 4; ++i)
        {
            result.m[i][i] = 1.0f;
        }

        return result;
    }

    // ---------------------------------------------------------
    // ELEMENT ACCESS
    // ---------------------------------------------------------

    float& Mat4::at(int row, int column)
    {
        if (row < 0 || row >= 4 ||
            column < 0 || column >= 4)
        {
            throw std::out_of_range("Mat4 index out of range.");
        }

        return m[row][column];
    }

    const float& Mat4::at(int row, int column) const
    {
        if (row < 0 || row >= 4 ||
            column < 0 || column >= 4)
        {
            throw std::out_of_range("Mat4 index out of range.");
        }

        return m[row][column];
    }

    // ---------------------------------------------------------
    // ADDITION
    // ---------------------------------------------------------

    Mat4 Mat4::operator+(const Mat4& other) const
    {
        Mat4 result;

        for (int row = 0; row < 4; ++row)
        {
            for (int column = 0; column < 4; ++column)
            {
                result.m[row][column] =
                    m[row][column] + other.m[row][column];
            }
        }

        return result;
    }

    // ---------------------------------------------------------
    // SUBTRACTION
    // ---------------------------------------------------------

    Mat4 Mat4::operator-(const Mat4& other) const
    {
        Mat4 result;

        for (int row = 0; row < 4; ++row)
        {
            for (int column = 0; column < 4; ++column)
            {
                result.m[row][column] =
                    m[row][column] - other.m[row][column];
            }
        }

        return result;
    }

    // ---------------------------------------------------------
    // SCALAR MULTIPLICATION
    // ---------------------------------------------------------

    Mat4 Mat4::operator*(float scalar) const
    {
        Mat4 result;

        for (int row = 0; row < 4; ++row)
        {
            for (int column = 0; column < 4; ++column)
            {
                result.m[row][column] =
                    m[row][column] * scalar;
            }
        }

        return result;
    }

    // ---------------------------------------------------------
    // MATRIX MULTIPLICATION
    // ---------------------------------------------------------

    Mat4 Mat4::operator*(const Mat4& other) const
    {
        Mat4 result;

        for (int row = 0; row < 4; ++row)
        {
            for (int column = 0; column < 4; ++column)
            {
                float sum = 0.0f;

                for (int k = 0; k < 4; ++k)
                {
                    sum += m[row][k] * other.m[k][column];
                }

                result.m[row][column] = sum;
            }
        }

        return result;
    }

    // ---------------------------------------------------------
    // TRANSPOSE
    // ---------------------------------------------------------

    Mat4 Mat4::transposed() const
    {
        Mat4 result;

        for (int row = 0; row < 4; ++row)
        {
            for (int column = 0; column < 4; ++column)
            {
                result.m[row][column] =
                    m[column][row];
            }
        }

        return result;
    }

    // ---------------------------------------------------------
    // DETERMINANT
    // ---------------------------------------------------------

    float Mat4::determinant() const
    {
        // Work on a copy because elimination modifies the matrix.
        float a[4][4];

        for (int row = 0; row < 4; ++row)
        {
            for (int column = 0; column < 4; ++column)
            {
                a[row][column] = m[row][column];
            }
        }

        float det = 1.0f;
        int sign = 1;

        for (int column = 0; column < 4; ++column)
        {
            // Find the row with the largest absolute pivot.
            int pivotRow = column;

            for (int row = column + 1; row < 4; ++row)
            {
                if (std::abs(a[row][column]) >
                    std::abs(a[pivotRow][column]))
                {
                    pivotRow = row;
                }
            }

            // A zero pivot means the matrix is singular.
            if (std::abs(a[pivotRow][column]) < epsilon)
            {
                return 0.0f;
            }

            // Row swaps change the determinant's sign.
            if (pivotRow != column)
            {
                for (int j = 0; j < 4; ++j)
                {
                    std::swap(a[column][j], a[pivotRow][j]);
                }

                sign *= -1;
            }

            const float pivot = a[column][column];

            det *= pivot;

            // Eliminate entries below the pivot.
            for (int row = column + 1; row < 4; ++row)
            {
                const float factor = a[row][column] / pivot;

                for (int j = column + 1; j < 4; ++j)
                {
                    a[row][j] -= factor * a[column][j];
                }

                a[row][column] = 0.0f;
            }
        }

        return det * static_cast<float>(sign);
    }

    // ---------------------------------------------------------
    // INVERSE - GAUSS-JORDAN ELIMINATION
    // ---------------------------------------------------------

    Mat4 Mat4::inversed() const
    {
        // Create an augmented matrix [A | I].
        float augmented[4][8] = {};

        for (int row = 0; row < 4; ++row)
        {
            for (int column = 0; column < 4; ++column)
            {
                augmented[row][column] = m[row][column];
            }

            augmented[row][row + 4] = 1.0f;
        }

        // Process one pivot column at a time.
        for (int column = 0; column < 4; ++column)
        {
            // Find the best available pivot.
            int pivotRow = column;

            for (int row = column + 1; row < 4; ++row)
            {
                if (std::abs(augmented[row][column]) >
                    std::abs(augmented[pivotRow][column]))
                {
                    pivotRow = row;
                }
            }

            const float pivotValue =
                augmented[pivotRow][column];

            // No usable pivot means the matrix is singular
            // or numerically too close to singular.
            if (std::abs(pivotValue) < epsilon)
            {
                throw std::domain_error(
                    "Cannot invert a singular Mat4."
                );
            }

            // Move the pivot row into the current position.
            if (pivotRow != column)
            {
                for (int j = 0; j < 8; ++j)
                {
                    std::swap(
                        augmented[column][j],
                        augmented[pivotRow][j]
                    );
                }
            }

            // Divide the entire pivot row by the pivot.
            // This makes the pivot equal to 1.
            const float pivot = augmented[column][column];

            for (int j = 0; j < 8; ++j)
            {
                augmented[column][j] /= pivot;
            }

            // Eliminate the other values in this column.
            for (int row = 0; row < 4; ++row)
            {
                if (row == column)
                {
                    continue;
                }

                const float factor = augmented[row][column];

                for (int j = 0; j < 8; ++j)
                {
                    augmented[row][j] -=
                        factor * augmented[column][j];
                }
            }
        }

        // The right-hand side now contains A inverse.
        Mat4 result;

        for (int row = 0; row < 4; ++row)
        {
            for (int column = 0; column < 4; ++column)
            {
                result.m[row][column] =
                    augmented[row][column + 4];
            }
        }

        return result;
    }

    // ---------------------------------------------------------
    // TRANSLATION
    // ---------------------------------------------------------

    Mat4 Mat4::translation(float tx, float ty, float tz)
    {
        Mat4 result = identity();

        result.m[0][3] = tx;
        result.m[1][3] = ty;
        result.m[2][3] = tz;

        return result;
    }

    // ---------------------------------------------------------
    // SCALING
    // ---------------------------------------------------------

    Mat4 Mat4::scaling(float sx, float sy, float sz)
    {
        Mat4 result = identity();

        result.m[0][0] = sx;
        result.m[1][1] = sy;
        result.m[2][2] = sz;

        return result;
    }

    // ---------------------------------------------------------
    // ROTATION X
    // ---------------------------------------------------------

    Mat4 Mat4::rotationX(float radians)
    {
        Mat4 result = identity();

        const float c = std::cos(radians);
        const float s = std::sin(radians);

        result.m[1][1] = c;
        result.m[1][2] = -s;
        result.m[2][1] = s;
        result.m[2][2] = c;

        return result;
    }

    // ---------------------------------------------------------
    // ROTATION Y
    // ---------------------------------------------------------

    Mat4 Mat4::rotationY(float radians)
    {
        Mat4 result = identity();

        const float c = std::cos(radians);
        const float s = std::sin(radians);

        result.m[0][0] = c;
        result.m[0][2] = s;
        result.m[2][0] = -s;
        result.m[2][2] = c;

        return result;
    }

    // ---------------------------------------------------------
    // ROTATION Z
    // ---------------------------------------------------------

    Mat4 Mat4::rotationZ(float radians)
    {
        Mat4 result = identity();

        const float c = std::cos(radians);
        const float s = std::sin(radians);

        result.m[0][0] = c;
        result.m[0][1] = -s;
        result.m[1][0] = s;
        result.m[1][1] = c;

        return result;
    }

    // ---------------------------------------------------------
    // TRANSFORM POINT
    // ---------------------------------------------------------

    Vec3 Mat4::transformPoint(const Vec3& point) const
    {
        const float x =
            m[0][0] * point.x +
            m[0][1] * point.y +
            m[0][2] * point.z +
            m[0][3];

        const float y =
            m[1][0] * point.x +
            m[1][1] * point.y +
            m[1][2] * point.z +
            m[1][3];

        const float z =
            m[2][0] * point.x +
            m[2][1] * point.y +
            m[2][2] * point.z +
            m[2][3];

        const float w =
            m[3][0] * point.x +
            m[3][1] * point.y +
            m[3][2] * point.z +
            m[3][3];

        if (std::abs(w) < epsilon)
        {
            throw std::domain_error(
                "Cannot transform point: resulting homogeneous w is zero."
            );
        }

        return Vec3(x / w, y / w, z / w);
    }

    // ---------------------------------------------------------
    // TRANSFORM DIRECTION
    // ---------------------------------------------------------

    Vec3 Mat4::transformDirection(const Vec3& direction) const
    {
        const float x =
            m[0][0] * direction.x +
            m[0][1] * direction.y +
            m[0][2] * direction.z;

        const float y =
            m[1][0] * direction.x +
            m[1][1] * direction.y +
            m[1][2] * direction.z;

        const float z =
            m[2][0] * direction.x +
            m[2][1] * direction.y +
            m[2][2] * direction.z;

        return Vec3(x, y, z);
    }
    
    
    //Camera LoookAt
    Mat4 Mat4::lookAt(
    const Vec3& eye,
    const Vec3& target,
    const Vec3& worldUp)
    {
        // 1. Calculate the camera's forward direction.
        const Vec3 forward = (target - eye).normalized();

        // 2. Calculate the camera's right direction.
        const Vec3 right = forward.cross(worldUp).normalized();

        // 3. Calculate the camera's corrected up direction.
        const Vec3 up = right.cross(forward);

        // 4. Start with an identity matrix.
        Mat4 result = Mat4::identity();

        // 5. First row: camera right direction.
        result.m[0][0] = right.x;
        result.m[0][1] = right.y;
        result.m[0][2] = right.z;
        result.m[0][3] = -right.dot(eye);

        // 6. Second row: camera up direction.
        result.m[1][0] = up.x;
        result.m[1][1] = up.y;
        result.m[1][2] = up.z;
        result.m[1][3] = -up.dot(eye);

        // 7. Third row: camera backward direction.
        result.m[2][0] = -forward.x;
        result.m[2][1] = -forward.y;
        result.m[2][2] = -forward.z;
        result.m[2][3] = forward.dot(eye);

        return result;
    }
}
