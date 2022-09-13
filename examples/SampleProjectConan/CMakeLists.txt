cmake_minimum_required(VERSION 3.13.0)

project(SampleApp)

###### Conan package manager configuration ######
execute_process(COMMAND "python" "-m" "pip" "install" "conan")

include(../../submodules/cmake-conan/conan.cmake)

conan_add_remote(NAME vectrom
                 INDEX 0
                 URL https://artifactory.plociennik.net/artifactory/api/conan/conan
                 VERIFY_SSL True)     

conan_cmake_run(CONANFILE conanfile.txt
                CONFIGURATION_TYPES "Release;Debug"
                BASIC_SETUP NO_OUTPUT_DIRS CMAKE_TARGETS KEEP_RPATHS UPDATE
                )

list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_BINARY_DIR}")
list(INSERT CMAKE_PREFIX_PATH 0 "${CMAKE_CURRENT_BINARY_DIR}")

find_package(PODSL REQUIRED CONFIG)

###### Build configuration ######
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    PODSL::PODSL
)

include(CTest)

add_test(RunWithoutCrash ${PROJECT_NAME})