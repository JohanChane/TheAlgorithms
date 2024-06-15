add_project_library(matrix_graph_utils INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/utils")

add_project_executable(floy_warshall "${CMAKE_CURRENT_SOURCE_DIR}/floy_warshall" algo_lib matrix_graph_utils)
add_project_executable(prim_mst "${CMAKE_CURRENT_SOURCE_DIR}/prim_mst" algo_lib matrix_graph_utils)
add_project_executable(unweight_sp "${CMAKE_CURRENT_SOURCE_DIR}/unweight_sp" algo_lib matrix_graph_utils)
