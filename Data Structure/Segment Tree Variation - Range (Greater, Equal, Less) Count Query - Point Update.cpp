/** All purpose segment tree - VARIATION */

/**
    IMPORANT!!!
    Segment Tree Variation Description:
        General Info:
            We have an array.
            In any range, we want to know how many numbers are bigger/smaller/equal/(similar query) than query value.
            Template at the moment can handle greater queries.

        Tree Type:
            2d segment tree
            Outer segment tree is for array index
            Inner segment tree is for values (Sum Tree)

        Init:
            Node *root = new Node1(v, 0, SZ(v));

        Updates:
            Since we only do point updates,
                maintain an array for the values at all times to get the 'new_val' & 'old_val'
            Only point ADD:
                return root->query(in, new_val, old_val);   Complexity: (log^2)n
            SET isn't implemented yet,
                it would be just like ADD (Very easy)       Complexity: (log^2)n

        Query:
            For x in range l to r:
                return root->query(l, r + 1, x);            Complexity: (log^2)n

    Problems (easy to hard) - (role model submission / problem page):
        i.  https://vjudge.net/contest/390493#problem/M (direct template)   [It gives TLE, but my implementation is good I believe, inshaAllah we'll get AC on another problem]
*/

struct Node2 {
	Node2 *l = 0, *r = 0;
	int lo, hi;
	int val = 0;
	Node2(int lo, int hi) : lo(lo), hi(hi) {}
    int query(int L, int R) {
		if (R <= lo || hi <= L) return 0;
		if (L <= lo && hi <= R) return val;
		push();
		return l->query(L, R) + r->query(L, R);
	}
	void add(int L, int R, int x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) val += x;
		else {
			push(), l->add(L, R, x), r->add(L, R, x);
			val = l->val + r->val;
		}
	}
	void push() {
		if (!l) {
			int mid = lo + (hi - lo)/2;
			l = new Node2(lo, mid); r = new Node2(mid, hi);
		}
	}
};

struct Node1 {
	Node1 *l = 0, *r = 0;
	int lo, hi;
	Node2 *tree;
	Node1(vector<int>& v, int lo, int hi) : lo(lo), hi(hi) {
		tree = new Node2(1, 10009); /// A segment tree that has one index for each value : lo and hi of the tree should reflect that
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo) / 2;
			l = new Node1(v, lo, mid); r = new Node1(v, mid, hi);
            for (int i = lo; i < hi; i++) {
                tree->add(v[i], v[i] + 1, 1);
            }
		}
		else tree->add(v[lo], v[lo] + 1, 1);
	}
    int query(int L, int R, int x) {
		if (R <= lo || hi <= L) return 0;
		if (L <= lo && hi <= R) return tree->query(x + 1, 10009);
		return l->query(L, R, x) + r->query(L, R, x);
	}
	void update(int in, int new_val, int old_val) {
        if (in < lo || in >= hi) return;
        if (in == lo && (hi - 1) == lo) {
            tree->add(new_val, new_val + 1, 1);
            tree->add(old_val, old_val + 1, -1);
        }
        else {
            l->update(in, new_val, old_val), r->update(in, new_val, old_val);
            tree->add(new_val, new_val + 1, 1);
            tree->add(old_val, old_val + 1, -1);
        }
	}
};

void clean2(Node2 *root)
{
    if (root->l) clean2(root->l);
    if (root->r) clean2(root->r);
    delete root;
}

void clean1(Node1 *root)
{
    if (root->l) clean1(root->l);
    if (root->r) clean1(root->r);
    clean2(root->tree);
    delete root;
}

/** All purpose segment tree - VARIATION */
