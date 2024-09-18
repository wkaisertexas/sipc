# Deliverable 1

The goal of this document is to split tasks for writing unit tests and ensure we are on track with our testing and test coverage.

## Boolean type with constants true and false, unary operator not, and non-short circuiting binary operators and and or.

- [ ] true should be used for a literal
- [ ] false should be used as a literal
- [ ] you should be able to use and and or to combine expressions
- [ ] Using xor should be an invalid operation

## Array type with constructors [E1, ..., En] and [E1 of E2], a unary prefix length operator #, and a binary array element reference operator E1[E2]. Note that it is permissable to have an empty array in the first of these type constructors, e.g., []; the length of such an array is 0, i.e., #[] == 0.

- [ ] Indexing into an array literal
- [ ] Indexing into an array identifier
- [ ] Getting the length of an array literal
- [ ] Getting the length of an array
- [ ] Making an array of another array
- [ ] Constructing an array literal

## Arithmetic operators are extended with %, the modulo operator, and, the arithmetic negation operator.

- [ ] Arithmetic negation is correctly applied and not mistaken for a minus sign
- [ ] No negation takes place
- [ ] The modulus operator has the same order of operations and multiplication and division
  
## Relational operators are extended with >=, <, and <=.

- [ ] `>=` is a valid expression
- [ ] `<=` is also a valid expression
- [ ] `<` is a valid expression

## Ternary conditional expression operator E1 ? E2 : E3 which implements an if then else expression.

- [ ] Ternaries parse properly
- [ ] Nested ternaries parse properly
  
##  For loop using an iterator-style for (E1 : E2) S

- [ ] Making a for loop with two identifiers
- [ ] Making a for loop with an expression and an identifier
- [ ] Making a for loop with two expressions 

# For loop using a range-style for (E1 : E2 .. E3 by E4) S, where the by E4 increment specification is optional and defaults to 1.

- [ ] For loop using range based with identifiers
- [ ] For loop using range based with by