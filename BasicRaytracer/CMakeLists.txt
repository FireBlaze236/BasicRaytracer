# CMakeList.txt : CMake project for BasicRaytracer, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (BasicRaytracer "BasicRaytracer.cpp" "BasicRaytracer.h" "Math.h" "Math.cpp" "Ray.h" "Ray.cpp" "Shape.h" "Shape.cpp" "Camera.h" "Camera.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET BasicRaytracer PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
