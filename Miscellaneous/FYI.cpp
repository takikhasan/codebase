
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

Given n coins, if we have to distribute them between k people(giving someone zero is allowed, but we have to give away all of the coins)
How many ways?
    => nCr(n + k - 1, n);

nCr = n! / (r! * (n - r)!)
nCr = (n-1)Cr + (n-1)C(r-1)
nPr = n! / (n - r)!

1 / (x - 1) = 1 / x + 1 / (x ^ 2) + 1 / (x ^ 3) + 1 / (x ^ 4) + 1 / (x ^ 5) + 1 / (x ^ 6) + ....
