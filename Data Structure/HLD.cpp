/**
 * Source & the following comments are from: KACTL Github
 * Author: Benjamin Qi, Oleksandr Kulkov, chilli
 * Date: 2020-01-12
 * License: CC0
 * Source: https://codeforces.com/blog/entry/53170, https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Trees%20(10)/HLD%20(10.3).h
 * Description: Decomposes a tree into vertex disjoint heavy paths and light
 * edges such that the path from any leaf to the root contains at most log(n)
 * light edges. Code does additive modifications and max queries, but can
 * support commutative segtree modifications/queries on paths and subtrees.
 * Takes as input the full adjacency list. VALS\_EDGES being true means that
 * values are stored in the edges, as opposed to the nodes. All values
 * initialized to the segtree default. Root must be 0.
 * Time: O((\log N)^2)
 * Status: stress-tested against old HLD
 */
#pragma once

#include "../data-structures/LazySegmentTree.h"

using vi = VI;
template <bool VALS_EDGES> struct HLD {
	int N, tim = 0;
	vector<vi> adj;
	vi par, siz, depth, rt, pos;
	Node *tree;
	HLD(vector<vi> adj_)
		: N(SZ(adj_)), adj(adj_), par(N, -1), siz(N, 1), depth(N),
		  rt(N),pos(N),tree(new Node(0, N)){ dfsSz(),dfsHld();}
	void dfsSz(int v = 0) {
		if (par[v] != -1) adj[v].erase(find(all(adj[v]), par[v]));
		for (int& u : adj[v]) {
			par[u] = v, depth[u] = depth[v] + 1;
			dfsSz(u);
			siz[v] += siz[u];
			if (siz[u] > siz[adj[v][0]]) swap(u, adj[v][0]);
		}
	}
	void dfsHld(int v = 0) {
		pos[v] = tim++;
		for (int u : adj[v]) {
			rt[u] = (u == adj[v][0] ? rt[v] : u);
			dfsHld(u);
		}
	}
	/**
        par[u] = parent of u, par[0] = -1, 0 is root.
        siz[u] = subtree size of u, including u itself.
        depth[u] = number of edges from root (0).

        pos[u] = index of u in the segment tree.
        rt[u] = highest vertex in the chain of u.

        Range of the subtree of u in the segment tree:
            -> [ pos[u] ... (pos[u]+siz[u]-1) ] (inclusive).
            -> Trick for edge (value in edges) mode:
                Each position of the segment tree corresponds to the edge between the corresponding node and its parent.
                So, the range will be [ (pos[u]+1) ... (pos[u]+siz[u]-1) ] (inclusive).

        If u and v are in the same chain, for the corresponding segment tree range:
            if (depth[u] > depth[v) /// Because, lower depth has lower position in the segment tree.
                swap(u, v);
            -> Now, the range is [ pos[u] ... pos[v] ] (inclusive).
            -> Trick for edge (value in edges) mode:
                Each position of the segment tree corresponds to the edge between the corresponding node and its parent.
                So, the range will be [ (pos[u]+1) ... pos[v] ] (inclusive).

        The chains are vertex disjoint.
	*/
	template <class B> void process(int u, int v, B op) {
		for (; rt[u] != rt[v]; v = par[rt[v]]) {
			if (depth[rt[u]] > depth[rt[v]]) swap(u, v);
			op(pos[rt[v]], pos[v] + 1);
		}
		if (depth[u] > depth[v]) swap(u, v);
		op(pos[u] + VALS_EDGES, pos[v] + 1);
	}
	void modifyPath(int u, int v, int val) {
		process(u, v, [&](int l, int r) { tree->add(l, r, val); });
	}
	int queryPath(int u, int v) { // Modify depending on query
		int res = -1e9;
		process(u, v, [&](int l, int r) {
				res = max(res, tree->query(l, r));
		});
		return res;
	}
	int querySubtree(int v) { // modifySubtree is similar
		return tree->query(pos[v] + VALS_EDGES, pos[v] + siz[v]);
	}
};
