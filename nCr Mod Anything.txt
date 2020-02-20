struct NCRMOD
{
    /* Tested with 1 <= mod <= 2 * 10e9 and 1 <= n <= 10e5 and 0 <= m <= n. */
    /* MOD is fixed */
    typedef long long ll;

    #define pll pair<ll,ll>
    #define PB push_back
    #define MP make_pair
    #define N 100001

    int n, MOD, PHI, residue[N], fact[N], inv_fact[N];
    vector<int> primeDivisors;
    vector< vector<int> > C, P;

    int ModExp(int a, int n)
    {
        ll x = a % MOD, y = 1 % MOD;
        while(n) {
            if(n % 2)
                y = (x * y) % MOD;
            x = (x * x) % MOD;
            n /= 2;
        }
        return (int)y;
    }

    int ModInv(int a)
    {
        return ModExp(a, PHI - 1);
    }

    void PreProcess()
    {
        int m = MOD;
        for(int i = 2; i * i <= m; ++i) {
            if(m % i == 0) {
                while(m % i == 0)
                    m /= i;
                primeDivisors.PB(i);
            }
        }
        if(m > 1)
            primeDivisors.PB(m);
        m = primeDivisors.size();
        C.resize(m);
        P.resize(m);
        fact[0] = 1, inv_fact[0] = 1;
        for(int i = 1; i <= n; ++i)
            residue[i] = i;
        PHI = MOD;
        for(int i = 0; i < m; ++i) {
            int p = primeDivisors[i];
            PHI /= p;
            PHI *= (p - 1);
            C[i].resize(n + 1);
            for(int j = p; j <= n; j += p) {
                int x = residue[j], k = 0;
                while(x % p == 0) {
                    x /= p;
                    ++k;
                }
                residue[j] = x;
                C[i][j] = k;
            }
            for(int j = 1; j <= n; ++j)
                C[i][j] += C[i][j - 1];
            P[i].resize(C[i][n] + 1);
            P[i][0] = 1 % MOD;
            for(int j = 1; j < P[i].size(); ++j)
                P[i][j] = (1ll * p * P[i][j - 1]) % MOD;
        }
        for(int i = 1; i <= n; ++i)
            fact[i] = (1ll * residue[i] * fact[i - 1]) % MOD;
        inv_fact[n] = ModInv(fact[n]);
        for(int i = n - 1; i > 0; --i)
            inv_fact[i] = (1ll * residue[i + 1] * inv_fact[i + 1]) % MOD;
    }

    int NCR(int n, int r)
    {
        if(n < 0 || r < 0 || n < r)
            return 0;
        else {
            ll ans = fact[n];
            ans = (ans * inv_fact[r]) % MOD;
            ans = (ans * inv_fact[n - r]) % MOD;
            for(int i = 0; i < primeDivisors.size(); ++i) {
                int c = C[i][n] - C[i][r] - C[i][n - r];
                ans = (ans * P[i][c]) % MOD;
            }
            return (int)ans;
        }
    }
} obj;