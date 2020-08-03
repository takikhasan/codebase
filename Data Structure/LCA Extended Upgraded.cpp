/*
    #1. T1 -> Data type required for query
    #2. T2 -> Data type required for edge weight
    #3. Introduced two data types for memory efficiency
*/
template<typename T1, typename T2>
struct LCA
{
    typedef pair<int, T2> ii;
    const int MIN = 1, MAX = 2, SUM = 3, GCD = 4;
    /* 0 indexed */
    int n;
    vector<int> l;
    vector<vector<int>> p;
    vector<vector<T1>> val;
    int OPTION;
    T1 OPTION_VAL;
    /* parent, val, option */
    int LOG;
    vector<int> logs, powr;
    vector<vector<ii>> g;
    LCA(int n, int option) : n(n), l(n), g(n), OPTION(option)
    {
        LOG = log2(n) + 1;
        OPTION_VAL = (OPTION == SUM || option == GCD) ? 0 : ((OPTION == MIN) ? numeric_limits<T1>::max() : numeric_limits<T1>::min());
    }
    LCA(int n, vector<vector<ii>> g, int option) : n(n), l(n), g(g), OPTION(option)
    {
        LOG = log2(n) + 1;
        OPTION_VAL = (OPTION == SUM || option == GCD) ? 0 : ((OPTION == MIN) ? numeric_limits<T1>::max() : numeric_limits<T1>::min());
    }
    void addEdge(int u, int v, T2 w)
    {
        g[u].pb(mp(v, w));
//        g[v].pb(mp(u, w));
    }
    void dfs(int u, int pp, int ll)
    {
        l[u] = ll++;
        p[u][0] = pp;
        for (ii x : g[u]) {
            if (x.ff != pp) {
                val[x.ff][0] = x.ss;
                dfs(x.ff, u, ll);
            }
        }
    }
    T1 func(T1 x, T2 y)
    {
//        return x + y;
//        return min(x, y);
//        return max(x, y);
        return gcd(x, y);
    }
    void build()
    {
        p = vector<vector<int>> (n, vector<int> (LOG));
        val = vector<vector<T1>> (n, vector<T1> (LOG));
        dfs(0, -1, 0);
        for (int i = 1; i < LOG; i++) {
            for (int j = 0; j < n; j++) {
                if (p[j][i-1] != -1) {
                    val[j][i] = func(val[j][i-1], val[p[j][i-1]][i-1]);
                    p[j][i] = p[p[j][i-1]][i-1];
                }
                else {
                    p[j][i] = -1;
                    val[j][i] = OPTION_VAL;
                }
            }
        }
    }
    int lca(int u, int v)
    {
        if (l[u] > l[v]) swap(u, v);
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
    T1 query(int u, int v)
    {
        T1 ret = OPTION_VAL;
        if (l[u] > l[v]) swap(u, v);
        int d = l[v] - l[u];
        for (int i = 0; i < LOG; i++) {
            if (CHECK(d, i)) {
                ret = func(ret, val[v][i]);
                v = p[v][i];
            }
        }
        if (u == v) return ret;
        for (int i = LOG - 1; i >= 0; i--) {
            if (p[u][i] != p[v][i]) {
                ret = func(ret, val[u][i]);
                ret = func(ret, val[v][i]);
                u = p[u][i];
                v = p[v][i];
            }
        }
        ret = func(ret, val[u][0]);
        ret = func(ret, val[v][0]);
        return ret;
    }
    /*
        To use array queries:

            Initialize for an array a[n]:
                LCA<T1, T2> lca(n + 1); // T1 -> Data type for Query, T2 -> Data type for array element
                for (int i = 0; i < n; i++) {
                    lca.addEdge(i, i + 1, a[i]);
                }
                lca.build();
                lca.fast_g(); // Only for O(1) queries

            For query(l, r) where l and r are 0-indexed but any kind of query
            including O(logn) and O(1) ones:
                O(logn):
                    cout << lca.query(l, r + 1) << endl;
                O(1):
                    cout << lca.fast_query(l, r + 1) << endl;

    */
    void fast_g()
    {
        logs.resize(n); powr.resize(LOG);
        logs[1] = 0;    powr[0] = 1;
        for (int i = 1; i < LOG; i++)   powr[i] = powr[i-1] * 2;
        for (int i = 2; i < n  ; i++)   logs[i] = logs[i/2] + 1;
    }
    T1 fast_query(int l, int r)
    {
        int j = logs[r-l];
        return func(val[r][j], val[l+powr[j]][j]);
    }
};
