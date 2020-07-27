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
            We may want to add 'x' to a single index or all the indexes in a range.
            We may want to set a single index or all the indexes in a range as 'x'.
            We may want to know the sum of squares in a range.
        Tree Type:
            SUM tree.
        Updates:
            Add 'x' to all the numbers in range l to r:
                root->add(l, r + 1, x);
            Replace (with 'x') all the numbers in range l to r:
                root->set(l, r + 1, x);
        Query:
            Return the sum of squares in range l to r:
                return root->query(l, r + 1);
        Note:
            The base tree can be thought of as a SUM tree with slight modifications in the update functions.
            I made necessary changes in "All Purpose Segment Tree".
            And cleared up the clutter by removing seemingly unnecessary things.


    Problems (easy to hard) - (role model submission / problem page):
        i.  https://vjudge.net/solution/26545279    (direct template)
*/

LL f(LL a, LL b)
{
    return a + b;
}

const LL SUM = 0;

struct Node {
	Node *l = 0, *r = 0;
	int lo, hi;
	LL mset = inf, madd = 0, val = SUM, aux = SUM;
	Node(int lo, int hi) : lo(lo), hi(hi) {}    /// Large interval of 0
	Node(vector<LL>& v, int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(v, lo, mid); r = new Node(v, mid, hi);
			val = f(l->val, r->val);
		}
		else val = v[lo] * v[lo];
	}
	LL query(int L, int R) {
		if (R <= lo || hi <= L) return SUM;
		if (L <= lo && hi <= R) return val;
		push();
		return f(l->query(L, R), r->query(L, R));
	}
	void set(int L, int R, LL x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
            mset = x, madd = 0;
            val = x * x * (hi - lo);
            aux = 2 * x * (hi - lo);
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
			val += x * x * (hi - lo) + aux * x;
            aux += 2 * x * (hi - lo);
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
