
#include "engine/math/Vec3.h"

#include <cassert>
#include <cmath>
#include <iostream>

using Engine::Math::Vec3;

bool approximatelyEqual(float a, float b)
{
	return std::abs(a - b) < 0.0001f;
}

int main()
{
	Vec3 a(2.0f, 3.0f, 4.0f);
	Vec3 b(1.0f, 5.0f, 2.0f);

	// Addition
	Vec3 sum = a + b;

	assert(approximatelyEqual(sum.x, 3.0f));
	assert(approximatelyEqual(sum.y, 8.0f));
	assert(approximatelyEqual(sum.z, 6.0f));

	// Subtraction
	Vec3 difference = a - b;

	assert(approximatelyEqual(difference.x, 1.0f));
	assert(approximatelyEqual(difference.y, -2.0f));
	assert(approximatelyEqual(difference.z, 2.0f));

	// Scalar multiplication
	Vec3 scaled = a * 2.0f;

	assert(approximatelyEqual(scaled.x, 4.0f));
	assert(approximatelyEqual(scaled.y, 6.0f));
	assert(approximatelyEqual(scaled.z, 8.0f));

	// Dot product
	assert(approximatelyEqual(a.dot(b), 25.0f));

	// Cross product
	Vec3 cross = a.cross(b);

	assert(approximatelyEqual(cross.x, -14.0f));
	assert(approximatelyEqual(cross.y, 0.0f));
	assert(approximatelyEqual(cross.z, 7.0f));

	// Magnitude
	assert(approximatelyEqual(a.length(), std::sqrt(29.0f)));

	// Normalisation
	Vec3 unit = a.normalized();

	assert(approximatelyEqual(unit.length(), 1.0f));

	// Distance
	assert(approximatelyEqual(a.distanceTo(b), 3.0f));

	// Projection
	Vec3 projection = Vec3(3.0f, 4.0f, 0.0f)
		.projectOnto(Vec3(1.0f, 0.0f, 0.0f));

	assert(approximatelyEqual(projection.x, 3.0f));
	assert(approximatelyEqual(projection.y, 0.0f));
	assert(approximatelyEqual(projection.z, 0.0f));

	// Linear interpolation
	Vec3 interpolated = Vec3::lerp(
		Vec3(0.0f, 0.0f, 0.0f),
		Vec3(10.0f, 20.0f, 30.0f),
		0.5f
	);

	assert(approximatelyEqual(interpolated.x, 5.0f));
	assert(approximatelyEqual(interpolated.y, 10.0f));
	assert(approximatelyEqual(interpolated.z, 15.0f));

	std::cout << "All Vec3 tests passed!\n";

	return 0;
}
