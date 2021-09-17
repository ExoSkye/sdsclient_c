include(FetchContent)

FetchContent_Declare(base64
        GIT_REPOSITORY  https://github.com/joedf/base64.c.git
        GIT_SHALLOW     TRUE
        SOURCE_DIR      ${CMAKE_BINARY_DIR}/b64-src
        )

FetchContent_GetProperties(base64)
if(NOT base64_POPULATED)
    message(STATUS "Fetching base64.c")
    FetchContent_Populate(base64)
    message(STATUS "Fetched base64.c")
endif()

add_library(base64-impl ${base64_SOURCE_DIR}/base64.c)

add_library(base64 INTERFACE)
target_include_directories(base64 INTERFACE ${base64_SOURCE_DIR})
target_link_libraries(base64 INTERFACE base64-impl)