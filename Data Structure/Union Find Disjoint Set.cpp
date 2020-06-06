/*
    #1. Elements are numbered from 0 to (n - 1) inclusive
    #2. Source: Competitive Programming 1 (Steven Halim)
*/
struct UnionFindDisjointSet
{
    vector<int> pset;
    UnionFindDisjointSet(int n) {
        pset.resize(n);
        for (int i = 0; i < n; i++) pset[i] = i;
    }
    int findSet(int i) {
        return (pset[i] == i) ? i : (pset[i] = findSet(pset[i]));
    }
    void unionSet(int i, int j) {
        pset[findSet(i)] = findSet(j);
    }
    bool isSameSet(int i, int j) {
        return findSet(i) == findSet(j);
    }
};
