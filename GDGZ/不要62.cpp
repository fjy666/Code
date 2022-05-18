// created time : 2022-04-08 14:26:39
// writer : fjy
#include <bits/stdc++.h>
#define _rep(i_,a_,b_) for(int i_ = a_;i_ <= b_;++i_)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
using namespace std;

int num[15];
ll f[15][2][2];
ll dp(int k,int _mx,int _6) {
	if(f[k][_mx][_6] != -1) return f[k][_mx][_6];
	if(!k) return 1ll;
	int _ub = _mx ? num[k] : 9;
	ll _res = 0;
	_rep(i,0,_ub) if(i != 4 && (i != 3 || !_6))
		_res += dp(k - 1,_mx && (i == num[k]),i == 6);
	return f[k][_mx][_6] = _res;
}

ll solve(ll x) {
	memset(f,-1,sizeof(f));
	num[0] = 0;
	do {
		num[++num[0]] = x % 10;
		x /= 10;
	} while(x);
	return dp(num[0],1,0);
}

int main() {
	ll l, r;
	while(true) {
		l = inl(),r = inl();
		if(l == 0 && r == 0) break;
		// ll ansr = solve(r);
	 	// ll ansl = (l - 1) >= 0 ? solve(l - 1) : 0;
		printf("%lld\n",solve(r) - solve(l - 1));
	}
	return 0;
}