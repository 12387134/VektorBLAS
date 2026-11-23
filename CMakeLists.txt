cmake_minimum_required(VERSION 4.4)

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD
    "f35a9ac6-8463-4d38-8eec-5d6008153e7d"
)

set(CMAKE_OSX_DEPLOYMENT_TARGET "14.4")
project(VektorBLAS LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(VEKTOR_ARCH_MODULES)

if (APPLE AND CMAKE_SYSTEM_PROCESSOR MATCHES "^(arm64|aarch64)$")

    list(APPEND VEKTOR_ARCH_MODULES
        src/matrix/matrix_arm.cpp
        src/vector/vector_arm.cpp
    )

    message(STATUS "VektorBLAS: Target architecture = ARM64 (NEON)")

elseif (CMAKE_SYSTEM_PROCESSOR MATCHES "^(x86_64|AMD64|amd64)$")

    list(APPEND VEKTOR_ARCH_MODULES
        src/matrix/matrix_avx.cpp
        src/vector/vector_avx.cpp
    )

    message(STATUS "VektorBLAS: Target architecture = x86_64 (AVX)")

else()

    message(FATAL_ERROR
        "Unsupported architecture: ${CMAKE_SYSTEM_PROCESSOR}"
    )

endif()

add_library(vektor_blas)
target_sources(vektor_blas
    PUBLIC
    FILE_SET CXX_MODULES FILES
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
    FILES
        include/vektor_math.cppm
        include/types.cppm
        include/vektor.cppm
        include/vector.cppm
        include/matrix.cppm
        include/simd.cppm
)

set_property(TARGET vektor_blas PROPERTY CXX_MODULE_STD ON)

include(CTest)
if (BUILD_TESTING)
    find_package(Catch2 3 QUIET)
    if (NOT Catch2_FOUND)
        include(FetchContent)
        FetchContent_Declare(Catch2
            GIT_REPOSITORY https://github.com/catchorg/Catch2.git
            GIT_TAG        v3.8.1)
        FetchContent_MakeAvailable(Catch2)
        list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
    endif()

    add_executable(tests
        tests/vector_tests.cpp
    )
    target_link_libraries(tests PRIVATE vektor_blas Catch2::Catch2WithMain)

    include(Catch)
    catch_discover_tests(tests)

endif()