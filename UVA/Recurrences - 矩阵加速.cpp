//created time: 2022-06-04 16:20:23
#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
#ifdef assert
#undef assert
#endif
#define assert(expression)\
	if(!(expression)) {\
		printf("Line = %d\n", __LINE__);\
		printf("Expression \"%s\" is false!\n", #expression);\
		exit(0);\
	}
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
const int kN = 20;
int a[kN], init[kN];

int m;
struct Matrix {	int a[kN][kN],n,m; } unit_mat, ini;
Matrix operator * (const Matrix &l, const Matrix &r) {
	Matrix res; 
	memset(res.a, 0, sizeof(res.a));
	res.n = l.n, res.m = r.m;  assert(l.m == r.n);
	_rep(i, 1, res.n) _rep(j, 1, res.m) _rep(k, 1, l.m) 
		res.a[i][j] = (res.a[i][j] + l.a[i][k] * r.a[k][j] % ::m) % ::m;
	return res;
}
Matrix fpm(Matrix a, int b) {
	assert(a.n == a.m);
	Matrix res; 
	memset(res.a,0,sizeof(res.a));
	res.n = a.n, res.m = a.m; _rep(i, 1, res.n) res.a[i][i] = 1;
	for(;b; b >>= 1, a = a * a) if(b & 1) res = res * a;
	return res;
}
int main() {
	int d, n;
	while(d = in(), n = in(), ::m = in(), d || n || ::m) {
		_rep(i, 1, d) a[i] = in();
		_rep(i, 1, d) init[i] = in();
		if(n <= d) {
			printf("%d\n", init[n] % ::m);
			continue;
		}
		reverse(a + 1, a + 1 + d);
		memset(unit_mat.a,0,sizeof(unit_mat.a));
		unit_mat.n = d, unit_mat.m = d;
		_rep(i, 1, d) unit_mat.a[d][i] = a[i] % ::m;
		_rep(i, 1, d - 1) unit_mat.a[i][i + 1] = 1;
		
		memset(ini.a,0,sizeof(ini.a));
		ini.n = d, ini.m = 1;
		_rep(i, 1, d) ini.a[i][1] = init[i] % ::m;
		
		printf("%d\n", (fpm(unit_mat, n - 1) * ini).a[1][1]);
	}
	return 0;
}
