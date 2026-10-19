# cmake -S . -B build-llvm

cmake_minimum_required(VERSION 4.4)

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD
    "f35a9ac6-8463-4d38-8eec-5d6008153e7d"
)

project(VektorBLAS LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_OSX_DEPLOYMENT_TARGET "14.4")

set(CMAKE_CXX_STDLIB_MODULES_JSON
    "/opt/homebrew/opt/llvm/lib/c++/libc++.modules.json"
)

add_executable(vektor_app
    src/main.cpp
)

if (APPLE AND CMAKE_SYSTEM_PROCESSOR MATCHES "arm64|aarch64")
    target_sources(vektor_app PRIVATE
        src/matrix/matrix_arm.cpp
        src/vector/vector_arm.cpp
    )
    message(STATUS "VektorBLAS: Target architecture = ARM64 (NEON)")

elseif (CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|AMD64")
    target_sources(vektor_app PRIVATE
        src/matrix/matrix_avx.cpp
        src/vector/vector_avx.cpp
    )
    message(STATUS "VektorBLAS: Target architecture = x86_64 (AVX)")

endif()

target_sources(vektor_app
    PUBLIC
    FILE_SET CXX_MODULES FILES
        include/vector.cppm
        include/matrix.cppm
)

set_property(TARGET vektor_app PROPERTY CXX_MODULE_STD ON)
