#include<bits/stdc++.h>
using namespace std;

// When using sort(vii.begin(), vii.end()) for vector<pair<int, int> > vii,
// the pairs are compared lexicographically. As a result, the pairs with
// equal first elements are also sorted by their second element. 
// But sometimes we might need to preserve the relative order of pairs with
// with the same first elements.
// This code sorts vii by their first element where the
// relative order of pairs with equal first elements is preserved.
// Complexity: nlogn
// Source: stackoverflow

struct compare_first_only {
    template<typename T1, typename T2>
    bool operator()(const std::pair<T1, T2>& p1, const std::pair<T1, T2>& p2) {
        return p1.first < p2.first;
    }
};

int main()
{
    vector<pair<int, int> > vii;
    stable_sort(vii.begin(), vii.end(), compare_first_only());

    return 0;
}