
#include "engine/math/Colour.h"

#include <stdexcept>

namespace Engine::Math
{
    // Default constructor: opaque black.
    Colour::Colour()
        : r(0.0f),
          g(0.0f),
          b(0.0f),
          a(1.0f)
    {
    }

    // Construct from floating-point components.
    Colour::Colour(float red, float green, float blue, float alpha)
        : r(red),
          g(green),
          b(blue),
          a(alpha)
    {
    }

    // Construct from 8-bit colour components.
    // Convert the range 0-255 into the range 0-1.
    Colour::Colour(unsigned char red,
                   unsigned char green,
                   unsigned char blue,
                   unsigned char alpha)
        : r(static_cast<float>(red) / 255.0f),
          g(static_cast<float>(green) / 255.0f),
          b(static_cast<float>(blue) / 255.0f),
          a(static_cast<float>(alpha) / 255.0f)
    {
    }

    // Component-wise addition.
    Colour Colour::operator+(const Colour& other) const
    {
        return Colour(
            r + other.r,
            g + other.g,
            b + other.b,
            a + other.a
        );
    }

    // Component-wise colour multiplication.
    Colour Colour::operator*(const Colour& other) const
    {
        return Colour(
            r * other.r,
            g * other.g,
            b * other.b,
            a * other.a
        );
    }

    // Multiply every component by the same scalar.
    Colour Colour::operator*(float scalar) const
    {
        return Colour(
            r * scalar,
            g * scalar,
            b * scalar,
            a * scalar
        );
    }

    // Divide every component by the same scalar.
    Colour Colour::operator/(float scalar) const
    {
        if (scalar == 0.0f)
        {
            throw std::invalid_argument(
                "Cannot divide a Colour by zero."
            );
        }

        return Colour(
            r / scalar,
            g / scalar,
            b / scalar,
            a / scalar
        );
    }
}
