#pragma once

namespace Engine::Math
{
	class Vec3
	{
	public:
		float x;
		float y;
		float z;

		Vec3();
		Vec3(float x, float y, float z);

		Vec3 operator+(const Vec3& other) const;
		Vec3 operator-(const Vec3& other) const;

		Vec3 operator*(float scalar) const;
		Vec3 operator/(float scalar) const;

		float dot(const Vec3& other) const;
		Vec3 cross(const Vec3& other) const;

		float lengthSquared() const;
		float length() const;

		Vec3 normalized() const;
		//New
		float distanceTo(const Vec3& other) const;
		Vec3 projectOnto(const Vec3& other) const;

		static Vec3 lerp(
			const Vec3& start,
			const Vec3& end,
			float t
		);

	};
}
