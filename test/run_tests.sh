#!/bin/bash

repo_root=$(git rev-parse --show-toplevel)

cd $repo_root/build

declare -a arr=(math/test-math-core
                utils/test-utils)


for i in "${arr[@]}"
do
    ./test/unit_tests/"$i"
    # echo "$i"
done
