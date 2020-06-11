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
        Tree type: MIN tree
        Updates: Range or point SET or ADD operation
        Query: For any range, the min value and the last index with that value
               Can be changed to find first index and/or to find max value
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
    return min(a, b); /// CHANGE IF NEEDED
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
	LL mset = inf, madd = 0, val = MIN; /// CHANGE IF NEEDED
	Node(int lo, int hi) : lo(lo), hi(hi) {} // Large interval of MAX
	Node(vector<LL>& v, int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(v, lo, mid); r = new Node(v, mid, hi);
			val = f(l->val, r->val);
		}
		else val = v[lo];
	}
	void getSegments(vector<Node*> &valid_segments, int L, int R) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
            valid_segments.pb(this); return;
		}
		push();
		r->getSegments(valid_segments, L, R), l->getSegments(valid_segments, L, R);
	}
    int innerQuery() {
        if (lo + 1 == hi) return lo;
        push();
        if (r->val <= l->val) return r->innerQuery();
        else return l->innerQuery();
    }
    pair<LL, int> query(int L, int R) {
        /* Complexity : logn + logn + logn (getting segments, iterating over segments & process one segment) */
        /* This function should only be called from root */
        vector<Node*> valid_segments;
        getSegments(valid_segments, L, R);
        /* Now we have at most logn segments */
        /* The segments do not overlap and they are stored from right to left */
        LL minn = MIN;
        Node *seg;
        for (auto node : valid_segments) {
            if (node->val < minn) {
                minn = node->val;
                seg = node;
            }
        }
        return {minn, seg->innerQuery()};
    }
	void set(int L, int R, LL x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
            mset = x, madd = 0;
            val = f2(x, hi - lo, OMIN); /// CHANGE IF NEEDED
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
			val += f2(x, hi - lo, OMIN); /// CHANGE IF NEEDED
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
