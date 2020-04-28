//
// Created by jiany on 4/25/2020.
//

#ifndef FINALPROJECT_UTIL_H
#define FINALPROJECT_UTIL_H

#include "NumCpp.hpp"

using namespace std;
using namespace nc;
namespace util {
    NdArray<float> StringToMat(const string& input);

    NdArray<float> StringToVec(const string& input);

    string MatToString(const NdArray<double>& mat);
}
#endif //FINALPROJECT_UTIL_H
