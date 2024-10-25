# Deliverable 2: Extending the front end to support SIP

By:

- William Kaiser (xbk6xm@virginia.edu)
- Varun Varma (kgy6hy@virginia.edu)

## Overview

During this deliverable, the Tiny Imperative Programming (TIP) language had the frontend extended to support the SIP language constructs produced by the SIP grammar changes.

We added the following new AST nodes: ASTArrayExpr, ASTArrayLenExpr, ASTBoolExpr, ASTForStmt, ASTIndexingExpr, ASTTerneryExpr, and ASTUpdateStmt.

## Workflow

To complete this project, we first completed one AST node from start to finish to gain an understanding of the process. Then, we split up and completed various parts on our own, since the procedure is similar for every AST node. A markdown file [Deliverable 2](./docs/deliverables/deliverable2.md) was used to keep track of our progress.

## Challenges

Completing this project was not parallel, in the sense that one person typically had to write the full code for an ASTNode all the way through before getting feedback. Most of the work was figuring out how to do the initial ASTNode, and it was fairly straight forward to replicate from there.

## Testing

We added tests in the following places: PrettyPrinterTest, ASTNodeTest, and ASTPrinterTest. We used our document to track that every piece of code we added was tested. For nodes like the for statement, we tested each variation. We verified the completeness of our tests by running a code coverage checker, which showed that all the new code in the newly added AST nodes were tested. We also recognize that code coverage alone is not enough, because the same line might have two different effects, so we were carefully to manually check all the variations.
