#!/bin/bash

T=(1 2 4 8)
I=5

make all > /dev/null

file=data-$(date +"%Y-%m-%d-%H-%M")

echo $'locktype\tthreads\ttests\tcost time' >> ../../data/$file 2>&1

for i in ${T[@]}; do
    taskset ff ./bench mutex ${i} ${I} >> ../../data/$file 2>&1
done

for i in ${T[@]}; do
    taskset ff ./bench spinlock ${i} ${I} >> ../../data/$file 2>&1
done

# echo "testing wrlock..."

# for i in ${W[@]}; do
#     taskset ff ./perf_rwlock ${T} ${i}
# done