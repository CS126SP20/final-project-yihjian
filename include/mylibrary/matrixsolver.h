// Copyright (c) 2020 [Yihong Jian]. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_MATRIXSOLVER_H_
#define FINALPROJECT_MYLIBRARY_MATRIXSOLVER_H_

#include <string>
#include "NumCpp.hpp"

using namespace std;
using namespace nc;
namespace matrixsolver {
    NdArray<float> StringToMat(const string& input);

    string MatToString(const NdArray<double>& mat);

    string Rref(const string& input);

    int RrefHelper(vector<vector<double>>& mat);

    //int RrefHelper(NdArray<double>& mat);

    string LUDecomp(const string& input);

    string Det(const string& input);

    string Eigen(string input);

    string SVD(const string& input);

    string Inv(const string& input);
}  // namespace matrixsolver


#endif // FINALPROJECT_MYLIBRARY_MATRIXSOLVER_H_
