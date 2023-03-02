
#!/bin/bash

#获取脚本的绝对执行路径
##echo "${BASH_SOURCE[0]}"
##echo "${BASH_SOURCE}"
##echo "$(dirname "${BASH_SOURCE[0]}")"
##echo "$( cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

cd "$(dirname "${BASH_SOURCE[0]}")/.." >/dev/null 2>&1  ||exit
WORKDIR=$(echo $(dirname "${BASH_SOURCE[0]}"))
echo "Current work dir is ${WORKDIR} vs pwd:$(pwd)"
#cd ${WORKDIR}

function parse()
{
for argv in $*;do
    case ${argv} in
    clean)
        rm -rf build;
        echo "clean build"
        ;;
    -opt=*|--lang-opt=*)
        VAR=${argv#*=}
        ;;
    *)
        ;;
    esac 
done
}

parse $*


cmake -B build
cmake --build build -j$(nproc);
