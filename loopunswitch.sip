/*
 * Benchmark for loop invariant code motion (LICM) optimization.
 * 
 * Compile with and without the -licm optimization then run:
 *   time ./licm 10000
 * to observe the execution time of the benchmark.
 * You should be able to see a 4x speedup with LICM.
 */
main(n) {
  var i, r, v;
  i = 0;
  v = 42;
  while (n > i) {
    r = hoist(n, v);
    i = i + 1;
  }
  return 0;
}
hoist(n, v) {
  var r, i;
  i = 0;
  r = 0;
  while (n > i) {
    r = r + (v*v-v*v+v*v+v/2*v-v*v);
    i = i + 1;
  }
  return r;
}