cmake_minimum_required(VERSION 3.14)
project(ComputerGraphics)

set(CMAKE_CXX_STANDARD 14)

include_directories(maths)

add_executable(ComputerGraphics
        maths/Matrix.cpp
        maths/Matrix.h
        maths/RGB.h
        maths/Vector.cpp
        maths/Vector.h)
