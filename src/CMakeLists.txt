set(MODULE_NAME PODSL)

set(MODULE_SOURCES
    ModelBase.cpp
)

set(MODULE_HEADERS
    ModelBase.h
)

add_library(${MODULE_NAME}
    STATIC
    ${MODULE_SOURCES}
    ${MODULE_HEADERS}
)

add_library(${MODULE_NAME}::${MODULE_NAME} ALIAS ${MODULE_NAME})