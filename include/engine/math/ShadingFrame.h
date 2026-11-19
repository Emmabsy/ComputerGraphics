
#pragma once

#include "engine/math/Vec3.h"

namespace Engine::Math
{
    class ShadingFrame
    {
    public:
        Vec3 tangent;
        Vec3 bitangent;
        Vec3 normal;

        ShadingFrame();

        explicit ShadingFrame(const Vec3& normal);

        Vec3 toWorld(const Vec3& localVector) const;

        Vec3 toLocal(const Vec3& worldVector) const;
    };
}
