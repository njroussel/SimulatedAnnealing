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
    )

pybind11_add_module(mcaa
    # Header files

    # Source files
    src/main.cpp
    )

#[[
set(CMAKE_BUILD_TYPE Debug)
find_package( Threads )

add_executable(mcaa
    # Header files
    include/mcaa/helpers.h
    include/mcaa/dpdf.h
    include/mcaa/sampler.h
    include/mcaa/rwm.h
    include/mcaa/mala.h
    include/mcaa/function1D.h
    include/mcaa/mcmc1D.h
    include/mcaa/mh1D.h
    include/mcaa/drm1D.h
    include/mcaa/mtm1D.h
    include/mcaa/multiRunner1D.h
    include/mcaa/function2D.h
    include/mcaa/mcmc2D.h
    include/mcaa/mh2D.h
    include/mcaa/drm2D.h
    include/mcaa/mtm2D.h
    include/mcaa/multiRunner2D.h

    # Source files
    src/helpers.cpp
    src/sampler.cpp
    src/rwm.cpp
    src/mala.cpp
    src/function1D.cpp
    src/mcmc1D.cpp
    src/mh1D.cpp
    src/drm1D.cpp
    src/mtm1D.cpp
    src/multiRunner1D.cpp
    src/function2D.cpp
    src/mcmc2D.cpp
    src/mh2D.cpp
    src/drm2D.cpp
    src/mtm2D.cpp
    src/multiRunner2D.cpp
    src/main.cpp
    )

target_link_libraries(mcaa PRIVATE pybind11::embed ${CMAKE_THREAD_LIBS_INIT})
]]
