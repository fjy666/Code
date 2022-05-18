#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
const int kN = 150;
int n = in(),q = in();
vector<pair<int,int> > g[kN];
int f[kN][kN],siz[kN];
void dfs(int u,int fa) {
	for(auto& [v,w] : g[u]) if(v != fa) {
		dfs(v,u); siz[u] += siz[v] + 1;
		for(int i = min(siz[u],q);~i;--i)
			for(int j = min(siz[v],i - 1);~j;--j) 
				f[u][i] = max(f[u][i], f[u][i - j - 1] + f[v][j] + w);
	}
}
int main() {
	_rep(i,2,n) {
		int a = in(),b = in(),c = in();
		g[a].push_back({b,c});
		g[b].push_back({a,c});
	}
	dfs(1,0);
	printf("%d\n",f[1][q]);
	return 0;
}
