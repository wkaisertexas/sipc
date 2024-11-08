# Deliverable 3: Weeding Pass, Type System, Type Constraints

By:

- William Kaiser (xbk6xm@virginia.edu)
- Varun Varma (kgy6hy@virginia.edu)

## Overview

In this project, we extended the Tiny Imperative Programming (TIP) language's weeding pass, type system, and type constraints to support the new features from the Simple Imperative Programming (SIP) language. This included adding support for arrays, booleans, for-loops, ternary expressions, logical operators, and array indexing in the type checking and weeding passes.

## Workflow

We started by picking one of the new constructs—the ternary expression—to update in the type checker and weeding pass. This helped us understand what changes were needed. After that, we divided the remaining constructs between us so we could work on them in parallel. We used a shared markdown document to keep track of our progress and coordinate our work.

## Challenges

One major challenge we faced was that the substitutor wasn't updated to handle the new AST nodes we added. This caused segmentation faults originating from the copier node during type checking. It took us over 4 hours to debug this issue because the error messages didn't point us in the right direction. Once we realized that the substitutor needed cases for the new nodes, we updated it, and that fixed the problem.

We also had to make sure the type constraints for the new constructs were correct. For example, with the ternary operator, we needed to ensure that the condition is a boolean and that both possible results are of the same type. Similarly, for array indexing, we had to enforce that the index is an integer and that the result type matches the array's element type.

## Testing

We wrote tests for each added type and used the coverage report to ensure that coverage was present for each line of added code.

The coverage report was the primary driver of testing, but in addition a checklist was made to make sure that each node was covered. Overall, a mix of positive and negative tests were created for each added node.

## Conclusion

By the end of this deliverable, we successfully extended the TIP language to support the new SIP constructs in both the weeding pass and the type system. Despite some tough challenges, especially with the substitutor causing segmentation faults, we managed to figure them out and get everything working. Our thorough testing gave us confidence that the new features are correctly integrated into the compiler.