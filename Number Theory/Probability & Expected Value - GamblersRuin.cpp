/*
    #1. Classical Definition: Two players begin with fixed stakes, transferring points until one or the other is "ruined" by getting to zero points.
    #2. A starts with a points and has probability p of taking 1 point from B in each round.
    #3. B starts with b points and has probability q = (1 - p) of taking 1 point from A in each round.
    #4. Source Inspiration:
        i.  http://www2.math.uu.se/~sea/kurser/stokprocmn1/slumpvandring_eng.pdf (Theorem 4 & 5)
        ii. https://en.wikipedia.org/wiki/Gambler%27s_ruin
*/
struct GamblersRuin
{
    LD a, b;
    LD p, q;
    GamblersRuin(LL a, LL b, LD p = 0.5) : a(a), b(b), p(p), q(1 - p) {}
    LD probabilityOfAWinning() {
        if (dcmp(p - 0.5) == 0) return a / (a + b);
        else return (pow(q / p, a) - 1) / (pow(q / p, a + b) - 1);
    }
    LD probabilityOfBWinning() {
        return 1 - probabilityOfAWinning();
    }
    LD expectedNumberOfRounds() {
        if (dcmp(p - 0.5) == 0) return a * b;
        else return (a / (q - p)) - (((a + b) / (q - p)) * probabilityOfAWinning());
    }
};
