/*
    #1. Finds the strongly connected components and creates the DAG made by considering strongly connected components as nodes
    #2. The algorithm is Kosaraju's algorithm
*/
struct Kosaraju
{
    vector<bool> vis;
    stack<int> stck;
    vector<vector<int>> g, rg;
    vector<int> col;
    vector<vector<int>> res_dag;
    void dfs1(int u)
    {
        vis[u] = 1;
        for (int v : g[u]) {
            if (!vis[v]) dfs1(v);
        }
        stck.push(u);
    }
    void dfs2(int u, int curr)
    {
        col[u] = curr;
        vis[u] = 1;
        for (int v : rg[u]) {
            if (!vis[v]) dfs2(v, curr);
        }
    }
    void solve(const vector<vector<int>> &gg)
    {
        g = gg;
        int n = SZ(g);
        rg.clear();
        rg.resize(n);
        for (int u = 0; u < n; u++) {
            for (int v : g[u]) rg[v].pb(u);
        }
        stck = stack<int>();
        vis.resize(n);
        fill(all(vis), 0);
        col.resize(n);
        res_dag.clear();
        /* Algorithm Start */
        for (int i = 0; i < n; i++) {
            if (!vis[i]) dfs1(i);
        }
        fill(all(vis), 0);
        int scc_count = 0;
        while (!stck.empty()) {
            int top = stck.top();
            stck.pop();
            if (!vis[top]) dfs2(top, scc_count++);
        }
        res_dag.resize(scc_count);
        for (int u = 0; u < n; u++) {
            for (int v : g[u]) {
                if (col[u] != col[v]) {
                    res_dag[col[u]].pb(col[v]); /* Multiple edges might be present, can be modified to change this */
                }
            }
        }
    }
};
