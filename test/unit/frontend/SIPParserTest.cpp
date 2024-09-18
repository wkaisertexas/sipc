#include "ExceptionContainsWhat.h"
#include "FrontEnd.h"
#include "ParseError.h"
#include "ParserHelper.h"

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
        return x;
      }
    )";

  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: arrays", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
      r() { var x, y; x = [1, 2, 3, 4, 5]; y = #x; y = x[0]; y = [1, 2, 3][1]; return x; }
    )";

  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: ternary expr", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
      fn1() { var x, y; x = x ? x : y; return x + y; }
      fn2() { var x, y; x = x ? x ? x : y : y; return x + y; }
    )";

  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: bool literals", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
      main() { var x, y; x = true; y = false; return x + y; }
    )";

  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: boolean logic", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
      main() { var x, y; x = true; x = x and y or x | y; return x + y; }
    )";

  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: plusplus and minus minus stmts", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
      main() { var x, y; x++; y--; return x + y; }
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