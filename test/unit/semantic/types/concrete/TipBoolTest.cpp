#include "TipBool.h"
#include "TipVar.h"

#include <catch2/catch_test_macros.hpp>

#include <sstream>
#include <string>

TEST_CASE("TipBool: test TipBool is a TipCons"
          "[tip_bool]") {
  TipBool t;
  REQUIRE_FALSE(nullptr == dynamic_cast<TipCons *>(&t));
}

TEST_CASE("TipBool: test TipBool is a TipType"
          "[tip_bool]") {
  TipBool t;
  REQUIRE_FALSE(nullptr == dynamic_cast<TipType *>(&t));
}

TEST_CASE("TipBool: test args is empty", "[tip_bool]") {
  TipBool t;
  REQUIRE(t.getArguments().empty());
}

TEST_CASE("TipBool: test toString returns bool", "[tip_bool]") {
  TipBool t;
  std::stringstream stream;
  stream << t;
  REQUIRE("bool" == stream.str());
}

TEST_CASE("TipBool: test all TipBools are equal", "[tip_bool]") {
  TipBool t1;
  TipBool t2;
  REQUIRE(t1 == t2);
}
