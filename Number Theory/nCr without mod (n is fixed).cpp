///*... nCr without mod ...*/

class nCrCalc
{
    ///     Time & space complexity: O(k), where k is
    ///     the maximum value of r in all nCr queries
private:
    ULL n;
    ULL* C;
    int last;

    gen(int st, int en)
    {
        for (int i = st; i <= en; i++) {
            C[i] = C[i-1] * (n - i + 1);
            C[i] /= i;
        }
        last = en;
    }

public:
    nCrCalc(ULL n, int MAX_K = -1)
    {
        this->n = n;
        if (MAX_K == -1) MAX_K = n;
        C = new ULL[MAX_K+1];
        C[0] = 1;
        last = 0;
    }

    ULL nCr(int k)
    {
        if (k > n - k) k = n - k;
        if (k > last) gen(last + 1, k);
        return C[k];
    }
};

///*... nCr without mod ...*/