#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
stack<int> s;
int main() {
	int n = in();
	int cnt = 0;
	_rep(i,1,n) {
		in(); int h = in();
		while(!s.empty() && s.top() > h) ++cnt,s.pop();
		while(!s.empty() && s.top() == h) s.pop();
		s.push(h);
	}
	printf("%d\n",cnt + s.size());
	return 0;
}
