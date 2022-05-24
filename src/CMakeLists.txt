set(MODULE_NAME PODSL)

set(MODULE_SOURCES
    ModelBase.cpp
)

set(MODULE_HEADERS
    Aspen.h
    ModelBase.h
)

add_library(${MODULE_NAME}
    STATIC
    ${MODULE_SOURCES}
    ${MODULE_HEADERS}
)

add_library(${MODULE_NAME}::${MODULE_NAME} ALIAS ${MODULE_NAME})

target_include_directories(${MODULE_NAME}
    PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
    PUBLIC
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
)
