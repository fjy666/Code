//基环树是啥？能吃吗？？？
#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
const int kN = 300500;
vector<int> g[kN];
int dfn[kN],dfs_clock,siz[kN],dep[kN];
void dfs(int u,int f) {
	siz[u] = 1,dfn[u] = ++dfs_clock,dep[u] = dep[f] + 1;
	for(auto &v : g[u]) if(v != f) dfs(v,u),siz[u] += siz[v];
}
ll a2;
void dfs2(int u,int f,int rt,int d) {
	if(dep[u] - dep[rt] > d) return;
	a2 += siz[u] - 1;
	for(auto &v : g[u]) if(v != f) dfs2(v,u,rt,d);
}
int main() {
	int n = in(),q = in();
	_rep(i,1,n - 1) {
		int u = in(),v = in();
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1,0);
	while(q--) {
		int p = in(),k = in();
		ll a1 = (ll) min(dep[p] - 1,k) * (siz[p] - 1);
		a2 = 0;
		for(auto &e : g[p]) if(dep[e] > dep[p]) dfs2(e,p,p,k);
		printf("%lld\n",a1 + a2);
	}
	return 0;
}
