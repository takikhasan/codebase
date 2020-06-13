/*
    #1. T1 -> Data type required for maximum distance
    #2. T2 -> Data type required for maximum edge weight
    #3. Introduced two data types for memory efficiency
*/
template<typename T1, typename T2>
class DirectedGraph
{
    typedef pair<T1, int> ii;
    const T1 INF = numeric_limits<T1>::max();

public:
    int nodes;
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
    void dijkstra(int s)
    {
        for (int i = 0; i < nodes; i++) {
            dist[i] = INF;
            par[i] = -1;
        }
        priority_queue<ii, vector<ii>, greater<ii>> pq; /** BFS: queue<ii> pq; */
        dist[s] = 0;
        pq.push(ii(0, s));
        while (!pq.empty()) {
            ii top = pq.top(); /** BFS: pq.front(); */
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
                }
            }
        }
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
};
