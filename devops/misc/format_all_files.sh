#! /bin/bash

# вызов конфигурационного скрипта для дополнительных переменных
# "./config.sh" @todo:
src_root="/home/rouvald/work/simple_vector"

# ========== НАЧАЛО ==========
declare -a paths=(
    "simple_vector_lib"
    "test"
)

for path in "${paths[@]}";
do
    for file in $(find "${src_root}/${path}" -type f \( -name "*.cpp" -o -name "*.c" -o -name "*.h" -o -name "*.hpp" \));
    do
        echo "${file}"
        clang-format -i -style=file ${file}
    done
done

# prevent closing console
# read