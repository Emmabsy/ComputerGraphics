
#pragma once

#include "engine/math/Vec3.h"

namespace Engine::Math
{
    class SphericalCoordinates
    {
    public:
        float theta;
        float phi;
        float radius;

        SphericalCoordinates();

        SphericalCoordinates(
            float theta,
            float phi,
            float radius
        );

        static SphericalCoordinates fromCartesian(
            const Vec3& vector
        );

        Vec3 toCartesian() const;
    };
}
