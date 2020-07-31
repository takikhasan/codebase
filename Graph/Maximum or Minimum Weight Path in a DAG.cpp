/*
    #1. T1 -> Data type required for maximum distance
    #2. T2 -> Data type required for maximum edge weight
    #3. Introduced two data types for memory efficiency
    #4. We want to know about the maximum/minimum weight path of a DAG
    #5. The path can start and end anywhere
    #6. dp[i] is the highest/lowest weight of the path that starts at i
        (path could stop anywhere, including at i, in order to maximize/minimize total path weight)
    #7. Inspiration:
        i.  https://www.geeksforgeeks.org/longest-path-in-a-directed-acyclic-graph-dynamic-programming/
    #8. Problems (easy to hard) - (role model submission / problem page):
        i.  https://vjudge.net/solution/26627427
*/
template<typename T1, typename T2>
class BestPathDAG
{
public:
    int nodes;
    vector<vector<pair<int, T2>>> AdjList;
    vector<T1> dp;
    VI to;
    VB vis;
    bool longest;   /* Maximum weight or not */
    int best_starting;
    BestPathDAG(int n, bool longest) : nodes(n), AdjList(n), dp(n), longest(longest)
    { }
    void addEdge(int u, int v, T2 c)
    {
        AdjList[u].push_back(make_pair(v, c));
    }
    void dfs(int u)
    {
        vis[u] = 1;
        for (auto e : AdjList[u]) {
            if (!vis[e.ff]) {
                dfs(e.ff);
            }
            T1 val = dp[e.ff] + e.ss;
            if (longest) {
                if (val > dp[u]) {
                    dp[u] = val;
                    to[u] = e.ff;
                }
            }
            else {
                if (val < dp[u]) {
                    dp[u] = val;
                    to[u] = e.ff;
                }
            }
        }
    }
    T1 Solve()
    {
        fill(all(dp), 0);
        vis = VB(nodes);
        to = VI(nodes, -1);
        for (int i = 0; i < nodes; i++) {
            if (!vis[i]) {
                dfs(i);
            }
        }
        T1 best = dp[0];
        best_starting = 0;
        for (int i = 1; i < nodes; i++) {
            if (longest) {
                if (dp[i] > best) {
                    best = dp[i];
                    best_starting = i;
                }
            }
            else {
                if (dp[i] < best) {
                    best = dp[i];
                    best_starting = i;
                }
            }
        }
        return best;
    }
    VI best_path_from(int start)
    {
        VI ret;
        ret.pb(start);
        while (to[start] != -1) {
            start = to[start];
            ret.pb(start);
        }
        return ret;
    }
    VI bestPath()
    {
        return best_path_from(best_starting);
    }
};
