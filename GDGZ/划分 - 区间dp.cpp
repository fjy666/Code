//created time: <TIMEDATE>
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
typedef long long ll;

namespace FastIO { //by fjy666
	char OBuf[1 << 23], *p = OBuf;
	inline void pc(char c) { *p++=c; }
	inline void out(ll x) { if(x < 0) pc('-'), x = -x; if(x > 9) out(x / 10); pc(x % 10 + '0'); }
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

const int p = 998244353,kN = 505;
char s[kN];
int cntOdd[kN];
int dp[kN][kN];
void add(int i,int j,int v) { for(;i < kN;i += i & -i) dp[i][j] = (dp[i][j] + v) % p; }
int qry(int i,int j) { int r = 0; for(;i;i -= i & -i) r = (r + dp[i][j]) % p; return r; }
int get(int i,int j) { return (qry(i,j) - qry(i - 1,j) + p) % p; }
pair<int,int> Range[kN][kN];
#define Odd(L,R) (cntOdd[R] - cntOdd[L - 1]) 
signed main() {
	scanf("%s",s + 1);
	int n = strlen(s + 1);
	
	_rep(i,1,n) cntOdd[i] = cntOdd[i - 1] + ((s[i] - '0') & 1);
	_rep(i,1,n) _rep(j,0,n) {
		//从i开始有连续j个奇数
		int k = i;
		while(k < n && Odd(i,k) != j) ++k;
		if(Odd(i,k) != j) {
			Range[i][j] = {-1,-1};
			continue;
		}
		Range[i][j].first = k;
		while(k < n && Odd(i,k + 1) == j) ++k;
		Range[i][j].second = k;
	}
	
	_rep(i,1,n) add(i,i,1),add(i,i - 1,1);
	
	_rep(len,2,n) _rep(l,1,n - len + 1) {
		int r = l + len - 1;
		add(l,r,1); //不分割，整体作为一串
		//dp[l][r] 表示 [l,r] 满足题目中的条件的方案数
		for(int d = r; d >= l; --d) {
			int _O = Odd(d,r);
			pair<int,int> R = Range[l][_O];
			if(R == pair<int,int> {-1,-1} || R.first >= d) continue;
			R.second = min(R.second, d - 1);
			//dp[l][r] += sum{dp[k][d - 1]} (R.first <= k <= R.second)
			add(l,r,(qry(R.second + 1,d - 1) - qry(R.first,d - 1) + p) % p);
		}
	}
	
	printf("%lld\n",get(1,n));
	return 0;
}
