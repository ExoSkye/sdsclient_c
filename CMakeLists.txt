cmake_minimum_required(VERSION 3.20)
project(sdsclient_c C)

set(CMAKE_C_STANDARD 11)

include(depends/sdl2.cmake)
include(depends/b64.cmake)
include(depends/curl.cmake)
include(depends/jsmn.cmake)

add_executable(sdsclient_c src/main.c src/netapi.c src/netapi.h src/config.c src/config.h src/timepoints.h src/timepoints.c src/json_helper.h)
target_link_libraries(sdsclient_c PRIVATE SDL2 sdl2-image-lib base64 curl-interface jsmn)
target_include_directories(sdsclient_c PRIVATE ${sdl2_SOURCE_DIR}/include)