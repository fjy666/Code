#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
const int kN = 1500;
vector<pair<int,int> > g[kN]; 
int fa[13][kN],dep[kN],dis[kN],lg[kN];
void dfs(int u,int f) {
	fa[0][u] = f; for(int i = 1;i <= 12;++i) fa[i][u] = fa[i - 1][fa[i - 1][u]];
	dep[u] = dep[f] + 1;
	for(auto &[v,w] : g[u]) if(v != f) {
		dis[v] = dis[u] + w;
		dfs(v,u);
	}
}
int LCA(int u,int v) {
	while(dep[u] != dep[v]) {
		if(dep[u] < dep[v]) swap(u,v);
		u = fa[lg[dep[u] - dep[v]]][u];
	}
	if(u == v) return u;
	for(int i = 12;~i;--i) if(fa[i][u] != fa[i][v]) u = fa[i][u],v = fa[i][v];
	return fa[0][u];
}
int main() {
	int n = in(),q = in();
	_rep(i,2,n) lg[i] = lg[i >> 1] + 1;
	_rep(i,1,n - 1) {
		int u = in(),v = in(),w = in();
		g[u].push_back({v,w});
		g[v].push_back({u,w});
	}
	dfs(1,0);
	_rep(i,1,q) {
		int a = in(),b = in();
		printf("%d\n",dis[a] + dis[b] - 2 * dis[LCA(a,b)]);
	}
	return 0;
}
