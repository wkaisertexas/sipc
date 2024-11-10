# Deliverable 3: Weeding Pass, Type System, Type Constraints

By:

- William Kaiser (xbk6xm@virginia.edu)
- Varun Varma (kgy6hy@virginia.edu)

## Overview

In this project, we extended the Tiny Imperative Programming (TIP) language's weeding pass, type system, and type constraints to support the new features from the Simple Imperative Programming (SIP) language. This included adding support for arrays, booleans, for-loops, ternary expressions, modulo, logical operators, and array indexing in the type checking and weeding passes.

## Workflow

We started by picking one of the new constructs—the ternary expression—to update in the type checker and weeding pass. This helped us understand what changes were needed. After that, we divided the remaining constructs between us so we could work on them in parallel. We used a shared markdown document to keep track of our progress and coordinate our work.

## Challenges

The major problem that we had was that we didn't realize that there needed to be changes to Substitutor and TipCons in order to accomodate the new TipArray variable. This lead to a lot of time wasted looking through the debugger trying to figure out why the unifier was seg-faulting. We eventually figured it out by searching for all instances of a similar type TipRef and realizing that there was unimplemented code. We also had issues with the linker when modifying the weeding pass to 


We ended up submitting this project late. This was because we got a decent amount of work done on the project early in the time period and left the last bit til later, not realizing it would be far more time consuming than the rest of the project put together. In the future, we will try to finish the project the first week instead of leaving it for the second.

## Testing

We wrote tests for each added type and used the coverage report to ensure that coverage was present for each line of added code. Specifically, we added tests in TypeConstraintCollectTest, but also individual tests for TipBool and TipArray as well as a test in UnifierTest. Our strategy was to put as little type information as possible per test program to ensure that the type system is inferring properly. This allowed us to mostly use one test per feature, though some more complex features required more tests to verify they were sound. We used a checklist to ensure every new feature was tested, and we verified it with the coverage report at the end,

## Conclusion

By the end of this deliverable, we successfully extended the TIP language to support the new SIP constructs in both the weeding pass and the type system. Despite some tough challenges, especially with the substitutor causing segmentation faults, we managed to figure them out and get everything working. Our thorough testing gave us confidence that the new features are correctly integrated into the compiler.