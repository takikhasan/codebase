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
        return __gcd(x, y);
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

/*
    #1. Source & Intuition:
        i.  https://codeforces.com/blog/entry/43230
        ii. https://cp-algorithms.com/data_structures/sqrt_decomposition.html
    #2. Problems (easy to hard):
        i.  https://vjudge.net/solution/27221065
        ii. https://vjudge.net/solution/27221085
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
        LCA<int, int> G(n, tree, 1);
        G.build();

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
