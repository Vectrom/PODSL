set(MODULE_NAME tests)
if(UNIX)
    set(MODULE_NAME tests.out)
endif()

set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
add_subdirectory(googletest)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/TestUtilsConstexpr.h.in ${CMAKE_CURRENT_BINARY_DIR}/TestUtilsConstexpr.h)

add_executable(${MODULE_NAME}
    Graph.cpp
    Model.cpp
    Simulation.cpp
    TestUtils.cpp
    TestUtils.h
    ${CMAKE_CURRENT_BINARY_DIR}/TestUtilsConstexpr.h
)

target_include_directories(${MODULE_NAME}
    PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${MODULE_NAME}
    gtest
    gtest_main
    PODSL::PODSL
)

set_property(TARGET ${MODULE_NAME} PROPERTY FOLDER "tests")
set_property(TARGET gtest PROPERTY FOLDER "tests")
set_property(TARGET gtest_main PROPERTY FOLDER "tests")

enable_testing()
add_test(NAME ${MODULE_NAME} COMMAND $<TARGET_FILE:${MODULE_NAME}> --gtest_output=xml:testresults.xml --gtest_color=yes)