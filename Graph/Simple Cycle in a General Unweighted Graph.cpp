/*
    #1. We have a general unweighted graph and we are interested in any simple cycle of this graph.
    #2. No self-loops or multiple edges allowed.
    #3. Usable Functions:
        i.   bool any() ->
             * Call this anytime to know if there is any cycle at all.
             * Time: O(nodes + edges) for DFS
        ii.  VI find_simple_cycle(int a, int b) ->
             * Call this anytime if you know a and b.
             * See more details about a & b in the comments inside the function.
             * It returns a vector containing the cycle.
             * Time: O(nodes + edges) for BFS
        iii. VI getSimpleCycle() ->
             * Call this anytime to get empty vector or the cycle depending on if there is any cycle or not.
             * First calling any() and then find_simple_cycle(..) is necessary.
             * Unless we already know a & b, in which case, just call find_simple_cycle(a, b).
               Handle this manually (change the code inside the function), if ever needed.
             * Time: 2 * O(nodes + edges) for any()(DFS) and find_simple_cycle(..)(BFS)
    #4. Source & Intuition Inspiration:
        i.   https://cp-algorithms.com/graph/finding-cycle.html
        ii.  https://www.geeksforgeeks.org/find-any-simple-cycle-in-an-undirected-unweighted-graph/
    #5. Problems (easy to hard) - (role model submission / problem page):
        i.   https://vjudge.net/solution/26627427
*/
struct SimpleCycleFinder
{
    int nodes;
    VVI AdjList;
    bool directed;
    SimpleCycleFinder(int n, bool directed) : nodes(n), AdjList(n), directed(directed)
    { }
    void addEdge(int u, int v)
    {
        AdjList[u].push_back(v);
    }
    VI color;
    int from, to;   /** Two members of a simple cycle with an edge between them */
    bool dfs(int v, int p)
    {
        color[v] = 1;
        for (int u : AdjList[v]) {
            if (!directed && u == p) continue;
            if (color[u] == 0) {
                if (dfs(u, v)) return true;
            }
            else if (color[u] == 1) {
                from = v;
                to = u;
                return true;
            }
        }
        color[v] = 2;
        return false;
    }
    bool any()  /** Check if there is any cycle in the graph */
    {
        color = VI(nodes);
        from = -1;
        for (int v = 0; v < nodes; v++) {
            if (color[v] == 0 && dfs(v, -1))
                break;
        }
        return from != -1;
    }
    VI find_simple_cycle(int a, int b)
    {
        /**
            #1. If directed, there is a directed edge (a -> b) which is part of a cycle.
            #2. If undirected, there is an undirected edge between a & b which is part of a cycle.
            #3. The returning vector that stores the simple cycle has a, then b as the first two nodes.
        */
        swap(a, b);
        VI simple_cycle;
        VI par = VI(nodes, -1);
        VB vis = VB(nodes);
        queue<int> q;
        q.push(a);
        bool ok = true;
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            vis[node] = 1;
            for (int child : AdjList[node]) {
                if (!directed && node == a && child == b) continue;
                if (vis[child] == 0) {
                    par[child] = node;
                    if (child == b) {
                        ok = false;
                        break;
                    }
                    q.push(child);
                    vis[child] = 1;
                }
            }
            if (ok == false) break;
        }
        simple_cycle.clear();
        int x = par[b];
        while (x != a) {
            simple_cycle.push_back(x);
            x = par[x];
        }
        simple_cycle.push_back(a);
        simple_cycle.push_back(b);
        reverse(all(simple_cycle));
        return simple_cycle;
    }
    VI getSimpleCycle() /** Finds any cycle if it exists, without knowing anything beforehand */
    {
        if (!any()) return {};
        else return find_simple_cycle(from, to);
    }
};
