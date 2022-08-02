set(MODULE_NAME PODSL)

set(MODULE_SOURCES
    Graph.cpp
    MajorityModel.cpp
    ModelBase.cpp
    Simulation.cpp
    SznajdModel.cpp
    VoterModel.cpp
)

set(MODULE_HEADERS
    Graph.h
    MajorityModel.h
    ModelBase.h
    PODSL.h
    Simulation.h
    SznajdModel.h
    VoterModel.h
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

target_link_libraries(${MODULE_NAME} PUBLIC Boost::graph)