#include <bits/stdc++.h>
using namespace std;
// #define _USE_FAST_IO
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
#define debug(variable, excepted) \
	if(variable != excepted) \
		printf("[Line %d] The expression %s should be %d, but now it is %d\n", __LINE__, #variable, excepted, variable);
#define muticase for(int curCase = 1, casecnt = in(); curCase <= casecnt; ++curCase)
typedef long long ll;

#ifdef _USE_FAST_IO
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
#else 
int in(void) { int x; scanf("%d",&x); return x; }
#endif
const int kN = 15;
double a[kN][kN],equ[kN][kN],res[kN];
int n = in();
int main() {
	_rep(i,1,n + 1) _rep(j,1,n) scanf("%lf", &a[i][j]);
	_rep(i,1,n) {
		_rep(j,1,n) equ[i][j] = 2 * (a[i][j] - a[i + 1][j]);
		_rep(j,1,n) equ[i][n + 1] += a[i][j] * a[i][j] - a[i + 1][j] * a[i + 1][j];
	}
	//快乐的高斯消元时间
	_rep(i,1,n) {
		int L = i; _rep(j, i + 1, n) if(fabs(equ[j][i]) > fabs(equ[L][i])) L = j;
		if(fabs(equ[L][i]) < 1e-6) {
			assert(false);
			return 0;
		}
		_rep(j,1,n + 1) swap(equ[i][j], equ[L][j]);
		_rep(j, i + 1, n) {
			double rate = equ[j][i] / equ[i][i];
			_rep(k, i, n + 1) equ[j][k] -= equ[i][k] * rate;
		}
	}
	res[n] = equ[n][n + 1] / equ[n][n];
	for(int i = n - 1;i; --i) {
		res[i] = equ[i][n + 1];
		_rep(j, i + 1, n) res[i] -= res[j] * equ[i][j];
		res[i] /= equ[i][i];
	}
	_rep(i,1,n) printf("%.3lf ",res[i]);
	return 0;
}