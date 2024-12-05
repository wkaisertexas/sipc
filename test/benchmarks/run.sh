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

# Helper function to measure runtime performance of a binary
measure_runtime() {
  /usr/bin/time -f "%e" "$@" 2>&1 | tail -n 1
}

# Variables
failed_benchmarks=0

# Test inliner.sip
echo "Running inliner.sip without the inliner optimization pass"
${TIPC} -do inliner.sip
${TIPCLANG} -w inliner.sip.bc ${RTLIB}/tip_rtlib.bc -o inliner
before_time=$(measure_runtime ./inliner "$@" 2>/dev/null)

echo "Running inliner.sip with optimizations"
${TIPC} --inliner inliner.sip
${TIPCLANG} -w inliner.sip.bc ${RTLIB}/tip_rtlib.bc -o inliner
after_time=$(measure_runtime ./inliner "$@" 2>/dev/null)

if (( $(echo "$after_time < $before_time" | bc -l) )); then
  echo "inliner.sip: passed (before: $before_time s, after: $after_time s)"
else
  echo "inliner.sip: failed (before: $before_time s, after: $after_time s)"
  ((failed_benchmarks++))
fi

# Test unroll.sip
echo "Running unroll.sip without the loop unrolling optimization pass"
${TIPC} unroll.sip
${TIPCLANG} -w unroll.sip.bc ${RTLIB}/tip_rtlib.bc -o unroll
before_time=$(measure_runtime ./unroll "$@" 2>/dev/null)

echo "Running unroll.sip with optimizations"
${TIPC} --unroll unroll.sip
${TIPCLANG} -w unroll.sip.bc ${RTLIB}/tip_rtlib.bc -o unroll
after_time=$(measure_runtime ./unroll "$@" 2>/dev/null)

if (( $(echo "$after_time < $before_time" | bc -l) )); then
  echo "unroll.sip: passed (before: $before_time s, after: $after_time s)"
else
  echo "unroll.sip: failed (before: $before_time s, after: $after_time s)"
  ((failed_benchmarks++))
fi

echo "Number of failed benchmarks: ${failed_benchmarks}"
