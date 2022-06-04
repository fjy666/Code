//created time: 2022-05-29 19:59:50
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

char s[25],ns[25]; 
ll ne[25],cnt = 0;
int main() {
	int T = in();
	while(T--) {
		memset(s,0,sizeof(s));
		ll n = inl();
		sprintf(s + 1,"%lld",n);
		int l = strlen(s + 1);
		cnt = 0;
		if(l > 2) {
			ne[++cnt] = 1;
			_rep(i,1,l - 1) ne[cnt] *= 10;
			--ne[cnt];
		}
		_rep(rep,1,l / 2) if(l % rep == 0) { //产生的新数的循环节
			memset(ns,0,sizeof(ns));
			_rep(i,1,rep) ns[i] = s[i];
			ll _Rep; sscanf(ns + 1, "%lld", &_Rep);
			_rep(i,rep + 1,l) ns[i] = ns[i - rep];
			ns[l + 1] = '\0';
			ll Num = 0;
			sscanf(ns + 1,"%lld",&Num);
			if(Num <= n) 
				ne[++cnt] = Num;
			else {
				ll _R = _Rep - 1;
				memset(ns,0,sizeof(ns));
				sprintf(ns + 1, "%lld", _R);
				if(strlen(ns + 1) != rep) continue;
				_rep(i,rep + 1,l) ns[i] = ns[i - rep];
				ns[l + 1] = '\0';
				sscanf(ns + 1, "%lld", &Num);
				ne[++cnt] = Num;
			}
		}
		printf("%lld\n",*max_element(ne + 1,ne + 1 + cnt));
	}
	return 0;
}
