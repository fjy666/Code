#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
const int kN = 100500,kb = 500,kf = -114514;
int a[kN],n = in(),tag[kN];
#define get(x) ((x - 1) / kb + 1)
inline void free(int id) {
	if(tag[id] != kf) 
		_rep(i,(id - 1) * kb + 1,id * kb) 
			a[i] = tag[id];
	tag[id] = kf;
}
int query(int l,int r,int c) {
	int res = 0;
	free(get(l));
	for(int i = l; i <= min(r,kb * get(l)); ++i)
		res += a[i] == c, a[i] = c;
	if(get(l) != get(r)) {
		free(get(r));	
		for(int i = (get(r) - 1) * kb + 1; i <= r; ++i)
			res += a[i] == c,a[i] = c;
	} 
	for(int i = get(l) + 1; i < get(r); ++i) {
		if(tag[i] == c) res += kb;
		else if(tag[i] == kf)
			for(int j = (i - 1) * kb + 1; j <= i * kb; ++j)
				res += a[j] == c;
		tag[i] = c;
	}
	return res;
}
int main() {
	_rep(i,1,n) a[i] = in();
	_rep(i,1,get(n)) tag[i] = kf;
	_rep(i,1,n) {
		int l = in(),r = in(),c = in();
		printf("%d\n",query(l,r,c));
	}
	return 0;
}
