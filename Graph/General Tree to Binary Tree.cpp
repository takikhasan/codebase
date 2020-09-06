/*
    #1. This is totally experimental.
    #2. I haven't solved even one problem using this.
    #3. One of the very few use cases this technique might have can be found here:
        i.  https://www.quora.com/What-is-the-approach-to-solve-the-SPOJ-problem-QTREE4/answer/Florian-Leimgruber
*/
struct GeneralToBinary  /// Tree ~ O(n * logn)
{
    void convert(vector<set<pii>> &g, int root)
    {
        /** We'll make this a binary tree rooted at the specified root,
            the trick is to give the extra weights values that will never change the answer of our queries.
        */
        dfs(g, root, -1);
    }
    void dfs(vector<set<pii>> &g, int u, int p)
    {
        vector<pii> v;
        for (auto it = g[u].begin(); it != g[u].end(); it++) {
            pii pp = *it;
            if (pp.ff != p) {
                v.pb(pp);
                g[pp.ff].erase({u, pp.ss});
            }
        }
        VI in;
        for (int i = 0; i < SZ(v) - 2; i++) {
            set<pii> e;
            in.pb(SZ(g));
            g.pb(e);
        }
        int last = u;
        for (int i = 0; i < SZ(v) - 2; i++) {
            g[u].erase(v[i]);
            g[last].insert(v[i]);
            g[v[i].ff].insert({last, v[i].ss});
            dfs(g, v[i].ff, last);
            g[last].insert({in[i], 0});
            g[in[i]].insert({last, 0});
            last = in[i];
        }
        for (int i = max(SZ(v) - 2, 0); i < SZ(v); i++) {
            g[u].erase(v[i]);
            g[last].insert(v[i]);
            g[v[i].ff].insert({last, v[i].ss});
            dfs(g, v[i].ff, last);
        }
    }
} Converter;
