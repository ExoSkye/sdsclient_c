include(FetchContent)

FetchContent_Declare(jsmn
        GIT_REPOSITORY  https://github.com/zserge/jsmn
        GIT_SHALLOW     TRUE
        SOURCE_DIR      ${CMAKE_BINARY_DIR}/jsnm-src
        )

FetchContent_GetProperties(jsmn)
if(NOT jsmn_POPULATED)
    message(STATUS "Fetching jsmn")
    FetchContent_Populate(jsmn)
    message(STATUS "Fetched jsmn")
endif()

add_library(jsmn INTERFACE)
target_include_directories(jsmn INTERFACE ${jsmn_SOURCE_DIR})