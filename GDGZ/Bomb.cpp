// created time : 2022-04-08 14:46:29
// writer : fjy
#include <bits/stdc++.h>
#define _rep(i_,a_,b_) for(int i_ = a_;i_ <= b_;++i_)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
using namespace std;

int num[25];
ll f[25][2][2][2];
ll dp(int k,int _mx,int _4,int _49) {
	if(f[k][_mx][_4][_49] != -1) return f[k][_mx][_4][_49];
	if(!k) return _49;

	int _ub = _mx ? num[k] : 9;
	ll _res = 0;
	_rep(i,0,_ub) 
		_res += dp(k - 1,_mx && (i == num[k]),i == 4,_49 || (_4 && i == 9));
	
	return f[k][_mx][_4][_49] = _res;
}

ll solve(ll x) {
	memset(f,-1,sizeof(f));
	num[0] = 0;
	do {
		num[++num[0]] = x % 10;
		x /= 10;
	} while(x);
	return dp(num[0],1,0,0);
}

int main() {
	int T = in();
	while(T--) {
		ll n = inl();
		printf("%lld\n",solve(n));
	}
	return 0;
}