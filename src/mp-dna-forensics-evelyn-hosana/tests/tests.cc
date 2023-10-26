#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
#include <catch/catch.hpp>
#include <string>

#include "functions.hpp"

TEST_CASE("No match", "[case-1]") {
  bool something = false;
  REQUIRE(something == true);
}
