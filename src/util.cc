//
// Created by jiany on 4/25/2020.
//

#include "mylibrary/util.h"
namespace util {
    NdArray<double> StringToMat(const string& input, bool vec) {
        if (input.empty()) {
            if (vec)
                throw exception("Please input additional vector");
            throw exception("Please input matrix");
        }

        auto tuple = StringToMatHelper(input);
        vector<double> mat = get<0>(tuple);
        size_t row_count = get<1>(tuple);

        // Return a column vector if specified vec=true
        if (vec) {
            return NdArray<double>{mat}.reshape(mat.size(),1);
        }

        // If missing an entry, throw out an error
        if (mat.size() % row_count != 0)
            throw exception("Matrix not in form n*m");
        return NdArray<double>{mat}.reshape(row_count, mat.size() / row_count);
    }

    pair<vector<double>, int> StringToMatHelper(const string& input) {
        istringstream iss_row(input);
        size_t row_count = 0;
        string row;
        vector<double> mat;
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
                mat.push_back(stod(col));
            }
        }

        return make_pair(mat, row_count);
    }

    vector<vector<double>> StringTo2dVec(const string& input) {
        if (input.empty()) {
            throw exception("Please input matrix");
        }

        auto tuple = StringToMatHelper(input);
        vector<double> vec = get<0>(tuple);
        size_t row_count = get<1>(tuple);

        //Return a 2d double vector instead of nc array
        size_t col_count = vec.size() / row_count;
        vector<vector<double>> mat(row_count);
        for (int i = 0; i < row_count; i++)
            mat[i] = vector<double> (&vec[i * col_count], &vec[i * col_count] + col_count);

        return mat;
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