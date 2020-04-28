// Copyright (c) 2020 [Yihong Jian]. All rights reserved.

#include <mylibrary/matrixsolver.h>
#include "mylibrary/util.h"

namespace matrixsolver {

    string Rref(const string& input) {
        NdArray<double> mat;
        try {
            mat = util::StringToMat(input).astype<double>();
        } catch (exception e) {
            // I can't catch "int e" for some reason.
            return e.what();
        }

        // Convert NdArray to 2DVec to calculate rref
        size_t row = mat.shape().rows;
        vector<vector<double>> matrix(row);
        for (int i = 0; i < row; i++)
            matrix[i] = mat.row(i).toStlVector();

        size_t rank = RrefHelper(matrix);
        // Strech out 2dvec
        string out;
        for (const auto& r:matrix) {
            out += "[";
            for(const auto& c:r) {
                out += to_string(c);
                out += ", ";
            }
            out += "]\n";
        }
        return "Rank is " + to_string(rank)
               + "\nReduced Row Echelon Form is\n" + out;
    }

    // Took this from https://github.com/yicheng-w/acm-icpc-notebook/blob/master/general-algorithm/rref.cpp
    // Should have don't it using cn::NdArray, but I could not update mat in
    // that form.
    int RrefHelper(vector<vector<double>>& mat) {
        int num_row = mat.size();
        int num_col = mat[0].size();
        int row = 0;
        for (int col = 0; col < num_col && row < num_row; col++) {
            // Find pivot rows, checking if next n-rows are greater than current
            // row on leading index
            int j = row;
            for (int i = row + 1; i < num_row; i++) {
                if (fabs(mat[i][col]) > fabs(mat[j][col]))
                    j = i;
            }
            if (fabs(mat[j][col]) < 1e-10)
                continue;
            swap(mat[j], mat[row]);

            // Normalize each row based with 1
            // subtract previous row.
            double s = 1.0 / mat[row][col];
            for (int j1 = 0; j1 < num_col; j1++) mat[row][j1] *= s;
            for (int i = 0; i < num_row; i++)
                if (i != row) {
                    double t = mat[i][col];
                    for (int j2 = 0; j2 < num_col; j2++) {
                        mat[i][j2] -= t * mat[row][j2];
                    }
                }
            row++;
        }
        return row;
    }

    string LUDecomp(const string& input) {
        NdArray<float> mat;
        try {
            mat = util::StringToMat(input);
        } catch (exception e) {
            // I can't catch "int e" for some reason.
            return e.what();
        }

        try {
            // LUDecomp may encounter error such as rectangular matrix
            // So we just catch whatever and print it out.
            auto lu_res = linalg::lu_decomposition(mat);
            string l = util::MatToString(get<0>(lu_res));
            string u = util::MatToString(get<1>(lu_res));
            return "L is:\n" + l + "U is\n" + u;
        } catch (exception e) {
            return e.what();
        }
    }

    string Det(const string& input) {
        NdArray<float> mat;
        try {
            mat = util::StringToMat(input);
        } catch (exception e) {
            // I can't catch "int e" for some reason.
            return e.what();
        }

        try {
            return "Determinant is " + to_string(linalg::det(mat));
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
            mat = util::StringToMat(input);
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

        return "U is:\n" + util::MatToString(u)
               + "S is\n" + util::MatToString(s)
               + "V-Transpose is\n" + util::MatToString(vt);
    }

    string Inv(const string& input) {
        NdArray<float> mat;
        try {
            mat = util::StringToMat(input);
        } catch (exception e) {
            // I can't catch "int e" for some reason.
            return e.what();
        }

        try {
            return "Inverse is\n" + util::MatToString(linalg::inv(mat));
        } catch (exception e) {
            return e.what();
        }
    }

    //!TODO
    string PowerIter(const string& input, const string& init_guess) {
        NdArray<double> mat;
        NdArray<double> vec;
        try {
            mat = util::StringToMat(input).astype<double>();
            vec = util::StringToVec(init_guess).astype<double>();
        } catch (exception e) {
            return e.what();
        }

        try {
            auto tmp = nc::norm(vec, static_cast<Axis>(1));
            NdArray<double> vec_normed = vec/tmp;
            auto y = mat.dot(vec_normed);
            return "Initial guess after 1 iteration is" + util::MatToString(y / y.norm());
        } catch (exception e) {
            return e.what();
        }
    }

    string LstSq(const string& input, const string& init_guess) {
        NdArray<float> A;
        NdArray<float> b;

        try {
            A = util::StringToMat(input);
            b = util::StringToVec(init_guess);
        } catch (exception e) {
            return e.what();
        }

        try {
            return util::MatToString(nc::linalg::lstsq(A, b));
        } catch (exception e) {
            return e.what();
        }
    }

}  // namespace matrixsolver
