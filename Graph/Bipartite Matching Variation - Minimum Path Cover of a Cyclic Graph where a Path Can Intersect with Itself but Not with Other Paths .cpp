/*
    #1. Minimum Path Cover on a Directed Graph (can contain cycles) where the path can intersect with itself, but not with other paths
    #2. After the helper DFS runs, O(3^n) Submask DP is used
    #3. The nodes are 0 indexed
*/
struct MPC
{
    int n;
    vector<VI> g;
    vector<VB> vis;
    VB path_exists;
    MPC(int n) : n(n), g(n) {}
    void addEdge(int u, int v) {
        g[u].pb(v);
    }
    void dfs(int mask, int last) {
        vis[mask][last] = 1;
        path_exists[mask] = 1;
        for (int v : g[last]) {
            int next_mask = ON(mask, v);
            if (!vis[next_mask][v]) dfs(next_mask, v);
        }
    }
    int solve() {
        VI dp(1 << n);
        vis = vector<VB> (1 << n, VB(n));
        path_exists = VB(1 << n);
        for (int i = 0; i < n; i++) {
            dfs(ON(0, i), i);
        }
        for (int mask = 0; mask < (1 << n); mask++) {
            dp[mask] = !mask ? 0 : (path_exists[mask] ? 1 : CNT(mask));
            if (mask && !path_exists[mask]) {
                for (int submask = (mask - 1) & mask; submask > 0; submask = (submask - 1) & mask) {
                    dp[mask] = min(dp[mask], dp[submask] + dp[submask^mask]);
                }
            }
        }
        return dp[(1<<n)-1];
    }
};
