
#pragma once

#include "engine/math/Vec3.h"

namespace Engine::Math
{
    class Mat4
    {
    public:
        // Matrix storage: 4 rows and 4 columns.
        float m[4][4];

        // Creates a zero matrix.
        Mat4();

        // Creates an identity matrix.
        static Mat4 identity();

        // Access a matrix element with bounds checking.
        float& at(int row, int column);
        const float& at(int row, int column) const;

        // Basic matrix arithmetic.
        Mat4 operator+(const Mat4& other) const;
        Mat4 operator-(const Mat4& other) const;
        Mat4 operator*(float scalar) const;

        // Matrix multiplication.
        Mat4 operator*(const Mat4& other) const;

        // Matrix operations.
        Mat4 transposed() const;
        float determinant() const;
        Mat4 inversed() const;

        // 3D transformations.
        static Mat4 translation(float tx, float ty, float tz);
        static Mat4 scaling(float sx, float sy, float sz);

        static Mat4 rotationX(float radians);
        static Mat4 rotationY(float radians);
        static Mat4 rotationZ(float radians);

        // Transform positions and directions separately.
        Vec3 transformPoint(const Vec3& point) const;
        Vec3 transformDirection(const Vec3& direction) const;
        
        //Camera
        static Mat4 lookAt(const Vec3& eye, const Vec3& target,const Vec3& worldUp);
    
        
    };
    
}
