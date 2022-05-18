#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
const int kN = 200500;
#define get(x) ((x - 1) / 500 + 1)
#define L(x) ((x - 1) * 500 + 1)
#define R(x) ((x) * 500)
int a[kN], d[kN], ans[kN];
struct query {
	int l,r,id;
	bool operator < (const query &rhs) const {
		return get(l) == get(rhs.l) ? r < rhs.r : get(l) < get(rhs.l);
	}
} q[kN];
int lft[kN],rgt[kN];
int solve(int L,int R) {
	int res = 0;
	static int l[kN], r[kN];
	_rep(i,L,R) { if(!l[a[i]]) l[a[i]] = i; r[a[i]] = i; }
	_rep(i,L,R) if(r[a[i]] - l[a[i]] > res) res = r[a[i]] - l[a[i]];
	_rep(i,L,R) r[a[i]] = l[a[i]] = 0;
	return res;
}
int cur = 0;
void add_r(int x) {
	if(!lft[a[x]]) lft[a[x]] = x;
	rgt[a[x]] = x;
	cur = max(cur,rgt[a[x]] - lft[a[x]]);
}
stack<pair<int,int> > clean_l,clean_r;
void add_l(int x) {
	if(!rgt[a[x]]) clean_r.push({a[x],rgt[a[x]]}), rgt[a[x]] = x;
	clean_l.push({a[x], lft[a[x]]}); lft[a[x]] = x;
	cur = max(cur,rgt[a[x]] - lft[a[x]]);
}
int main() {
	int n = in();
	_rep(i,1,n) d[i] = a[i] = in();
	sort(d + 1,d + 1 + n);
	_rep(i,1,n) a[i] = lower_bound(d + 1,d + 1 + n,a[i]) - d;
	int m = in();
	_rep(i,1,m) q[i].l = in(), q[i].r = in(), q[i].id = i;
	sort(q + 1,q + 1 + m);
	for(int bl = 1,j = 1; bl <= get(n); ++bl) {
		memset(lft,0,sizeof(lft)); memset(rgt,0,sizeof(rgt)); cur = 0;
		int r = R(bl);
		while(j <= m && get(q[j].l) == bl) {
			if(q[j].r <= R(bl)) {
				ans[q[j].id] = solve(q[j].l, q[j].r);
				++j; continue;
			}
			while(r < q[j].r) add_r(++r);
			int tmp = cur,l = R(bl) + 1;
			while(l > q[j].l) add_l(--l);
			ans[q[j].id] = cur; cur = tmp;
			while(!clean_l.empty()) lft[clean_l.top().first] = clean_l.top().second,clean_l.pop();
			while(!clean_r.empty()) rgt[clean_r.top().first] = clean_r.top().second,clean_r.pop();
			++j;
		}
	}
	_rep(i,1,m) printf("%d\n",ans[i]);
	return 0;
}
