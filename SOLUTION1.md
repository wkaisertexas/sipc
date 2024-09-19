# Deliverable 1: Extending the TIP parser to the SIP parser

By:

- William Kaiser (xbk6xm@virginia.edu)
- Varun Varma (kgy6hy@virginia.edu)

## Overview

During this project, the Tiny Imperative Programming (TIP) Language had the grammar used be extended to the SIP language constructs. 

## Challenges

When developing the grammar, an error with left recursion causing ternaries to not be parsed correctly. The ternary as added in a similar way to `recordExpr` or `arrayExpr`. However, adding a ternary as part of `expr` itself eliminated the left-recursion present.

```console
expr : expr '(' (expr (',' expr)*)? ')' 	#funAppExpr
     | expr '.' IDENTIFIER 			#accessExpr
     | '*' expr 				#deRefExpr
     | SUB NUMBER				#negNumber
     | '&' expr					#refExpr
     | expr op=(MUL | DIV | MOD) expr 		#multiplicativeExpr
     | expr op=(ADD | SUB) expr 		#additiveExpr
     | expr op=(GT | LTE | GTE | LT) expr 				#relationalExpr
     | expr op=(EQ | NE) expr 			#equalityExpr
     | expr '?' expr ':' expr   #ternaryExpr
     | '#' IDENTIFIER           #arrayLength
     | '#' arrayExpr            #arrayLengthLiteral
     | expr '[' expr ']' #arrayIndexingExpr
     | IDENTIFIER				#varExpr
     | NUMBER					#numExpr
     | KINPUT					#inputExpr
     | KALLOC expr				#allocExpr
     | KNULL					#nullExpr
     | op=(KTRUE | KFALSE)      #boolExpr
     | SUB expr                 #negExpr
     | KNOT expr                #not
     | recordExpr				#recordRule
     | arrayExpr                #arrayLiteral
     | expr op=(LOR | LAND) expr #nonShortCircuiting
     | expr op=(KAND | KOR) expr #boolOps
     | '(' expr ')'				#parenExpr
;

recordExpr : '{' (fieldExpr (',' fieldExpr)*)? '}' ;

arrayExpr : '[' (expr (',' expr)*)? ']'
          | '[' expr KOF expr ']' ;

fieldExpr : IDENTIFIER ':' expr ;
```

## Workflow

Development of the grammar was completed in the [ANTLR Lab](http://lab.antlr.org/) to rapidly make changes without needing to rebuild the project each time. In addition to being faster to prototype, using the ANTLR lab ensured that certain features of the new language, namely, nested ternaries were parsed properly.

For example, the following SIP program was parsed into:

```c
fn2() { 
     var x, y;
     x = x ? x ? x : y : y; 
     return x + y; 
}
```

![Document tree of the SIP program](./docs/assets/summaries/nested-ternaries-parse-tree.png)

## Testing

A markdown file [Deliverable 1](./docs/deliverables/deliverable1.md) was used as a working document to coordinate the delegation of testing between the group members. While the scope of all tests was followed as initially described, a few tests were merged using the existing tests in `TIPParserTest.cpp` expressed the same pattern. For instance, a general test `SIP Parser: operators` was used to test multiple operators in a single test.