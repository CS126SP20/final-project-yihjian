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

    string Rref(const string& input) {
        NdArray<double> mat;
        try {
            mat = StringToMat(input).astype<double>();
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

//    int RrefHelper(NdArray<double>& mat) {
//        int num_row = mat.shape().rows;
//        int num_col = mat.shape().cols;
//        int row = 0;
//        for (int col = 0; col < num_col && row < num_row; col++) {
//            int j = row;
//            for (int i = row + 1; i < num_row; i++) {
//                if (fabs(mat(i, col)) > fabs(mat(j, col)))
//                    j = i;
//            }
//
//            if (fabs(mat(j, col)) < 1e-10)
//                continue;
//
//            auto tmp = mat.row(j);
//            mat.row(j) = mat.row(row);
//            mat.row(row) = tmp;
//            cout<<mat<<endl;
//
//            double norm_factor = 1.0 / mat(row, col);
//            mat.row(row) * norm_factor;
//            cout<<mat<<endl;
//            for (int i = 0; i < num_row; i++)
//                if (i != row) {
//                    double col_factor = mat(i, col);
//                    mat.row(i) - col_factor * mat(row, j);
//                }
//            cout<<mat<<endl;
//            row++;
//        }
//        return row;
//    }

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
               + "V-Transpose is\n" + MatToString(vt);
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
            return "Inverse is\n" + MatToString(linalg::inv(mat));
        } catch (exception e) {
            return e.what();
        }
    }
}  // namespace matrixsolver
