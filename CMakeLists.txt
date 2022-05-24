cmake_minimum_required(VERSION 3.15.5)

project(PODSL VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(UNIX AND NOT APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif()

if(MSVC)
    add_definitions(/W4)
    add_definitions(/WX)
elseif(UNIX AND NOT APPLE)
    add_compile_options(-Wall -pedantic -Werror)
elseif(APPLE)
    add_compile_options(-Wall -pedantic -Werror)
endif()

# tests
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT tests)

add_subdirectory(src)