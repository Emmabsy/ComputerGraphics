
#include "engine/math/ShadingFrame.h"

#include <cassert>
#include <cmath>
#include <iostream>
#include <stdexcept>

using namespace Engine::Math;

namespace
{
    constexpr float EPSILON = 1e-5f;

    bool approximatelyEqual(float a, float b)
    {
        return std::abs(a - b) < EPSILON;
    }

    bool approximatelyEqual(const Vec3& a, const Vec3& b)
    {
        return approximatelyEqual(a.x, b.x) &&
               approximatelyEqual(a.y, b.y) &&
               approximatelyEqual(a.z, b.z);
    }

    void testDefaultConstructor()
    {
        ShadingFrame frame;

        assert(approximatelyEqual(frame.tangent, Vec3(1, 0, 0)));
        assert(approximatelyEqual(frame.bitangent, Vec3(0, 1, 0)));
        assert(approximatelyEqual(frame.normal, Vec3(0, 0, 1)));
    }

    void testNormalIsNormalized()
    {
        ShadingFrame frame(Vec3(0, 0, 5));

        assert(approximatelyEqual(frame.normal, Vec3(0, 0, 1)));
    }

    void testBasisVectorsHaveUnitLength()
    {
        ShadingFrame frame(Vec3(2, 3, 4));

        assert(approximatelyEqual(frame.tangent.length(), 1.0f));
        assert(approximatelyEqual(frame.bitangent.length(), 1.0f));
        assert(approximatelyEqual(frame.normal.length(), 1.0f));
    }

    void testBasisVectorsAreOrthogonal()
    {
        ShadingFrame frame(Vec3(2, 3, 4));

        assert(approximatelyEqual(frame.tangent.dot(frame.bitangent), 0.0f));
        assert(approximatelyEqual(frame.tangent.dot(frame.normal), 0.0f));
        assert(approximatelyEqual(frame.bitangent.dot(frame.normal), 0.0f));
    }

    void testZeroNormalThrows()
    {
        bool threw = false;

        try
        {
            ShadingFrame frame(Vec3(0, 0, 0));
        }
        catch (const std::invalid_argument&)
        {
            threw = true;
        }

        assert(threw);
    }

    void testToWorld()
    {
        ShadingFrame frame;

        const Vec3 local(2, 3, 4);
        const Vec3 world = frame.toWorld(local);

        assert(approximatelyEqual(world, Vec3(2, 3, 4)));
    }

    void testToLocal()
    {
        ShadingFrame frame;

        const Vec3 world(2, 3, 4);
        const Vec3 local = frame.toLocal(world);

        assert(approximatelyEqual(local, Vec3(2, 3, 4)));
    }

    void testRoundTripTransformation()
    {
        ShadingFrame frame(Vec3(2, 3, 4));

        const Vec3 original(5, -2, 3);

        const Vec3 world = frame.toWorld(original);
        const Vec3 recovered = frame.toLocal(world);

        assert(approximatelyEqual(recovered, original));
    }

    void testToWorldUsesSurfaceBasis()
    {
        ShadingFrame frame(Vec3(0, 1, 0));

        const Vec3 local(0, 0, 1);
        const Vec3 world = frame.toWorld(local);

        assert(approximatelyEqual(world, Vec3(0, 1, 0)));
    }
}

int main()
{
    testDefaultConstructor();
    testNormalIsNormalized();
    testBasisVectorsHaveUnitLength();
    testBasisVectorsAreOrthogonal();
    testZeroNormalThrows();
    testToWorld();
    testToLocal();
    testRoundTripTransformation();
    testToWorldUsesSurfaceBasis();

    std::cout << "All ShadingFrame tests passed.\n";

    return 0;
}
