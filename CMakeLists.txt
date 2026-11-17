
cmake_minimum_required(VERSION 3.20)

project(ComputerGraphics
        VERSION 1.0
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Mathematics library
add_library(GraphicsMath
        src/math/Vec3.cpp
        src/math/Vec4.cpp
        src/math/Mat3.cpp
        src/math/Mat4.cpp
)

target_include_directories(GraphicsMath
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Main application
add_executable(ComputerGraphics
        app/main.cpp
        tests/math/Vec4Tests.cpp
        tests/math/Vec4Tests.cpp
        include/engine/math/Vec4.h
)

target_link_libraries(ComputerGraphics
        PRIVATE GraphicsMath
)

# Enable testing
enable_testing()

# Vec3 tests
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
# Vec4 Tests
add_executable(Vec4Tests
        tests/math/Vec4Tests.cpp
)

target_link_libraries(Vec4Tests PRIVATE GraphicsMath)

add_test(NAME Vec4Tests COMMAND Vec4Tests)

# Mat3 tests
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

# Mat4 tests
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
