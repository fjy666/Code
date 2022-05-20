//author: fjy666
//created time: 2022-05-20 12:39:19
#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
const int kN = 1000500;
int gcd(int a,int b) { return !b ? a : gcd(b,a % b); }
int main() {
	int n = in(),b = in();
	_rep(i,1,b) printf("%d\n",gcd(i,n));
	return 0;
}
