#!/bin/bash

WORKDIR=$(echo $(pwd))
echo "Current work dir is ${WORKDIR}"
cd ${WORKDIR}

function parse()
{
for argv in $*;do
    case ${argv} in
    clean)
        rm -rf build;
        echo "clean build"
        ;;
    *)
        ;;
    esac 
done
}

parse $*


cmake -B build
cmake --build build -j$(nproc);
