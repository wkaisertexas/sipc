# Deliverable 1

The goal of this document is to split tasks for writing unit tests and ensure we are on track with our testing and test coverage.

## Boolean type with constants true and false, unary operator not, and non-short circuiting binary operators and and or.

- [x] true should be used for a literal
- [x] false should be used as a literal
- [x] you should be able to use and and or to combine expressions
- [x] Using xor should be an invalid operation

## Array type with constructors [E1, ..., En] and [E1 of E2], a unary prefix length operator #, and a binary array element reference operator E1[E2]. Note that it is permissable to have an empty array in the first of these type constructors, e.g., []; the length of such an array is 0, i.e., #[] == 0.

- [x] Indexing into an array literal
- [x] Indexing into an array identifier
- [x] Getting the length of an array literal
- [x] Getting the length of an array
- [x] Making an array of another array
- [x] Constructing an array literal

## Arithmetic operators are extended with %, the modulo operator, and, the arithmetic negation operator.

- [x] Arithmetic negation is correctly applied and not mistaken for a minus sign
- [x] No negation takes place
- [x] The modulus operator has the same order of operations and multiplication and division
  
## Relational operators are extended with >=, <, and <=.

- [x] `>=` is a valid expression
- [x] `<=` is also a valid expression
- [x] `<` is a valid expression

## Ternary conditional expression operator E1 ? E2 : E3 which implements an if then else expression.

- [x] Ternaries parse properly
- [x] Nested ternaries parse properly
  
##  For loop using an iterator-style for (E1 : E2) S

- [X] Making a for loop with two identifiers
- [X] Making a for loop with an expression and an identifier
- [X] Making a for loop with two expressions 

# For loop using a range-style for (E1 : E2 .. E3 by E4) S, where the by E4 increment specification is optional and defaults to 1.

- [X] For loop using range based with identifiers
- [X] For loop using range based with by