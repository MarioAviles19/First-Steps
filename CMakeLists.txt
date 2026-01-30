cmake_minimum_required(VERSION 3.23)

project(FirstSteps)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm CONFIG REQUIRED)

include_directories(
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/src
)

add_executable(FirstSteps main.cpp 
  src/glad.c 
  src/sprite_renderer.cpp
  src/window.cpp
  src/renderer.cpp
  src/component.cpp
)

set_property(TARGET FirstSteps PROPERTY CXX_STANDARD 23)
set_property(TARGET FirstSteps PROPERTY CXX_STANDARD_REQUIRED ON)

target_compile_options(FirstSteps PRIVATE -g -O0)

target_sources(FirstSteps
  PRIVATE
    main.cpp
    src/glad.c 
    src/sprite_renderer.cpp
    src/window.cpp
)
target_link_libraries(FirstSteps
  PRIVATE OpenGL::OpenGL glfw 
)
add_custom_command(
  TARGET FirstSteps
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
          ${CMAKE_SOURCE_DIR}/shaders
          $<TARGET_FILE_DIR:FirstSteps>/shaders
)
