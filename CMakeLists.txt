
cmake_minimum_required(VERSION 3.28)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")

project(unicursal)

add_executable(unicursal
  unicursal.cc)

add_custom_target(run
  DEPENDS unicursal
  COMMAND unicursal)
