// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <cinder/Rand.h>

#include <mylibrary/matrixsolver.h>
#include <mylibrary/util.h>


TEST_CASE("Random sanity test", "[random]") {
    const float random = cinder::randFloat();
    REQUIRE(0. <= random);
    REQUIRE(random <= 1.);
}

TEST_CASE("Test matrix solver") {
    string input = "1.13, 123.2130, 213\n14351.14321,12837.970,219830.9\n21,213,219";
    auto mat = util::StringToMat(input);
    REQUIRE(mat(1, 1) == 12837.97f);
    REQUIRE(mat(1, 0) == 14351.14321f);
    REQUIRE(mat(2, 1) == 213.0f);

    string input1 = "1.13, 123.2130, 213\n14351.14321,12837.970,219830.9\n21,213,";
    REQUIRE_THROWS(util::StringToMat(input1));
}

TEST_CASE("rref") {

    double A[5][4] = {
            {16, 2,  3,  13},
            {5,  11, 10, 8},
            {9,  7,  6,  12},
            {4,  14, 15, 1},
            {13, 21, 21, 13}};
    vector<vector<double>> a(5);
    for (int i = 0; i < 5; i++)
        a[i] = vector<double>(A[i], A[i] + 4);
    int rank = matrixsolver::RrefHelper(a);
    REQUIRE(rank == 3);
}

