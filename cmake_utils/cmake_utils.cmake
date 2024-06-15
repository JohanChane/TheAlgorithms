# config
set(cfg_hdr_suffix "h")

function(config_c)
  set(cfg_src_suffix "c" PARENT_SCOPE)

  config_c_compiler()
  config_project()
endfunction()

function(config_cpp)
  set(cfg_src_suffix "cc" PARENT_SCOPE)

  config_cpp_compiler()
  config_project()
endfunction()

function(config_c_compiler)
  set(CMAKE_C_STANDARD 11)
  set(CMAKE_C_COMPILER "gcc")
  #set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
endfunction()

function(config_cpp_compiler)
  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_COMPILER "g++")
  #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endfunction()

function(config_project)
  #set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
  #set(CMAKE_BUILD_TYPE Release)
endfunction()

function(add_project_library library_name library_type source_dir)
  file(GLOB_RECURSE srcs "${source_dir}/*.${cfg_src_suffix}")
  file(GLOB_RECURSE hdrs "${source_dir}/*.${cfg_hdr_suffix}")

  if(library_type STREQUAL "INTERFACE")
    add_library(${library_name} INTERFACE)
    if(srcs)
      target_sources(${library_name} INTERFACE ${srcs})
    else()
      target_sources(${library_name} INTERFACE ${hdrs})
    endif()
    target_include_directories(${library_name} INTERFACE ${source_dir})
  elseif(library_type STREQUAL "STATIC" OR library_type STREQUAL "SHARED")
    add_library(${library_name} ${library_type} ${srcs})
    target_include_directories(${library_name} PUBLIC ${source_dir})
  else()
    message(FATAL_ERROR "Unknown library type: ${library_type}")
  endif()
endfunction()

# usage: add_project_executable(executable_name source_dir lib1 lib2 ...)
function(add_project_executable executable_name source_dir)
  file(GLOB_RECURSE srcs "${source_dir}/*.${cfg_src_suffix}")
  add_executable(${executable_name} ${srcs})
  target_link_libraries(${executable_name} ${ARGN})
endfunction()

# 将指定目录下的每个 .cc 文件对应生成一个可执行文件
function(add_exes_from_directory dir)
  file(GLOB srcs "${dir}/*.${cfg_src_suffix}")

  foreach(src ${srcs})
    get_filename_component(exe_name ${src} NAME_WE)
    add_executable(${exe_name} ${src})
  endforeach()
endfunction()

function(add_custom_run_target target)
  add_custom_target(run_${target} ALL 
    COMMAND ${CMAKE_COMMAND} -E echo "Executing ${target}..."
    COMMAND $<TARGET_FILE:${target}>
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    DEPENDS ${target}
  )
endfunction()

function(run_run_shell target deps)
  add_custom_target(run_${target} ALL 
    COMMAND ${CMAKE_COMMAND} -E echo "Executing ${target}..."
    COMMAND env BINARY_DIR=${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/run.sh
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDS ${deps}
  )
endfunction()
