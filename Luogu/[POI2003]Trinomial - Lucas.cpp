#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
const int p = 3;
int C[p][p];
ll Lucas(ll n,ll m) {
	if(!m) return 1ll;
	return Lucas(n / 3,m / 3) * C[n % 3][m % 3] % 3;
}
int main() {
	C[0][0] = 1;
	C[1][0] = C[1][1] = 1;
	C[2][0] = C[2][2] = 1, C[2][1] = 2;
	int t = in();
	while(t--) {
		ll n = inl(),p = inl();
		//(calc ax^p -> a)
		printf("%lld\n",(Lucas(2 * n,p) * ((2 * n - p) & 1 ? -1 : 1) % 3 + 3) % 3);
	}
	return 0;
}
