#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
const int kN = 100500;
int a[kN],n;
int main() {
	int T = in();
	while(T--) {
		n = in();
		_rep(i,1,n) a[i] = in();
		int ans = 0,OR_SUM = 0;
		_rep(i,1,n) OR_SUM |= a[i];
		_rep(i,1,n) ans ^= (OR_SUM & a[i]);
		printf("%d\n",ans);
	}
	return 0;
}
