cmake_minimum_required(VERSION 3.10)

# Set the project name
project(PixelEngine)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source files
file(GLOB_RECURSE ENGINE_SOURCES "src/engine/*.cpp")

# Add include directories
include_directories(src/engine/header)

# Add executable
add_executable(PixelEngine ${ENGINE_SOURCES})

# Link libraries
target_link_libraries(PixelEngine glfw GL GLEW glm m imgui)

# Set output directories
set_target_properties(PixelEngine PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
  ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
  LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

# Add custom target for cleaning
add_custom_target(clean-all
  COMMAND ${CMAKE_COMMAND} -P ${CMAKE_BINARY_DIR}/cmake_clean.cmake
)

# Add custom command for cleaning
file(WRITE ${CMAKE_BINARY_DIR}/cmake_clean.cmake
  "file(REMOVE_RECURSE ${CMAKE_BINARY_DIR}/bin ${CMAKE_BINARY_DIR}/lib ${CMAKE_BINARY_DIR}/CMakeFiles ${CMAKE_BINARY_DIR}/CMakeCache.txt ${CMAKE_BINARY_DIR}/cmake_install.cmake ${CMAKE_BINARY_DIR}/Makefile)"
)