#include "ASTArrayOfExpr.h"
#include "ASTHelper.h"

#include <catch2/catch_test_macros.hpp>

#include <iostream>

TEST_CASE("ASTAccessExprTest: Test methods of AST subtype.",
          "[ASTNodes]") {
  std::stringstream stream;
  stream << R"(
      foo() {
         return {f : 0}.f;
      }
    )";

  auto ast = ASTHelper::build_ast(stream);
  auto expr = ASTHelper::find_node<ASTAccessExpr>(ast);

  std::stringstream o1;
  o1 << expr->getField();
  REQUIRE(o1.str() == "f");

  std::stringstream o2;
  o2 << *expr->getRecord();
  REQUIRE(o2.str() == "{f:0}");
}

TEST_CASE("ASTAllocExprTest: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo() {
         return alloc 2 + 3;
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto expr = ASTHelper::find_node<ASTAllocExpr>(ast);

    std::stringstream o1;
    o1 << *expr->getInitializer();
    REQUIRE(o1.str() == "(2+3)");
}

TEST_CASE("ASTArrayLenExpr: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo(p) {
         return #p;
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto expr = ASTHelper::find_node<ASTArrayLenExpr>(ast);

    std::stringstream o1;
    o1 << *expr;
    REQUIRE(o1.str() == "(#p)");
    REQUIRE(expr->getChildren().size() == 1);
}

TEST_CASE("ASTTernaryExpr: Test methods of AST subtype.",
          "[ASTNodes]") {
   std::stringstream stream;
   stream << R"(
   foo(p) {
      return p ? 1 : 0;
   }
   )";

   auto ast = ASTHelper::build_ast(stream);
   auto expr = ASTHelper::find_node<ASTTernaryExpr>(ast);

   std::stringstream o1, o2, o3;
   o1 << *expr->getCondition();
   REQUIRE(o1.str() == "p");
   o2 << *expr->getThen();
   REQUIRE(o2.str() == "1");
   o3 << *expr->getElse();
   REQUIRE(o3.str() == "0");

   REQUIRE(expr->getChildren().size() == 3);
}

TEST_CASE("ASTAssignStmtTest: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo(p) {
         *p = 2 + 7;
         return *p - 1;
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto stmt = ASTHelper::find_node<ASTAssignStmt>(ast);

    std::stringstream o1;
    o1 << *stmt->getLHS();
    REQUIRE(o1.str() == "(*p)");

    std::stringstream o2;
    o2 << *stmt->getRHS();
    REQUIRE(o2.str() == "(2+7)");
}

TEST_CASE("ASTBinaryExprTest: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo() {
         var x;
         x = x + foo();
         return x;
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto expr = ASTHelper::find_node<ASTBinaryExpr>(ast);

    std::stringstream o1;
    o1 << *expr->getLeft();
    REQUIRE(o1.str() == "x");

    std::stringstream o2;
    o2 << *expr->getRight();
    REQUIRE(o2.str() == "foo()");

    std::stringstream o3;
    o3 << expr->getOp();
    REQUIRE(o3.str() == "+");
}

TEST_CASE("ASTBlockStmtTest: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo() {
         var x;
         if (1 > 0) {
             x = 0;
             x = 1;
         }
         return x+1;
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto stmt = ASTHelper::find_node<ASTBlockStmt>(ast);

    auto stmts = stmt->getStmts();
    REQUIRE(stmts.size() == 2);
}

TEST_CASE("ASTUpdateStmtTest: Test increment.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo() {
         var x;
         x++;
         return x+1;
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto stmt = ASTHelper::find_node<ASTUpdateStmt>(ast);
    auto arg = dynamic_cast<ASTVariableExpr*>(stmt->getArg());

   REQUIRE(stmt->getIncrement() == true);
   REQUIRE(arg != nullptr);
   REQUIRE(arg->getName() == "x");

   REQUIRE(stmt->getChildren().size() == 1);
}

TEST_CASE("ASTUpdateStmtTest: Test decrement.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo() {
         var x;
         x--;
         return x+1;
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto stmt = ASTHelper::find_node<ASTUpdateStmt>(ast);
    auto arg = dynamic_cast<ASTVariableExpr*>(stmt->getArg());

   REQUIRE(stmt->getIncrement() == false);
   REQUIRE(arg != nullptr);
   REQUIRE(arg->getName() == "x");

   REQUIRE(stmt->getChildren().size() == 1);
}

TEST_CASE("ASTDeclNodeTest: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo() {
         var x;
         return 0;
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto decl = ASTHelper::find_node<ASTDeclNode>(ast);

    REQUIRE(decl->getName() == "x");
}

TEST_CASE("ASTDeclStmtTest: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo() {
         var v1, v2, v3, v4;
         return 0;
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto stmt = ASTHelper::find_node<ASTDeclStmt>(ast);

    auto stmts = stmt->getVars();
    REQUIRE(stmts.size() == 4);
}

TEST_CASE("ASTDerefExprTest: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo(p) {
         return **p;
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto expr = ASTHelper::find_node<ASTDeRefExpr>(ast);

    std::stringstream o1;
    o1 << *expr->getPtr();
    REQUIRE(o1.str() == "(*p)");
}

TEST_CASE("ASTIndexingExprTest: Test methods of the AST subtype.", "[ASTNodes]") {
   std::stringstream stream;
   stream << R"(
      foo(p) {
         return p[1];
      }
    )";

   auto ast = ASTHelper::build_ast(stream);
   auto expr = ASTHelper::find_node<ASTIndexingExpr>(ast);

   std::stringstream o1, o2;
   o1 << *expr->getArr();
   REQUIRE(o1.str() == "p");
   o2 << *expr->getIdx();
   REQUIRE(o2.str() == "1");

   REQUIRE(expr->getChildren().size() == 2);
}

TEST_CASE("ASTErrorStmtTest: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo() {
         error 13 - 1;
         return 0;
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto stmt = ASTHelper::find_node<ASTErrorStmt>(ast);

    std::stringstream o1;
    o1 << *stmt->getArg();
    REQUIRE(o1.str() == "(13-1)");
}

TEST_CASE("ASTFieldExprTest: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo() {
         return {f : 13};
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto expr = ASTHelper::find_node<ASTFieldExpr>(ast);

    std::stringstream o1;
    o1 << expr->getField();
    REQUIRE(o1.str() == "f");

    std::stringstream o2;
    o2 << *expr->getInitializer();
    REQUIRE(o2.str() == "13");
}

TEST_CASE("ASTFunAppExprTest: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo() {
         return bar(1,2,3);
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto expr = ASTHelper::find_node<ASTFunAppExpr>(ast);

    std::stringstream o1;
    o1 << *expr->getFunction();
    REQUIRE(o1.str() == "bar");

    auto arguments = expr->getActuals();
    REQUIRE(arguments.size() == 3);
}

TEST_CASE("ASTFunctionTest: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo(x, y) {
         var z;
         var r;
         z = x - 1;
         z = z * 2;
         return x + y;
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto fun = ASTHelper::find_node<ASTFunction>(ast);

    std::stringstream o1;
    o1 << *fun->getDecl();
    REQUIRE(o1.str() == "foo");

    REQUIRE(fun->getName() == "foo");
    REQUIRE(!fun->isPoly());
    REQUIRE(fun->getFormals().size() == 2);
    REQUIRE(fun->getDeclarations().size() == 2);
    REQUIRE(fun->getStmts().size() == 3);
}

TEST_CASE("ASTIfStmtTest: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo(c) {
         var x;
         if (c > 0)
            x = 13;
         else
            x = 7;
         return x;
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto stmt = ASTHelper::find_node<ASTIfStmt>(ast);

    std::stringstream o1;
    o1 << *stmt->getCondition();
    REQUIRE(o1.str() == "(c>0)");

    std::stringstream o2;
    o2 << *stmt->getThen();
    REQUIRE(o2.str() == "x = 13;");

    std::stringstream o3;
    o3 << *stmt->getElse();
    REQUIRE(o3.str() == "x = 7;");
}

TEST_CASE("ASTIfStmtTest: No else.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo(c) {
         var x;
         x = 7;
         if (c > 0) x = 13;
         return x;
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto stmt = ASTHelper::find_node<ASTIfStmt>(ast);

    REQUIRE(stmt->getElse() == nullptr);
}

TEST_CASE("ASTInputExprTest: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo() {
         return input;
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto expr = ASTHelper::find_node<ASTInputExpr>(ast);

    REQUIRE(expr != nullptr);
}

TEST_CASE("ASTNullExprTest: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo() {
         return null;
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto expr = ASTHelper::find_node<ASTNullExpr>(ast);

    REQUIRE(expr != nullptr);
}

TEST_CASE("ASTNumberExprTest: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo() {
         return 13;
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto expr = ASTHelper::find_node<ASTNumberExpr>(ast);

    REQUIRE(expr->getValue() == 13);
}

TEST_CASE("ASTBoolExprTest: Test true.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo() {
         return true;
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto expr = ASTHelper::find_node<ASTBoolExpr>(ast);

    REQUIRE(expr->getValue());
}

TEST_CASE("ASTBoolExprTest: Test false",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo() {
         return false;
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto expr = ASTHelper::find_node<ASTBoolExpr>(ast);

    REQUIRE(!expr->getValue());
}

TEST_CASE("ASTOutputStmtTest: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo() {
         output 17;
         return 0;
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto stmt = ASTHelper::find_node<ASTOutputStmt>(ast);

    std::stringstream o1;
    o1 << *stmt->getArg();
    REQUIRE(o1.str() == "17");
}

TEST_CASE("ASTRecordExprTest: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo() {
         return {f : 0, g : 1, h : 2};
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto expr = ASTHelper::find_node<ASTRecordExpr>(ast);

    REQUIRE(expr->getFields().size() == 3);
}

TEST_CASE("ASTRefExprTest: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo() {
         var x;
         return &x;
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto expr = ASTHelper::find_node<ASTRefExpr>(ast);

    std::stringstream o1;
    o1 << *expr->getVar();
    REQUIRE(o1.str() == "x");
}

TEST_CASE("ASTReturnStmtTest: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo() {
         return 123;
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto stmt = ASTHelper::find_node<ASTReturnStmt>(ast);

    std::stringstream o1;
    o1 << *stmt->getArg();
    REQUIRE(o1.str() == "123");
}

TEST_CASE("ASTVariableExprTest: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo(x) {
         return x + 1;
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto expr = ASTHelper::find_node<ASTVariableExpr>(ast);

    REQUIRE(expr->getName() == "x");
}

TEST_CASE("ASTWhileStmtTest: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo(x) {
         var y;
         while (x > 0) {
            x = x - 1;
         }
         return {f : 0}.f;
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto stmt = ASTHelper::find_node<ASTWhileStmt>(ast);

    std::stringstream o1;
    o1 << *stmt->getCondition();
    REQUIRE(o1.str() == "(x>0)");

    std::stringstream o2;
    o2 << *stmt->getBody();
    REQUIRE(o2.str() == "{ x = (x-1); }");
}

TEST_CASE("ASTForStmtTest: Test methods of AST subtype for item-iterator version.", "[ASTNodes]") {
   std::stringstream stream;
   stream << R"(
   foo(x) {
      var x, y;
      for (i : y) {
         x = x + i;
      }
      return y;
   }
   )";

   auto ast = ASTHelper::build_ast(stream);
   auto stmt = ASTHelper::find_node<ASTForStmt>(ast);
   
   std::stringstream o1;
   o1 << *stmt->getBody();
   REQUIRE(o1.str() == "{ x = (x+i); }");

   std::stringstream o2;
   o2 << *stmt->getItem();
   REQUIRE(o2.str() == "i");

   std::stringstream o3;
   o3 << *stmt->getIterator();
   REQUIRE(o3.str() == "y");

   REQUIRE(stmt->getChildren().size() == 3);
}

TEST_CASE("ASTForStmtTest: Test methods of AST array of expr", "[ASTNodes]") {
   std::stringstream stream;
   stream << R"(
   foo(x) {
      var x, y;
      x = [1 of 2];
      return y;
   }
   )";

   auto ast = ASTHelper::build_ast(stream);
   auto stmt = ASTHelper::find_node<ASTArrayOfExpr>(ast);

   std::stringstream o;
   o << *stmt;
   REQUIRE(o.str() == "[1 of 2]");  

   REQUIRE(stmt->getChildren().size() == 2);
}


TEST_CASE("ASTForStmtTest: Test methods of AST subtype for item-range version.", "[ASTNodes]") {
   std::stringstream stream;
   stream << R"(
   foo(x) {
      var x, y;
      for (i : 1..10) {
         x = x + i;
      }
      return y;
   }
   )";

   auto ast = ASTHelper::build_ast(stream);
   auto stmt = ASTHelper::find_node<ASTForStmt>(ast);
   
   std::stringstream o1;
   o1 << *stmt->getBody();
   REQUIRE(o1.str() == "{ x = (x+i); }");

   std::stringstream o2;
   o2 << *stmt->getItem();
   REQUIRE(o2.str() == "i");

   std::stringstream o3;
   o3 << *stmt->getRangeStart();
   REQUIRE(o3.str() == "1");

   std::stringstream o4;
   o4 << *stmt->getRangeEnd();
   REQUIRE(o4.str() == "10");

   REQUIRE(stmt->getChildren().size() == 4);
}

TEST_CASE("ASTForStmtTest: Test methods of AST subtype for item-range-by version.", "[ASTNodes]") {
   std::stringstream stream;
   stream << R"(
   foo(x) {
      var x, y;
      for (i : 1..10 by 2) {
         x = x + i;
      }
      return y;
   }
   )";

   auto ast = ASTHelper::build_ast(stream);
   auto stmt = ASTHelper::find_node<ASTForStmt>(ast);
   
   std::stringstream o1;
   o1 << *stmt->getBody();
   REQUIRE(o1.str() == "{ x = (x+i); }");

   std::stringstream o2;
   o2 << *stmt->getItem();
   REQUIRE(o2.str() == "i");

   std::stringstream o3;
   o3 << *stmt->getRangeStart();
   REQUIRE(o3.str() == "1");

   std::stringstream o4;
   o4 << *stmt->getRangeEnd();
   REQUIRE(o4.str() == "10");

   std::stringstream o5;      
   o5 << *stmt->getIncrement();
   REQUIRE(o5.str() == "2");

   REQUIRE(stmt->getChildren().size() == 5);
}


TEST_CASE("ASTArrayExprTest: Test methods of AST subtype for arrays.", "[ASTNodes]") {
   std::stringstream stream;
   stream << R"(
   foo(x) {
      var x, y;
      x = [1, y, [a, b, c]]
      return x;
   }
   )";

   auto ast = ASTHelper::build_ast(stream);
   auto expr = ASTHelper::find_node<ASTArrayExpr>(ast);
   
   std::stringstream o1;
   o1 << *expr->getElements()[0];
   REQUIRE(o1.str() == "1");

   std::stringstream o2;
   o2 << *expr->getElements()[1];
   REQUIRE(o2.str() == "y");

   std::stringstream o3;
   o3 << *expr->getElements()[2];
   REQUIRE(o3.str() == "[a, b, c]");

   REQUIRE(expr->getChildren().size() == 3);

}

TEST_CASE("ASTTNotExprTest: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo(p) {
         return not (p + p);
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto expr = ASTHelper::find_node<ASTNotExpr>(ast);

    std::stringstream o1;
    o1 << *expr->getArg();
    REQUIRE(o1.str() == "(p+p)");

    REQUIRE(expr->getChildren().size() == 1);
}

TEST_CASE("ASTTNegExprTest: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo(p) {
         return -(p + p);
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto expr = ASTHelper::find_node<ASTNegExpr>(ast);

    std::stringstream o1;
    o1 << *expr->getArg();
    REQUIRE(o1.str() == "(p+p)");

    REQUIRE(expr->getChildren().size() == 1);
}