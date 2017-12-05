cmake_minimum_required(VERSION 3.0)
project(mcaa)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(ext ext_build)

include_directories(
    # Include files
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    # Pseudorandom number generator
    ${PCG32_INCLUDE_DIR}
    # Python bindings
    ${PYBIND11_INCLUDE_DIR}
    # Eigen
    ${EIGEN_INCLUDE_DIR}
    )

#[[
pybind11_add_module(mcaa
    # Header files
    include/mcaa/common.h
    include/mcaa/helpers.h
    include/mcaa/sampler.h
    include/mcaa/mcmc.h

    # Source files
    src/helpers.cpp
    src/sampler.cpp
    src/mcmc.cpp
    src/main.cpp
    )
]]

set(CMAKE_BUILD_TYPE Debug)
find_package( Threads )

add_executable(mcaa
    # Header files
    include/mcaa/common.h
    include/mcaa/helpers.h
    include/mcaa/sampler.h
    include/mcaa/mcmc.h

    # Source files
    src/helpers.cpp
    src/sampler.cpp
    src/mcmc.cpp
    src/main.cpp
    )

target_link_libraries(mcaa PRIVATE pybind11::embed ${CMAKE_THREAD_LIBS_INIT})
