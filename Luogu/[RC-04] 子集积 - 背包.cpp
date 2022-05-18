#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
const int kN = 1000500,p = 998244353;
ll n = inl(),m = inl(),cnt[kN];
ll fac[kN],ifac[kN],iv[kN];
void init(void) {
	fac[0] = 1,ifac[0] = 1,iv[1] = 1;
	_rep(i,2,n) iv[i] = (p - p / i) * iv[p % i] % p;
	_rep(i,1,n) fac[i] = fac[i - 1] * i % p, ifac[i] = ifac[i - 1] * iv[i] % p;
}
ll C(ll n,ll m) { return fac[n] * ifac[m] % p * ifac[n - m] % p; }
ll f[kN];
int main() {
	init();
	_rep(i,1,n) ++cnt[in()];
	f[1] = 1;
	_rep(i,2,1000000) if(cnt[i]) {
		for(int k = m / i;k;--k) {
			ll ms = 1;
			for(int j = 1;j <= cnt[i] && k * ms * i <= m; ++j) {
				ms *= i; //重量有 ms 的物品
				f[ms * k] = (f[ms * k] + f[k] * C(cnt[i],j) % p) % p;
			}
		}
	}
	ll s1 = 1;
	_rep(i,1,cnt[1]) s1 = (s1 << 1) % p;
	ll s2 = 1;
	_rep(i,1,n) s2 = (s2 << 1) % p;
	ll s3 = 0;
	_rep(i,1,m) s3 = (s3 + f[i]) % p;
	printf("%lld\n", (s2 - s3 * s1 % p + p) % p);
	return 0;
}
