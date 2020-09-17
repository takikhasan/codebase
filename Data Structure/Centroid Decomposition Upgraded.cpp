/*
    #1. Intuition:
        i.  https://www.quora.com/q/threadsiiithyderabad/Centroid-Decomposition-of-a-Tree
    #2. Source:
        i.  https://codeforces.com/contest/342/submission/11945201
    #3. Problems (Easy to Hard):
        i.  https://vjudge.net/solution/27239179
        ii. https://vjudge.net/solution/27176384
        iii.https://vjudge.net/solution/27296953
        iv. https://vjudge.net/solution/27315325
        v.  https://vjudge.net/solution/27331469
*/
struct CentroidDecomposition {
	VI par;
	VI sub;
	VB done;
	int nn;

	CentroidDecomposition(const VVI &g) {
		int n = SZ(g);
		par = sub = VI(n);
		done = VB(n);
		decompose(0, -1, g);
	}

    void dfs1(int u, int p, const VVI &g)
    {
        sub[u] = 1;
        nn++;
        for(int v : g[u]) {
            if(!done[v] && v != p) {
                dfs1(v, u, g);
                sub[u] += sub[v];
            }
        }
    }

    int dfs2(int u, int p, const VVI &g)
    {
        for(int v : g[u]) {
            if(sub[v] > (nn / 2) && !done[v] && v != p)
                return dfs2(v, u, g);
        }
        return u;
    }

    void decompose(int root, int p, const VVI &g)
    {
        nn = 0;
        dfs1(root, root, g);

        int centroid = dfs2(root, root, g);
        if(p == -1) p = centroid;

        par[centroid] = p;
        done[centroid] = 1;

        for(int v : g[centroid]) {
            if (!done[v]) decompose(v, centroid, g);
        }
    }
};
