/** All purpose segment tree */

/**
 * Source Inspiration: KACTL github
 * Description: Segment tree with ability to add or set values of large intervals, and compute max of intervals.
 * Can be changed to other things.
 * Use with a bump allocator for better performance, and SmallPtr or implicit indices to save memory.
 * Time: O(\log N).
 * Usage: Node* tr = new Node(v, 0, sz(v));
 * Range(L, R) means range (L to R-1) inclusive
 */

/*
    #pragma once

    #define size_0 (300 << 19) // 150 MEGABYTES
    #define size_1 (350 << 19) // 175 MEGABYTES -> Safe with moderate capacity
    #define size_2 (400 << 19) // 200 MEGABYTES -> Safe with huge capacity
    #define size_3 (450 << 19) // 225 MEGABYTES

    static char buf[size_1];
    void* operator new(size_t s) {
        static size_t i = sizeof buf;
        assert(s < i);
        return (void*)&buf[i -= s];
    }
    void operator delete(void*) {}
*/

LL f(LL a, LL b)
{
    return max(a, b); /// CHANGE IF NEEDED
}

const int OSUM = 1, OMIN = 2, OMAX = 3, OXOR = 4, OOR = 5, OAND = 6, OGCD = 7, OLCM = 8;

LL f2(LL x, LL len, int OPTION)
{
    /*
        f2 function should work wonderfully for any kind of tree's SET operation,
        and for SUM, MIN, MAX type tree's ADD operation, but for other types - doubtful (maybe improved later).
    */
    if (OPTION == OSUM) {
        return len * x;
    }
    else if (OPTION == OXOR) {
        if (len % 2 == 0) return 0;
        else return x;
    }
    else {
        return x;
    }
}

const LL SUM = 0, MIN = LLONG_MAX, MAX = LLONG_MIN, XOR = 0, OR = 0, GCD = 0, LCM = 1;
const LL AND = (1LL << 60) - 1; /// 60 on bits

struct Node {
	Node *l = 0, *r = 0;
	int lo, hi;
	LL mset = inf, madd = 0, val = MAX; /// CHANGE IF NEEDED
	Node(int lo, int hi) : lo(lo), hi(hi) {} // Large interval of MAX
	Node(vector<LL>& v, int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(v, lo, mid); r = new Node(v, mid, hi);
			val = f(l->val, r->val);
		}
		else val = v[lo];
	}
	LL query(int L, int R) {
		if (R <= lo || hi <= L) return MAX; /// CHANGE IF NEEDED
		if (L <= lo && hi <= R) return val;
		push();
		return f(l->query(L, R), r->query(L, R));
	}
	void set(int L, int R, LL x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
            mset = x, madd = 0;
            val = f2(x, hi - lo, OMAX); /// CHANGE IF NEEDED
		}
		else {
			push(), l->set(L, R, x), r->set(L, R, x);
			val = f(l->val, r->val);
		}
	}
	void add(int L, int R, LL x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
			if (mset != inf) mset += x;
			else madd += x;
			val += f2(x, hi - lo, OMAX); /// CHANGE IF NEEDED
		}
		else {
			push(), l->add(L, R, x), r->add(L, R, x);
			val = f(l->val, r->val);
		}
	}
	void push() {
		if (!l) {
			int mid = lo + (hi - lo)/2;
			l = new Node(lo, mid); r = new Node(mid, hi);
		}
		if (mset != inf)
			l->set(lo,hi,mset), r->set(lo,hi,mset), mset = inf;
		else if (madd)
			l->add(lo,hi,madd), r->add(lo,hi,madd), madd = 0;
	}
};

/** All purpose segment tree */

template<typename T>
vector<int> lis(vector<T> v, bool strict)
{
    vector<int> ret(SZ(v)); /* longest increasing/non-decreasing subsequence ending at index i */
    T minn = numeric_limits<T>::max(), maxx = numeric_limits<T>::min();
    for (T x : v) minn = min(minn, x), maxx = max(maxx, x);
    Node *root = new Node(minn, maxx + 1);
    for (int i = 0; i < SZ(v); i++) {
        int val = root->query(minn, v[i] + !strict);
        ret[i] = max(1, val + 1);
        root->set(v[i], v[i] + 1, ret[i]);
    }
    return ret;
}

template<typename T>
vector<int> lds(vector<T> v, bool strict)
{
    vector<int> ret(SZ(v)); /* longest decreasing/non-increasing subsequence ending at index i */
    T minn = numeric_limits<T>::max(), maxx = numeric_limits<T>::min();
    for (T x : v) minn = min(minn, x), maxx = max(maxx, x);
    Node *root = new Node(minn, maxx + 1);
    for (int i = 0; i < SZ(v); i++) {
        int val = root->query(v[i] + strict, maxx + 1);
        ret[i] = max(1, val + 1);
        root->set(v[i], v[i] + 1, ret[i]);
    }
    return ret;
}

template<typename T>
vector<int> lis_reverse(vector<T> v, bool strict)
{
    /* longest increasing/non-decreasing subsequence starting at index i */
    reverse(all(v));
    auto ret = lds(v, strict);
    reverse(all(ret));
    return ret;
}

template<typename T>
vector<int> lds_reverse(vector<T> v, bool strict)
{
    /* longest decreasing/non-increasing subsequence starting at index i */
    reverse(all(v));
    auto ret = lis(v, strict);
    reverse(all(ret));
    return ret;
}
