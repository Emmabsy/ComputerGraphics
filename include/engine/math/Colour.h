
#pragma once

namespace Engine::Math
{
    class Colour
    {
    public:
        float r;
        float g;
        float b;
        float a;

        // Constructors
        Colour();
        Colour(float r, float g, float b, float a = 1.0f);
        Colour(unsigned char r,
               unsigned char g,
               unsigned char b,
               unsigned char a = 255);

        // Colour arithmetic
        Colour operator+(const Colour& other) const;
        Colour operator*(const Colour& other) const;

        // Scalar arithmetic
        Colour operator*(float scalar) const;
        Colour operator/(float scalar) const;
    };
}
