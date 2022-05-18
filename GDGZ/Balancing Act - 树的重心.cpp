#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
const int kN = 20500;
vector<int> g[kN];
int siz[kN],mx[kN],n;
int ansx = INT_MAX,ansy;
void dfs(int u,int fa) {
	siz[u] = 1, mx[u] = INT_MIN;
	for(auto &v : g[u]) if(v != fa) {
		dfs(v,u);
		siz[u] += siz[v];
		mx[u] = max(mx[u],siz[v]);
	}
	mx[u] = max(mx[u], n - siz[u]);
	if(mx[u] < ansx || (mx[u] == ansx && u < ansy)) ansx = mx[u], ansy = u;
}
int main() {
	int t = in();
	while(t--) {
		n = in();
		_rep(i,1,n) g[i].clear();
		_rep(i,2,n) {
			int u = in(),v = in(); 
			g[u].push_back(v);
			g[v].push_back(u);
		}
		ansx = INT_MAX;
		dfs(1,-1);
		printf("%d %d\n",ansy, ansx);
	}
	return 0;
}
