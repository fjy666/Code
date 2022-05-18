#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
const int kN = 50500,blk = 300;
int a[kN],n = in(),cnt[kN];
#define get(x) ((x - 1) / blk + 1)
struct query {
	int l,r,id,w;
	bool operator < (const query &q) const {
		return get(l) == get(q.l) ? (get(l) & 1 ? r < q.r : r > q.r) : get(l) < get(q.l);
	}
}q[kN * 4];
ll res,ans[kN];
int c1[kN],c2[kN];

void addl(int x) { res += c2[a[x]]; ++c1[a[x]]; }
void addr(int x) { res += c1[a[x]]; ++c2[a[x]]; }
void dell(int x) { res -= c2[a[x]];	--c1[a[x]]; }
void delr(int x) { res -= c1[a[x]];	--c2[a[x]]; }

int main() {
	_rep(i,1,n) a[i] = in();
	int Q = in(),m = 0;
	_rep(i,1,Q) {
		int l1 = in(),r1 = in(),l2 = in(),r2 = in();
		q[++m] = {r1,r2,i,1};
		q[++m] = {l1 - 1,r2,i,-1};
		q[++m] = {l2 - 1,r1,i,-1};
		q[++m] = {l1 - 1,l2 - 1,i,1};
	}
	sort(q + 1,q + 1 + m);
	int l = 0,r = 0;
	_rep(i,1,m) {
		while(l < q[i].l) addl(++l);
		while(r < q[i].r) addr(++r);
		while(l > q[i].l) dell(l--);
		while(r > q[i].r) delr(r--);
		ans[q[i].id] += q[i].w * res;
	}
	_rep(i,1,Q) printf("%lld\n",ans[i]);
	return 0;
}
