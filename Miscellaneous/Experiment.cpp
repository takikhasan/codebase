/**
 *  To be used as a member of MST class.
 */
pair<T1, VI> MST_multiple(bool minimum) /* Total cost & vector of resultant tree edge ids */
{
    T1 mst_cost = 0; VI tree_edges;
    UnionFindDisjointSet S(nodes);
    VI sorted;
    for (int i = 0; i < SZ(edges); i++) sorted.pb(i);
    sort(all(sorted), [&](int a, int b) { return edges[a].first < edges[b].first; });
    if (!minimum) reverse(all(sorted));
    VI same;
    VVI equal_weights;
    for (const int &in : sorted) {
        const auto &top = edges[in];
        if (SZ(same) == 0) {
            same.pb(in);
        }
        else {
            if (edges[same.back()].first == top.first) {
                same.pb(in);
            }
            else {
                equal_weights.pb(same);
                same.clear();
                same.pb(in);
            }
        }
    }
    equal_weights.pb(same);
    VVI options;
    options.clear();
    for (const VI &equals : equal_weights) {
        unordered_map<pii, VI, custom_hash_pair> table;
        for (const int &in : equals) {
            const auto &top = edges[in];
            int st1 = S.findSet(top.ss.ff);
            int st2 = S.findSet(top.ss.ss);
            if (st1 != st2) {
                if (st1 > st2) swap(st1, st2);
                table[{st1,st2}].pb(in);
            }
        }
        for (const int &in : equals) {
            const auto &top = edges[in];
            int st1 = S.findSet(top.ss.ff);
            int st2 = S.findSet(top.ss.ss);
            if (st1 != st2) {
                mst_cost += top.ff;
                S.unionSet(top.ss.ff, top.ss.ss);
                tree_edges.pb(in);
                /* One of the selected edges, do anything else if needed */
                options.pb(table[{st1,st2}]);
            }
        }
    }
    return {mst_cost, tree_edges};
}
