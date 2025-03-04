// Copyright (c) 2020 [Yihong Jian]. All rights reserved.

#include <mylibrary/matrixsolver.h>
#include "mylibrary/util.h"
#include <Eigenvalues>

// Taken from numcpp reference
typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> EigenIntMatrix;
typedef Eigen::Map<EigenIntMatrix> EigenMatrixMap;

namespace matrixsolver {

    string Rref(const string& input) {
        // Convert to 2d array and solve
        vector<vector<double>> mat;
        try {
            mat = util::StringTo2dVec(input);
        } catch (exception e) {
            // I can't catch "int e" for some reason.
            return e.what();
        }
        size_t rank = MatReducer(mat);

        // Strech out 2dvec to a string
        string out;
        for (const auto& r:mat) {
            out += "[";
            for (const auto& c:r) {
                out += to_string(c);
                out += ", ";
            }
            out += "]\n";
        }
        return "Rank is " + to_string(rank)
               + "\nReduced Row Echelon Form is\n" + out;
    }

    // Took this from https://github.com/yicheng-w/acm-icpc-notebook/blob/master/general-algorithm/rref.cpp
    int MatReducer(vector<vector<double>>& mat) {
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
        NdArray<double> mat;
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
        vector<vector<double>> mat;
        try {
            mat = util::StringTo2dVec(input);
        } catch (exception e) {
            return e.what();
        }

        size_t n = mat.size();
        if (n != mat[0].size())
            return "Determinant Requires Square Matrix";

        double det = 1.0;

        for (int i = 0; i < n; ++i) {
            double pivotElement = mat[i][i];
            int pivotRow = i;
            for (int row = i + 1; row < n; ++row) {
                if (std::abs(mat[row][i]) > std::abs(pivotElement)) {
                    pivotElement = mat[row][i];
                    pivotRow = row;
                }
            }
            if (pivotElement == 0.0) {
                det = 0.0;
                break;
            }
            if (pivotRow != i) {
                mat[i].swap(mat[pivotRow]);
                det *= -1.0;
            }
            det *= pivotElement;

            for (int row = i + 1; row < n; ++row) {
                for (int col = i + 1; col < n; ++col) {
                    mat[row][col] -= mat[row][i] * mat[i][col] / pivotElement;
                }
            }
        }

        return "Determinant is " + to_string(det);
    }

    string Eig(const string& input) {
        NdArray<double> mat;
        try {
            mat = util::StringToMat(input);
        } catch (exception e) {
            // I can't catch "int e" for some reason.
            return e.what();
        }

        if (mat.numCols() != mat.numRows())
            return "Can't perform eigen calculation with non-square matrix";
        // Map numcpp array to Eigen Matrix
        auto eigen_mat = EigenMatrixMap(mat.data(), mat.numRows(), mat.numCols());
        // Retrieve Eigen values
        Eigen::EigenSolver<Eigen::MatrixXd> es(eigen_mat);
        Eigen::VectorXd eigen_values = es.eigenvalues().real();
        Eigen::MatrixXd eigen_vectors = es.eigenvectors().real();

        // Map eigen matrix to string
        ostringstream val;
        val << eigen_values;
        ostringstream vec;
        vec << eigen_vectors;

        return "CAUTION, complex eigenvalue caused UNDEFINED behavior\n"
               "Eigenvalues are\n" + val.str() +
               "\nEigenvectors(in columns) are\n" + vec.str();
    }

    string SVD(const string& input) {
        NdArray<double> mat;
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
            linalg::svd(mat, u, s, vt);
        } catch (exception e) {
            // I can't catch "int e" for some reason.
            return e.what();
        }

        return "U is:\n" + util::MatToString(u)
               + "S is\n" + util::MatToString(s)
               + "V-Transpose is\n" + util::MatToString(vt);
    }

    string Inv(const string& input) {
        NdArray<double> mat;
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

    pair<string, string> PowerIter(const string& input, const string& init_guess) {
        NdArray<double> mat;
        NdArray<double> vec;
        try {
            mat = util::StringToMat(input).astype<double>();
            vec = util::StringToMat(init_guess, true).astype<double>();
        } catch (exception e) {
            return make_pair(e.what(), init_guess);
        }

        try {
            // Normalize input to prevent overflow
            // Broadcasting doesn't work too well between arrays, so
            // I extracted the double contained in array for broadcasting
            NdArray<double> vec_normed = vec / vec.norm()(0, 0);
            NdArray<double> y = mat.dot(vec_normed);
            NdArray<double> res = y / y.norm()(0, 0);
            return make_pair("Initial guess after 1 iteration is\n" + util::MatToString(res),
                             util::VecToLine(res));
        } catch (exception e) {
            return make_pair(e.what(), init_guess);
        }
    }

    string LstSq(const string& input, const string& init_guess) {
        NdArray<double> A;
        // Assume b is only one column
        NdArray<double> b;

        try {
            A = util::StringToMat(input);
            b = util::StringToMat(init_guess, true);
        } catch (exception e) {
            return e.what();
        }

        if (A.numRows() != b.numRows())
            return "For Ax = b, rows of A and b does not match";

        try {
            return util::MatToString(nc::linalg::lstsq(A, b));
        } catch (exception e) {
            return e.what();
        }
    }

}  // namespace matrixsolver
