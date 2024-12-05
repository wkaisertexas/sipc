#!/bin/bash

num_runs=$1
shift
command="$@"

total_time=0

echo "Running '$command' $num_runs times..."
for i in $(seq 1 $num_runs); do
    start_time=$(date +%s%3N)
    eval $command
    end_time=$(date +%s%3N)
    elapsed_time=$((end_time - start_time))

    echo "Run #$i: ${elapsed_time}ms"
    total_time=$((total_time + elapsed_time))
done

# Calculate average time
average_time=$((total_time / num_runs))

echo "Average time: ${average_time}ms"