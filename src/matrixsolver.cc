// Copyright (c) 2020 [Yihong Jian]. All rights reserved.

#include <mylibrary/matrixsolver.h>

namespace matrixsolver {
    NdArray<float> StringToMat(string string) {
        return NdArray<float>{{0, 0}};
    }
    string MatToString(NdArray<float> mat) {
        return "hello";
    }
    string Rref(string input) {
        return "rref";
    }
    string LUDecomp(string input){
        return "lu";
    }
    string Diag(string input){
        return "diag";
    }
    string Eigen(string input){
        return "eigen";
    }
    string SVD(string input){
        return "svd";
    }
}  // namespace matrixsolver
