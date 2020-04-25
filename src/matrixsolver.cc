// Copyright (c) 2020 [Yihong Jian]. All rights reserved.

#include <mylibrary/matrixsolver.h>


namespace matrixsolver {
    NdArray<float> StringToMat(const string& input) {
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
                                  not1(ptr_fun<int, int>(std::isspace))));
                col.erase(find_if(col.rbegin(),
                                  col.rend(),
                                  not1(ptr_fun<int, int>(std::isspace))).base(),
                          col.end());
                // Convert to float and append to vec.
                mat.push_back(stof(col));
            }
        }
        // If missing an entry, throw out an error
        if (mat.size() % row_count != 0)
            throw std::exception("Matrix not in form n*m");
        return NdArray<float>{mat}.reshape(row_count, mat.size() / row_count);
    }

    string MatToString(const NdArray<double>& mat) {
        ostringstream oss;
        oss << mat;
        return oss.str();
    }

    //!TODO: Rewrite Rref, library way doesn't work properly.
    string Rref(const string& input) {
        NdArray<float> mat;
        try {
            mat = StringToMat(input);
        } catch (exception e) {
            // I can't catch "int e" for some reason.
            return e.what();
        }
        auto plu_res = linalg::pivotLU_decomposition(mat);
        string res = MatToString(get<1>(plu_res));
        return res;
    }

    string LUDecomp(const string& input) {
        NdArray<float> mat;
        try {
            mat = StringToMat(input);
        } catch (exception e) {
            // I can't catch "int e" for some reason.
            return e.what();
        }

        try {
            // LUDecomp may encounter error such as rectangular matrix
            // So we just catch whatever and print it out.
            auto lu_res = linalg::lu_decomposition(mat);
            string l = MatToString(get<0>(lu_res));
            string u = MatToString(get<1>(lu_res));
            return "L is:\n" + l + "U is\n" + u;
        } catch (exception e) {
            return e.what();
        }
    }

    string Det(const string& input) {
        NdArray<float> mat;
        try {
            mat = StringToMat(input);
        } catch (exception e) {
            // I can't catch "int e" for some reason.
            return e.what();
        }

        try {
            return "Determinant is" + to_string(linalg::det(mat));
        } catch (exception e) {
            return e.what();
        }
    }

    //!TODO I don't have built in for this...Perhaps power iteration first.
    string Eigen(string input) {
        return "eigen";
    }

    string SVD(const string& input) {
        NdArray<float> mat;
        try {
            mat = StringToMat(input);
        } catch (exception e) {
            // I can't catch "int e" for some reason.
            return e.what();
        }

        nc::NdArray<double> u;
        nc::NdArray<double> s;
        nc::NdArray<double> vt;
        try {
            linalg::svd(mat.astype<double>(), u, s, vt);
        } catch (exception e) {
            // I can't catch "int e" for some reason.
            return e.what();
        }

        return "U is:\n" + MatToString(u)
               + "S is\n" + MatToString(s)
               + "V-Transpose is" + MatToString(vt);
    }

    string Inv(const string& input) {
        NdArray<float> mat;
        try {
            mat = StringToMat(input);
        } catch (exception e) {
            // I can't catch "int e" for some reason.
            return e.what();
        }

        try {
            return "Inverse is" + MatToString(linalg::inv(mat));
        } catch (exception e) {
            return e.what();
        }
    }
}  // namespace matrixsolver
