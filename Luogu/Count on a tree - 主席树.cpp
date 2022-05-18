#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
const int kN = 100500;
int n = in(),m = in(),v[kN],d[kN];
vector<int> g[kN];
namespace LCA {
	int fa[20][kN],dep[kN],lg[kN];
	void dfs(int u,int f) { dep[u] = dep[f] + 1;
		fa[0][u] = f; for(int i = 1;i < 20;++i) fa[i][u] = fa[i - 1][fa[i - 1][u]];
		for(int i = 0;i < g[u].size();++i) if(g[u][i] != f) dfs(g[u][i],u);
	}
	void init(void) { for(int i = 2;i < kN;++i) lg[i] = lg[i >> 1] + 1; dfs(1,0); }
	int query(int u,int v) {
		while(dep[u] != dep[v]) {
			if(dep[u] < dep[v]) swap(u,v);
			u = fa[lg[dep[u] - dep[v]]][u];
		}
		if(u == v) return u;
		for(int i = 19;~i;--i) if(fa[i][u] != fa[i][v]) u = fa[i][u],v = fa[i][v];
		return fa[0][u];
	}
}
namespace Seg {
	int ch[10000005][2],siz[10000005],nc,rt[10000005];
	int clone(int x) { return ++nc,siz[nc] = siz[x],ch[nc][0] = ch[x][0],ch[nc][1] = ch[x][1],nc; }
	void insert(int &rt,int L,int R,int v) { rt = clone(rt);
		if(L == R) { ++siz[rt]; return; }
		if(v <= mid) insert(ch[rt][0],L,mid,v); else insert(ch[rt][1],mid + 1,R,v);
		siz[rt] = siz[ch[rt][0]] + siz[ch[rt][1]];
	}
	void dfs(int u) {
		rt[u] = rt[LCA::fa[0][u]]; insert(rt[u], 1, n,v[u]);
		for(int i = 0;i < g[u].size();++i) { int v = g[u][i]; if(v != LCA::fa[0][u]) dfs(v); }
	}
}

int lastans = 0;
int query(int rt1,int rt2,int rt3,int rt4, int L,int R,int k) {
	if(L == R) return L;
	int lsz = Seg::siz[Seg::ch[rt3][0]] + Seg::siz[Seg::ch[rt4][0]] - Seg::siz[Seg::ch[rt1][0]] - Seg::siz[Seg::ch[rt2][0]];
	if(k <= lsz) return query(Seg::ch[rt1][0],Seg::ch[rt2][0],Seg::ch[rt3][0],Seg::ch[rt4][0],L,mid,k);
	else return query(Seg::ch[rt1][1],Seg::ch[rt2][1],Seg::ch[rt3][1],Seg::ch[rt4][1],mid + 1,R,k - lsz);
}
int main() {
	_rep(i,1,n) v[i] = d[i] = in();
	sort(d + 1,d + 1 + n);
	_rep(i,1,n) v[i] = lower_bound(d + 1,d + 1 + n,v[i]) - d;
	_rep(i,1,n - 1) {
		int u = in(),v = in();
		g[u].push_back(v);
		g[v].push_back(u);
	}
	LCA::init(); Seg::dfs(1);
	_rep(i,1,m) {
		int u = in() ^ lastans,v = in(),k = in();
		int lca = LCA::query(u,v);
		printf("%d\n",lastans = d[query(Seg::rt[lca],Seg::rt[LCA::fa[0][lca]],Seg::rt[u],Seg::rt[v],1,n,k)]);
	}
	return 0;
}
