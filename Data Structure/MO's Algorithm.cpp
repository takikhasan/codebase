/*
    #1. Source & Intuition:
        i.  https://cp-algorithms.com/data_structures/sqrt_decomposition.html
    #2. Problems (easy to hard):
        i.  https://codeforces.com/contest/86/submission/91150884
*/
namespace MO
{
    struct Query {
        int l, r, idx;
    };

    const int BLOCK_SIZE = 400; /** root(array size) +- 50 */

    inline bool operator < (const Query &a, const Query &b) {
        if (a.l / BLOCK_SIZE != b.l / BLOCK_SIZE)
            return make_pair(a.l, a.r) < make_pair(b.l, b.r);
        return (a.l / BLOCK_SIZE & 1) ? (a.r < b.r) : (a.r > b.r);
    }

    namespace DS
    {
        /** Variables & methods to maintain answer */
        /** Depends on the problem */

        inline void removes(int idx) {

        }
        inline void add(int idx) {

        }
        inline LL get_answer() {

        }
    };

    using namespace DS;

    VLL algorithm(vector<Query> queries) {
        VLL answers(SZ(queries));
        sort(all(queries));

        int cur_l = 0;
        int cur_r = -1;
        // invariant: data structure will always reflect the range [cur_l, cur_r]
        for (Query q : queries) {
            while (cur_l > q.l) {
                cur_l--;
                add(cur_l);
            }
            while (cur_r < q.r) {
                cur_r++;
                add(cur_r);
            }
            while (cur_l < q.l) {
                removes(cur_l);
                cur_l++;
            }
            while (cur_r > q.r) {
                removes(cur_r);
                cur_r--;
            }
            answers[q.idx] = get_answer();
        }
        return answers;
    }
}

using namespace MO;
