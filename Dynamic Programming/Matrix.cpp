/**   Matrix   */

/*
    #1. Problems (easy to hard) - (role model submission / problem page):
        i.  https://vjudge.net/solution/26176019
*/
template<typename T>
struct Matrix
{
    vector<vector<T>> matrix;

    Matrix() {}

    Matrix(int n, int m)
    {
        matrix = vector<vector<T>> (n, vector<T> (m));
    }

    Matrix operator * (const Matrix& B) const
    {
        int n = SZ(matrix), m = SZ(B[0]), c = SZ(matrix[0]);
        Matrix ret(n, m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                /**
                 * Initializing ret[i][j] with correct value (and dimension when T is Matrix).
                 * (%) operator should ignore (Matrix<T> % (int/LL/ULL..)) type operation.
                 * Using (%) operator here is necessary if mod value is given.
                 */
                ret[i][j] = matrix[i][0] * B[0][j];
                for (int k = 1; k < c; k++) {
                    ret[i][j] = ret[i][j] + matrix[i][k] * B[k][j];
                }
            }
        }
        return ret;
    }

    Matrix operator + (const Matrix& B) const
    {
        int n = SZ(matrix), m = SZ(B[0]);
        Matrix ret(n, m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                /**
                 * (%) operator should ignore (Matrix<T> % (int/LL/ULL..)) type operation.
                 * Using (%) operator here also is necessary if mod value is given.
                 */
                ret[i][j] = matrix[i][j] + B[i][j];
            }
        }
        return ret;
    }

    template<typename P>
    Matrix pow(P p) {
        if (p == 1) return *this;
        Matrix ret = pow(p / 2);
        ret = ret * ret;
        if (p % 2) ret = ret * (*this);
        return ret;
    }

    template<typename P>
    Matrix faster_pow(P p) {  /** This is faster than pow() in my experience, but I'm keeping both for the moment. */
        int row = SZ(matrix);
        int col = SZ(matrix[0]);
        Matrix ret(row, col);
        for (int i = 0; i < row; i++) {
            ret.matrix[i][i] = 1;
        }
        Matrix temp = *this;
        while (p) {
            if (p & 1) ret = ret * temp;
            temp = temp * temp;
            p >>= 1;
        }
        return ret;
    }

    template<typename N>
    Matrix& operator % (const N ignore)
    {
        return *this;
    }

    vector<T>& operator [] (int u) { return matrix[u]; }
    const vector<T>& operator [] (int u) const { return matrix[u]; }
};

template<typename T>
struct Solver
{
    /**
     * T -> Data type required for storing result
     */
    template<typename N>
    T nthFib(N n, T x, T y) const
    {
        /**
         * x -> fib(0), y -> fib(1)
         */
        if (!n) return 0;
        Matrix<T> a(2, 2), b(2, 1);
        a[0][1] = a[1][0] = a[1][1] = 1;
        b[0][0] = x; b[1][0] = y;
        return (a.pow(n) * b)[0][0];
    }
};

/**   Matrix   */
