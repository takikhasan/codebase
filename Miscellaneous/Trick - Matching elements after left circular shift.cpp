/*
    #1. The value of temp[i] indicates the number of matching elements (a[i] == b[i])
    #2. Here, hypothetical array a means array of (i, i + 1, i + 2, ..., (i + n - 1) % n) elements of curr
    #3. And, hypothetical array b means array of (0, 1, 2, ..., n - 1) elements of target
    #4. Assumption: Elements of target must be unique (not proven, just intuition)
    #5. Problems (easy to hard) - (role model submission / problem page):
        i.  https://codeforces.com/contest/1365/submission/82814035 (direct template)
        ii. https://codeforces.com/contest/1294/submission/82290705 (direct template)
*/
int func(vector<int> curr, vector<int> target)
{
    gp_hash_table<int, int, custom_hash> pos;
    for (int i = 0; i < SZ(target); i++) {
        pos[target[i]] = i;
    }
    vector<int> temp(SZ(target), 0);
    for (int i = 0; i < SZ(curr); i++) {
        if (pos.find(curr[i]) != pos.end()) {
            int in = ((i-pos[curr[i]] % SZ(target)) + SZ(target)) % SZ(target);
            temp[in]++;
        }
    }
    int ret = INT_MIN;
    for (int i = 0; i < SZ(temp); i++) {
        ret = max(ret, temp[i]);
    }
    return ret;
}
