/*
    #1. Using Gaussian Elimination (basically concept of Vector Space and Vector Basis and how they can be used for XOR),
        we can solve many problems where subset XOR is the main theme.
    #2. Intuition (by order of importance):
        i.  https://codeforces.com/blog/entry/68953
        ii. https://en.wikipedia.org/wiki/Basis_(linear_algebra)#:~:text=In%20mathematics%2C%20a%20set%20B,on%20B%20of%20the%20vector.
        iii.https://math.stackexchange.com/a/1054206
        iv. https://www.hackerearth.com/practice/notes/gaussian-elimination/
        v.  https://codeforces.com/blog/entry/60003
    #3. Problems (easy to hard) - (role model submission/problem page):
        i.  https://vjudge.net/solution/26195313 (direct template)
*/
class VectorSpace
{
    /* It's a (Z^d)2 vector space */
    /* (d - 1) is the highest MSB possible (0 indexed) */
    int d;
    VULL basis_vectors;
    int basis_size = 0;
public:
    VectorSpace(int d = 64) : d(d), basis_vectors(d) {}
    void insertVector(ULL mask) {
        for (int i = d - 1; i >= 0; i--) {
            if (CHECK(mask, i)) {
                if (basis_vectors[i]) {
                    mask ^= basis_vectors[i];
                }
                else {
                    basis_vectors[i] = mask;
                    basis_size++;
                    return;
                }
            }
        }
    }
    /* Add one member function for every type of problem solved in the future */
    ULL maximumSubsetXOR() {
        ULL ret = 0;
        for (int i = d - 1; i >= 0; i--) {
            if (basis_vectors[i]) {
                if (!CHECK(ret, i)) ret ^= basis_vectors[i];
            }
        }
        return ret;
    }
    ULL possibleDistinctValuesUsingSubsetXOR() {
        return 1ULL << basis_size;
    }
};
