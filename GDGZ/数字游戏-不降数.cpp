// created time : 2022-04-08 15:23:09
// writer : fjy
#include <bits/stdc++.h>
#define _rep(i_,a_,b_) for(int i_ = a_;i_ <= b_;++i_)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
using namespace std;


int num[15];
ll f[15][2][10];
ll dp(int k,int _mx,int _pre) {
	if(f[k][_mx][_pre] != -1) return f[k][_mx][_pre];
	if(!k) return 1ll;
	int _ub = _mx ? num[k] : 9;
	ll _res = 0;
	_rep(i,_pre,_ub)
		_res += dp(k - 1,_mx && (i == num[k]),i);
	return f[k][_mx][_pre] = _res;
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
	ll a, b;
	while(~scanf("%lld%lld",&a,&b)) {
		printf("%lld\n",solve(b) - solve(a - 1));
	}
	return 0;
}