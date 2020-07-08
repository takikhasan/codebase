struct LCA
{
    /* 0 indexed */
    int n;
    int *l;
    int **p;
    int **mn;
    int **mx;
    LL **sum;
    /* parent, min, max, sum */
    int LOG;
    int *logs;
    int *powr;
    vector<pii > *g;
    void init1(int nn)
    {
        n = nn;
        l = new int[nn];
        p = new int*[nn];
        mn = new int*[nn];
        mx = new int*[nn];
        sum = new LL*[nn];
        LOG = log2(nn) + 2;
        for (int i = 0; i < nn; i++) {
            p[i] = new int[LOG];
            mn[i] = new int[LOG];
            mx[i] = new int[LOG];
            sum[i] = new LL[LOG];
        }
        g = new vector<pii >[nn];
    }
    void init2(int nn, vector<pii> gg[])
    {
        n = nn;
        l = new int[nn];
        p = new int*[nn];
        mn = new int*[nn];
        mx = new int*[nn];
        sum = new LL*[nn];
        LOG = log2(nn) + 2;
        for (int i = 0; i < nn; i++) {
            p[i] = new int[LOG];
            mn[i] = new int[LOG];
            mx[i] = new int[LOG];
            sum[i] = new LL[LOG];
        }
        g = new vector<pii >[nn];
        for (int i = 0; i < nn; i++) {
            for (auto x : gg[i]) {
                g[i].push_back(x);
            }
        }
    }
    void addEdge(int u, int v, int w)
    {
        g[u].push_back(mp(v, w));
        g[v].push_back(mp(u, w));
    }
    void dfs(int u, int pp, int ll)
    {
        l[u] = ll;
        p[u][0] = pp;
        for (auto x : g[u]) {
            if (x.ff != pp) {
                mn[x.ff][0] = mx[x.ff][0] = sum[x.ff][0] = x.ss;
                dfs(x.ff, u, ll + 1);
            }
        }
    }
    void build()
    {
        dfs(0, -1, 0);
        for (int i = 1; i < LOG; i++) {
            for (int j = 0; j < n; j++) {
                if (p[j][i-1] != -1) {
                    mn[j][i] = min(mn[j][i-1], mn[p[j][i-1]][i-1]);
                    mx[j][i] = max(mx[j][i-1], mx[p[j][i-1]][i-1]);
                    sum[j][i] = sum[j][i-1] + sum[p[j][i-1]][i-1];
                    p[j][i] = p[p[j][i-1]][i-1];
                }
                else {
                    p[j][i] = -1;
                    mn[j][i] = INT_MAX;
                    mx[j][i] = INT_MIN;
                    sum[j][i] = 0;
                }
            }
        }
    }
    int lca(int u, int v)
    {
        if (l[u] > l[v])
            swap(u, v);
        int d = l[v] - l[u];
        for (int i = 0; i < LOG; i++) {
            if (CHECK(d, i)) {
                v = p[v][i];
            }
        }
        if (u == v) return u;
        for (int i = LOG - 1; i >= 0; i--) {
            if (p[u][i] != p[v][i]) {
                u = p[u][i];
                v = p[v][i];
            }
        }
        return p[u][0];
    }
    int minimum(int u, int v)
    {
        int ret = INT_MAX;
        if (l[u] > l[v])
            swap(u, v);
        int d = l[v] - l[u];
        for (int i = 0; i < LOG; i++) {
            if (CHECK(d, i)) {
                ret = min(ret, mn[v][i]);
                v = p[v][i];
            }
        }
        if (u == v) return ret;
        for (int i = LOG - 1; i >= 0; i--) {
            if (p[u][i] != p[v][i]) {
                ret = min(ret, mn[u][i]);
                ret = min(ret, mn[v][i]);
                u = p[u][i];
                v = p[v][i];
            }
        }
        ret = min(ret, mn[u][0]);
        ret = min(ret, mn[v][0]);
        return ret;
    }
    int maximum(int u, int v)
    {
        int ret = INT_MIN;
        if (l[u] > l[v])
            swap(u, v);
        int d = l[v] - l[u];
        for (int i = 0; i < LOG; i++) {
            if (CHECK(d, i)) {
                ret = max(ret, mx[v][i]);
                v = p[v][i];
            }
        }
        if (u == v) return ret;
        for (int i = LOG - 1; i >= 0; i--) {
            if (p[u][i] != p[v][i]) {
                ret = max(ret, mx[u][i]);
                ret = max(ret, mx[v][i]);
                u = p[u][i];
                v = p[v][i];
            }
        }
        ret = max(ret, mx[u][0]);
        ret = max(ret, mx[v][0]);
        return ret;
    }
    LL accumulation(int u, int v)
    {
        LL ret = 0;
        if (l[u] > l[v])
            swap(u, v);
        int d = l[v] - l[u];
        for (int i = 0; i < LOG; i++) {
            if (CHECK(d, i)) {
                ret += sum[v][i];
                v = p[v][i];
            }
        }
        if (u == v) return ret;
        for (int i = LOG - 1; i >= 0; i--) {
            if (p[u][i] != p[v][i]) {
                ret += sum[u][i];
                ret += sum[v][i];
                u = p[u][i];
                v = p[v][i];
            }
        }
        ret += sum[u][0];
        ret += sum[v][0];
        return ret;
    }
    /*
        To use array queries:

            Initialize for an array a[n]:
                LCA lca;
                lca.init1(n + 1);
                for (int i = 0; i < n; i++) {
                    lca.addEdge(i, i + 1, a[i]);
                }
                lca.build();
                lca.fast_g(); // Only for O(1) queries

            For query(l, r) where l and r are 0-indexed but any kind of query
            including O(logn) and O(1) ones:
                O(logn):
                    cout << lca.minimum(l, r + 1) << endl;
                    cout << lca.maximum(l, r + 1) << endl;
                    cout << lca.accumulation(l, r + 1) << endl;
                O(1):
                    cout << lca.fast_min(l, r + 1) << endl;
                    cout << lca.fast_max(l, r + 1) << endl;

    */
    void fast_g()
    {
        logs = new int[n];
        powr = new int[LOG];
        logs[1] = 0;
        powr[0] = 1;
        for (int i = 1; i < LOG; i++)
            powr[i] = powr[i-1] * 2;
        for (int i = 2; i < n; i++)
            logs[i] = logs[i/2] + 1;
    }
    int fast_min(int l, int r)
    {
        int j = logs[r-l];
        return min(mn[r][j], mn[l+powr[j]][j]);
    }
    int fast_max(int l, int r)
    {
        int j = logs[r-l];
        return max(mx[r][j], mx[l+powr[j]][j]);
    }
};