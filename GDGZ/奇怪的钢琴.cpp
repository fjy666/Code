//created time: 2022-06-03 09:51:30
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
const int kN = 100500;
int n,m,a[kN],s[kN];
int main() {
	int t = in();
	while(t--) {
		n = in(), m = in();
		_rep(i,1,n) a[i] = in();
		sort(a + 1, a + 1 + n);
		int sum = accumulate(a + 1,a + 1 + n, 0);
		if(a[1] >= 0) {
			printf("%d\n", sum);
			continue;
		}
		if(n == m) {
			printf("%d\n", max(sum, -sum));
			continue;
		}
		_rep(i,1,n) s[i] = s[i - 1] - a[i] * 2;
		if(m & 1) printf("%d\n", *max_element(s,s + 1 + n) + sum);
		else {
			int ans = 0;
			for(int i = 0; i <= n; i += 2) ans = max(ans, s[i]);
			printf("%d\n", ans + sum);
		}
	}
	return 0;
}
