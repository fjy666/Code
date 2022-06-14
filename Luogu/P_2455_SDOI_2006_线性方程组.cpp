#include <bits/stdc++.h>
using namespace std;
#define _USE_FAST_IO
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
ll in(void) { ll x; scanf("%lld",&x); return x; }
#endif
const int kN = 55;
double a[kN][kN], res[kN]; int n;
int main() {
	scanf("%d", &n);
	_rep(i,1,n) _rep(j,1,n + 1) scanf("%lf", &a[i][j]);
	int x = 1, r = 1; //x表示未知数， r表示行
	for(; x <= n; ++x) {
		int L = r; _rep(i,r + 1, n) if(fabs(a[i][x]) > fabs(a[L][x])) L = i;
		if(fabs(a[L][x]) < 1e-6) continue; //系数为0，直接跳
		_rep(i,1,n + 1) swap(a[r][i], a[L][i]);
		_rep(i, r + 1, n) {
			double rate = a[i][x] / a[r][x];
			_rep(j, x, n + 1) a[i][j] -= rate * a[r][j];
		} ++r;
	}
	if(r <= n) {
		_rep(i, r, n) if(a[i][n + 1]) {
			puts("-1"); return 0;
		}
		puts("0"); return 0;
	} else {
		res[n] = a[n][n + 1] / a[n][n];
		for(int i = n - 1;i;--i) {
			res[i] = a[i][n + 1];
			_rep(j, i + 1, n) res[i] -= res[j] * a[i][j];
			res[i] /= a[i][i];
		}
		_rep(i,1,n) printf("x%d=%.2lf\n",i, fabs(res[i]) <= 1e-6 ? 0.0 : res[i]);
	}
	return 0;
}