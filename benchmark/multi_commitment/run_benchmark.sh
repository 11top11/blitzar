#!/bin/bash

EXEC_CMD="bazel run -c opt //benchmark/multi_commitment:benchmark"

############################################

verbose=1
backend="cpu"
results_dir="benchmark/multi_commitment/.results/"

word_sizes=("4")

# word_sizes=("1" "4" "8" "16" "32")
# cols=("10" "100" "1000")
# rows=("10" "100" "1000" "10000" "10000")

cols=("10" "100" "1000")
rows=("10" "100" "1000" "10000")

mkdir -p ${results_dir}

# Run all the benchmarks
for ws in ${word_sizes[@]}; do
    for c in ${cols[@]}; do
        for r in ${rows[@]}; do
            curr_benchmark_file="${results_dir}/${ws}_${c}_${r}.out"
            ${EXEC_CMD} -- ${backend} ${c} ${r} ${ws} ${verbose} > ${curr_benchmark_file}
        done
    done
done

# Extract the duration time of each benchmark
for ws in ${word_sizes[@]}; do
    echo word_size=${ws}

    for c in ${cols[@]}; do
        for r in ${rows[@]}; do
            curr_benchmark_file="${results_dir}/${ws}_${c}_${r}.out"
            IFS=':'; read -a line_arr <<< $(awk '{if(NR==6) print $0}' ${curr_benchmark_file});            
            echo ${line_arr[1]}
        done
    done
done