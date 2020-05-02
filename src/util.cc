//
// Created by jiany on 4/25/2020.
//

#include "mylibrary/util.h"
namespace util {
    NdArray<float> StringToMat(const string& input, bool vec) {
        if (input.empty()) {
            throw exception("Please input matrix");
        }

        istringstream iss_row(input);
        size_t row_count = 0;
        string row;
        vector<float_t> mat;
        // Every row is sperated by "\n", so getline would return every row
        while (getline(iss_row, row)) {
            // Use ',' as token to split every column
            row_count++;
            istringstream iss_col(row);
            string col;
            while (getline(iss_col, col, ',')) {
                // Stackoverflow method of "trim"
                col.erase(col.begin(),
                          find_if(col.begin(),
                                  col.end(),
                                  not1(ptr_fun<int, int>(isspace))));
                col.erase(find_if(col.rbegin(),
                                  col.rend(),
                                  not1(ptr_fun<int, int>(isspace))).base(),
                          col.end());
                // Convert to float and append to vec.
                mat.push_back(stof(col));
            }
        }

        // Return a column vector if specified vec=true
        if (vec) {
            return NdArray<float>{mat}.reshape(mat.size(),1);
        }

        // If missing an entry, throw out an error
        if (mat.size() % row_count != 0)
            throw exception("Matrix not in form n*m");
        return NdArray<float>{mat}.reshape(row_count, mat.size() / row_count);
    }

    string MatToString(const NdArray<double>& mat) {
        ostringstream oss;
        oss << mat;
        return oss.str();
    }

    string VecToLine(const NdArray<double>& vec) {
        string out;
        for(auto& value:vec) {
            out += to_string(value);
            out += ",";
        }
        return out;
    }
}