#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
const int kN = 55;
char s[kN];
int main() {
	int n = in(),a = in(),q = in();
	if(q == 0) {
		printf("1.000");
		return 0;
	}
	scanf("%s",s);
	double single = a / 100.0,tot = 0.0;
	_rep(i,q,n) {
		unsigned long long cur = (1ull << i) - 1, limit = (1ull << n);
		while(cur < limit) {
			double pos = 1;
			_rep(j,0,n - 1) 
				if(cur & (1ull << j)) pos *= s[j] == '1' ? single : (1 - single); 
				else pos *= s[j] == '1' ? (1 - single) : single;
			tot += pos;
			unsigned long long lb = cur & -cur,r = cur + lb;
			cur = ((r ^ cur) >> (__builtin_ctzll(lb) + 2)) | r;
		}
	}
	print
	printf("%.3f",tot);
	return 0;
}
