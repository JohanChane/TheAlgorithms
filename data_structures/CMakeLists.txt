cmake_minimum_required(VERSION 3.15)
project(data_structures VERSION 0.1.0)

set(project_dir "..")
include(${project_dir}/cmake_utils/cmake_utils.cmake)

config_c()

add_project_library(algo_lib INTERFACE "${project_dir}/algo_lib")

add_subdirectory(sorting)
add_subdirectory(linked_list)
add_subdirectory(tree)
add_subdirectory(hash_table)
add_subdirectory(heap)
add_subdirectory(stack_queue)
add_subdirectory(graph)
