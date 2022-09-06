# Disable clang-tidy for 3rdparty directories
set(CMAKE_CXX_CLANG_TIDY "")

# Add 3rdparty components
add_subdirectory(${THIRDPARTY_DIR}/SDL)
add_subdirectory(${THIRDPARTY_DIR}/libconfig)
add_subdirectory(${THIRDPARTY_DIR}/spdlog)
add_subdirectory(${THIRDPARTY_DIR}/soci)
