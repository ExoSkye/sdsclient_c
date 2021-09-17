include(FetchContent)

FetchContent_Declare(yaml
        GIT_REPOSITORY  https://github.com/tlsa/libcyaml.git
        GIT_TAG         v1.2.0
        GIT_SHALLOW     TRUE
        SOURCE_DIR      ${CMAKE_BINARY_DIR}/yaml-src
        )

FetchContent_GetProperties(yaml)
if(NOT yaml_POPULATED)
    message(STATUS "Fetching yaml")
    FetchContent_Populate(yaml)
    message(STATUS "Fetched yaml")
endif()

add_library(cyaml-impl
        ${yaml_SOURCE_DIR}/include/cyaml/cyaml.h
        ${yaml_SOURCE_DIR}/src/data.h
        ${yaml_SOURCE_DIR}/src/free.c
        ${yaml_SOURCE_DIR}/src/load.c
        ${yaml_SOURCE_DIR}/src/mem.c
        ${yaml_SOURCE_DIR}/src/mem.h
        ${yaml_SOURCE_DIR}/src/save.c
        ${yaml_SOURCE_DIR}/src/utf8.h
        ${yaml_SOURCE_DIR}/src/utf8.c
        ${yaml_SOURCE_DIR}/src/util.h
        ${yaml_SOURCE_DIR}/src/util.c)

add_library(cyaml INTERFACE)

target_link_libraries(cyaml INTERFACE cyaml-impl)
target_include_directories(cyaml INTERFACE ${yaml_SOURCE_DIR}/include/)