#include "ExceptionContainsWhat.h"
#include "FrontEnd.h"
#include "ParseError.h"
#include "ParserHelper.h"
#include <iostream>
using namespace std;

#include <catch2/catch_test_macros.hpp>

TEST_CASE("SIP Parser: conditionals", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
      short() {
        var x, y, z;
        if (x >= 0) {
          while (y <= z) {
            y = y + 1;
          }
        } else {
          z = z + 1;
        }
        return z;
      }
    )";

  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: operators", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
      operators() {
        var x;
        x = x % 1;
        x = x and 1;
        x = x or 1;
        x = x | 1;
        x = x & 1;
        x = x >= 1;
        x = x <= 1;
        x = x < 1;
        x = x > 1;
        x = not x;
        x = #x;
        return x;
      }
    )";

  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: arrays", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
      r() { 
        var x, y; 
        x = [1, 2, 3, 4, 5]; 
        y = #x; 
        y = x[0]; 
        y = [1, 2, 3][1]; 
        return x; 
      }
    )";

  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: ternary expr", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
      fn1() { 
        var x, y; 
        x = x ? x : y; 
        return x + y; 
      }
      fn2() { 
        var x, y; 
        x = x ? x ? x : y : y; 
        return x + y; 
      }
    )";

  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: bool literals", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
      main() { 
        var x, y; 
        x = true; 
        y = false; 
        return x and y; 
      }
    )";

  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: boolean logic", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
      main() { 
        var x, y; 
        x = true; 
        x = x and y or x | y; 
        return x;
      }
    )";

  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: plusplus and minus minus stmts", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
      main() { 
        var x, y; 
        x++; 
        y--; 
        return x + y; 
      }
    )";

  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SUP Parser: Multiplication and modulo have same precedence. ", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(main() { return x * x % x;})";
  std::string expected = "(expr (expr (expr x) * (expr x)) % (expr x))";
  std::string tree = ParserHelper::parsetree(stream);
  REQUIRE(tree.find(expected) != std::string::npos);

  stream << R"(main() { return x % x * x;})";
  std::string expected2 = "(expr (expr (expr x) % (expr x)) * (expr x))";
  std::string tree2 = ParserHelper::parsetree(stream);
  REQUIRE(tree2.find(expected2) != std::string::npos);
}


TEST_CASE("SUP Parser: Negation and not have higher precedence.", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(main() { return a + -b % not c; })";
  std::string expected = "(expr (expr a) + (expr (expr - (expr b)) % (expr not (expr c))))";
  std::string tree = ParserHelper::parsetree(stream);
  REQUIRE(tree.find(expected) != std::string::npos);
}

TEST_CASE("SUP Parser: Array length has higher precedence.", "[TIP Parser]") {
  std::stringstream stream;
  stream << R"(main() { return #a + b; })";
  std::string expected = "(expr (expr # (expr a)) + (expr b))";
  std::string tree = ParserHelper::parsetree(stream);
  REQUIRE(tree.find(expected) != std::string::npos);
}

TEST_CASE("SUP Parser: Relational operators have higher precedence than equality operators.", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(main() { return a == b < c; })";
  std::string expected = "(expr (expr a) == (expr (expr b) < (expr c)))";
  std::string tree = ParserHelper::parsetree(stream);
  REQUIRE(tree.find(expected) != std::string::npos);
}

TEST_CASE("SUP Parser: Ternery if statement precedence.", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(main() { return x ? x ? 1 : 2 : 3; })";
  std::string expected = "(expr (expr x) ? (expr (expr x) ? (expr 1) : (expr 2)) : (expr 3))";
  std::string tree = ParserHelper::parsetree(stream);
  REQUIRE(tree.find(expected) != std::string::npos);
}

TEST_CASE("SIP Parser: For loop with two identifiers", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
      fn() {
        for(i : x) {
        }
        return 1;
      }
    )";

  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: For loop with identifer and expression", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
      fn() {
        for(i : []) {
        }
        return 1;
      }
    )";

  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: For loop with expression and identifer", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
      fn() {
        for(a[i] : x) {
        }
        return 1;
      }
    )";

  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: For loop with two expressions", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
      fn() {
        for(a[i] : []) {
        }
        return 1;
      }
    )";

  REQUIRE(ParserHelper::is_parsable(stream));
}


TEST_CASE("SIP Parser: For loop with range", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
      fn() {
        for(i : 1..2) {
        }
        return 1;
      }
    )";

  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: For loop with range as identifiers", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
      fn() {
        for(i : x..y) {
        }
        return 1;
      }
    )";

  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: For loop with expression increment", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
      fn() {
        for(i : x..y by 2) {
        }
        return 1;
      }
    )";

  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: For loop with identifer increment", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
      fn() {
        for(i : x..y by z) {
        }
        return 1;
      }
    )";

  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: For loop with no curly brackets", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
      fn() {
        var x;
        for(i : x) x = x + 1;
        for(i : x..y) x = x + 1;
        for(i : x..y by z) x = x + 1;
        return 1;
      }
    )";

  REQUIRE(ParserHelper::is_parsable(stream));
}

/************ The following are expected to fail parsing ************/

TEST_CASE("SIP Parser: unbalanced logical expression", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
      operators() { var x; x = y and or 1; return x; }
    )";

  REQUIRE_FALSE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: unbalanced non-short-circuiting expression", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
      operators() { var x; x = x & | 1; return x; }
    )";

  REQUIRE_FALSE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: xor (short circuiting expression is not supported)", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
      operators() { var x; x = y ^ 1; return x; }
    )";

  REQUIRE_FALSE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: For loop without suffecient arguments fail", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
      fn() {
        for(i) {
        }
        return 1;
      }
    )";

  REQUIRE_FALSE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: For loop without suffecient arguments fail 2", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
      fn() {
        for() {
        }
        return 1;
      }
    )";

  REQUIRE_FALSE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: Ternery conditional without inputs.", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
      fn() {
        x = ? : ;
        return 1;
      }
    )";

  REQUIRE_FALSE(ParserHelper::is_parsable(stream));
}