#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
const int kN = 1000500,p = 1000000007;
int a[kN],res = 1;
int main() {
	int n = in();
	_rep(i,1,n) a[i] = in();
	_rep(i,1,n) res = (ll)res * (i - a[i] + 1) % p;
	printf("%d\n",res);
	return 0;
}
