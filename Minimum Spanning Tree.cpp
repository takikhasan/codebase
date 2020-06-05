#include<bits/stdc++.h>
using namespace std;

// Source: Competitive Programming 1(Steven Halim)
// Minimum spanning tree for undirected weighed graph

typedef pair<int, int> ii;
priority_queue< pair<int, ii > > EdgeList;
#define REP(i, a, b) for (int i = int(a); i <= int(b); i++)
vector<int> pset(1000);
void initSet(int _size) { pset.resize(_size); REP (i, 0, _size - 1) pset[i] = i; }
int findSet(int i) { return (pset[i] == i) ? i : (pset[i] = findSet(pset[i])); }
void unionSet(int i, int j) { pset[findSet(i)] = findSet(j); }
bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
// this is union find disjoint set library

int main()
{
    // EdgeList.push(make_pair(-1, make_pair(u, v))); => First this is how you need to make the EdgeList
    int mst_cost = 0; initSet(V); // V is the number of vertices, they will be numbered 0...V-1
    vector<pair<int, int> > ans; // to store the edges of the resulting minimum spanning tree
    while (!EdgeList.empty()) {
            pair<int, ii> front = EdgeList.top(); EdgeList.pop();
            if (!isSameSet(front.second.first, front.second.second)) {
                    mst_cost += (-front.first);
                    unionSet(front.second.first, front.second.second);
                    ans.push_back(make_pair(front.second.first, front.second.second)); // Edge was just added
		    // Do anything else if needed
            }
    }
    printf("%d\n", mst_cost);

    return 0;
}