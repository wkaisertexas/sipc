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

Completing this project was embarassingly not parallel. High degrees of coordination were required when writing this project to make sure that the work was completed properly.

## Testing

We added tests in the following places: PrettyPrinterTest, ASTNodeTest, and ASTPrinterTest.
We used code coverage to determine the effectiveness of codes. 
