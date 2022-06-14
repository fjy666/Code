#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define muticase for(int curCase = 1, casecnt = in(); curCase <= casecnt; ++curCase)
typedef long long ll;
// #define _USE_FAST_IO

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
ll inl(void) { ll x; scanf("%lld",&x); return x; }
#endif

string s,t;
int get_min(const string &s) {
	int k = 0, i = 0, j = 1;
	while(k < s.size() && i < s.size() && j < s.size()) {
		if(s[(i + k) % s.size()] == s[(k + j) % s.size()]) ++k;
		else {
			if(s[(i + k) % s.size()] > s[(j + k) % s.size()]) i += k + 1;
			else j += k + 1;
			if(i == j) ++i; k = 0;
		}
	}
	return min(i, j);
}
int main() {
	ios::sync_with_stdio(false);
	cin >> s >> t;
	rotate(s.begin(), s.begin() + get_min(s), s.end());
	rotate(t.begin(), t.begin() + get_min(t), t.end());
	puts(s == t ? "Yes" : "No");
	if(s == t) printf("%s\n", s.c_str());
	return 0;
}