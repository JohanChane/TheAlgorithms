#!/bin/bash

function build {
  project_dir="$1"
  if [ -z "$project_dir" ]; then
    return
  fi

  save_wd="$(pwd)"
  cd "$project_dir"

  # ## Build
  rm -rf build

  [ ! -d build ] && mkdir build
  cd build

  # ## Generate build system
  #compiler="env CC=/usr/bin/clang CXX=/usr/bin/clang++"
  #compiler="env CC=/usr/bin/gcc CXX=/usr/bin/g++"
  cmake_option=("-G Ninja")
  cmake_option+=("-DCMAKE_EXPORT_COMPILE_COMMANDS=1")
  cmake_option+=("-DCMAKE_BUILD_TYPE=Debug")
  $compiler cmake .. ${cmake_option[*]}

  # ## Compile/Link
  cmake --build .

  cd "$save_wd"
}
