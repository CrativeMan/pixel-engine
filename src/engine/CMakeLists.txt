file (GLOB ENGINE_SOURCES "*.cpp")

add_library(jade ${ENGINE_SOURCES})
include_directories(${CMAKE_SOURCE_DIR}/src/engine)
include_directories(${CMAKE_SOURCE_DIR}/external)

target_include_directories(jade
    PUBLIC
        ${CMAKE_SOURCE_DIR}/src/include
)