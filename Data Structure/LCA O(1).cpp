/*
    #1. An LCA Template that gives us O(1) per lca(a, b) query.
    #2. Using that, we can get a few queries like path sum query in O(1).
    #3. Source:
        i.  https://github.com/kth-competitive-programming/kactl/blob/master/content/graph/LCA.h
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
