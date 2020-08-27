/*
    #1. Intuition: https://cp-algorithms.com/data_structures/treap.html
    #2. Source Inspiration: https://github.com/kth-competitive-programming/kactl/blob/master/content/data-structures/Treap.h
    #3. Problems (easy to hard):
        i.  https://vjudge.net/solution/27020013 (direct template)
*/

struct Node {
	Node *l = NULL, *r = NULL;
	Node *par = NULL;
	Node *corresponding = NULL;
	int val;
	int y;
	int sz = 1;
	Node(int val) : val(val), y(rand()) {}
	void recalc() {
         sz = 1;
         if (l) {
            l->par = this;
            sz += l->sz;
         }
         if (r) {
            r->par = this;
            sz += r->sz;
         }
	}
};

int cnt(Node* n) { return n ? n->sz : 0; }

pair<Node*, Node*> split(Node* n, int k) {  /// [0..pos-1] and [pos..(sz-1)]
	if (!n) return {};
	if (cnt(n->l) >= k) {
		auto pa = split(n->l, k);
		n->l = pa.second;
		n->recalc();
		return {pa.first, n};
	} else {
		auto pa = split(n->r, k - cnt(n->l) - 1);
		n->r = pa.first;
		n->recalc();
		return {n, pa.second};
	}
}

Node* merge(Node* l, Node* r) {
	if (!l) return r;
	if (!r) return l;
	if (l->y > r->y) {
		l->r = merge(l->r, r);
		l->recalc();
		return l;
	} else {
		r->l = merge(l, r->l);
		r->recalc();
		return r;
	}
}

Node* ins(Node* t, Node* n, int pos) {
	auto pa = split(t, pos);
	return merge(merge(pa.first, n), pa.second);
}

Node* del(Node* t, int pos) {
	auto pa = split(t, pos);
	auto pb = split(pa.second, 1);
	return merge(pa.first, pb.second);
}

Node* getNode(Node* t, int pos) {
    if (cnt(t->l) == pos) return t;
    else if (cnt(t->l) > pos) return getNode(t->l, pos);
    else return getNode(t->r, pos - cnt(t->l) - 1);
}

/// Example application: move the range [l, r) to index k
void move(Node*& t, int l, int r, int k) {
	Node *a, *b, *c;
	tie(a,b) = split(t, l); tie(b,c) = split(b, r - l);
	if (k <= l) t = merge(ins(a, b, k), c);
	else t = merge(a, ins(c, b, k - r));
}

int implicit_key(Node *t, Node *n) {
    int ret = cnt(n->l);
    Node *curr = n;
    while (curr != t) {
        if (curr->par->r == curr)
            ret += cnt(curr->par->l) + 1;
        curr = curr->par;
    }
    return ret;
}

///

vector<Node *> treaps(100001, NULL);    /// one for maintaining relative array for each value + one (treap[0]) for maintaining actual array

int cnt_less_equal(int val, int r)  /// (log^2)(n)
{
    int low = 0, high = cnt(treaps[val]) - 1;
    if (low > high) return 0;
    while (low < high) {
        int mid = (low + high + 1) / 2;
        Node *node = getNode(treaps[val], mid); /// logn
        Node *c = node->corresponding;
        int key = implicit_key(treaps[0], c);   /// logn
        if (key <= r) {
            low = mid;
        }
        else {
            high = mid - 1;
        }
    }
    Node *node = getNode(treaps[val], low); /// logn
    Node *c = node->corresponding;
    int key = implicit_key(treaps[0], c);   /// logn
    if (key > r) low = -1;
    return low + 1;
}

void rotate(int l, int r)
{
    Node *node = getNode(treaps[0], r);
    int key_r = implicit_key(treaps[node->val], node->corresponding);
    int key_l = cnt_less_equal(node->val, l - 1);
    if (key_l != key_r) move(treaps[node->val], key_r, key_r + 1, key_l);
    if (l != r) move(treaps[0], r, r + 1, l);
}

int query(int val, int l, int r)
{
    return cnt_less_equal(val, r) - cnt_less_equal(val, l - 1);
}
