//created time: 2022-06-04 19:57:05
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
const int kN = 200050;
int cnt[kN];
vector<int> fac[kN];

bool isPerfectSquare(int x) {
	int rt = floor(sqrt(x));
	return rt * rt == x;
}

int main() {
	int n = in();
	_rep(i,1,n) cnt[i] = cnt[i - 1] + isPerfectSquare(i);
	_rep(i,2,n) if(!fac[i].size()) {
		for(int j = i; j <= n; j += i) {
			int tmpj = j;
			while(tmpj % i == 0) {
				tmpj /= i;
				fac[j].push_back(i);
			}
		}
	} 
	static int c[kN];
	ll res = 0;
	_rep(i,1,n) {
		int _r = 1;
		for(auto &f : fac[i]) ++c[f];
		for(auto &f : fac[i]) 
			if(c[f]) {
				if(c[f] & 1) _r *= f;
				c[f] = 0;
			}
		res += cnt[n / _r];
	}
	printf("%lld\n", res);
	return 0;
}
