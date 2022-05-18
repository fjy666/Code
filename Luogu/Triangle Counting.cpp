#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
const int kN = 1000500;
ll f[kN];
int main() {
	_rep(i,3,1000000) f[i] = f[i - 1] + ((ll)(i - 1) * (i - 2) / 2 - (i - 1) / 2) / 2;
	int n;
	f[114514]
	while(n = in(),n >= 3) printf("%lld\n",f[n]);
	return 0;
}

