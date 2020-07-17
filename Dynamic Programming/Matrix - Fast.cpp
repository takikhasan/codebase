/*
    #1. This is a mimic of: https://github.com/takikhasan/codebase/blob/master/Dynamic%20Programming/Matrix.cpp
    #2. But, in this implementation, we give up some generalization for performance (mainly time complexity)
    #3. Problems that specifically require this version (easy to hard) - (role model submission / problem page):
        i.  https://vjudge.net/solution/26396639
*/
using matrix_type = LD;   /** CHANGE IF NEEDED */
struct Matrix
{
    matrix_type matrix[2][2];    /** CHANGE IF NEEDED */
    int row, col;
    inline Matrix() {}
    inline Matrix(int n, int m) {
        row = n;
        col = m;
    }
    inline Matrix operator * (const Matrix& B) const {
        int n = row, m = B.col, c = col;
        Matrix ret(n, m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                /**
                 * Using (%) operator here is necessary if mod value is given.
                 */
                ret.matrix[i][j] = matrix[i][0] * B.matrix[0][j];
                for (int k = 1; k < c; k++) {
                    ret.matrix[i][j] = ret.matrix[i][j] + matrix[i][k] * B.matrix[k][j];
                }
            }
        }
        return ret;
    }
    inline Matrix operator + (const Matrix& B) const {
        int n = row, m = B.col;
        Matrix ret(n, m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                /**
                 * Using (%) operator here also is necessary if mod value is given.
                 */
                ret.matrix[i][j] = matrix[i][j] + B.matrix[i][j];
            }
        }
        return ret;
    }
    inline Matrix pow(int p) {  /** CHANGE TYPE OF 'p' IF NEEDED */
        Matrix ret(row, col);
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                ret.matrix[i][j] = 0;
            }
        }
        for (int i = 0; i < row; i++) ret.matrix[i][i] = 1;
        Matrix temp = *this;
        while (p) {
            if (p & 1) ret = ret * temp;
            temp = temp * temp;
            p >>= 1;
        }
        return ret;
    }
};
struct Solver
{
    inline LL nthFib(int n, int x, int y) const {   /** CHANGE TYPE OF 'n' AND/OR RETURN TYPE IF NEEDED */
        /**
         * x -> fib(0), y -> fib(1)
         */
        if (!n) return 0;
        Matrix a(2, 2), b(2, 1);
        a.matrix[0][0] = 0;
        a.matrix[0][1] = a.matrix[1][0] = a.matrix[1][1] = 1;
        b.matrix[0][0] = x; b.matrix[1][0] = y;
        return (a.pow(n) * b).matrix[0][0];
    }
};
