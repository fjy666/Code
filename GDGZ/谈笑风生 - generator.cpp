#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }

mt19937 gen(time(0));
int rx(int x) {
	return abs((int) gen()) % x + 1;
}
int main() {
	int n = rx(100) + 100,q = rx(100) + 100;
	printf("%d %d\n",n,q);
	_rep(i,2,n) {
		int fjy = rx(i - 1);
		printf("%d %d\n",i,fjy);
	}
	_rep(i,1,q) 
		printf("%d %d\n",rx(n),rx(n));
	fflush(stdout);
	return 0;
}
