/*
    #1. Intuition:
        i.  https://www.quora.com/q/threadsiiithyderabad/Centroid-Decomposition-of-a-Tree
    #2. Source:
        i.  https://codeforces.com/contest/342/submission/11945201
    #3. Problems (Easy to Hard):
        i.  https://vjudge.net/solution/27239179
        ii. https://vjudge.net/solution/27176384
*/
struct CentroidDecomposition {
	vector<set<int>> g; // it's not vector<vector<int>>!
	vector<int> par;
	vector<int> sub;
	int nn;

	CentroidDecomposition(vector<set<int>> &tree) : g(tree) {
		int n = tree.size();
		par.resize(n);
		sub = VI(n);
		decompose(0, -1);
	}

    void dfs1(int u,int p)
    {
        sub[u]=1;
        nn++;
        for(auto it=g[u].begin();it!=g[u].end();it++)
            if(*it!=p)
            {
                dfs1(*it,u);
                sub[u]+=sub[*it];
            }
    }
    int dfs2(int u,int p)
    {
        for(auto it=g[u].begin();it!=g[u].end();it++)
            if(*it!=p && sub[*it]>nn/2)
                return dfs2(*it,u);
        return u;
    }
    void decompose(int root,int p)
    {
        nn=0;
        dfs1(root,root);
        int centroid = dfs2(root,root);
        if(p==-1)p=centroid;
        par[centroid]=p;
        for(auto it=g[centroid].begin();it!=g[centroid].end();it++)
        {
            g[*it].erase(centroid);
            decompose(*it,centroid);
        }
        g[centroid].clear();
    }
};
