// requires c++11 or higher

#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int main()
{
    ordered_set<int> s;
    s.insert(1);
    s.insert(12);
    s.insert(123);
    s.insert(1234);
    s.erase(123);
    cout << s.size() << endl;
    cout << s.order_of_key(1234) << endl; // how many numbers less than 1234
    cout << *s.find_by_order(1) << endl; // the value at index 1 (0 indexed)
    cout << (end(s) == s.find_by_order(100)) << endl;

    return 0;
}
