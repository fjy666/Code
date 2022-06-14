#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;

int in(void) { int x; scanf("%d", &x); return x; }
ll inl(void) { ll x; scanf("%lld", &x); return x; }
const int kN = 105;
int a[kN], n = in();

int main() { 
	_rep(i,1,n) a[i] = in();
	sort(a + 1, a + 1 + n, greater<int>());
	_rep(i,1,n) printf("%d ", a[i]);
	return 0;
}