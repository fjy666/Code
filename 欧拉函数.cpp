//author: fjy666
//created time: 2022-05-20 11:50:21
#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1) 
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
const int kN = 1005000;
int phi[kN],p[kN];
vector<int> primes;
int main() {
	int n = in();
	phi[1] = 1;
	_rep(i,2,n) {
		if(!p[i]) primes.push_back(i), phi[i] = i - 1;
		for(auto &P : primes) {
			if(i * P > 1000000) break; 
			if(i % P) 
				p[i * P] = 1,phi[i * P] = phi[i] * phi[P];
			else {
				p[i * P] = 1,phi[i * P] = phi[i] * P;
				break;
			}
		}
	}
	_rep(i,1,n) printf("%d\n",phi[i]);
	return 0;
}
