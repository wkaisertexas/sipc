# Deliverable 5: Optimization Passes

By:

- William Kaiser (xbk6xm@virginia.edu)
- Varun Varma (kgy6hy@virginia.edu)

## Overview

In this deliverable, we added a series of code optimization passes to the compiler. To ensure the effectiveness of our optimizations, we created microbenchmarks and a benchmark script that checks if the optimizations improved performance, both in isolation and in combination with other optimizations.

Our optimizations were: 
- Constant Merging: Replaces operations on constants with the constant result.
- Inliner: Takes calls to simple functions and replaces them with the function contents.
- Loop Rotation: Gives loops a pre-header and moves the loop condition to the end. This standardizes loops and allows further optimizations.
- Loop Unrolling: Takes a loop that operations a small constant number of times and replaces it with its contents repeated that number of times.
- Inductive Variable Simplification: Takes a loop with simple arithmetic loop contents and replaces it with a single arithmetic operation that takes into account the loop length. For example, for(i : 0..n) {x = x + 2} is converted into x = x + 2 * n; 

## Workflow

When running this, Varun implemented the optimization passes and William wrote the test runner. After initially finding no improvements to these optimizations, the test runner was rewritten to have multiple trials and produce an average runtime instead of a single instance. 

## Issues

We selected our optimizations by simply trying various options and checking if they changed the generated .ll file. A lot of optimizations didn't work, but eventually we found 5 that did.

Optimizations initially had negative impacts on the performance of the optimizer. However, we determined that it wasn't a problem with our optimizations, rather it was because the some of our tests ran for an invariant number of times. For example:

```console
Running inliner sip without the inliner optimization pass
Running inliner. sip with optimizations inliner-sip: failed (before: 2.53 s, after: 3.62 s)
Running unroll. sip without the loop unrolling optimization pass
Running unroll sip with optimizations
unroll-sip: passed (before: 3.92 s, after: 3.91 s)
Number of failed benchmarks: 1
```

This was the initial script which did not produce a code improvement.

```
add_two(x) {
  return x + 2;
}

main(a) {
  var x, i;

  x = 0;
  i = 0;
  while(i < 1000000000) {
    x = add_two(a);
    i = i + 1;
  }
  
  return x;
}
```

However, this function produced a code improvement:

```console
add_two(x) {
  return x + 2;
}

main(n) {
  var i, s;
  s = 0;
  for(i : 0 .. n) {
    s = add_two(i);
    s = add_two(i);
    s = add_two(i);
    s = add_two(i);
    s = add_two(i);
  }
  return s;
}
```

We identified this issue, fixed our tests, and all our optimizations were showing performance increases.

We were trying to use auto-vectorization in my code. However, we were having issues because bounds-checking is automatically applied for each index into a loop. For this reason, the auto-vectorization passes were unable to vectorize a simple vector addition loop.

## Testing

We wrote a microbenchmark for each optimization. The test runner script (run.sh in /tests/benchmarks) uses multiple trials (either 50 or 100) to produce average runtimes. The average runtime of each microbenchmark was compared with and without the specific optimization. Additionally, all optimizations were compared to the single optimization.

The table below shows our results. In this table, the *ablation* study represents the programs performance running every other optimization pass besides the tested optimization and comparing this to running all optimizations. This allows us to determine if an optimization improved performance while being used with the other optimizations, not just in isolation. All our optimizations caused performance increases.


| Optimization               | Flag       | \# of Trials | Before | After | % Decrease | Ablation Before | Ablation After | % Decrease |
| -------------------------- | ---------- | ------------ | ------ | ----- | ---------- | --------------- | -------------- | ---------- |
| Loop Rotation              | looprotate | 20           | 0.33   | 0.31  | 7.98%      | 0.29            | 0.27           | 7.0%       |
| Constant Merging           | constmerge | 100          | 0.38   | 0.37  | 3.10%      | 0.37            | 0.00           | 100.0%     |
| Inliner                    | inliner    | 50           | 0.10   | 0.04  | 56.38%     | 0.09            | 0.02           | 78.0%      |
| Unrolling                  | unroll     | 50           | 0.18   | 0.10  | 46.83%     | 0.18            | 0.10           | 47.2%      |
| Inductive Variant Simplify | ivs        | 50           | 0.04   | 0.00  | 100.00%    | 0.04            | 0.00           | 100.0%     |

