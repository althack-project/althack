cmake_minimum_required(VERSION 3.8)
project(althack)

# Project cmake settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_MAJOR_VERSION 0)
set(CMAKE_MINOR_VERSION 1)
set(CMAKE_PATCH_VERSION 0)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3 -fPIC" )
set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} -Wall -O3 -fPIC" )

set(THIRDPARTY_DIR ${PROJECT_SOURCE_DIR}/3rdparty)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

set(BUILD_PLATFORM "Windows")
#set(BUILD_PLATFORM "Linux")

if("${BUILD_PLATFORM}" STREQUAL "Windows")
  set(CMAKE_THREAD_LIBS_INIT "-lpthread" CACHE STRING "" FORCE)
  set(CMAKE_HAVE_THREADS_LIBRARY 1 CACHE BOOL "" FORCE)
  set(CMAKE_USE_WIN32_THREADS_INIT 0 CACHE BOOL "" FORCE)
  set(CMAKE_USE_PTHREADS_INIT 1 CACHE BOOL "" FORCE)
  set(THREADS_PREFER_PTHREAD_FLAG ON CACHE BOOL "" FORCE)

  set(MINGW_PREFIX "x86_64-w64-mingw32" CACHE STRING "" FORCE)
  set(CMAKE_SYSTEM_NAME "Windows" CACHE STRING "" FORCE)
  set(CMAKE_SYSTEM_VERSION "10" CACHE STRING "" FORCE)
  set(CMAKE_SYSTEM "${CMAKE_SYSTEM_NAME}" CACHE STRING "" FORCE)
  set(CMAKE_C_COMPILER "/usr/bin/${MINGW_PREFIX}-gcc" CACHE STRING "" FORCE)
  set(CMAKE_CXX_COMPILER "/usr/bin/${MINGW_PREFIX}-g++" CACHE STRING "" FORCE)
  set(CMAKE_FIND_ROOT_PATH "/usr/${MINGW_PREFIX}" CACHE STRING "" FORCE)
  set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER CACHE STRING "" FORCE)
  set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY CACHE STRING "" FORCE)
  set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY CACHE STRING "" FORCE)
  set(WIN32 ON CACHE BOOL "" FORCE)
  set(CMAKE_RC_COMPILER "/usr/bin/${MINGW_PREFIX}-windres" CACHE STRING "" FORCE)
endif()

# clang settings
set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=*,-modernize-use-trailing-return-type,-cppcoreguidelines-avoid-magic-numbers,-readability-magic-numbers,-fuchsia-default-arguments-calls,-fuchsia-statically-constructed-objects")

# Project subdirectories
add_subdirectory("docs")

# libconfig cmake switches
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_TESTS OFF CACHE BOOL "" FORCE)

# SOCI cmake switches
set(SOCI_STATIC OFF CACHE BOOL "" FORCE)
set(SOCI_SHARED ON CACHE BOOL "" FORCE)
set(SOCI_TESTS OFF CACHE BOOL "" FORCE)
set(SOCI_EMPTY OFF CACHE BOOL "" FORCE)
set(SOCI_MYSQL OFF CACHE BOOL "" FORCE)
set(SOCI_FIREBIRD OFF CACHE BOOL "" FORCE)
set(SOCI_ODBC OFF CACHE BOOL "" FORCE)
set(SOCI_ORACLE OFF CACHE BOOL "" FORCE)
set(SOCI_POSTGRESQL OFF CACHE BOOL "" FORCE)
set(SOCI_DB2 OFF CACHE BOOL "" FORCE)

# Add 3rdparty directory
add_subdirectory(${THIRDPARTY_DIR})

configure_file(include/althack/config.hpp.in include/althack/config.hpp)

include_directories(
  include
  ${THIRDPARTY_DIR}/imgui
  ${THIRDPARTY_DIR}/imgui/backends
  ${THIRDPARTY_DIR}/SDL/include
  ${THIRDPARTY_DIR}/libconfig/lib
  ${THIRDPARTY_DIR}/spdlog/include
  ${THIRDPARTY_DIR}/soci/include
  ${CMAKE_BINARY_DIR}/3rdparty/soci/include
  ${CMAKE_BINARY_DIR}/include)

link_directories(
  ${CMAKE_BINARY_DIR}/lib)

add_library(imgui
  ${THIRDPARTY_DIR}/imgui/imgui.cpp
  ${THIRDPARTY_DIR}/imgui/imgui_draw.cpp
  ${THIRDPARTY_DIR}/imgui/imgui_tables.cpp
  ${THIRDPARTY_DIR}/imgui/imgui_widgets.cpp
  ${THIRDPARTY_DIR}/imgui/backends/imgui_impl_sdl.cpp
  ${THIRDPARTY_DIR}/imgui/backends/imgui_impl_sdlrenderer.cpp)

target_link_libraries(imgui
  SDL2
  SDL2main)

add_library(${PROJECT_NAME}
  src/althack/althack.cpp)

add_executable(${PROJECT_NAME}-bin
  src/main.cpp
  src/althack/main_window.cpp
  src/althack/frontend.cpp
  src/althack/backend.cpp
  src/althack/backends/server_backend.cpp
  src/althack/database.cpp
  src/althack/databases/soci_database.cpp
  src/althack/visuals/node.cpp
  src/althack/visuals/account_node.cpp)

target_link_libraries(${PROJECT_NAME}
  imgui
  SDL2
  config++
  soci_core
  soci_sqlite3
  dl
  stdc++fs)

target_link_libraries(${PROJECT_NAME}-bin
  ${PROJECT_NAME})
