# Deliverable 4: Code Generation

By:

- William Kaiser (xbk6xm@virginia.edu)
- Varun Varma (kgy6hy@virginia.edu)

## Overview

In this project, we implement code generation for the sipc language extension. This consisted of writing new codegen functions and fixing a few segmentation faults we had found with the old line annotator. To the surprise of no one global variables were the cause.

## Workflow

When working on this project, the instability of the test runner made us very hesitant to make any changes which were not 100% end-to-end working. Varun made a bunch of changes which had to be reverted to ensure that they were not causing issues and then go one-by-one through implementing statements in the test.

One of the things that was insisted upon was using int64 as a boolean type which, all though wasteful, made sure that any type correct program could have the exact same process for codegen when generating arrays.

## Issues

One interesting bug that was found was the following:

```
x[0] = 1;
```

In this bug, the l-value of the `x[0]` needs to be found. However, this also generated the l-value of `x` which refers to the location of the pointer which points to the array. However, this is not what we want. Instead, we want the l-value of the entire expression which is the r-value of `x` and the l-value of the first index of x. Overall, this was something fairly tricky to figure out.

## Testing

A test per unimplemented codegen statement was created to ensure features were working as intended. These tests used the `error` statement as an assertion to check the properties of the generated. Finally, sample sip programs from the zip-file located on canvas were also included as tests. All tests which worked out-of-the-box were added first and then the others were debugged one-by-one. All the errors we found were obscure parser errors, not anything related to codegen or type checking.

As always, we double checked the completeness of our tests by using the code coverage report.