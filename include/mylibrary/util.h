//
// Created by jiany on 4/25/2020.
//

#ifndef FINALPROJECT_UTIL_H
#define FINALPROJECT_UTIL_H

#include "NumCpp.hpp"

using namespace std;
using namespace nc;
namespace util {
    NdArray<float> StringToMat(const string& input, bool vec = false);

    //vector<vector<double>> StringTo2dVec(const string& input);

    string MatToString(const NdArray<double>& mat);

    string VecToLine(const NdArray<double>& vec);
}
#endif //FINALPROJECT_UTIL_H
