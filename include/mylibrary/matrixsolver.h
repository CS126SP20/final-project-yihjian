// Copyright (c) 2020 [Yihong Jian]. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_MATRIXSOLVER_H_
#define FINALPROJECT_MYLIBRARY_MATRIXSOLVER_H_

#include <string>
#include <Dense>
#include "NumCpp.hpp"


using namespace std;
using namespace nc;
namespace matrixsolver {
    string Rref(const string& input);

    int RrefHelper(vector<vector<double>>& mat);

    //int RrefHelper(NdArray<double>& mat);

    string LUDecomp(const string& input);

    string Det(const string& input);

    string Eig(const string& input);

    string SVD(const string& input);

    string Inv(const string& input);

    pair<string, string> PowerIter(const string& input, const string& init_guess);

    string LstSq(const string& input, const string& init_guess);
}  // namespace matrixsolver


#endif // FINALPROJECT_MYLIBRARY_MATRIXSOLVER_H_
