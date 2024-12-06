#!/bin/bash
# Runs all benchmarks to show performance improvements with compiler optimizations

declare -r ROOT_DIR=${TRAVIS_BUILD_DIR:-$(git rev-parse --show-toplevel)}
declare -r TIPC=${ROOT_DIR}/build/src/tipc
declare -r RTLIB=${ROOT_DIR}/rtlib
declare -r SCRATCH_DIR=$(mktemp -d)

if [ -z "${TIPCLANG}" ]; then
  echo error: TIPCLANG env var must be set
  exit 1
fi

curdir="$(basename `pwd`)"
if [ "${curdir}" != "benchmarks" ]; then
  echo "Test runner must be executed in .../tipc/test/benchmarks"
  exit 1
fi

# Helper function to measure average runtime performance of a binary
measure_average_runtime() {
  local binary=$1
  local inp=$2
  local trials=$3
  local total_time=0

  for ((i = 1; i <= trials; i++)); do
    local time=$(/usr/bin/time -f "%e" "$binary" "$inp" 2>&1 | tail -n 1)
    total_time=$(echo "$total_time + $time" | bc -l)
  done

  # Calculate average runtime
  echo "scale=4; $total_time / $trials" | bc -l
}

# Helper function to run benchmarks and compare performance
# Arguments:
#   $1: Benchmark name (e.g., "inliner")
#   $2: Optimized flag
#   $3: Input
#   $4: Number of trials
run_benchmark() {
  local name=$1
  local optimized_flag=$2
  local inp=$3
  local trials=$4
  local unoptimized_flag=$5

  # Unoptimized test.
  echo "Running ${name} without optimizations (${unoptimized_flag})"
  ${TIPC} -asm ${name}.sip
  mv ${name}.sip.ll ${name}_no_opt.sip.ll
  ${TIPC} ${name}.sip
  ${TIPCLANG} -w ${name}.sip.bc ${RTLIB}/tip_rtlib.bc -o ${name}_no_opt
  local before_time=$(measure_average_runtime ./${name}_no_opt $inp $trials)

  # Optimized test.
  echo "Running ${name} with optimizations (${optimized_flag})"
  ${TIPC} -asm ${optimized_flag} ${name}.sip
  ${TIPC} ${optimized_flag} ${name}.sip
  ${TIPCLANG} -w ${name}.sip.bc ${RTLIB}/tip_rtlib.bc -o ${name}_opt
  local after_time=$(measure_average_runtime ./${name}_opt $inp $trials)

  # Compare average runtimes.
  if (( $(echo "$after_time < $before_time" | bc -l) )); then
    echo "${name}: passed (average before: $before_time s, after: $after_time s)"
  else
    echo "${name}: failed (average before: $before_time s, after: $after_time s)"
    ((failed_benchmarks++))
  fi

  # Check if the .ll files are different.
  if diff -q "${name}_no_opt.sip.ll" "${name}.sip.ll" > /dev/null; then
    echo "Error: The .ll files are not different."
  fi

  # Remove files afterwards.
  rm -f ${name}_no_opt ${name}_opt ${name} ${name}.sip.bc
  #rm -f ${name}_no_opt.sip.ll ${name}.sip.ll
  
  echo ""
}

# Variables
failed_benchmarks=0

echo "Running benchmarks in isolation"

# Run benchmarks in isolation
run_benchmark "looprotate" "--looprotate" 750 20 ""
run_benchmark "constmerge" "--constmerge" 100000000 100 ""
run_benchmark "inliner" "--inliner" 10000000 50 ""
run_benchmark "unroll" "--unroll" 10000000 50 ""
run_benchmark "ivs" "--ivs" 10000000 50 ""

echo "Running bechmarks with all optimizations enabled"

# Run benchmarks
run_benchmark "looprotate" "--looprotate --unroll" 750 20 "--unroll --inliner --ivs" # using unroll is fair because that is also a significant loop optimization
run_benchmark "constmerge" "--constmerge --inliner --unroll --ivs --looprotate" 100000000 150 "--inliner --unroll --ivs --looprotate"
run_benchmark "inliner" "--inliner --unroll --ivs --constmerge --looprotate" 10000000 50 "--unroll --ivs --constmerge --looprotate"
run_benchmark "unroll" "--unroll --inliner --ivs --constmerge --looprotate" 10000000 50 "--inliner --ivs --constmerge --looprotate"
run_benchmark "ivs" "--ivs --inliner --unroll --constmerge --looprotate" 10000000 50 "--inliner --unroll --constmerge --looprotate"

echo "Number of failed benchmarks: ${failed_benchmarks}"

