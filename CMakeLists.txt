cmake_minimum_required(VERSION 3.15.5)

project(PODSL VERSION 1.0.0)

###### Conan package manager configuration ######
execute_process(COMMAND "python" "-m" "pip" "install" "conan")

include(submodules/cmake-conan/conan.cmake)

# conan_add_remote(NAME vectrom
#                  INDEX 0
#                  URL https://artifactory.plociennik.net/artifactory/api/conan/conan
#                  VERIFY_SSL True)     

# conan_add_remote(NAME bincrafters 
#                  INDEX 1
#                  URL https://api.bintray.com/conan/bincrafters/public-conan
#                  VERIFY_SSL True)     

conan_cmake_run(CONANFILE conanfile.txt
                BUILD missing
                CONFIGURATION_TYPES "Release;Debug"
                BASIC_SETUP NO_OUTPUT_DIRS CMAKE_TARGETS KEEP_RPATHS UPDATE
                )

list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_BINARY_DIR}")
list(INSERT CMAKE_PREFIX_PATH 0 "${CMAKE_BINARY_DIR}")

find_package(Boost COMPONENTS graph REQUIRED CONFIG)

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