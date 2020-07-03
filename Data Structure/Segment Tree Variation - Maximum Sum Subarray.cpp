/** All purpose segment tree - VARIATION */

/**
 * Source Inspiration: KACTL github
 * Description: Segment tree with ability to add or set values of large intervals, and compute max of intervals.
 * Can be changed to other things.
 * Use with a bump allocator for better performance, and SmallPtr or implicit indices to save memory.
 * Time: O(\log N).
 * Usage: Node* tr = new Node(v, 0, sz(v));
 * Range(L, R) means range (L to R-1) inclusive
 */

 /**
    IMPORANT!!!
    Segment Tree Variation Description:
        Tree type: MAX tree with four significant values for each node (not straightforward MAX tree)
        Updates: Range or point SET operation, point ADD operation
        Query: For any range, maximum sub-array sum (picking at least one element)

    Problems (easy to hard) - (role model submission / problem page):
        i.  https://vjudge.net/solution/26173596 (direct template)
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

const LL SUM = 0, MIN = LLONG_MAX, MAX = LLONG_MIN, XOR = 0, OR = 0, GCD = 0, LCM = 1;
const LL AND = (1LL << 60) - 1; /// 60 on bits

struct NodeValue
{
    LL sum = MAX, right_aligned = MAX, left_aligned = MAX, max_sum = MAX;
};

inline NodeValue f(const NodeValue &a, const NodeValue &b)
{
    if (a.max_sum == MAX) return b;
    else if (b.max_sum == MAX) return a;
    else return {a.sum + b.sum, max(b.right_aligned, b.sum + a.right_aligned), max(a.left_aligned, a.sum + b.left_aligned), max(max(a.max_sum, b.max_sum), a.right_aligned + b.left_aligned)}; /// CHANGE IF NEEDED
}

const int OSUM = 1, OMIN = 2, OMAX = 3, OXOR = 4, OOR = 5, OAND = 6, OGCD = 7, OLCM = 8;

NodeValue f2(LL x, LL len, int OPTION)
{
    /*
        f2 function should work wonderfully for any kind of tree's SET operation,
        and for SUM, MIN, MAX type tree's ADD operation, but for other types - doubtful (maybe improved later).
    */
    LL aligned = (x < 0) ? x : x * len;
    return {x * len, aligned, aligned, aligned};
}

struct Node {
	Node *l = 0, *r = 0;
	int lo, hi;
	LL mset = inf, madd = 0;
	NodeValue val;  /// CHANGE IF NEEDED
	Node(int lo, int hi) : lo(lo), hi(hi) {}    /// Large interval of MAX
	Node(vector<LL>& v, int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(v, lo, mid); r = new Node(v, mid, hi);
			val = f(l->val, r->val);
		}
		else val = {v[lo], v[lo], v[lo], v[lo]};
	}
	NodeValue query(int L, int R) {
		if (R <= lo || hi <= L) return NodeValue(); /// CHANGE IF NEEDED
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
	void add(int L, int R, LL x) {  /** We call add() for point add only */
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
			if (mset != inf) mset += x;
			else madd += x;
			val.sum += x, val.right_aligned += x, val.left_aligned += x, val.max_sum += x;  /// CHANGE IF NEEDED
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

/** All purpose segment tree - VARIATION */
