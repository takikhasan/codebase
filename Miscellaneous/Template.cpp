#include<stdio.h>
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;


#define     UI                      unsigned int
#define     LL                      long long int
#define     LD                      long double
#define     ULL                     unsigned long long int
#define     VI                      vector<int>
#define     VB                      vector<bool>
#define     VLL                     vector<LL>
#define     VULL                    vector<ULL>


#define     pii                     pair<int, int>
#define     mp                      make_pair
#define     pb                      push_back
#define     ff                      first
#define     ss                      second
#define     SZ(x)                   (int)x.size()
#define     all(x)                  x.begin(), x.end()


#define     sp(x)                   setprecision(x) << fixed
#define     what_is(x)              cout << #x << " is " << x << endl


#define     PI                      acos(-1.0)
#define     EPS                     1e-12
#define     S_SIZE                  4000010     /* 3.81640625 mb */


const LL inf = 1000000000;
const LL mod = 1000000000 + 7;


inline void IO() { ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0); }
template<typename T> inline int dcmp (T x) { const T eps = EPS; return x < -eps ? -1 : (x > eps); }


template<class T> inline int CHECK(T MASK, int i) { return (MASK >> i) & 1; }
template<class T> inline T ON(T MASK, int i) { return MASK | (T(1) << i); }
template<class T> inline T OFF(T MASK, int i) { return MASK & (~(T(1) << i)); }
template<typename T> inline int CNT(T MASK) {
    if (numeric_limits<T>::digits <= numeric_limits<unsigned int>::digits) return __builtin_popcount(MASK);
    else return __builtin_popcountll(MASK);
}
template<class T> inline int RIGHT(T MASK) { return log2(MASK & -MASK); }


int dx4[] = { 0, 0, -1, +1 };
int dy4[] = { +1, -1, 0, 0 };
int dx8[] = { 1, 1, 0, -1, -1, -1, 0, 1, 0 };
int dy8[] = { 0, 1, 1, 1, 0, -1, -1, -1, 0 };


inline void I(int &a) { scanf("%d", &a); }
inline void I(LL &a) { scanf("%lld", &a); }
inline void I(ULL &a) { scanf("%llu", &a); }
inline void I(char *a) { scanf("%s", a); }
char Iarr[S_SIZE]; inline void I(string &a) { scanf("%s", Iarr); a = Iarr; }
inline void I(LD &a) { cin >> a; }
inline void I(double &a) { cin >> a; }
inline void I(bool &a) { int aa; I(aa); a = aa; }
template<typename T1, typename T2> inline void I(pair<T1, T2> &a) { I(a.ff); I(a.ss); }
template<typename T> inline void I(vector<T> &a) { for (T &aa : a) I(aa); }
template<typename T, typename... Args> inline void I(T &a, Args &... args) { I(a); I(args...); }


inline void OUT(const int &a) { printf("%d", a); }
inline void OUT(const LL &a) { printf("%lld", a); }
inline void OUT(const ULL &a) { printf("%llu", a); }
inline void OUT(const char *a) { printf("%s", a); }
inline void OUT(const char &a) { printf("%c", a); }
inline void OUT(const string &a) { for (const char &aa : a) OUT(aa); }
inline void OUT(const bool &a) { printf("%d", a); }
template<typename T1, typename T2> inline void OUT(const pair<T1, T2> &a) { OUT("{"); OUT(a.ff); OUT(", "); OUT(a.ss); OUT("}"); }
template<typename T> inline void OUT(const T &a) { int i = 0; OUT("{"); for (const auto &aa : a) { if (i++) OUT(", "); OUT(aa); } OUT("}"); }
template<typename T, typename... Args> inline void OUT(const T &a, const Args &... args) { OUT(a); OUT(" "); OUT(args...); }
template<typename... Args> inline void O(const Args &... args) { OUT(args...); OUT("\n"); }


#define error(args...) { string _s = "[" + string(#args) + "] = ["; OUT(_s); err(args); }
void err() {}
template<typename T, typename... Args>
void err(T a, Args... args) {
	OUT(a), OUT((sizeof...(args) ? ", " : "]\n"));
	err(args...);
}


struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15; x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9; x = (x ^ (x >> 27)) * 0x94d049bb133111eb; return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count(); return splitmix64(x + FIXED_RANDOM);
    }
};
struct custom_hash_pair {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15; x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9; x = (x ^ (x >> 27)) * 0x94d049bb133111eb; return x ^ (x >> 31);
    }
    size_t operator()(pair<uint64_t, uint64_t> x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x.ff + FIXED_RANDOM) * 3 + splitmix64(x.ss + FIXED_RANDOM);
    }
};


inline void faster(auto &unorderedMap, int n) { int num = 2; while (num < n) num *= 2; unorderedMap.reserve(num); unorderedMap.max_load_factor(0.25); }

// gp_hash_table<LL, int, custom_hash> table;
// unordered_map<LL, int, custom_hash> table;
// head


const int M = 200010; // maximum number of cubes


int main()
{


    return 0;
}

