cmake_minimum_required(VERSION 3.10.0)
project(MathCounter VERSION 0.1.0 LANGUAGES C CXX)

add_executable(MathCounter main.cpp)

include(CTest)
enable_testing()


find_package(PkgConfig REQUIRED)

pkg_check_modules(GMP REQUIRED IMPORTED_TARGET gmp)
pkg_check_modules(GMPXX REQUIRED IMPORTED_TARGET gmpxx)



set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

target_link_libraries(MathCounter PRIVATE
    PkgConfig::GMP
    PkgConfig::GMPXX
)