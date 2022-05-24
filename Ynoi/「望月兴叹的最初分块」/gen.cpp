//created time: 2022-05-23 12:40:55
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

mt19937 engine((unsigned) time(0));
int gen(int x) { return abs((int) engine()) % x + 1; }
int a[11000000];
const int N = 10000;
int main() {
	int n = gen(N),m = gen(N);
	out(n),pc(' '),out(m),pc('\n');
	_rep(i,1,n) a[i] = gen(N),out(a[i]),pc(' ');
	pc('\n');
	_rep(i,1,m) {
		int op = gen(2),l = gen(n),r = gen(n); 
		if(l > r) swap(l,r);
		out(op),pc(' '),out(l),pc(' '),out(r); 
		if(op == 1) pc(' '), out(gen(N)), pc(' '), out(gen(N)), pc('\n');
		else pc(' '), out(gen(r - l + 1)), pc('\n');
	}
	return 0;
}
