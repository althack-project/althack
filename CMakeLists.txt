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

# libconfig cmake switches
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_TESTS OFF CACHE BOOL "" FORCE)

# Add 3rdparty components
add_subdirectory(${THIRDPARTY_DIR}/SDL)
add_subdirectory(${THIRDPARTY_DIR}/libconfig)
add_subdirectory(${THIRDPARTY_DIR}/spdlog)

configure_file(include/althack/config.hpp.in include/althack/config.hpp)

include_directories(
  include
  ${THIRDPARTY_DIR}/imgui
  ${THIRDPARTY_DIR}/imgui/backends
  ${THIRDPARTY_DIR}/SDL/include
  ${THIRDPARTY_DIR}/libconfig/lib
  ${THIRDPARTY_DIR}/spdlog/include
  ${CMAKE_BINARY_DIR}/include)

add_library(imgui
  ${THIRDPARTY_DIR}/imgui/imgui.cpp
  ${THIRDPARTY_DIR}/imgui/imgui_draw.cpp
  ${THIRDPARTY_DIR}/imgui/imgui_tables.cpp
  ${THIRDPARTY_DIR}/imgui/imgui_widgets.cpp
  ${THIRDPARTY_DIR}/imgui/backends/imgui_impl_sdl.cpp
  ${THIRDPARTY_DIR}/imgui/backends/imgui_impl_sdlrenderer.cpp)

add_library(${PROJECT_NAME}
  src/althack/althack.cpp)

add_executable(${PROJECT_NAME}-bin
  src/main.cpp
  src/althack/main_window.cpp
  src/althack/backend.cpp
  src/althack/backends/server_backend.cpp
  src/althack/visuals/node.cpp
  src/althack/visuals/account_node.cpp)

target_link_libraries(${PROJECT_NAME}
  imgui
  SDL2
  config++)

target_link_libraries(${PROJECT_NAME}-bin
  ${PROJECT_NAME})

# Doxygen Documentation
find_package(Doxygen
  REQUIRED dot)

set(DOXYGEN_GENERATE_HTML YES)
set(DOXYGEN_GENERATE_MAN NO)

set(DOXYGEN_PROJECT_BRIEF "${PROJECT_NAME}")
doxygen_add_docs(
  doxygen
  ${PROJECT_SOURCE_DIR}/src
  ${PROJECT_SOURCE_DIR}/include
  COMMENT "Generate source code documentation")
