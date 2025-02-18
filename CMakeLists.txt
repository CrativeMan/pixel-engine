cmake_minimum_required(VERSION 3.10)
project(main)

set (OSBitness 32)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(OSBitness 64)
endif()

set (FullOutputDir "${CMAKE_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}${OSBitness}/${CMAKE_BUILD_TYPE}")
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${FullOutputDir}/static libs")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${FullOutputDir}")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${FullOutputDir}")

add_subdirectory(src/engine)
include_directories(src/.)
include_directories(external/.)

add_executable(${PROJECT_NAME} src/game/main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE Engine GL glfw GLEW imgui)
target_include_directories(${PROJECT_NAME} PRIVATE src/engine)
