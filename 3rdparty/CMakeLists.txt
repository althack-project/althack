# CMake settings and includes
include(ExternalProject)

# Disable clang-tidy for 3rdparty directories
set(CMAKE_CXX_CLANG_TIDY "")

# Add 3rdparty components
add_subdirectory(${THIRDPARTY_DIR}/SDL)
add_subdirectory(${THIRDPARTY_DIR}/libconfig)
add_subdirectory(${THIRDPARTY_DIR}/spdlog)
add_subdirectory(${THIRDPARTY_DIR}/soci)

# OpenSSL
find_program(MAKE_EXECUTABLE NAMES gmake make mingw32-make REQUIRED)
set(openssl_LIBRARY ${CMAKE_INSTALL_PREFIX}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}openssl${CMAKE_STATIC_LIBRARY_SUFFIX})

ExternalProject_Add(openssl
  SOURCE_DIR ${THIRDPARTY_DIR}/openssl
  UPDATE_DISCONNECTED true
  CONFIGURE_COMMAND "${THIRDPARTY_DIR}/openssl/Configure"
  BUILD_COMMAND ${MAKE_EXECUTABLE} -j
  INSTALL_COMMAND ${MAKE_EXECUTABLE} -j DESTDIR="${CMAKE_BINARY_DIR}/openssl-build" install
  BUILD_BYPRODUCTS ${openssl_LIBRARY})
