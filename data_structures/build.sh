#!/bin/bash

#set -e
#set -x

script_dir=$(dirname "$(readlink -f "$0")")
project_dir="${script_dir}/.."
source $project_dir/shell_utils/build.sh

cd $script_dir
build $script_dir
