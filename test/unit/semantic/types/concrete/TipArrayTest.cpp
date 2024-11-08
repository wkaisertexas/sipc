#include "TipArray.h"
#include "TipBool.h"
#include "TipFunction.h"
#include "TipInt.h"

#include <catch2/catch_test_macros.hpp>

#include <sstream>

TEST_CASE("TipArray: Test TipArrays have a constant size"
          "[TipArray]") {
  auto term = std::make_shared<TipInt>();
  TipArray tipArray(term);

  SECTION("Equal when terms are the same") {
    auto term = std::make_shared<TipInt>();
    TipArray tipArray2(term);
    REQUIRE(tipArray == tipArray2);
  }

  SECTION("Not equal when terms are different") {
    auto term2 = std::make_shared<TipBool>();
    TipArray tipArray2(term2);

    REQUIRE_FALSE(tipArray == tipArray2);
  }
}

TEST_CASE("TipArray: Test arity is one"
          "[TipArray]") {
  auto term = std::make_shared<TipInt>();
  TipArray tipArr(term);
  REQUIRE(1 == tipArr.arity());
}

TEST_CASE("TipArray: Test output stream"
          "[TipArray]") {
  auto term = std::make_shared<TipInt>();
  TipArray tipArr(term);

  auto expectedValue = "[int]";
  std::stringstream stream;
  stream << tipArr;
  std::string actualValue = stream.str();

  REQUIRE(expectedValue == actualValue);
}
