
cmake_minimum_required(VERSION 3.20)

project(ComputerGraphics
        VERSION 1.0
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(GraphicsMath
        src/math/Vec3.cpp
        src/math/Mat3.cpp
)

target_include_directories(GraphicsMath
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(ComputerGraphics
        app/main.cpp
)

target_link_libraries(ComputerGraphics
        PRIVATE GraphicsMath
)

enable_testing()

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
