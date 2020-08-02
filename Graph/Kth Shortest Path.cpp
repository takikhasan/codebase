/*
    #1. T1 -> Data type required for maximum distance
    #2. T2 -> Data type required for maximum edge weight
    #3. Introduced two data types for memory efficiency
    #4. In a general graph, we are interested in the Kth shortest paths to every node from a source node
    #5. Problems (easy to hard) - (role model submission / problem page):
        i.  https://vjudge.net/solution/26653200
*/
template<typename T1, typename T2>
class DirectedGraph
{
    typedef pair<T1, int> ii;
    const T1 INF = numeric_limits<T1>::max();

public:
    int nodes;
    vector<vector<pair<int, T2>>> AdjList;
    vector<vector<T1>> dist;
    vector<VI> par;
    VI vis;
    DirectedGraph(int n)
    {
        nodes = n;
        AdjList.resize(n);
        dist.resize(n);
        par.resize(n);
        vis.resize(n);
    }
    void addEdge(int u, int v, T2 c)
    {
        AdjList[u].push_back(make_pair(v, c));
    }
    struct Compare
    {
        bool operator()(const pair<ii, int> &a, const pair<ii, int> &b)
        {
            return a.ff.ff > b.ff.ff;
        }
    };
    void KthShortestPath(int s, int k)
    {
        /*
            We want to know the k'th shortest path to every node from s.
            In the process, we will find all the (1...k)th shortest paths from s.
            We will visit(use it to relax others) each node at most k times, that is enough for finding (1 to k)th shortest paths.

            dist[i][j] = (j + 1)'th shortest path distance from s to i where, (j >= 0 && j < k).
            par[i][j] = parent of i in the (j + 1)'th shortest path from s to i where, (j >= 0 && j < k).
            If par[i][j] == -1, that means there is no (j + 1)'th shortest path to i (Exception: starting node).

            vis[i] = number of times we have used i to 'relax' it's neighbors.
            vis[i] also means that we have found (1 to vis[i] inclusive) shortest paths from s to i.
            After the algorithm is over, if vis[i] < j, that means there is no j'th shortest path to i.

            We use any node for relaxing its neighbors at most k times.
        */
        for (int i = 0; i < nodes; i++) {
            par[i] = VI(k, -1);
            vis[i] = 0;
            dist[i].resize(k);
            for (int j = 0; j < k; j++) {
                dist[i][j] = INF;
            }
        }
//        auto compare = [](const pair<ii, int> &a, const pair<ii, int> &b) -> bool { return a.ff.ff > b.ff.ff; }; /* using capture should be useless here and may even be costly */
//        priority_queue<pair<ii, int>, vector<pair<ii, int>>, decltype(compare)> pq(compare); /** BFS: queue<ii> pq; */
        priority_queue<pair<ii, int>, vector<pair<ii, int>>, Compare> pq; /** BFS: queue<ii> pq; */
        pq.push({ii(0, s), -1});
        while (!pq.empty()) {
            auto top = pq.top(); /** BFS: pq.front(); */
            pq.pop();
            T1 d = top.first.ff;
            int u = top.ff.second;
            if (vis[u] < k) {
                dist[u][vis[u]] = d;
                par[u][vis[u]] = top.ss;
                vis[u]++;
                for (auto it = AdjList[u].begin(); it != AdjList[u].end(); it++) {
                    int v = it->first; T2 weight_u_v = it->second;
                    pq.push({ii(d + weight_u_v, v), u});
                }
            }
        }
        /*
            Time Complexity benchmark:
                After a lot of submissions, using struct as the comparator seems constant,
                while lambda is sometime slower, sometimes the same as struct. (We're going with struct)
                struct (40ms) : https://vjudge.net/solution/26653200
                lambda (50ms) : https://vjudge.net/solution/26653191
                lambda (40ms) : https://vjudge.net/solution/26653309
        */
    }
    vector<int> path(int dest, int k) /* Get the kth (1 indexed) shortest path to the dest */
    {
        vector<int> ret;
        if (par[dest][k-1] == -1)
            return ret;
        int curr = dest;
        while (curr != -1) {
            ret.pb(curr);
            curr = par[curr][k-1];
        }
        reverse(all(ret));
        return ret;
    }
};
