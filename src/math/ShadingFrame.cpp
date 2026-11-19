
#include "engine/math/ShadingFrame.h"

#include <cmath>
#include <stdexcept>

namespace Engine::Math
{
    namespace
    {
        constexpr float EPSILON = 1e-6f;
    }

    ShadingFrame::ShadingFrame()
        : tangent(1.0f, 0.0f, 0.0f),
          bitangent(0.0f, 1.0f, 0.0f),
          normal(0.0f, 0.0f, 1.0f)
    {
    }

    ShadingFrame::ShadingFrame(const Vec3& inputNormal)
    {
        // Step 1: Normalize the supplied normal.
        const float normalLength = std::sqrt(
            inputNormal.x * inputNormal.x +
            inputNormal.y * inputNormal.y +
            inputNormal.z * inputNormal.z
        );

        if (normalLength < EPSILON)
        {
            throw std::invalid_argument(
                "ShadingFrame normal cannot be zero."
            );
        }

        normal = Vec3(
            inputNormal.x / normalLength,
            inputNormal.y / normalLength,
            inputNormal.z / normalLength
        );

        // Step 2: Choose a helper axis that is least
        // aligned with the normal.
        Vec3 helper;

        const float absX = std::abs(normal.x);
        const float absY = std::abs(normal.y);
        const float absZ = std::abs(normal.z);

        if (absX <= absY && absX <= absZ)
        {
            helper = Vec3(1.0f, 0.0f, 0.0f);
        }
        else if (absY <= absX && absY <= absZ)
        {
            helper = Vec3(0.0f, 1.0f, 0.0f);
        }
        else
        {
            helper = Vec3(0.0f, 0.0f, 1.0f);
        }

        // Step 3: Calculate the projection of the helper
        // vector onto the normal.
        const float projection =
            helper.x * normal.x +
            helper.y * normal.y +
            helper.z * normal.z;

        // Step 4: Subtract the projection.
        // This removes the component parallel to normal.
        const Vec3 perpendicular(
            helper.x - projection * normal.x,
            helper.y - projection * normal.y,
            helper.z - projection * normal.z
        );

        // Step 5: Normalize the tangent.
        const float tangentLength = std::sqrt(
            perpendicular.x * perpendicular.x +
            perpendicular.y * perpendicular.y +
            perpendicular.z * perpendicular.z
        );

        tangent = Vec3(
            perpendicular.x / tangentLength,
            perpendicular.y / tangentLength,
            perpendicular.z / tangentLength
        );

        // Step 6: Calculate the bitangent using
        // the cross product: B = N x T.
        bitangent = Vec3(
            normal.y * tangent.z - normal.z * tangent.y,
            normal.z * tangent.x - normal.x * tangent.z,
            normal.x * tangent.y - normal.y * tangent.x
        );
    }

    Vec3 ShadingFrame::toWorld(const Vec3& localVector) const
    {
        return Vec3(
            tangent.x * localVector.x +
            bitangent.x * localVector.y +
            normal.x * localVector.z,

            tangent.y * localVector.x +
            bitangent.y * localVector.y +
            normal.y * localVector.z,

            tangent.z * localVector.x +
            bitangent.z * localVector.y +
            normal.z * localVector.z
        );
    }

    Vec3 ShadingFrame::toLocal(const Vec3& worldVector) const
    {
        return Vec3(
            worldVector.x * tangent.x +
            worldVector.y * tangent.y +
            worldVector.z * tangent.z,

            worldVector.x * bitangent.x +
            worldVector.y * bitangent.y +
            worldVector.z * bitangent.z,

            worldVector.x * normal.x +
            worldVector.y * normal.y +
            worldVector.z * normal.z
        );
    }
}
