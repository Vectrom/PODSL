set(MODULE_NAME PODSL)

set(MODULE_SOURCES
    ErrorCodes.cpp
    Exception.cpp
    Graph.cpp
    MajorityModel.cpp
    ModelBase.cpp
    PODSLEnums.cpp
    QVoterModel.cpp
    Simulation.cpp
    StringUtils.cpp
    SznajdModel.cpp
    VoterModel.cpp
)

set(MODULE_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/ErrorCodes.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Exception.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Graph.h
    ${CMAKE_CURRENT_SOURCE_DIR}/MajorityModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ModelBase.h
    ${CMAKE_CURRENT_SOURCE_DIR}/PajekParser.h
    ${CMAKE_CURRENT_SOURCE_DIR}/PODSL.h
    ${CMAKE_CURRENT_SOURCE_DIR}/PODSLEnums.h
    ${CMAKE_CURRENT_SOURCE_DIR}/QVoterModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Simulation.h
    ${CMAKE_CURRENT_SOURCE_DIR}/StringUtils.h
    ${CMAKE_CURRENT_SOURCE_DIR}/SznajdModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/VoterModel.h
)

add_library(${MODULE_NAME}
    STATIC
    ${MODULE_SOURCES}
    ${MODULE_HEADERS}
)

add_library(${MODULE_NAME}::${MODULE_NAME} ALIAS ${MODULE_NAME})

set_target_properties(${MODULE_NAME} PROPERTIES PUBLIC_HEADER "${MODULE_HEADERS}")
target_include_directories(${MODULE_NAME}
    PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
    PUBLIC
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${MODULE_NAME} PUBLIC
                        Boost::graph
                        RapidJSON::RapidJSON
                        )

if(UNIX AND NOT APPLE)
    target_link_libraries(${MODULE_NAME} PUBLIC
                            -lstdc++fs # to handle std::filesystem on GCC8
                            )
endif()
                        