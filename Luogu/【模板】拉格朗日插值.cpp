//created time: 2022-06-01 09:54:20
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
int n = in(), k = in();
int x[10056],y[10086];
int fpm(int a, int b) {
	int res = 1 % p;
	for(; b; b >>= 1, a = (ll) a * a % p) if(b & 1) res = (ll) res * a % p;
	return res;
}
int main() {
	_rep(i,0,n - 1) x[i] = in(), y[i] = in();
	// f(k) = \sum{ yi * \mul { k - x[j] / x[i] - x[j] }  }
	int ans = 0;
	_rep(i,0,n - 1) {
		int f = 1, d = 1;
		_rep(j,0,n - 1) if(i != j) {
			f = (ll) f * (k - x[j]) % p; f = (f + p) % p;
			d = (ll) d * fpm(((x[i] - x[j]) % p + p) % p, p - 2) % p; d = (d + p) % p;
		}
		ans = (ans + (ll) y[i] * f % p * d % p) % p;
	}
	printf("%d\n", ans);
	return 0;
}
