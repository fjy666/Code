#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) ((x - 1) / kb + 1)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
const int kN = 50005,kb = 200;
struct query {
	int l,r,id;
	bool operator < (const query &rhs) const {
		return get(l) == get(rhs.l) ? r < rhs.r : get(l) < get(rhs.l);
	}
} q[kN];
int a[kN],n = in(),m = in(),d[kN],ans[kN];
int l[kN],r[kN],res;

void addr(int x) {
	if(!l[a[x]]) l[a[x]] = x;
	r[a[x]] = x; res = max(res,r[a[x]] - l[a[x]]);
}
stack<pair<int,int> > cl,cr;
void addl(int x) {
	if(!r[a[x]]) cr.push({a[x],r[a[x]]}), r[a[x]] = x;
	cl.push({a[x], l[a[x]]}), l[a[x]] = x;
	res = max(res,r[a[x]] - l[a[x]]);
}

int calc(int L,int R) {
	static int l[kN],r[kN]; int ans = 0;
	_rep(i,L,R) { if(!l[a[i]]) l[a[i]] = i; r[a[i]] = i; }
	_rep(i,L,R) ans = max(ans,r[a[i]] - l[a[i]]);
	_rep(i,L,R) l[a[i]] = r[a[i]] = 0;
	return ans;
}

int main() {
	_rep(i,2,n + 1) a[i] = in(); ++n; _rep(i,2,n) d[i] = (a[i] += a[i - 1]);
	sort(d + 1,d + 1 + n); _rep(i,1,n) a[i] = lower_bound(d + 1,d + 1 + n,a[i]) - d;
	_rep(i,1,m) q[i].id = i,q[i].l = in(),q[i].r = in() + 1;
	sort(q + 1,q + 1 + m);
	for(int b = 1, j = 1; b <= get(n); ++b) {
		memset(l,0,sizeof(l)); memset(r,0,sizeof(r)); res = 0;
		int R = b * kb;
		while(j <= m && get(q[j].l) == b) {
			if(q[j].r <= b * kb) {
				ans[q[j].id] = calc(q[j].l,q[j].r);
				++j; continue;
			}
			while(R < q[j].r) addr(++R);
			int _ = res; int L = b * kb + 1;
			while(L > q[j].l) addl(--L);
			ans[q[j].id] = res; res = _;
			while(!cl.empty()) l[cl.top().first] = cl.top().second, cl.pop();
			while(!cr.empty()) r[cr.top().first] = cr.top().second, cr.pop();
			++j;
		}
	}
	_rep(i,1,m) printf("%d\n",ans[i]);
	return 0;
}
