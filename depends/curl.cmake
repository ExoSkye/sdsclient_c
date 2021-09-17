include(FetchContent)

FetchContent_Declare(curl
        GIT_REPOSITORY  https://github.com/curl/curl.git
        GIT_TAG         curl-7_79_0
        GIT_SHALLOW     TRUE
        SOURCE_DIR      ${CMAKE_BINARY_DIR}/curl-src
        )

FetchContent_GetProperties(curl)
if(NOT curl_POPULATED)
    message(STATUS "Fetching curl 7.79.0")
    FetchContent_Populate(curl)
    message(STATUS "Fetched curl 7.79.0")
endif()

add_subdirectory(${curl_SOURCE_DIR})

add_library(curl-interface INTERFACE)
target_include_directories(curl-interface INTERFACE ${curl_SOURCE_DIR}/include)
target_link_libraries(curl-interface INTERFACE libcurl)