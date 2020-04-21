// Copyright (c) 2020 [Yihong Jian]. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_MATRIXSOLVER_H_
#define FINALPROJECT_MYLIBRARY_MATRIXSOLVER_H_

#include <string>
#include "NumCpp.hpp"

using namespace std;
using namespace nc;
namespace matrixsolver {
    NdArray<float> StringToMat(string input);

    string MatToString(NdArray<float> mat);

    string Rref(string input);

    string LUDecomp(string input);

    string Diag(string input);

    string Eigen(string input);

    string SVD(string input);
}  // namespace matrixsolver


#endif // FINALPROJECT_MYLIBRARY_MATRIXSOLVER_H_
