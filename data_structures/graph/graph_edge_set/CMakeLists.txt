add_project_library(edge_set_graph_utils INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/utils")

add_project_executable(bellman_ford "${CMAKE_CURRENT_SOURCE_DIR}/bellman_ford" algo_lib edge_set_graph_utils)
add_project_executable(kruskal_mst "${CMAKE_CURRENT_SOURCE_DIR}/kruskal_mst" algo_lib edge_set_graph_utils)
