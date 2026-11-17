
#include "engine/math/Vec3.h"


#include <iostream>

int main()
{
	Engine::Math::Vec3 a(2.0f, 3.0f, 4.0f);
	Engine::Math::Vec3 b(1.0f, 5.0f, 2.0f);

	Engine::Math::Vec3 result = a + b;

	std::cout << "Result: "
		<< result.x << ", "
		<< result.y << ", "
		<< result.z << '\n';

	return 0;
}
