class nCrModPrime
{
    ///     Time & space complexity: O(n)
    ///     mod has to be prime
private:
    int n;
    ULL* fact;
    ULL* inv;
    ULL* invFact;
    ULL primeMod;

public:
    nCrModPrime(int n, ULL m)
    {
        this->n = n;
        primeMod = m;
        fact = new ULL[n+1];
        inv = new ULL[n+1];
        invFact = new ULL[n+1];
        fact[0] = 1;
        for (int i = 1; i <= n; i++)
            fact[i] = (fact[i-1] * i) % m;
        num.genModInv(n, m, inv);
        num.genModInvFact(n, m, inv, invFact);
    }

    ULL nCr(int n, int r)
    {
        if (n < r) return 0;
        return (((fact[n] * invFact[r]) % primeMod) * invFact[n-r]) % primeMod;
    }
};