#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
#define get(x) ((x - 1) / 300 + 1)
#define L(x) ((x - 1) * 300 + 1)
#define R(x) ((x) * 300)
const int kN = 100500;
struct query {
	int l,r,id;
	bool operator < (const query &rhs) const {
		return get(l) == get(rhs.l) ? r < rhs.r : l < rhs.l;
	}
} q[kN];
int a[kN],d[kN];
ll ans[kN];

int cnt[kN]; ll cur;
void add(int x) {
	++cnt[a[x]];
	cur = max(cur,(ll) d[a[x]] * cnt[a[x]]);
}

ll solve(int l,int r) {
	static int cnt0[kN];
	_rep(i,l,r) ++cnt0[a[i]];
	ll res = LLONG_MIN;
	_rep(i,l,r) res = max(res,(ll)d[a[i]] * cnt0[a[i]]);
	_rep(i,l,r) --cnt0[a[i]];
	return res;
}

int main() {
	int n = in(),m = in();
	_rep(i,1,n) d[i] = a[i] = in();
	sort(d + 1,d + 1 + n);
	_rep(i,1,n) a[i] = lower_bound(d + 1,d + 1 + n,a[i]) - d;
	_rep(i,1,m) q[i].l = in(),q[i].r = in(),q[i].id = i;
	sort(q + 1,q + 1 + m);
	for(int bl = 1,j = 1; bl <= get(n); ++bl) {
		int r = R(bl); memset(cnt,0,sizeof(cnt)); cur = 0;
		while(j <= m && get(q[j].l) == bl) {
			if(q[j].r <= R(bl)) {
				ans[q[j].id] = solve(q[j].l,q[j].r);
				++j; continue;
			}
			int l = R(bl) + 1;
			while(r < q[j].r) add(++r);
			ll resume = cur;
			while(l > q[j].l) add(--l);
			ans[q[j].id] = cur;
			_rep(i,q[j].l,R(bl)) --cnt[a[i]];
			cur = resume; ++j;
		}
	}
	_rep(i,1,m) printf("%lld\n", ans[i]);
	return 0;
}
