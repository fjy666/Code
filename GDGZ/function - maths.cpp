#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
int main() {
	ll a = inl(),b = inl(),c = inl(),d = inl(),e = inl();
	b -= d; c -= e;
	if(a == 0) {
		//退化
		if(b == 0) printf("%d\n",c == 0 ? -1 : 0);
		else printf("%d\n",1);
	} else {
		double delta = b * 1.0 * b - 4.0 * a * c;
		if(delta > 0) puts("2");
		else if(delta == 0) puts("1");
		else puts("0");
	}
	return 0;
}
