// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <cinder/Rand.h>

#include <mylibrary/matrixsolver.h>
#include <mylibrary/util.h>

TEST_CASE("Test String to Mat", "[StringToMat]") {
    string input = "1.13, 123.2130, 213\n14351.14321,12837.970,219830.9\n21,213,219";
    auto mat = util::StringToMat(input);
    REQUIRE(mat(1, 1) == 12837.97);
    REQUIRE(mat(1, 0) == 14351.14321);
    REQUIRE(mat(2, 1) == 213.0);

    string input1 = "1.13, 123.2130, 213\n14351.14321,12837.970,219830.9\n21,213,";
    REQUIRE_THROWS(util::StringToMat(input1));
}

TEST_CASE("rref", "[rref]") {
    double A[5][4] = {
            {16, 2,  3,  13},
            {5,  11, 10, 8},
            {9,  7,  6,  12},
            {4,  14, 15, 1},
            {13, 21, 21, 13}};
    vector<vector<double>> a(5);
    for (int i = 0; i < 5; i++)
        a[i] = vector<double>(A[i], A[i] + 4);
    int rank = matrixsolver::MatReducer(a);
    REQUIRE(rank == 3);
}

TEST_CASE("det", "[det]") {
    string mat1 = "1, 3, 5, 9\n1, 3, 1, 7\n4, 3, 9, 7\n5, 2, 0, 9";
    REQUIRE(matrixsolver::Det(mat1) == "Determinant is "+to_string(-376.0));
    string mat2 = "1,2,3\n4,5,6\n7,8,9";
    REQUIRE(matrixsolver::Det(mat2) == "Determinant is "+to_string(-0.0));
    string mat3 = "0";
    REQUIRE(matrixsolver::Det(mat3) == "Determinant is "+to_string(0.0));
    string mat4 = "0,0\n0,8";
    REQUIRE(matrixsolver::Det(mat4) == "Determinant is "+to_string(0.0));
}
