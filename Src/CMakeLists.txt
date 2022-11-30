cmake_minimum_required(VERSION 3.22)
project(ToyRT)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenMP)
find_package(TBB REQUIRED)

add_executable(ToyRT
        main.cpp
        Time.cpp
        Tuple.cpp
        Tuple.h
        easyppm.c
        easyppm.h
        Assets/Ray.cpp
        Assets/Ray.h
        Assets/Objects/GeometryObject.cpp
        Assets/Objects/GeometryObject.h
        Assets/Objects/Sphere.cpp
        Assets/Objects/Sphere.h
        Assets/Objects/Plane.cpp
        Assets/Objects/Plane.h
        Scene.cpp
        Scene.h
        Assets/Materials/MaterialBase.cpp
        Assets/Materials/MaterialBase.h
        Assets/Materials/Diffusion.cpp
        Assets/Materials/Diffusion.h
        Assets/Materials/Reflection.cpp
        Assets/Materials/Reflection.h
        Assets/Cameras/CameraBase.cpp Assets/Cameras/CameraBase.h Assets/Cameras/PTCamera.cpp Assets/Cameras/PTCamera.h Rgb.cpp Rgb.h Assets/Objects/XYLimitedPlane.cpp Assets/Objects/XYLimitedPlane.h Assets/Materials/Emission.cpp Assets/Materials/Emission.h Random.h Random.cpp)

if(OpenMP_CXX_FOUND)
    target_link_libraries(ToyRT PRIVATE OpenMP::OpenMP_CXX)
endif()

target_link_libraries(ToyRT PRIVATE TBB::tbb)
