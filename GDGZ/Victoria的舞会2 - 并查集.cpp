// -< fjy666 >-
//ALWAYS TO REMAMBER DELETE THE DEBUGGING STATEMENT
#include <bits/stdc++.h>
#define _rep(i_,a_,b_) for(int i_ = a_;i_ <= b_;++i_)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
using namespace std;
int f[2555];
int get(int x) {
	return f[x] == x ? x : f[x] = get(f[x]);
}
int main() {
	int n = in();
	_rep(i,1,n) f[i] = i;
	int cnt = n;
	_rep(i,1,n) {
		int j;
		while(j = in()) {
			if(get(i) == get(j)) continue;
			--cnt;
			f[get(i)] = get(j);
		}
	}
	printf("%d\n",cnt);
	return 0;
}

