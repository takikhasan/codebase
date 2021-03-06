
If the problem requires input/output via file(s):
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

In c++:
    for precision:
	cout << setprecision(x) << fixed << y << setpecision(w) << fixed << z << endl;
	where x and w are how precise the output must be and y and z are the double
	variables.

For hashing:
    base = 347, mod = 1000000007, mod2 = 22801761391
    all of these are prime numbers

Bitwise fact:
    a + b = a ^ b + 2 * (a & b);

Position of rightmost set bit(0 indexed, from right):
    int pos = log2(mask&-mask);

Bitset:
    B.Find_first(); B.Find_next(pos);   /** Complexity: (BITSET_LENGTH / 32)  */

Given n coins, if we have to distribute them between k people(giving someone zero is allowed, but we have to give away all of the coins)
How many ways?
    => nCr(n + k - 1, n);

nCr = n! / (r! * (n - r)!)
nCr = (n-1)Cr + (n-1)C(r-1)
nPr = n! / (n - r)!

Geometric series heavily applicable for probability problems (because, r >= 0 && r <= 1 for probability problems):
    r^0 + r^1 + r^2 + r^3 + ... = 1 / (1 - r), for |r| < 1.
Handle r = 1 as a corner case if r = 1 is possible.
Other forms:
    1 + r^1 + r^2 + r^3 + ... = 1 / (1 - r), for |r| < 1.   [Same Thing]
    r^1 + r^2 + r^3 + ... = (1 / (1 - r)) - 1, for |r| < 1. [Subtracting 1 from Both Sides]
