//created time: 2022-06-04 19:57:14
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
int A[kN], B[kN], n = in();

int ch[kN * 4][2], nc, val[kN * 4];
void insert(int val) {
	int cur = 0;
	int stk[20],top = 0;
	while(val) stk[++top] = val & 1, val >>= 1;
	reverse(stk + 1, stk + 1 + top);
	_rep(i,1,top) {
		if(!ch[cur][stk[i]]) ch[cur][stk[i]] = ++nc;
		cur = ch[cur][stk[i]];
	}
	val[cur] = 1;
}

int main() {
	int ca = 0, cb = 0;
	_rep(i,1,n) A[i] = in(), ca += __builtin_popcount(A[i]); 
	_rep(i,1,n) B[i] = in(), cb += __builtin_popcount(B[i]);
	if(ca < cb) {
		puts("-1");
		return 0;
	}
	sort(A + 1,A + 1 + n,[](const int &a,const int &b) ->bool { return __builtin_popcount(a) < __builtin_popcount(b); });
	sort(B + 1,B + 1 + n,[](const int &a,const int &b) ->bool { return __builtin_popcount(a) < __builtin_popcount(b); });
	_rep(i,1,n) insert(A[i]);
	_rep(i,1,n) { //match B[i]
		int TrueBi = B[i] >> __builtin_ctz(B[i]);
		int cur = 0, stk[25], top = 0;
		while(TrueBi) {
			stk[++top] = TrueBi & 1;
			TrueBi >>= 1;
		}
		reverse(stk + 1,stk + 1 + top);
		
		
	}
	return 0;
}
