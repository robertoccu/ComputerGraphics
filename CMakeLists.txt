cmake_minimum_required(VERSION 3.14)
project(ComputerGraphics)

set(CMAKE_CXX_STANDARD 14)

include_directories(maths)

add_executable(ComputerGraphics
        maths/Matrix.cpp
        maths/Matrix.h
        maths/RGB.h
        maths/Vector.cpp
        maths/Vector.h
        main.cpp
        geometry/Ray.cpp
        geometry/Ray.h
        geometry/Sphere.cpp
        geometry/Sphere.h
        PlanetaryMaths.cpp utils/IOppm.cpp utils/IOppm.h)
