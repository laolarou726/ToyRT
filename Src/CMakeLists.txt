cmake_minimum_required(VERSION 3.22)
project(ToyRT)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenMP)
find_package(TBB REQUIRED)

add_subdirectory(Dependencies/fmt EXCLUDE_FROM_ALL)

file(GLOB ASSETS_SOURCES
        ${PROJECT_SOURCE_DIR}/Assets/*.h
        ${PROJECT_SOURCE_DIR}/Assets/*.cpp
        ${PROJECT_SOURCE_DIR}/Assets/Cameras/*.h
        ${PROJECT_SOURCE_DIR}/Assets/Cameras/*.cpp
        ${PROJECT_SOURCE_DIR}/Assets/Materials/*.h
        ${PROJECT_SOURCE_DIR}/Assets/Materials/*.cpp
        ${PROJECT_SOURCE_DIR}/Assets/Objects/*.h
        ${PROJECT_SOURCE_DIR}/Assets/Objects/*.cpp)

file(GLOB MODELS_SOURCES
        ${PROJECT_SOURCE_DIR}/Models/*.h
        ${PROJECT_SOURCE_DIR}/Models/*.cpp)

file(GLOB UTILS_SOURCES
        ${PROJECT_SOURCE_DIR}/Utils/*.h
        ${PROJECT_SOURCE_DIR}/Utils/*.c
        ${PROJECT_SOURCE_DIR}/Utils/*.cpp)

add_executable(ToyRT
        main.cpp
        ${ASSETS_SOURCES}
        ${MODELS_SOURCES}
        ${UTILS_SOURCES} Assets/Materials/Dielectric.cpp Assets/Materials/Dielectric.h Utils/GammaUtils.cpp Utils/GammaUtils.h)

if(OpenMP_CXX_FOUND)
    target_link_libraries(ToyRT PRIVATE OpenMP::OpenMP_CXX)
endif()

target_link_libraries(ToyRT PRIVATE TBB::tbb)
target_link_libraries(ToyRT PRIVATE fmt::fmt-header-only)
