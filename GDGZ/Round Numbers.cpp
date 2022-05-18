// created time : 2022-04-08 15:23:09
// writer : fjy
#include <bits/stdc++.h>
#define _rep(i_,a_,b_) for(int i_ = a_;i_ <= b_;++i_)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
using namespace std;


int num[105];
ll f[65][2][65][65][2];
ll dp(int k,int _mx,int _c0,int _c1,int _0) {
	if(f[k][_mx][_c0][_c1][_0] != -1) return f[k][_mx][_c0][_c1][_0];
	if(!k) return _c0 >= _c1;
	int _ub = _mx ? num[k] : 1;
	ll _res = 0;
	_rep(i,0,_ub)
		_res += dp(k - 1,_mx && (i == num[k]),_c0 + (i == 0 && !_0),_c1 + (i == 1),_0 && (i == 0));
	return f[k][_mx][_c0][_c1][_0] = _res;
}

ll solve(ll x) {
	memset(f,-1,sizeof(f));
	num[0] = 0;
	do {
		num[++num[0]] = x & 1;
		x >>= 1;
	} while(x);
	return dp(num[0],1,0,0,1);
}


int main() {
	// while(1) printf("%lld\n",solve(inl()));
	ll a, b;
	while(~scanf("%lld%lld",&a,&b)) {
		printf("%lld\n",solve(b) - solve(a - 1));
	}
	return 0;
}