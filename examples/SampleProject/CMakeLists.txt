cmake_minimum_required(VERSION 3.13.0)

project(SampleApp)

###### Build configuration ######
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../.. ${CMAKE_CURRENT_BINARY_DIR}/PODSL)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    PODSL::PODSL
)

include(CTest)

add_test(RunWithoutCrash ${PROJECT_NAME})