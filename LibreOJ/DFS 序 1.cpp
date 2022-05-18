#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
const int kN = 1000500;
int a[kN],siz[kN],dfn[kN],dfs_clock;
vector<int> g[kN];

void dfs(int rt,int fa) {
	dfn[rt] = ++dfs_clock; siz[rt] = 1;
	for(auto &v : g[rt])
		if(v != fa) {
			dfs(v,rt);
			siz[rt] += siz[v];
		}
}

ll c[kN];
void add(int pos,ll x) {
	for(;pos < kN; pos += pos & -pos) c[pos] += x;
}
ll query(int pos) {
	ll ans = 0;  for(;pos;pos -= pos & -pos) ans += c[pos]; return ans;
}
ll query(int l,int r) { return query(r) - query(l - 1); }

int main() {
	int n = in(),m = in(),r = in();
	_rep(i,1,n) a[i] = in();
	_rep(i,1,n - 1) {
		int u = in(),v = in();
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(r,-1);
	_rep(i,1,n) add(dfn[i],a[i]);
	_rep(i,1,m) {
		int opt = in(),a = in();
		if(opt == 1) add(dfn[a],in());
		else printf("%lld\n",query(dfn[a],dfn[a] + siz[a] - 1));
	}
	return 0;
}
