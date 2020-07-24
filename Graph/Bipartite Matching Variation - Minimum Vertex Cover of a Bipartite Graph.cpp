/*
    #1. Optimized Kuhn for Maximum Matching on Bipartite Graph
    #2. Worst case: O(V*V) (much faster in use)
    #3. Works better than hopcroft-karp (if not always, almost always)
*/
struct BipartiteMatcher {
    vector<vector<int>> G;
    vector<int> L, R, Viz;

    BipartiteMatcher(int n, int m) :
        G(n), L(n, -1), R(m, -1), Viz(n) {
    }
    void AddEdge(int a, int b)
    {
        G[a].push_back(b);
    }
    bool Match(int node)
    {
        if (Viz[node]) return false;
        Viz[node] = true;
        for (auto vec : G[node]) {
            if (R[vec] == -1) {
                L[node] = vec;
                R[vec] = node;
                return true;
            }
        }
        for (auto vec : G[node]) {
            if (Match(R[vec])) {
                L[node] = vec;
                R[vec] = node;
                return true;
            }
        }
        return false;
    }
    int Solve()
    {
        bool ok = true;
        while (ok) {
            ok = 0;
            fill(Viz.begin(), Viz.end(), 0);
            for (int i = 0; i < (int)L.size(); ++i) {
                if (L[i] == -1) ok |= Match(i);
            }
        }
        int ret = 0;
        for (int i = 0; i < L.size(); ++i)
            ret += (L[i] != -1);
        return ret;
    }
};

/*
    #1. Minimum Vertex Cover of a Bipartite Graph
    #2. We want to cover at least one end of all the edges using minimum number of nodes.
    #3. According to Konig's theorem: In bipartite graphs, maximum matching = minimum vertex cover.
    #4. Intuition:
        i.  https://en.wikipedia.org/wiki/K%C5%91nig%27s_theorem_(graph_theory)#:~:text=In%20particular%2C%20the%20minimum%20vertex,in%20fact%20the%20same%20size.
    #5. Problems (easy to hard) - (role model submission / problem page):
        i.  https://vjudge.net/solution/26503097
*/
struct MVC
{
    BipartiteMatcher G = BipartiteMatcher(0, 0);
    MVC(int n, int m) : G(n, m) {}
    void addEdge(int u, int v) {
        G.AddEdge(u, v);
    }
    int solve() {
        return G.Solve();
    }
};
