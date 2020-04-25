// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <cinder/Rand.h>

#include <mylibrary/matrixsolver.h>


TEST_CASE("Random sanity test", "[random]") {
  const float random = cinder::randFloat();
  REQUIRE(0. <= random);
  REQUIRE(random <= 1.);
}

TEST_CASE("Test matrix solver"){
    string input = "1.13, 123.2130, 213\n14351.14321,12837.970,219830.9\n21,213,219";
    auto mat = matrixsolver::StringToMat(input);
    REQUIRE(mat(1,1) == 12837.97f);
    REQUIRE(mat(1,0) == 14351.14321f);
    REQUIRE(mat(2,1) == 213.0f);

    string input1 = "1.13, 123.2130, 213\n14351.14321,12837.970,219830.9\n21,213,";
    REQUIRE_THROWS(matrixsolver::StringToMat(input1));
}

