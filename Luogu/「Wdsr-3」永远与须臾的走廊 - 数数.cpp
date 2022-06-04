//created time: 2022-05-29 19:29:26
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
const int kN = 100500,p = 998244353;

int fpm(int a,int b) {
	int r = 1;
	for(;b;b >>= 1,a = (ll) a * a % p) if(b & 1) r = (ll) r * a % p;
	return r;
}

char s[100005];
int main() {
	int n; scanf("%d",&n); scanf("%s",s + 1);
	int cnt_left = 0, cnt_right = 0, cnt_que = 0;
	_rep(i,1,n) {
		switch(s[i]) {
			case '(': ++cnt_left; break;
			case ')': ++cnt_right; break;
			case '?': ++cnt_que; break;
		}
	}
	//C(cnt_que, n / 2 - cnt_left)
	if(n & 1) {
		puts("0");
		return 0;
	}
	int res = 1;
	_rep(i,1,cnt_que) res = (ll) res * i % p;
	if(cnt_left > n / 2 || cnt_que < (n / 2 - cnt_left)) {
		puts("0");
		return 0;
	}
	_rep(i,1,n / 2 - cnt_left) res = (ll) res * fpm(i, p - 2) % p;
	_rep(i,1,cnt_que - (n / 2 - cnt_left)) res = (ll) res * fpm(i,p - 2) % p;
	printf("%d\n",res);
	return 0;
}
