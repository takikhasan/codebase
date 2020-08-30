/** All purpose segment tree - VARIATION */

/**
 * Source Inspiration: KACTL github
 * Time: O(log^2 N) per query, O(N log N) for initialization.
 * Usage: Node* tr = new Node(v, 0, sz(v));
 * Range(L, R) means range (L to R-1) inclusive
 */

/**
    IMPORANT!!!
    Segment Tree Variation Description:
        General Info:
            We have an array.
            In any range, we want to know how many numbers are bigger/smaller/equal/(similar query) than query value.
        Tree Type:
            Merge Sort Tree.
        Updates:
            No updates. If update is required, some of the following may be used:
                i.  Implicit Segment Tree with each node being Implicit Segment Tree as well.
                ii. Implicit Segment Tree with each node being a Treap (Implicit or not - depends).
        Query:
            For x in range l to r:
                return root->query(l, r + 1, x);    Complexity: (log^2)n
        Important Note:
            This tree, or the other two types mentioned in updates section (and even others) can be used for many queries
            that may be thought of as problems that require MO's algorithm (sqrt decomposition).

            Obviously, I don't prefer O((N + Q)sqrt(N)) to O(Q(log^2 N) + N(log^2 N)).
            The sqrt(N) is ungraceful in my opinion. Also, MO is offline. No updates, nothing. We don't want that. Using powerful
            data structures like the ones I have mentioned, update is also possible.

            Build intuition my solving many problems. Create templates, understand variations and keep digital notes.
            Beautiful intuition source for "Distinct Number in Range" and the likes:
                i.  https://codeforces.com/blog/entry/10508?#comment-158835

    Problems (easy to hard) - (role model submission / problem page):
        i.  https://vjudge.net/solution/27070430    (direct template) (Problem Name: D-query, Problem Info: Distinct Elements in Range without Updates)
*/


struct Node {
	Node *l = 0, *r = 0;
	int lo, hi;
	VI val;
	Node(int lo, int hi) : lo(lo), hi(hi) {}
	Node(vector<int>& v, int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo) / 2;
			l = new Node(v, lo, mid); r = new Node(v, mid, hi);
			val.resize(SZ(l->val) + SZ(r->val));
			merge(all(l->val), all(r->val), val.begin());
		}
		else {
            val = {v[lo]};
		}
	}
    int query(int L, int R, int x) {
		if (R <= lo || hi <= L) return 0;
		if (L <= lo && hi <= R) {
            auto it = lower_bound(all(val), x + 1);
            return SZ(val) - (it - val.begin());    /// Numbers greater than x in range
//            return it - val.begin();    /// Numbers less equal x in range
		}
		return l->query(L, R, x) + r->query(L, R, x);
	}
};

void clean(Node *root)
{
    if (root->l) clean(root->l);
    if (root->r) clean(root->r);
    root->val.clear();
    delete root;
}

/** All purpose segment tree - VARIATION */
