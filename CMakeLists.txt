
cmake_minimum_required(VERSION 3.20)

project(ComputerGraphics
        VERSION 1.0
        LANGUAGES CXX
)

# C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# ==========================================
# Mathematics library
# ==========================================

add_library(GraphicsMath

        # Vectors
        src/math/Vec3.cpp
        src/math/Vec4.cpp

        # Matrices
        src/math/Mat3.cpp
        src/math/Mat4.cpp

        # Colour
        src/math/Colour.cpp
        #
        src/math/ShadingFrame.cpp
        src/math/Quaternion.cpp
        #
        src/math/SphericalCoordinates.cpp
)

target_include_directories(GraphicsMath
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)


# ==========================================
# Main application
# ==========================================

add_executable(ComputerGraphics
        app/main.cpp
)

target_link_libraries(ComputerGraphics
        PRIVATE GraphicsMath
)


# ==========================================
# Enable testing
# ==========================================

enable_testing()


# ==========================================
# Vec3 tests
# ==========================================

add_executable(GraphicsMathTests
        tests/math/Vec3Tests.cpp
)

target_link_libraries(GraphicsMathTests
        PRIVATE GraphicsMath
)

add_test(
        NAME GraphicsMathTests
        COMMAND GraphicsMathTests
)


# ==========================================
# Vec4 tests
# ==========================================

add_executable(Vec4Tests
        tests/math/Vec4Tests.cpp
)

target_link_libraries(Vec4Tests
        PRIVATE GraphicsMath
)

add_test(
        NAME Vec4Tests
        COMMAND Vec4Tests
)


# ==========================================
# Mat3 tests
# ==========================================

add_executable(Mat3Tests
        tests/math/Mat3Tests.cpp
)

target_link_libraries(Mat3Tests
        PRIVATE GraphicsMath
)

add_test(
        NAME Mat3Tests
        COMMAND Mat3Tests
)


# ==========================================
# Mat4 tests
# ==========================================

add_executable(Mat4Tests
        tests/math/Mat4Tests.cpp
)

target_link_libraries(Mat4Tests
        PRIVATE GraphicsMath
)

add_test(
        NAME Mat4Tests
        COMMAND Mat4Tests
)


# ==========================================
# Colour tests
# ==========================================

add_executable(ColourTests
        tests/math/ColourTests.cpp
        
)

target_link_libraries(ColourTests PRIVATE GraphicsMath)

add_test(NAME ColourTests COMMAND ColourTests)
target_link_libraries(ColourTests PRIVATE GraphicsMath)



# ==========================================
# Shading Frame tests
# ==========================================

add_executable(ShadingFrameTests
        tests/math/ShadingFrameTests.cpp
)

target_link_libraries(ShadingFrameTests PRIVATE GraphicsMath)

add_test(NAME ShadingFrameTests COMMAND ShadingFrameTests)

# ==========================================
# Quaternion tests
# ==========================================

add_executable(QuaternionTests
tests/math/QuaternionTests.cpp
)

target_link_libraries(QuaternionTests PRIVATE GraphicsMath)

add_test(NAME QuaternionTests COMMAND QuaternionTests)

# ==========================================
# Spherical tests
# ==========================================

add_executable(SphericalCoordinatesTests
        tests/math/SphericalCoordinatesTests.cpp
)

target_link_libraries(SphericalCoordinatesTests PRIVATE GraphicsMath)

add_test(
        NAME SphericalCoordinatesTests
        COMMAND SphericalCoordinatesTests
)