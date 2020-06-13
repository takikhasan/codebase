/*
    #1. T1 -> Data type required for maximum distance
    #2. T2 -> Data type required for maximum edge weight
    #3. Introduced two data types for memory efficiency
    #4. Problems (easy to hard) - (role model submission / problem page):
        i.  https://codeforces.com/contest/1206/submission/83601330 (direct template)
        ii. https://codeforces.com/contest/1364/submission/83696823
*/
template<typename T1, typename T2>
class DirectedGraph
{
    typedef pair<T1, int> ii;
    const T1 INF = numeric_limits<T1>::max();

public:
    int nodes;
    int furthest_member, second_furthest;
    vector<vector<pair<int, T2>>> AdjList;
    vector<T1> dist;
    vector<int> par;
    DirectedGraph(int n)
    {
        nodes = n;
        AdjList.resize(n);
        dist.resize(n);
        par.resize(n);
    }
    void addEdge(int u, int v, T2 c)
    {
        AdjList[u].push_back(make_pair(v, c));
    }
    T1 minimumWeightCycle(int s)
    {
        T1 ret = numeric_limits<T1>::max();
        for (int i = 0; i < nodes; i++) {
            dist[i] = INF;
            par[i] = -1;
        }
        priority_queue<ii, vector<ii>, greater<ii>> pq; /** For unweighted graph(BFS): queue<ii> pq; */
        dist[s] = 0;
        pq.push(ii(0, s));
        while (!pq.empty()) {
            ii top = pq.top(); /** For unweighted graph(BFS): pq.front(); */
            pq.pop();
            T1 d = top.first;
            int u = top.second;
            if (dcmp(d - dist[u]) == 0) {
                for (auto it = AdjList[u].begin(); it != AdjList[u].end(); it++) {
                    int v = it->first; T2 weight_u_v = it->second;
                    if (dcmp(dist[u] + weight_u_v - dist[v]) == -1) {
                        dist[v] = dist[u] + weight_u_v;
                        par[v] = u;
                        pq.push(ii(dist[v], v));
                    }
                    else {
                        if (par[v] != u && par[u] != v) {
                            T1 curr = dist[u] + dist[v] + weight_u_v;
                            if (curr < ret) {
                                ret = curr;
                                furthest_member = u;
                                second_furthest = v;
                            }
                        }
                    }
                }
            }
        }
        return ret;
    }
    vector<int> path(int dest)
    {
        vector<int> ret;
        if (par[dest] == -1)
            return ret;
        int curr = dest;
        while (curr != -1) {
            ret.pb(curr);
            curr = par[curr];
        }
        reverse(all(ret));
        return ret;
    }
    vector<int> cycle()
    {
        vector<int> path1 = path(furthest_member);
        vector<int> path2 = path(second_furthest);
        reverse(all(path2)); path2.pop_back();
        vector<int> ret;
        for (int u : path1) ret.pb(u);
        for (int u : path2) ret.pb(u);
        return ret;
    }
    vector<int> flower()
    {
        /**
            Because this is an undirected graph, sometimes the minimum weight cycle through 's' may look like a flower,
            with repeating nodes at the beginning and at the end with a simple cycle in between.
            This function returns the simple cycle in the middle (top of the flower).
        */
        vector<int> path1 = path(furthest_member);
        vector<int> path2 = path(second_furthest);
        reverse(all(path1)); reverse(all(path2));
        int flower_start;
        while (path1.back() == path2.back()) {
            flower_start = path1.back();
            path1.pop_back();
            path2.pop_back();
        }
        reverse(all(path1));
        vector<int> ret;
        ret.push_back(flower_start);
        for (int u : path1) ret.pb(u);
        for (int u : path2) ret.pb(u);
        return ret;
    }
};
