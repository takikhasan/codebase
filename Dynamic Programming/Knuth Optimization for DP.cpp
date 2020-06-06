/* Knuth Optimization for DP */
/*
    Source Inspiration: https://www.quora.com/What-is-Knuths-optimization-in-dynamic-programming
    Template directly solves: https://www.spoj.com/problems/BRKSTRNG/
    (My source code for the problem is on vjudge)
*/
/* For "Matrix Chain Multiplication(MCM)" type problems - not the actual MCM AFAIK */
/* Converts O(n^3) to O(n^2) */
/* In this implementation, every range is inclusive */
/* 0 indexed */
/* T -> data type required for storing result */
/* Usage: KnuthDP<LL>(n) -> n: Array length */


/// depends on problem - start (to help determine costs)
vector<LL> sum;
/// depends on problem - end

template<typename T>
inline T KnuthDP(int n)
{
    vector<vector<T>> res(n, vector<T> (n));
    vector<vector<int>> mid(n, vector<int> (n));
    for (int len = 1; len <= n; len++) {
        for (int r = len - 1; r < n; r++) {
            int l = r - len + 1;
            if (len == 1) {
                res[l][r] = 0; /// depends on problem
                mid[l][r] = l;
                continue;
            }
            int mLeft = mid[l][r-1];
            int mRight = mid[l+1][r];
            res[l][r] = numeric_limits<T>::max(); /// depends on problem
            for (int m = mLeft; m <= mRight; m++) {
                if (m == r) continue; /* for len == 2 */
                /// depends on problem - start
                    T tres = res[l][m] + res[m+1][r];
                    T cost = sum[r];
                    if (l) cost -= sum[l-1];
                    tres += cost;
                    if (tres < res[l][r]) {
                        res[l][r] = tres;
                        mid[l][r] = m;
                    }
                /// depends on problem - end
            }
        }
    }
    return res[0][n-1];
}


/* Knuth Optimization for DP */
