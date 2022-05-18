// -< fjy666 >-
//ALWAYS TO REMAMBER DELETE THE DEBUGGING STATEMENT
#include <bits/stdc++.h>
#define _rep(i_,a_,b_) for(int i_ = a_;i_ <= b_;++i_)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
using namespace std;


const int kN = 2305;
struct Edge {
	int u,v;
	ll cap,flow;
};
vector<Edge> E;
vector<int> G[kN];
void add_edge(int u,int v,ll f) {
	E.push_back({u,v,f,0});
	G[u].push_back(E.size() - 1);
	E.push_back({v,u,0,0});
	G[v].push_back(E.size() - 1);
}
int dep[kN];
bool bfs(int s,int t) {
	memset(dep,0,sizeof(dep));
	queue<int> q;
	q.push(s); dep[s] = 1;
	while(!q.empty()) {
		int u = q.front(); q.pop();
		for(int &id : G[u]) {
			Edge &e = E[id];
			if(e.cap > e.flow && !dep[e.v]) {
				dep[e.v] = dep[u] + 1;
				q.push(e.v);
			}
		}
	}
	if(dep[t]) return true;
	return false;
} 
ll dfs(int u,ll flow,int t) {
	if(u == t) return flow;
	ll ans = 0;
	for(auto &id : G[u]) {
		Edge &e = E[id];
		if(dep[e.v] == dep[u] + 1 && e.cap > e.flow) {
			ll f = dfs(e.v,min(e.cap - e.flow,flow),t);
			ans += f;
			flow -= f;
			E[id].flow += f;
			E[id ^ 1].flow -= f;
		}
	}
	if(!ans) dep[u] = 0;
	return ans;
}
ll max_flow(int s,int t) {
	ll res = 0;
	while(bfs(s,t))
		res += dfs(s,LLONG_MAX,t);
	return res;
}

int main() {
	int n = in(),m = in(),S = 0,T = kN - 1;
	_rep(i,1,n) {
		int t;
		while(t = in()) add_edge(i,n + t,1);
	}
	_rep(i,1,n) add_edge(S,i,1);
	_rep(i,1,m) add_edge(n + i,T,1);
	printf("%lld\n",max_flow(S,T));
	return 0;
}

