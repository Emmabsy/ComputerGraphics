
#pragma once

#include "engine/math/Vec3.h"

namespace Engine::Math
{
    class Mat3
    {
    public:

        float m[3][3];

        // Construction
        Mat3();

        // Matrix creation
        static Mat3 identity();

        // Element access
        float& at(int row, int column);
        const float& at(int row, int column) const;

        // Matrix arithmetic
        Mat3 operator+(const Mat3& other) const;
        Mat3 operator-(const Mat3& other) const;
		Mat3 transposed() const;
		float determinant() const;
		Mat3 inversed() const;

		//Scaling
		static Mat3 scaling(float sx, float sy, float sz);

		//Rotation

		static Mat3 rotationZ(float radians); //Rotation around z axis

		static Mat3 rotationX(float radians); //Rotation around X axis
		static Mat3 rotationY(float radians); //Rotation around Y axis


        // Multiplication
        Mat3 operator*(float scalar) const;
        Mat3 operator*(const Mat3& other) const;
        Vec3 operator*(const Vec3& vector) const;
    };
}
