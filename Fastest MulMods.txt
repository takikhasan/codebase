/** The Fastest mulmod **/
long long int mulmod(long long int a,long long int b, long long MOD) {
   long double res = a;
   res *= b;
   long long int c = (long long)(res / MOD);
   a *= b;
   a -= c * MOD;
   a %= MOD;
   if (a < 0) a += MOD;
   return a;
}
/** The Fastest mulmod **/



/** The Second Fastest mulmod **/
long long modit(long long x,long long mod) {
	if(x>=mod) x-=mod;
	return x;
}
long long mult(long long x,long long y,long long mod) {
	long long s=0,m=x%mod;
	while(y) {
		if(y&1) s=modit(s+m,mod);
		y>>=1;
		m=modit(m+m,mod);
	}
	return s;
}
/** The Second Fastest mulmod **/