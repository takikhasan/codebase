/** 
    Rho, prime checking, factorization
    https://codeforces.com/blog/entry/61901?#comment-458901
**/

namespace Big
{
    using u128 = __uint128_t;
    using i128 = __int128;
    using u64 = unsigned long long;
    using i64 = long long;

    const int C1 = 126;
    const int C2 = 64;
    static const int step = 1 << 9;

    const u128 prime[13] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41};
    const int psize = 13;
}

namespace Small
{
    using u128 = ULL;
    using i128 = LL;
    using u64 = unsigned int;
    using i64 = int;

    const int C1 = 126 / 2;
    const int C2 = 64 / 2;
    static const int step = 1 << 8;

    const u128 prime[7] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    const int psize = 7;
}

using namespace Big; /// Small

namespace Factor
{
    int const num_tries = 10;
    u128 n, niv_n;

    void setn(u128 n_)
    {
        n = n_;
        niv_n = 1;
        u128 x = n;
        for (int i = 1; i <= C1; i++) {
            niv_n *= x;
            x *= x;
        }
    }

    u128 HI(u128 x) { return x >> C2; };
    u128 LO(u128 x) { return u64(x); };

    struct u256
    {
        u128 hi, lo;

        static u256 mul128(u128 x, u128 y)
        {
            u128 t1 = LO(x) * LO(y);
            u128 t2 = HI(x) * LO(y) + HI(y) * LO(x) + HI(t1);
            return {HI(x) * HI(y) + HI(t2), (t2 << C2) + LO(t1)};
        }
    };

    u128 mmul(u128 x, u128 y)
    {
        u256 m = u256::mul128(x, y);
        u128 ans = m.hi - u256::mul128(m.lo * niv_n, n).hi;
        if (i128(ans) < 0) ans += n;
        return ans;
    }

    inline u128 f(u128 x, u128 inc)
    {
        return mmul(x, x) + inc;
    }

    inline u128 gcd(u128 a, u128 b)
    {
        int shift = __builtin_ctzll(a | b);
        b >>= __builtin_ctzll(b);
        while (a) {
            a >>= __builtin_ctzll(a);
            if (a < b) swap(a, b);
            a -= b;
        }
        return b << shift;
    }

    inline u128 rho(u128 seed, u128 n, u64 inc)
    {
        setn(n);
        auto sub = [&] (u128 x, u128 y) { return x > y ? x - y : y - x; };
        u128 y = f(seed, inc), a = f(seed, inc);
        for (int l = 1; ; l <<= 1) {
            u128 x = y;
            for (int i = 1; i <= l; i++) y = f(y, inc);
            for (int k = 0; k < l; k += step) {
                int d = min(step, l - k);
                u128 g = seed, y0 = y;
                for (int i = 1; i <= d; i++) {
                    y = f(y, inc);
                    g = mmul(g, sub(x, y));
                }
                g = gcd(g,n);
                if (g == 1) continue;
                if (g != n) return g;
                u128 y = y0;
                while (gcd(sub(x, y), n) == 1) y = f(y, inc);
                return gcd(sub(x, y), n) % n;
            }
        }
        return 0;
    }

    mt19937_64 rd;

    u128 rho(u128 x)
    {
        if (x % 2 == 0) return 2;
        if (x % 3 == 0) return 3;
        uniform_int_distribution<u64> rng(2, u64(x) - 1);
        for (int i = 2; i < num_tries; i++) {
            u128 ans = rho(rng(rd), x, i);
            if (ans != 0 && ans != x) return ans;
        }
        return 0;
    }

    u128 factor(u128 x)
    {
        return rho(x);
    }
}

#define gc (c = getchar())
template <typename T>
void read(T &x)
{
    char c;
    while (gc < '0');
    x = c - '0';
    while (gc >= '0') x = x * 10 + c - '0';
}

template <typename T>
void write(T x, char c)
{
    static char st[40];
    int top = 0;
    do { st[++top] = '0' + x % 10; } while (x /= 10);
    do { putchar(st[top]); } while (--top);
    putchar(c);
}

u128 modit(u128 x, u128 mod)
{
	if (x >= mod) x -= mod;
	return x;
}

u128 mult(u128 x, u128 y, u128 mod) {
	u128 s = 0, m = x % mod;
	while (y) {
		if (y & 1) s = modit(s + m, mod);
		y >>= 1;
		m = modit(m + m, mod);
	}
	return s;
}

class MillerRabin
{
    private:
    u128 bigmod(u128 a, u128 p, u128 mod)
    {
        u128 x = a % mod, res = 1;
        while (p) {
            if (p & 1) res = mult(res, x, mod);
            x = mult(x, x, mod);
            p >>= 1;
        }
        return res;
    }

    bool witness(u128 a, u128 d, u128 s, u128 n)
    {
        u128 r = bigmod(a, d, n);
        if (r == 1 || r == n - 1) return false;
        int i;
        for (i = 0; i < s - 1; i++) {
            r = mult(r, r, n);
            if (r == 1) return true;
            if (r == n - 1) return false;
        }
        return true;
    }

    public:
    bool isPrime(u128 n)
    {
        if (n <= 1) return false;
        u128 p = n - 1, s = 0;
        while (!(p & 1)) {
            p /= 2;
            s++;
        }
        u128 d = p;
        p = n - 1;
        for (int i = 0; i < psize && prime[i] < n; i++) {
            if (witness(prime[i], d, s, n)) return false;
        }
        return true;
    }
} millerRabin;

const int factorizerConst = 350000;
struct Factorizer
{
    bitset<factorizerConst+1> flag;
    vector<u128> primes;
    vector<pair<u128, int> > factors;

    void init()
    {
        flag.set();
        for (u128 i = 2; i <= factorizerConst; i++) {
            if (flag[i]) {
                primes.pb(i);
                for (u128 j = i * i; j <= factorizerConst; j += i) {
                    flag[j] = 0;
                }
            }
        }
    }

    void clr()
    {
        factors.clear();
    }

    void rhoFactorize(u128 n)
    {
        while (n != 1) {
            if (millerRabin.isPrime(n)) {
                factors.pb(mp(n, 1));
                return;
            }
            u128 x = Factor::factor(n);
            if (!millerRabin.isPrime(x)) {
                u128 y = n / x;
                rhoFactorize(x);
                if (x != y) rhoFactorize(y);
                return;
            }
            int cnt = 0;
            while (n % x == 0) {
                n /= x;
                cnt++;
            }
            factors.pb(mp(x, cnt));
        }
    }

    void factorize(u128 n)
    {
        for (u128 p : primes) {
            if (p * p > n) break;
            if (n % p == 0) {
                int cnt = 0;
                while (n % p == 0) {
                    cnt++;
                    n /= p;
                }
                factors.pb(mp(p, cnt));
            }
        }
        rhoFactorize(n);
        sort(all(factors));
    }
};

/** Rho, prime checking, factorization **/