cmake_minimum_required(VERSION 3.14)
project(ComputerGraphics)

set(CMAKE_CXX_STANDARD 14)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc -static")

include_directories(maths)

add_executable(ComputerGraphics
        maths/Matrix.cpp
        maths/Matrix.h
        maths/Vector.cpp
        maths/Vector.h
        main.cpp
        geometry/Ray.cpp
        geometry/Ray.h
        geometry/Sphere.cpp
        geometry/Sphere.h
        geometry/Plane.h
        geometry/Plane.cpp
        utils/PlanetaryMaths.h
        utils/IOppm.cpp
        utils/IOppm.h
        imaging/RGB.cpp
        imaging/RGB.h
        imaging/Image.cpp
        imaging/Image.h
        imaging/ToneMapper.cpp
        imaging/ToneMapper.h render/Camera.cpp render/Camera.h render/Screen.cpp render/Screen.h render/Scene.cpp render/Scene.h geometry/CollisionObject.h material/Material.h render/tracer.cpp render/tracer.h geometry/Disk.cpp geometry/Disk.h geometry/Triangle.cpp geometry/Triangle.h geometry/TriangleMeshes.cpp geometry/TriangleMeshes.h material/Phong.h material/Composite.h material/SpecularPerfect.h imaging/DotLight.cpp imaging/DotLight.h utils/Prng.h)
