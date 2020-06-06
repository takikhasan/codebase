/*
    Optimized Kuhn (weighted nodes allowed) for Bipartite Matching
*/

/*
    Only one side is weighted. The vector 'order' stores all
    pair<weight[node], node> - such pairs. We assume that
    the left side (corresponding variables: n, L) is
    weighted.
    'order' is sorted as desired first.
    'mt' from this snippet and 'R' from the other version
    are same.
    Many other things are similar.
*/

/*
    Source:
        http://e-maxx.ru/algo/vertex_weighted_matching
        http://e-maxx.ru/algo/kuhn_matching
*/


vector<pair<int, int>> order;

struct BipartiteMatcher {
    int n, k;
    vector < vector<int> > g;
    vector<int> mt;
    vector<char> used;
    vector<int> L;

    BipartiteMatcher(int nn, int kk)
    {
        n = nn;
        k = kk;
        g.resize(n);
        used.resize(n);
        mt.resize(k);
        L.resize(n);
    }

    void AddEdge(int u, int v)
    {
        g[u].push_back(v);
    }

    bool try_kuhn (int v) {
        if (used[v])  return false;
        used[v] = true;
        for (size_t i=0; i<g[v].size(); ++i) {
            int to = g[v][i];
            if (mt[to] == -1 || try_kuhn (mt[to])) {
                mt[to] = v;
                return true;
            }
        }
        return false;
    }

    int Solve() {
        sort(all(order));
        int ret = 0;

        mt.assign (k, -1);
        for (int v=0; v<n; ++v) {
            int x = order[v].second;
            used.assign (n, false);
            try_kuhn (x);
            L[x] = -1;
        }

        for (int i=0; i<k; ++i)
            if (mt[i] != -1) {
                ret++;
                L[mt[i]] = i;
            }

        return ret;
    }
};

/*
    Optimized Kuhn (weighted nodes allowed) for Bipartite Matching
*/