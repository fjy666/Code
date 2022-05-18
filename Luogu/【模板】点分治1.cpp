#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
const int kN = 10500;
vector<pair<int,int> > g[kN];
int n = in(),m = in(),qry[kN],siz[kN],ful,root,rm,ans[kN];
int forbbiden[kN];
void calc(int u,int f) {
	siz[u] = 1; int mx = 0;
	for(pair<int,int> &e : g[u]) if(!forbbiden[e.first] && e.first != f) 
		calc(e.first,u), siz[u] += siz[e.first], mx = max(mx,siz[e.first]); 
	mx = max(mx,ful - siz[u]); if(mx < rm) root = u,rm = mx;
} 
int dis[kN], top, d[kN];
void f(int u,int fa) { if(d[u] > 10000000) return;
	dis[++top] = d[u]; 
	for(pair<int,int> &e : g[u]) if(!forbbiden[e.first] && e.first != fa) {
		d[e.first] = d[u] + e.second; f(e.first,u);
	}
}
int vis[10000050],_[kN],_t;
void solve(int u) {
	_t = 0; vis[0] = 1;
	for(pair<int,int> &e : g[u]) if(!forbbiden[e.first]) {
		d[e.first] = e.second; top = 0; f(e.first,u);
		_rep(i,1,top) _rep(j,1,m) if(qry[j] >= dis[i] && vis[qry[j] - dis[i]]) ans[j] = 1;
		_rep(i,1,top) _[++_t] = dis[i], vis[dis[i]] = 1;
	}
	_rep(i,1,_t) vis[_[i]] = 0;
}
void divid(int u) {
	solve(u);
	forbbiden[u] = 1;
	for(pair<int,int> &e : g[u]) {
		if(forbbiden[e.first]) continue;
		ful = siz[e.first], rm = INT_MAX; calc(e.first,u);
		divid(root);
	}
}
int main() {
	vis[0] = 1;
	_rep(i,1,n - 1) {
		int u = in(),v = in(),w = in();
		g[u].push_back({v,w});
		g[v].push_back({u,w});
	}
	_rep(i,1,m) qry[i] = in();
	ful = n,rm = INT_MAX; calc(1,0);
	divid(root);
	_rep(i,1,m) puts(ans[i] ? "AYE" : "NAY");
	return 0;
}
