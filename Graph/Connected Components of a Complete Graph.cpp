/*
    #1. There is a complete graph, but there are some blocked roads
    #2. We need to find the components without using blocked roads
    #3. Because the number of usable roads is too high, we should use this template
    #4. Otherwise, basic dfs is enough
    #4. Problems (easy to hard) - (role model submission / problem page):
        i.  https://codeforces.com/contest/1243/submission/82715710 (direct template)
        ii. https://codeforces.com/contest/190/submission/82717910
*/
vector<int> ust[M];
unordered_set<int, custom_hash> un_vis;

bool f(int u, int v)
{
    if (!SZ(ust[u])) return 0;
    auto it = lower_bound(all(ust[u]), v);
    if (it == ust[u].end()) return 0;
    return *it == v;
}

void dfs(int u)
{
    vector<int> a;
    for (int v : un_vis) {
        if (!f(u, v)) {
            a.pb(v);
        }
    }
    for (int v : a) {
        un_vis.erase(v);
    }
    for (int v : a) {
        dfs(v);
    }
}

int main()
{
    int n, m;
    I(n, m);
    for (int i = 0; i < n; i++) {
        un_vis.insert(i);
    }
    while (m--) {
        int a, b;
        I(a, b);
        a--; b--;
        ust[a].pb(b);
        ust[b].pb(a);
    }
    for (int i = 0; i < n; i++) {
        sort(all(ust[i]));
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (un_vis.find(i) != un_vis.end()) {
            un_vis.erase(i);
            dfs(i);
            ans++;
        }
    }
    O(ans - 1);

    return 0;
}
