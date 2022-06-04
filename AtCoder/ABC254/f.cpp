//created time: 2022-06-04 19:57:10
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
const int kN = 200500;
int a[kN], b[kN], n = in(), q = in(), c[kN], lg[kN], d[kN];
int gcd(int a, int b) { return !b ? a : gcd(b, a % b); }
int st[20][kN],sq[20][kN];
void init_1(void) {
	_rep(i,1,n) st[0][i] = c[i];
	for(int i = 1; i < 20; ++i) _rep(j, 1, n - (1 << i) + 1) 
		st[i][j] = gcd(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
}
void init_2(void) {
	_rep(i,1,n) sq[0][i] = d[i];
	for(int i = 1; i < 20; ++i) _rep(j, 1, n - (1 << i) + 1) 
		sq[i][j] = gcd(sq[i - 1][j], sq[i - 1][j + (1 << (i - 1))]);
}
int query_1(int l,int r) {
	int k = lg[r - l + 1];
	return gcd(st[k][l], st[k][r - (1 << k) + 1]);
}
int query_2(int l,int r) {
	int k = lg[r - l + 1];
	return gcd(sq[k][l], sq[k][r - (1 << k) + 1]);
}

int main() {
	_rep(i,1,n) a[i] = in();
	_rep(i,1,n) b[i] = in();
	_rep(i,2,n) lg[i] = lg[i >> 1] + 1;
	_rep(i,1,n) c[i] = abs(b[i] - b[i - 1]);
	_rep(i,1,n) d[i] = abs(a[i] - a[i - 1]);
	init_1();
	init_2();
	_rep(i,1,q) {
		int h1 = in(), h2 = in(), w1 = in(), w2 = in();
		int res = a[h1] + b[w1];
		if(h1 < h2) 
			res = gcd(res, query_2(h1 + 1, h2));
		if(w1 < w2)
			res = gcd(res, query_1(w1 + 1, w2));
		printf("%d\n", res);
	}
	return 0;
}
