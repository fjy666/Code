//created time: 2022-05-31 13:07:23
#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;

namespace FastIO { //by fjy666
	char OBuf[1 << 23], *p = OBuf;
	inline void pc(char c) { *p++=c; }
	inline void out(ll x) { if(x < 0) pc('-'), x = -x; if(x > 9) out(x / 10); pc(x % 10 + '0'); }
	inline void out(int x) { if(x < 0) pc('-'), x = -x; if(x > 9) out(x / 10); pc(x % 10 + '0'); }
	inline void out(char *s) { if(*s) pc(*s),out(s+1); }
	inline void flush(void) { fwrite(OBuf,p - OBuf,1,stdout); }
	struct _Flusher{ ~_Flusher(){ flush(); } } flusher;
	
	char IBuf[1 << 23], *i1 = IBuf,*i2 = IBuf;
	inline char gc(void) { return (i1 == i2 && (i2 = (i1 = IBuf) + fread(IBuf,1,1 << 23,stdin),i1 == i2)) ? EOF : *i1++; }
	inline int in(void) {
		char c = gc(); int x = 0,f = 1; while(!isdigit(c)) { if(c == '-') f = -1; c = gc(); }
		while(isdigit(c)) { x = x * 10 + c - '0', c = gc(); } return x * f;
	}
	inline ll inl(void) {
		char c = gc(); ll x = 0,f = 1; while(!isdigit(c)) { if(c == '-') f = -1; c = gc(); }
		while(isdigit(c)) { x = x * 10 + c - '0', c = gc(); } return x * f;
	}
} using FastIO::pc; using FastIO::out; using FastIO::gc; using FastIO::in; using FastIO::inl;

const int p = 998244353;
int n = in(), fac[100005], ifac[100005], iv[100005];
void init(void) {
	fac[0] = 1; _rep(i,1,n) fac[i] = (ll) fac[i - 1] * i % p;
	iv[1] = 1; _rep(i,2,n - 1) iv[i] = (ll) iv[p % i] * (p - p / i) % p;
	ifac[0] = 1; _rep(i,1,n) ifac[i] = (ll) ifac[i - 1] * iv[i] % p;
}
int C(int n, int m) {
	return (ll) fac[n] * ifac[m] % p * ifac[n - m] % p;
}
int main() {
	init();
	int res = 0;
	_rep(S,1,n - 1) {
		int T = n - S;
		if(S != T) 
			res = (res + C(n - 2, S - 1)) % p;
	}
	printf("%d\n", res);
	return 0;
}
