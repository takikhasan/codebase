/** All purpose segment tree - VARIATION */

/**
 * Use with a bump allocator for better performance, and SmallPtr or implicit indices to save memory.
 * Time: O(\log N).
 * Usage: Node* tr = new Node(v, 0, sz(v));
 * Range(L, R) means range (L to R-1) inclusive
 */

/**
    IMPORANT!!!
    Segment Tree Variation Description:
        General Info:
            We have an array of 0 and 1.
            We may want to toggle a single index or all the indexes in a range.
            We may want to set a single index or all the indexes in a range as 0 or 1.
            We may want to know the number of 1s in a range.
        Tree Type:
            SUM tree.
        Updates:
            Toggle (0 to 1 and vice-versa) all the numbers in range l to r:
                root->toggle(l, r + 1);
            Replace (with x = 0 or x = 1) all the numbers in range l to r:
                root->set(l, r + 1, x);
        Query:
            Return the number of 1s in range l to r:
                return root->query(l, r + 1);
        Note:
            The base tree can be thought of as a SUM tree with slight modifications in the update functions.
            I made necessary changes in "All Purpose Segment Tree".
            And cleared up the clutter by removing seemingly unnecessary things.


    Problems (easy to hard) - (role model submission / problem page):
        i.  https://vjudge.net/solution/26539805
*/

using T = int;  /// USE LONG LONG INT WHEN RANGE IS TOO BIG

T f(T a, T b)
{
    return a + b;
}

const T SUM = 0;

struct Node {
	Node *l = 0, *r = 0;
	T lo, hi;
	int mset = -1;
	bool mtoggle = 0;
	T val = SUM;
	Node(T lo, T hi) : lo(lo), hi(hi) {}    /// Large interval of 0
	Node(vector<int>& v, int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(v, lo, mid); r = new Node(v, mid, hi);
			val = f(l->val, r->val);
		}
		else val = v[lo];
	}
	T query(T L, T R) {
		if (R <= lo || hi <= L) return SUM;
		if (L <= lo && hi <= R) return val;
		push();
		return f(l->query(L, R), r->query(L, R));
	}
	void set(T L, T R, bool x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
            mset = x, mtoggle = 0;
            val = (hi - lo) * x;
		}
		else {
			push(), l->set(L, R, x), r->set(L, R, x);
			val = f(l->val, r->val);
		}
	}
	void toggle(T L, T R) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
            mtoggle ^= 1;
            val = hi - lo - val;  /** We replace with complement, whenever we are in a relevant node */
		}
		else {
			push(), l->toggle(L, R), r->toggle(L, R);
			val = f(l->val, r->val);
		}
	}
	void push() {
		if (!l) {
			int mid = lo + (hi - lo)/2;
			l = new Node(lo, mid); r = new Node(mid, hi);
		}
		if (mset != -1)
			l->set(lo,hi,mset), r->set(lo,hi,mset), mset = -1;
		else if (mtoggle != 0)
			l->toggle(lo,hi), r->toggle(lo,hi), mtoggle = 0;
	}
};

/** All purpose segment tree - VARIATION */
