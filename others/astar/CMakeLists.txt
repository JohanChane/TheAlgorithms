cmake_minimum_required(VERSION 3.15)
project(app VERSION 0.1.0)

set(project_dir "../..")
include(${project_dir}/cmake_utils/cmake_utils.cmake)

config_cpp()

add_project_executable(astar "${CMAKE_CURRENT_SOURCE_DIR}/src")
