
#include "engine/math/Colour.h"

#include <cassert>
#include <cmath>
#include <iostream>
#include <stdexcept>

using Engine::Math::Colour;

bool approximatelyEqual(float a, float b)
{
    return std::abs(a - b) < 0.0001f;
}

void testDefaultConstructor()
{
    Colour colour;

    assert(approximatelyEqual(colour.r, 0.0f));
    assert(approximatelyEqual(colour.g, 0.0f));
    assert(approximatelyEqual(colour.b, 0.0f));
    assert(approximatelyEqual(colour.a, 1.0f));
}

void testFloatConstructor()
{
    Colour colour(0.2f, 0.4f, 0.6f, 0.8f);

    assert(approximatelyEqual(colour.r, 0.2f));
    assert(approximatelyEqual(colour.g, 0.4f));
    assert(approximatelyEqual(colour.b, 0.6f));
    assert(approximatelyEqual(colour.a, 0.8f));
}

void testByteConstructor()
{
    Colour colour(
        static_cast<unsigned char>(255),
        static_cast<unsigned char>(128),
        static_cast<unsigned char>(0),
        static_cast<unsigned char>(255)
    );

    assert(approximatelyEqual(colour.r, 1.0f));
    assert(approximatelyEqual(colour.g, 128.0f / 255.0f));
    assert(approximatelyEqual(colour.b, 0.0f));
    assert(approximatelyEqual(colour.a, 1.0f));
}

void testAddition()
{
    Colour first(0.1f, 0.2f, 0.3f, 0.4f);
    Colour second(0.2f, 0.3f, 0.4f, 0.5f);

    Colour result = first + second;

    assert(approximatelyEqual(result.r, 0.3f));
    assert(approximatelyEqual(result.g, 0.5f));
    assert(approximatelyEqual(result.b, 0.7f));
    assert(approximatelyEqual(result.a, 0.9f));
}

void testComponentWiseMultiplication()
{
    Colour first(0.5f, 0.4f, 0.8f, 1.0f);
    Colour second(0.2f, 0.5f, 0.5f, 1.0f);

    Colour result = first * second;

    assert(approximatelyEqual(result.r, 0.1f));
    assert(approximatelyEqual(result.g, 0.2f));
    assert(approximatelyEqual(result.b, 0.4f));
    assert(approximatelyEqual(result.a, 1.0f));
}

void testScalarMultiplication()
{
    Colour colour(0.2f, 0.4f, 0.6f, 1.0f);

    Colour result = colour * 0.5f;

    assert(approximatelyEqual(result.r, 0.1f));
    assert(approximatelyEqual(result.g, 0.2f));
    assert(approximatelyEqual(result.b, 0.3f));
    assert(approximatelyEqual(result.a, 0.5f));
}

void testScalarDivision()
{
    Colour colour(0.2f, 0.4f, 0.6f, 1.0f);

    Colour result = colour / 2.0f;

    assert(approximatelyEqual(result.r, 0.1f));
    assert(approximatelyEqual(result.g, 0.2f));
    assert(approximatelyEqual(result.b, 0.3f));
    assert(approximatelyEqual(result.a, 0.5f));
}

void testDivisionByZero()
{
    Colour colour(0.2f, 0.4f, 0.6f, 1.0f);

    bool exceptionThrown = false;

    try
    {
        Colour result = colour / 0.0f;
    }
    catch (const std::invalid_argument&)
    {
        exceptionThrown = true;
    }

    assert(exceptionThrown);
}

int main()
{
    testDefaultConstructor();
    testFloatConstructor();
    testByteConstructor();
    testAddition();
    testComponentWiseMultiplication();
    testScalarMultiplication();
    testScalarDivision();
    testDivisionByZero();

    std::cout << "All Colour tests passed!\n";

    return 0;
}
