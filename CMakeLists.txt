cmake_minimum_required(VERSION 3.15.5)

project(PODSL VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_definitions(/W4)
    add_definitions(/WX)
elseif(UNIX AND NOT APPLE)
    add_compile_options(-Wall -pedantic -Werror)
elseif(APPLE)
    add_compile_options(-Wall -pedantic -Werror)
endif()

add_subdirectory(src)