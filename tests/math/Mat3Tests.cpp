
#include "engine/math/Mat3.h"

#include <cassert>
#include <cmath>
#include <iostream>
#include <stdexcept>

using Engine::Math::Mat3;
using Engine::Math::Vec3;

bool approximatelyEqual(float a, float b)
{
    return std::abs(a - b) < 0.0001f;
}

int main()
{
    // 1. Default constructor
    Mat3 zero;

    for (int row = 0; row < 3; ++row)
    {
        for (int column = 0; column < 3; ++column)
        {
            assert(zero.at(row, column) == 0.0f);
        }
    }

    // 2. Identity matrix
    Mat3 identity = Mat3::identity();

    for (int row = 0; row < 3; ++row)
    {
        for (int column = 0; column < 3; ++column)
        {
            float expected = (row == column) ? 1.0f : 0.0f;

            assert(identity.at(row, column) == expected);
        }
    }

    // 3. Matrix addition
    Mat3 A;
    Mat3 B;

    A.at(0, 0) = 1.0f;
    A.at(0, 1) = 2.0f;
    A.at(0, 2) = 3.0f;

    A.at(1, 0) = 4.0f;
    A.at(1, 1) = 5.0f;
    A.at(1, 2) = 6.0f;

    A.at(2, 0) = 7.0f;
    A.at(2, 1) = 8.0f;
    A.at(2, 2) = 9.0f;

    B.at(0, 0) = 9.0f;
    B.at(0, 1) = 8.0f;
    B.at(0, 2) = 7.0f;

    B.at(1, 0) = 6.0f;
    B.at(1, 1) = 5.0f;
    B.at(1, 2) = 4.0f;

    B.at(2, 0) = 3.0f;
    B.at(2, 1) = 2.0f;
    B.at(2, 2) = 1.0f;

    Mat3 addition = A + B;

    for (int row = 0; row < 3; ++row)
    {
        for (int column = 0; column < 3; ++column)
        {
            assert(approximatelyEqual(
                addition.at(row, column), 10.0f
            ));
        }
    }

    // 4. Matrix subtraction
    Mat3 subtraction = A - B;

    assert(approximatelyEqual(subtraction.at(0, 0), -8.0f));
    assert(approximatelyEqual(subtraction.at(1, 1), 0.0f));
    assert(approximatelyEqual(subtraction.at(2, 2), 8.0f));

    // 5. Scalar multiplication
    Mat3 scaled = A * 2.0f;

    assert(approximatelyEqual(scaled.at(0, 0), 2.0f));
    assert(approximatelyEqual(scaled.at(1, 1), 10.0f));
    assert(approximatelyEqual(scaled.at(2, 2), 18.0f));

    // 6. Matrix multiplication
    Mat3 product = A * B;

    assert(approximatelyEqual(product.at(0, 0), 30.0f));
    assert(approximatelyEqual(product.at(0, 1), 24.0f));
    assert(approximatelyEqual(product.at(0, 2), 18.0f));

    assert(approximatelyEqual(product.at(1, 0), 84.0f));
    assert(approximatelyEqual(product.at(1, 1), 69.0f));
    assert(approximatelyEqual(product.at(1, 2), 54.0f));

    assert(approximatelyEqual(product.at(2, 0), 138.0f));
    assert(approximatelyEqual(product.at(2, 1), 114.0f));
    assert(approximatelyEqual(product.at(2, 2), 90.0f));

    // 7. Matrix-vector multiplication
    Mat3 scaling = Mat3::identity();

    scaling.at(0, 0) = 2.0f;
    scaling.at(1, 1) = 3.0f;
    scaling.at(2, 2) = 4.0f;

    Vec3 vector(1.0f, 2.0f, 3.0f);

    Vec3 transformed = scaling * vector;

    assert(approximatelyEqual(transformed.x, 2.0f));
    assert(approximatelyEqual(transformed.y, 6.0f));
    assert(approximatelyEqual(transformed.z, 12.0f));

    // 8. Invalid indexing
    bool exceptionThrown = false;

    try
    {
        A.at(5, 5);
    }
    catch (const std::out_of_range&)
    {
        exceptionThrown = true;
    }

    assert(exceptionThrown);

    // 9. Identity matrix multiplication
    Mat3 unchanged = identity * A;

    for (int row = 0; row < 3; ++row)
    {
        for (int column = 0; column < 3; ++column)
        {
            assert(approximatelyEqual(
                unchanged.at(row, column),
                A.at(row, column)
            ));
        }
    }
    
    // 10. Transpose
    
    // 10. Transpose

    Mat3 original;

    original.at(0, 0) = 1.0f;
    original.at(0, 1) = 2.0f;
    original.at(0, 2) = 3.0f;

    original.at(1, 0) = 4.0f;
    original.at(1, 1) = 5.0f;
    original.at(1, 2) = 6.0f;

    original.at(2, 0) = 7.0f;
    original.at(2, 1) = 8.0f;
    original.at(2, 2) = 9.0f;

    Mat3 result = original.transposed();

    assert(approximatelyEqual(result.at(0, 0), 1.0f));
    assert(approximatelyEqual(result.at(0, 1), 4.0f));
    assert(approximatelyEqual(result.at(0, 2), 7.0f));

    assert(approximatelyEqual(result.at(1, 0), 2.0f));
    assert(approximatelyEqual(result.at(1, 1), 5.0f));
    assert(approximatelyEqual(result.at(1, 2), 8.0f));

    assert(approximatelyEqual(result.at(2, 0), 3.0f));
    assert(approximatelyEqual(result.at(2, 1), 6.0f));
    assert(approximatelyEqual(result.at(2, 2), 9.0f));

    // Verify that the original matrix remains unchanged.
    assert(approximatelyEqual(original.at(0, 1), 2.0f));
    assert(approximatelyEqual(original.at(1, 0), 4.0f));
    
    // 11. Matrix determinant

    Mat3 determinantMatrix;

    determinantMatrix.at(0, 0) = 1.0f;
    determinantMatrix.at(0, 1) = 2.0f;
    determinantMatrix.at(0, 2) = 3.0f;

    determinantMatrix.at(1, 0) = 0.0f;
    determinantMatrix.at(1, 1) = 4.0f;
    determinantMatrix.at(1, 2) = 5.0f;

    determinantMatrix.at(2, 0) = 1.0f;
    determinantMatrix.at(2, 1) = 0.0f;
    determinantMatrix.at(2, 2) = 6.0f;

    float determinant = determinantMatrix.determinant();

    assert(approximatelyEqual(determinant, 22.0f));
    
    
    // 12. Zero determinant

    Mat3 singularMatrix;

    singularMatrix.at(0, 0) = 1.0f;
    singularMatrix.at(0, 1) = 2.0f;
    singularMatrix.at(0, 2) = 3.0f;

    singularMatrix.at(1, 0) = 2.0f;
    singularMatrix.at(1, 1) = 4.0f;
    singularMatrix.at(1, 2) = 6.0f;

    singularMatrix.at(2, 0) = 1.0f;
    singularMatrix.at(2, 1) = 0.0f;
    singularMatrix.at(2, 2) = 1.0f;

    assert(approximatelyEqual(singularMatrix.determinant(), 0.0f));
    
    // 14. Matrix inverse

    Mat3 inverseMatrix;

    inverseMatrix.at(0, 0) = 1.0f;
    inverseMatrix.at(0, 1) = 2.0f;
    inverseMatrix.at(0, 2) = 3.0f;

    inverseMatrix.at(1, 0) = 0.0f;
    inverseMatrix.at(1, 1) = 4.0f;
    inverseMatrix.at(1, 2) = 5.0f;

    inverseMatrix.at(2, 0) = 1.0f;
    inverseMatrix.at(2, 1) = 0.0f;
    inverseMatrix.at(2, 2) = 6.0f;

    Mat3 inverse = inverseMatrix.inversed();

    // Verify A * A^-1 = I.
    Mat3 verification = inverseMatrix * inverse;

    for (int row = 0; row < 3; ++row)
    {
        for (int column = 0; column < 3; ++column)
        {
            float expected = (row == column) ? 1.0f : 0.0f;

            assert(approximatelyEqual(
                verification.at(row, column),
                expected
            ));
        }
    }
    
    // 15. Singular matrix inverse

    Mat3 singular;

    singular.at(0, 0) = 1.0f;
    singular.at(0, 1) = 2.0f;
    singular.at(0, 2) = 3.0f;

    singular.at(1, 0) = 2.0f;
    singular.at(1, 1) = 4.0f;
    singular.at(1, 2) = 6.0f;

    singular.at(2, 0) = 1.0f;
    singular.at(2, 1) = 0.0f;
    singular.at(2, 2) = 1.0f;

    // 15. Singular matrix inverse

    exceptionThrown = false;

    try
    {
        Mat3 invalidInverse = singular.inversed();
    }
    catch (const std::domain_error&)
    {
        exceptionThrown = true;
    }

    assert(exceptionThrown);
    
    // 16. Test: Scaling transformation

    Mat3 scalingMatrix = Mat3::scaling(2.0f, 3.0f, 2.0f);

    Vec3 originalVector(2.0f, 3.0f, 4.0f);

    Vec3 scaledVector = scalingMatrix * originalVector;

    assert(approximatelyEqual(scaledVector.x, 4.0f));
    assert(approximatelyEqual(scaledVector.y, 9.0f));
    assert(approximatelyEqual(scaledVector.z, 8.0f));
    
    
    //Main print
    std::cout << "All Mat3 tests passed!\n";

    return 0;
}
