/*
    #1. Elements are numbered from 0 to (n - 1) inclusive
    #2. Source: Competitive Programming 1 (Steven Halim)
*/
struct UnionFindDisjointSet
{
    vector<int> pset;
    UnionFindDisjointSet(int n) {
        pset.resize(n);
        for (int i = 0; i < n; i++) pset[i] = i;
    }
    int findSet(int i) {
        return (pset[i] == i) ? i : (pset[i] = findSet(pset[i]));
    }
    void unionSet(int i, int j) {
        pset[findSet(i)] = findSet(j);
    }
    bool isSameSet(int i, int j) {
        return findSet(i) == findSet(j);
    }
};

/*
    #1. T1 -> Data type required for resultant tree's total edge weight (MST cost)
    #2. T2 -> Data type required for maximum edge weight
    #3. Nodes are numbered from 0 to (n - 1) inclusive
    #4. Can find minimum MST or maximum MST depending on value of 'bool minimum' during function call
    #5. Introduced two data types for memory efficiency
    #6. Source: Competitive Programming 1 (Steven Halim)
*/
template<typename T1, typename T2>
struct UndirectedGraphMST
{
    int nodes;
    vector<pair<T2, pii>> edges;

    UndirectedGraphMST(int n)
    {
        nodes = n;
    }
    void addEdge(int u, int v, T2 weight)
    {
        edges.pb({weight, {u, v}});
    }
    pair<T1, vector<pii>> MST(bool minimum)  /* Total cost & vector of resultant tree edges */
    {
        T1 sign = minimum ? 1 : -1;
        T1 mst_cost = 0; vector<pii> tree_edges;
        UnionFindDisjointSet S(nodes);
        priority_queue<pair<T2, pii>> edgeList;
        for (auto e : edges) edgeList.push({-e.ff * sign, {e.ss.ff, e.ss.ss}});

        while (!edgeList.empty()) {
            pair<T2, pii> top = edgeList.top(); edgeList.pop();
            if (!S.isSameSet(top.ss.ff, top.ss.ss)) {
                mst_cost += -top.ff * sign;
                S.unionSet(top.ss.ff, top.ss.ss);
                tree_edges.pb({top.ss.ff, top.ss.ss});
                /* One of the selected edges, do anything else if needed */
            }
        }
        return {mst_cost, tree_edges};
    }
};
