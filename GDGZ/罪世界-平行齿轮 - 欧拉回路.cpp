// -< fjy666 >-
//ALWAYS TO REMAMBER DELETE THE DEBUGGING STATEMENT
#include <bits/stdc++.h>
#define _rep(i_,a_,b_) for(int i_ = a_;i_ <= b_;++i_)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
using namespace std;
const int kN = 1000500;
int d[kN];
int main() {
	int n = in(),m = in();
	_rep(i,1,m) {
		int a = in(),b = in();
		++d[a]; ++d[b];
	}
	ll cnt1 = 0,cnt2 = 0;
	_rep(i,1,n) {
		if(d[i] & 1) ++cnt1;
		else ++cnt2;
	}
	printf("%lld\n",cnt1 / 2); 
	return 0;
}

