/*
    #1. What we want is this: among all the possible tree diameters, the one that has the smallest/biggest node
        at one of its ends.
    #2. The idea is very simple, just use/look at the code snippet given below.
    #3. The code is for the smallest node and it's a bit incomplete, but it conveys the trick.
    #4. Problems (easy to hard) - (role model submission/problem page):
        i.  https://vjudge.net/solution/26210889
*/
int maxx, max_node;
void dfs(int u, int p, int d)
{
    if (d > maxx) {
        maxx = d;
        max_node = u;
    }
    else if (d == maxx) {
        max_node = min(max_node, u);
    }
    for (int v : g[u]) {
        if (v != p) {
            dfs(v, u, d + 1);
        }
    }
}
int diameter_head()
{
    maxx = -1;
    dfs(0, -1, 0);
    int head = max_node;
    maxx = -1;
    dfs(head, -1, 0);
    int tail = max_node;
    return min(head, tail);
}
