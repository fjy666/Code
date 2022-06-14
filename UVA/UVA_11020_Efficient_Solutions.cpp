#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;

int in(void) { int x; scanf("%d", &x); return x; }
ll inl(void) { ll x; scanf("%lld", &x); return x; }
multiset<pair<int,int> > s;
int main() { 
	int t = in();
	_rep(tt, 1, t) {
		printf("Case #%d:\n", tt);
		s.clear();
		int n = in();
		_rep(i,1,n) {
			pair<int,int> a; a.first = in(), a.second = in();
			auto it = s.upper_bound(a);
			if(it != s.begin() && prev(it)->second < a.second) goto print;
			it = s.lower_bound(a);
			while(it != s.end()) {
				//it->first >= a.first
				if(it->second > a.second || (it->second == a.second && it->first > a.first)) 
					it = s.erase(it);
				else break;
			}
			s.insert(a);
			print: printf("%d\n", s.size());
		}

		if(tt != t) puts("");
	}
	return 0;
}