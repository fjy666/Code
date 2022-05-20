//author: fjy666
//created time: 2022-05-20 12:24:13
#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
const int kN = 1005000;
int iv[kN];
int main() {
	int n = in();
	iv[1] = 1;
	_rep(i,2,n - 1) iv[i] = (ll)(n - n / i) * iv[n % i] % n;
	_rep(i,1,n - 1) printf("%d\n",iv[i]);
	return 0;
}
