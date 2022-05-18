#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
const int kN = 40500;
vector<pair<int,int> > g[kN];
int n = in(),k = in(),siz[kN],ful,mx[kN],rt;
int ban[kN];
void calc(int u,int f) {
	siz[u] = 1,mx[u] = 0;
	for(auto &[v,w] : g[u])
		if(v != f && !ban[v]) {
		calc(v,u);
		siz[u] += siz[v];
		mx[u] = max(mx[u],siz[v]);
	}
	mx[u] = max(mx[u],ful - siz[u]); 
	if(mx[u] < mx[rt]) rt = u;
}
int dis[kN],top,d[kN];
void get_dis(int u,int fa) { if(d[u] > k) return;
	dis[++top] = d[u];
	for(auto &[v,w] : g[u]) if(!ban[v] && v != fa) {
		d[v] = d[u] + w;
		get_dis(v,u);
	}
}

int bit[kN];
//void add(int p,int d) { for(;p < kN;p += p & -p) bit[p] += /d; }
//int qry(int p) { int a = 0; for(;p;p -= p & -p) a += bit[p]; return a; }

ll res = 0;
void solve(int u) {
	queue<int> q;
	for(auto &[v,w] : g[u]) if(!ban[v]) {
		top = 0; d[v] = w; get_dis(v,u);
		_rep(i,1,top) res += bit[k - dis[i]];
		_rep(i,1,top) ++bit[dis[i]],q.push(dis[i]);
	}
	while(!q.empty()) --bit[q.front()],q.pop();
}

void divid(int u) {
	solve(u);
	ban[u] = 1;
	for(auto &[v,w] : g[u])
		if(!ban[v]) {
		ful = siz[v],rt = 0;
		calc(v,u);
		divid(rt);
	}
}
int main() {
	mx[0] = INT_MAX,ful = n;
	++bit[0];
	_rep(i,2,n) {	
		int a = in(),b = in();//,c = in();
		g[a].push_back({b,1});
		g[b].push_back({a,1});
	}
	calc(1,0);
	divid(rt);
	printf("%lld\n",res);
	return 0;
}
