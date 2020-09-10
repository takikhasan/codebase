/*
    #1. Intuition:
        i.  https://blog.anudeep2011.com/persistent-segment-trees-explained-with-spoj-problems/
    #2. Problems (Easy to Hard):
        i.  https://vjudge.net/solution/27227401
        ii. https://vjudge.net/solution/27227426
*/

struct Node {
	Node *l = 0, *r = 0;
	int lo, hi;
	int val = 0;
	Node(int lo, int hi) : lo(lo), hi(hi) {}
	Node(vector<int>& v, int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(v, lo, mid); r = new Node(v, mid, hi);
		}
	}
	int query(int L, int R) {
		if (R <= lo || hi <= L) return 0;
		if (L <= lo && hi <= R) return val;
		push();
		return l->query(L, R) + r->query(L, R);
	}
	void add(int L, int R, int x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
			val += x;
		}
		else {
			push(), l->add(L, R, x), r->add(L, R, x);
			val = l->val + r->val;
		}
	}
	void persistent_add(int L, int R, int x, Node *corres) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
			corres->val += x;
		}
		else {
			push();
			if (L >= l->lo && L < l->hi) {
                corres->r = r;
                Node *now = new Node(l->lo, l->hi);
                now->val = l->val;
                corres->l = now;
                l->persistent_add(L, R, x, now);
			}
			else {
                corres->l = l;
                Node *now = new Node(r->lo, r->hi);
                now->val = r->val;
                corres->r = now;
                r->persistent_add(L, R, x, now);
			}
			corres->val = corres->l->val + corres->r->val;
		}
	}
	void push() {
		if (!l) {
			int mid = lo + (hi - lo)/2;
			l = new Node(lo, mid); r = new Node(mid, hi);
		}
	}
};

#define rep(i, a, b) for(int i = a; i < (b); ++i)

template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= SZ(V); pw *= 2, ++k) {
			jmp.emplace_back(SZ(V) - pw * 2 + 1);
			rep(j, 0, SZ(jmp[k]))
				jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(int a, int b) {
		int dep = 31 - __builtin_clz(b - a);
		return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

struct LCA {
	int T = 0;
	VI time, path, ret;
	RMQ<int> rmq;
	LCA(vector<VI>& C) : time(SZ(C)), rmq((dfs(C, 0, -1), ret)) {}
	void dfs(vector<VI> &C, int v, int par) {
		time[v] = T++;
		for (int y : C[v]) {
            if (y != par) {
                path.push_back(v), ret.push_back(time[v]);
                dfs(C, y, v);
            }
		}
	}
	int lca(int a, int b) {
		if (a == b) return a;
		tie(a, b) = minmax(time[a], time[b]);
		return path[rmq.query(a, b)];
	}
};

struct KthMinTreePath   /** Weights in nodes, not edges */  /** For Arrays, make a chain tree */
{
    int n;
    VI compressed;
    VI sorted;
    vector<Node*> root;
    LCA _lca;

    KthMinTreePath(VVI &g, VI &v) : _lca(g) /** The tree and the node values */
    {
        n = SZ(g);
        set<int> s(all(v));
        sorted = VI(all(s));
        compressed = VI(n);
        for (int i = 0; i < n; i++) {
            compressed[i] = pos(sorted, v[i]);
        }

        root = vector<Node*>(n, NULL);
        root[0] = new Node(compressed, 0, n);
        root[0]->add(compressed[0], compressed[0] + 1, 1);
        dfs(0, -1, g);
    }

    int pos(VI &v, int x)
    {
        auto it = lower_bound(all(v), x);
        return it - v.begin();
    }

    void dfs(int i, int p, VVI &g)
    {
        if (i != 0) {
            Node *now = new Node(root[p]->lo, root[p]->hi);
            now->val = root[p]->val;
            root[p]->persistent_add(compressed[i], compressed[i] + 1, 1, now);
            root[i] = now;
        }
        for (int v : g[i]) {
            if (v != p) {
                dfs(v, i, g);
            }
        }
    }

    int query(Node *a, Node *b, Node *c, int lca, int k)
    {
        if (a->lo == a->hi - 1) {
            return a->lo;
        }

        int seg_left_sum = a->l->val + b->l->val - 2 * (c->l->val);
        int seg_right_sum = a->r->val + b->r->val - 2 * (c->r->val);

        if (compressed[lca] < a->l->hi && compressed[lca] >= a->l->lo) seg_left_sum++;
        else if (compressed[lca] < a->r->hi && compressed[lca] >= a->r->lo) seg_right_sum++;

        if (k <= seg_left_sum) {
            a = a->l;
            b = b->l;
            c = c->l;
        }
        else {
            a = a->r;
            b = b->r;
            c = c->r;
            k -= seg_left_sum;
        }

        return query(a, b, c, lca, k);
    }

    int ask(int u, int v, int k)
    {
        int l = _lca.lca(u, v);
        int res = query(root[u], root[v], root[l], l, k);
        return sorted[res];
    }
};
