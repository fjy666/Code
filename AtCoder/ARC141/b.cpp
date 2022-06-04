//created time: 2022-05-29 19:59:52
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

const ll p = 998244353;
ll f[65][65];
int main() {
	ll n = inl(),m = inl();
	if(n > 64) {
		puts("0");
		return 0;
	}
	_rep(i,0,62) if((1ll << i) <= m)
		f[1][i] = (min(m, (1ll << (i + 1)) - 1) - (1ll << i) + 1) % p;
//	printf("%lld\n",f[1][0]);
	_rep(i,2,n) _rep(j,1,62) {
		if((1ll << j) > m) continue;
		_rep(k,0,j - 1) f[i][j] = (f[i][j] + f[i - 1][k] * ((min(m, (1ll << (j + 1)) - 1) - (1ll << j) + 1) % p)) % p;
	}
	ll res = 0;
	_rep(i,0,62) res = (res + f[n][i]) % p;
	printf("%lld\n",res);
	return 0;	
}
