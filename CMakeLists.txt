cmake_minimum_required(VERSION 3.15.5)

project(PODSL VERSION 1.0.0)

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(PODSL_STANDALONE ON)

    if(NOT DEFINED PODSL_CREATE_PACKAGE)
        set(PODSL_CREATE_PACKAGE ON)
    endif()
    if(NOT DEFINED PODSL_ADD_INSTALL)
        set(PODSL_ADD_INSTALL OFF)
    endif()
endiF()

option(PODSL_CREATE_PACKAGE OFF)
option(PODSL_ADD_INSTALL OFF)

if(PODSL_STANDALONE)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()


###### Conan package manager configuration ######
execute_process(COMMAND "python" "-m" "pip" "install" "conan")

include(submodules/cmake-conan/conan.cmake)

conan_add_remote(NAME vectrom
                 INDEX 0
                 URL https://artifactory.plociennik.net/artifactory/api/conan/conan
                 VERIFY_SSL True)     

if(APPLE)
    conan_cmake_run(CONANFILE conanfile.txt
                    CONFIGURATION_TYPES "Release;Debug"
                    BASIC_SETUP NO_OUTPUT_DIRS CMAKE_TARGETS KEEP_RPATHS UPDATE
                    SETTINGS compiler.cppstd=17
                    )
else()
    conan_cmake_run(CONANFILE conanfile.txt
                    CONFIGURATION_TYPES "Release;Debug"
                    BASIC_SETUP NO_OUTPUT_DIRS CMAKE_TARGETS KEEP_RPATHS UPDATE
                    )
endif()

list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_BINARY_DIR}")
list(INSERT CMAKE_PREFIX_PATH 0 "${CMAKE_CURRENT_BINARY_DIR}")

find_package(Boost COMPONENTS graph REQUIRED CONFIG)
find_package(RapidJSON REQUIRED CONFIG)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(UNIX AND NOT APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif()

if(PODSL_STANDALONE)
    if(MSVC)
        add_definitions(/W4)
        add_definitions(/WX)
    elseif(UNIX AND NOT APPLE)
        add_compile_options(-Wall -pedantic -Werror)
    elseif(APPLE)
        add_compile_options(-Wall -pedantic -Werror)
    endif()
endif()

# tests
if(PODSL_STANDALONE)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT tests)
endif()

add_subdirectory(src)

if(PODSL_CREATE_PACKAGE)
    install(TARGETS PODSL
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        PUBLIC_HEADER DESTINATION include
    )

    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(PODSL_ARCHITECTURE "x64")
    elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
        set(PODSL_ARCHITECTURE "x86")
    endif()

    if(NOT CMAKE_CONFIGURATION_TYPES)
        set(PODSL_BUILD_TYPE ${CMAKE_BUILD_TYPE})
    endif()

    include(InstallRequiredSystemLibraries)

    set(CPACK_GENERATOR "ZIP")
    set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)
    set(CPACK_PACKAGE_NAME "PODSL")
    set(CPACK_PACKAGE_VERSION_MAJOR ${PODSL_VERSION_MAJOR})
    set(CPACK_PACKAGE_VERSION_MINOR ${PODSL_VERSION_MINOR})
    set(CPACK_PACKAGE_VERSION_PATCH ${PODSL_VERSION_PATCH})
    set(CPACK_PACKAGE_VERSION ${PODSL_VERSION})
    set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CMAKE_CXX_COMPILER_ID}-${CMAKE_CXX_COMPILER_VERSION}-${PODSL_ARCHITECTURE}-${PODSL_BUILD_TYPE}")

    include(CPack)
endif()

if(PODSL_ADD_INSTALL)
    install(TARGETS PODSL
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        PUBLIC_HEADER DESTINATION include
    )
endif()