# Deliverable 5: Optimization Passes

By:

- William Kaiser (xbk6xm@virginia.edu)
- Varun Varma (kgy6hy@virginia.edu)

## Overview

In this deliverable, code optimization passes were added to the compiler. After this, benchmarks were created and ran to ensure a performance improvement.

## Workflow

When running this, Varun implemented the optimization passes and then William wrote the test runner. After initially finding no improvements to these optimizations, the test runner was rewritten to have multiple trials.

## Issues

Optimizations initially had negative impacts on the performance of the optimizer. However, in our testing, it was determined that weird interactions with the input variable caused 

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

From this information, it was determined that none of our optimization tests should include arguments to main as inputs to functions as this seemed to mess with the optimizer.

I was trying to use auto-vectorization in my code. However, I was having issues because bounds-checking is automatically applied for each index into a loop. For this reason, the autovectorization passes were unable to vectorize a simple vector addition loop.

## Testing

The test runner created uses multiple trials (either 50 or 100) to test the differences. The runtime of each sample program was compared with and without the specific optimization. Additionally, all optimizations were compared to the single optimization.