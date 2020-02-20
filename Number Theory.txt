struct NumberTheory {
    LL gcd(LL a, LL b) { while (b) { a %= b; swap(a, b); } return a; }
    LL lcm(LL a, LL b) { return (a / gcd(a, b)) * b; }
    LL bigMod(LL p, LL e, LL m) {
        LL ret = 1; p %= m;
        while (e > 0) { if (e & 1) ret = (ret * p) % m; p = (p * p) % m; e >>= 1; }
        return ret;
    }
    /// (1/a) % m when a & m are co-primes
    LL modInverse(LL a, LL m) {
        LL g = gcd(a, m);
        if (g != 1) {
            cout << "Inverse doesn't exist" << endl; return -1;
        }
        LL m0 = m;
        LL y = 0, x = 1;
        if (m == 1) return 0;
        while (a > 1) {
            LL q = a / m;
            LL t = m;
            m = a % m, a = t;
            t = y;
            y = x - q * y;
            x = t;
        }
        if (x < 0) x += m0;
        return x;
    }
    /// generate all (1/i) % m in [1..n] where n is less than m
    /// m must be prime
    void genModInv(int n, LL m, ULL inv[]) {
        inv[1] = 1;
        for (int i = 2; i <= n; ++i)
            inv[i] = (m - (m / i) * inv[m%i] % m) % m;
    }
    /// generate all (1/i!) % m in [1..n] where n is less than m
    /// m must be prime
    void genModInvFact(int n, LL m, ULL inv[], ULL invFact[]) {
        invFact[0] = invFact[1] = 1;
        for (int i = 2; i <= n; i++)
            invFact[i] = (invFact[i-1] * inv[i]) % m;
    }
} num;