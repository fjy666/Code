//created time: 2022-06-04 19:57:07
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
const int kN = 150500;
vector<int> g[kN];
int n = in(), m = in();
int q[kN], st, ed, d[kN];

void bfs(int x, int k) {
	st = 1, ed = 0;
	q[++ed] = x; d[x] = 1; 
	ll res = x;
	while(st <= ed) {
		int u = q[st++]; if(d[u] == k + 1) continue; 
		for(auto &v : g[u]) if(!d[v]) {
			d[v] = d[u] + 1;
			q[++ed] = v;
			res += v;
		}
	}
	printf("%lld\n", res);
	_rep(i, 1, ed) d[q[i]] = 0;
}


int main() {
	_rep(i,1,m) {
		int a = in(), b = in();
		g[a].push_back(b);
		g[b].push_back(a);
	}
	int q = in();
	while(q--) {
		int x = in(), k = in();
		bfs(x,k);
	}
	return 0;
}
