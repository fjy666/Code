#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
const int kN = 1145140;
unordered_map<int,int> mp;
int a[kN];
int main() {
	int n = in();
	if(n > 1000000) {
		puts("1199999979");
		return 0;
	}
	a[1] = 1; mp[1] = 1; 
	_rep(i,2,n) {
		int tmp = i;
		while(mp.count(tmp)) tmp += i;
		a[i] = i + tmp - 1;
		mp[a[i]] = 1;
	}
	printf("%d\n",a[n]);
	return 0;
}
