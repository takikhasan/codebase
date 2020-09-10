/*
    #1. An LCA Template that gives us O(1) per lca(a, b) query.
    #2. Using that, we can get a few queries like path sum query in O(1).
    #3. Source:
        i.  https://github.com/kth-competitive-programming/kactl/blob/master/content/graph/LCA.h
    #4. Problems (Easy to Hard):
        i.  https://vjudge.net/solution/27176384
*/

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
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

struct LCA {
	int T = 0;
	VI time, path, ret;
	VI dist;
	RMQ<int> rmq;

	LCA(vector<vector<pii>>& C) : dist(SZ(C)), time(SZ(C)), rmq((dfs(C, 0, -1, 0), ret)) {}

	void dfs(vector<vector<pii>> &C, int v, int par, int curr_sum) {
		time[v] = T++;
		dist[v] = curr_sum;
		for (pii p : C[v]) {
            int w = p.ss, y = p.ff;
            if (y != par) {
                path.push_back(v), ret.push_back(time[v]);
                dfs(C, y, v, curr_sum + w);
            }
		}
	}

	int lca(int a, int b) {
		if (a == b) return a;
		tie(a, b) = minmax(time[a], time[b]);
		return path[rmq.query(a, b)];
	}

	int distt(int a, int b) { return dist[a] + dist[b] - 2 * dist[lca(a,b)]; }
	/**
        When weight is in nodes (For this template and the other),
            Tree creation:
                Just add edges like this:
                    For edge (a->b),
                        tree[a].push_back(b, weight[b]);
                        tree[b].push_back(a, weight[a]);
            Query:
                Handle lca(a, b) separately.
    */
};

/*
    #1. Source & Intuition:
        i.  https://codeforces.com/blog/entry/43230
        ii. https://cp-algorithms.com/data_structures/sqrt_decomposition.html
    #2. Problems (easy to hard):
        i.  https://vjudge.net/solution/27221065
        ii. https://vjudge.net/solution/27225143
        iii.https://vjudge.net/solution/27221085
*/
namespace MO_Tree_Path
{
    struct Query {
        int l, r, idx;
        int lca = -1;
    };

    const int BLOCK_SIZE = 450; /** root(array size) +- 50 */

    inline bool operator < (const Query &a, const Query &b) {
        if (a.l / BLOCK_SIZE != b.l / BLOCK_SIZE)
            return make_pair(a.l, a.r) < make_pair(b.l, b.r);
        return (a.l / BLOCK_SIZE & 1) ? (a.r < b.r) : (a.r > b.r);
    }

    bool EDGE_MODE;
    int time;
    VI st, en;
    VI slot;
    VI par;
    VI a;   /** 'a' holds node weights, needed when EDGE_MODE = false   */
    VI weight;  /** When the nodes have weights/values, weight[i] means value of the node.
                    When the edges have weights/values, weight[i] means value of the edge connecting to the parent and i.
                */

    namespace DS
    {
        /** Variables & methods to maintain answer */
        /** Depends on the problem */
        VI cnt;

        inline void actual_remove(int node) {
            if (EDGE_MODE && !node) return;

            /** MAIN PART */
        }
        inline void actual_add(int node) {
            if (EDGE_MODE && !node) return;

            /** MAIN PART */
        }
        inline void removes(int idx) {
            cnt[slot[idx]]--;
            if (cnt[slot[idx]] % 2 == 0) {
                // Actual Remove
                actual_remove(slot[idx]);
            }
            else {
                // Actual Add
                actual_add(slot[idx]);
            }
        }
        inline void add(int idx) {
            cnt[slot[idx]]++;
            if (cnt[slot[idx]] % 2 == 0) {
                // Actual Remove
                actual_remove(slot[idx]);
            }
            else {
                // Actual Add
                actual_add(slot[idx]);
            }
        }
        inline int get_answer() {
            /** MAIN PART */

            /// If current_query.lca != -1, current_query.lca must be handled separately, depending on the problem
            /// Can only happen when EDGE_MODE = false
        }
    };

    using namespace DS;

    void dfs(int u, int p, auto &g) {
        st[u] = time;
        slot[time++] = u;
        for (auto e : g[u]) {
            if (e.ff != p) {
                par[e.ff] = u;
                weight[e.ff] = e.ss;
                dfs(e.ff, u, g);
            }
        }
        en[u] = time;
        slot[time++] = u;
    }

    void preprocess(vector<vector<pair<int, int>>> tree, vector<Query> &queries) {  /** {edge_to, edge_weight}  */
        /** First, flatten the tree and calculate what's necessary */
        time = 0;
        int n = SZ(tree);
        slot = VI(n * 2);
        st = en = VI(n);
        par = VI(n);
        weight = VI(n);
        cnt = VI(n);
        dfs(0, -1, tree);
        if (!EDGE_MODE) {
            weight = a; /** 'a' is a vector of node weights */
        }

        /** Second, initialize LCA */
        LCA G(tree);

        /** Third, use LCA to turn queries into sub-arrays */
        for (Query &q : queries) {
            int u = q.l, v = q.r;
            if (st[u] > st[v]) swap(u, v);
            int p = G.lca(u, v);
            if (p == u) {
                if (EDGE_MODE) {
                    if (u == v) {
                        q.l = q.r = -1; // Empty Query
                    }
                    else {
                        q.l = st[u] + 1;
                        q.r = st[v];
                    }
                }
                else {
                    q.l = st[u];
                    q.r = st[v];
                }
            }
            else {
                if (EDGE_MODE) {
                    q.l = en[u];
                    q.r = st[v];
                }
                else {
                    q.l = en[u];
                    q.r = st[v];
                    q.lca = p;
                }
            }
        }
    }

    VI algorithm(vector<vector<pair<int, int>>> tree, vector<Query> queries) {
        preprocess(tree, queries);

        VI answers(SZ(queries));
        sort(all(queries));

        int cur_l = 0;
        int cur_r = -1;
        for (Query q : queries) {
            if (q.l == -1) {
                /// This may only happen in EDGE_MODE
                /// The path has one node only and no edge
                answers[q.idx] = 0; /// Depends on the problem
                continue;
            }
            while (cur_l > q.l) {
                cur_l--;
                add(cur_l);
            }
            while (cur_r < q.r) {
                cur_r++;
                add(cur_r);
            }
            while (cur_l < q.l) {
                removes(cur_l);
                cur_l++;
            }
            while (cur_r > q.r) {
                removes(cur_r);
                cur_r--;
            }
            answers[q.idx] = get_answer();
        }
        return answers;
    }
}

using namespace MO_Tree_Path;
