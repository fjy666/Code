#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
const int kN = 1000500;
int d[kN],v[kN],g[kN];
vector<int> primes;
int main() {
	int n = 1000000;
	d[1] = 1;
	_rep(i,2,n) {
		if(!v[i]) primes.push_back(i), d[i] = i + 1, g[i] = i;
		for(auto &p : primes) {
			if(p * i > n) break;
			v[i * p] = 1;
			if(i % p == 0 && g[i] == i) { //i*p = p^k
				g[i * p] = i * p;
				d[i * p] = d[i] + i * p;
				break;
			}
			if(i % p) {
				g[p * i] = p;
				d[p * i] = d[p] * d[i]; 
			} else {
				g[p * i] = p * g[i];
				d[p * i] = d[p * i / g[p * i]] * d[g[p * i]];
				break;
			}
		}
	}
	_rep(i,1,n) printf("%d\n",d[i]);
	return 0;
}
