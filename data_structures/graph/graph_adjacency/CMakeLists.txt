add_project_library(adjacency_graph_utils INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/utils")

add_project_executable(bfs "${CMAKE_CURRENT_SOURCE_DIR}/bfs" algo_lib adjacency_graph_utils)
add_project_executable(dfs "${CMAKE_CURRENT_SOURCE_DIR}/dfs" algo_lib adjacency_graph_utils)

add_project_executable(acyclic "${CMAKE_CURRENT_SOURCE_DIR}/acyclic" algo_lib adjacency_graph_utils)
add_project_executable(dijkstra "${CMAKE_CURRENT_SOURCE_DIR}/dijkstra" algo_lib adjacency_graph_utils)
add_project_executable(floyd_warshall "${CMAKE_CURRENT_SOURCE_DIR}/floyd_warshall" algo_lib adjacency_graph_utils)
