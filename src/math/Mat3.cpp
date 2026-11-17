#include "engine/math/Mat3.h"
#include <cmath>
#include <stdexcept>

namespace Engine::Math
{
    Mat3::Mat3()
    {
        for (int row = 0; row < 3; ++row)
        {
            for (int column = 0; column < 3; ++column)
            {
                m[row][column] = 0.0f;
            }
        }
    }
    
    Mat3 Mat3::identity()
    {
        Mat3 result;
        for (int i = 0; i<3; i++)
        {
            result.m[i][i] = 1.0f;
        }
        return result;
    }
    
    
    float& Mat3::at (int row, int column)
    {
        if (row < 0 || row >= 3 || column < 0 || column >= 3)
        {
            throw std::out_of_range("Mat3 index out of range");
        }
        return m[row][column];
    }
    
    const float& Mat3::at(int row, int column) const
    {
        if (row < 0 || row >= 3 || column < 0 || column >= 3)
        {
            throw std::out_of_range("Mat3 index out of range");
        }
        return m[row][column];
    }

    Mat3 Mat3::operator+(const Mat3& other) const
    {
        Mat3 result;
        for(int row = 0; row < 3; ++row)
        {
            for(int column = 0; column < 3; ++column){
                result.m[row][column] = m[row][column]+ other.m[row][column];
            }

        }
        return result;
    }
    
    Mat3 Mat3::operator-(const Mat3& other) const
    {
        Mat3 result;
        for (int row = 0; row < 3; ++row)
        {
            for (int column = 0; column < 3; ++column)
            {
                result.m[row][column] = m[row][column] - other.m[row][column];
            }
        }
        return result;
    }
    
    
    Mat3 Mat3::operator*(float scalar) const
    {
        Mat3 result;

        for (int row = 0; row < 3; ++row)
        {
            for (int column = 0; column < 3; ++column)
            {
                result.m[row][column] =
                    m[row][column] * scalar;
            }
        }

        return result;
    }
    Mat3 Mat3::operator*(const Mat3& other) const
    {
        Mat3 result;

        for (int row = 0; row < 3; ++row)
        {
            for (int column = 0; column < 3; ++column)
            {
                float sum = 0.0f;

                for (int k = 0; k < 3; ++k)
                {
                    sum += m[row][k] * other.m[k][column];
                }

                result.m[row][column] = sum;
            }
        }

        return result;
    }
    
    Vec3 Mat3::operator*(const Vec3& vector) const
    {
        return Vec3(
            m[0][0] * vector.x +
            m[0][1] * vector.y +
            m[0][2] * vector.z,

            m[1][0] * vector.x +
            m[1][1] * vector.y +
            m[1][2] * vector.z,

            m[2][0] * vector.x +
            m[2][1] * vector.y +
            m[2][2] * vector.z
        );
    }
    
    //Transposed
    Mat3 Mat3::transposed() const
    {
        Mat3 result;

        for (int row = 0; row < 3; ++row)
        {
            for (int column = 0; column < 3; ++column)
            {
                result.m[row][column] = m[column][row];
            }
        }

        return result;
    }
    
    //Determinant
    float Mat3::determinant() const
    {
        const float a = m[0][0];
        const float b = m[0][1];
        const float c = m[0][2];

        const float d = m[1][0];
        const float e = m[1][1];
        const float f = m[1][2];

        const float g = m[2][0];
        const float h = m[2][1];
        const float i = m[2][2];

        return
            a * (e * i - f * h)
            - b * (d * i - f * g)
            + c * (d * h - e * g);
    }
    
    ///Matrix Inverse
    
    Mat3 Mat3::inversed() const
    {
        const float det = determinant();

        constexpr float epsilon = 1e-6f;

        if (std::abs(det) < epsilon)
        {
            throw std::domain_error(
                "Cannot invert a matrix with a zero or near-zero determinant."
            );
        }

        const float a = m[0][0];
        const float b = m[0][1];
        const float c = m[0][2];

        const float d = m[1][0];
        const float e = m[1][1];
        const float f = m[1][2];

        const float g = m[2][0];
        const float h = m[2][1];
        const float i = m[2][2];

        Mat3 result;

        result.m[0][0] = (e * i - f * h) / det;
        result.m[0][1] = (c * h - b * i) / det;
        result.m[0][2] = (b * f - c * e) / det;

        result.m[1][0] = (f * g - d * i) / det;
        result.m[1][1] = (a * i - c * g) / det;
        result.m[1][2] = (c * d - a * f) / det;

        result.m[2][0] = (d * h - e * g) / det;
        result.m[2][1] = (b * g - a * h) / det;
        result.m[2][2] = (a * e - b * d) / det;

        return result;
    }
    
    //Tranformation
    
    Mat3 Mat3::scaling(float sx, float sy, float sz)
    {
        Mat3 result;

        result.m[0][0] = sx;
        result.m[1][1] = sy;
        result.m[2][2] = sz;

        return result;
    }
    
}
