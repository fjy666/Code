#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
int main() {
	int T = in();
	while(T--) {
		ll n = inl();
		ll a = 1;
		for(;a * 3 - 1 <= n; a = a * 3 - 1);
		if(!((n - a) & 1)) printf("%lld\n",a - (n - a) / 2);
		else printf("%lld\n", 2 * a + (n - a - 1) / 2);
	}
	return 0;
}
