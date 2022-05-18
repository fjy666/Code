// -< fjy666 >-
//ALWAYS TO REMAMBER DELETE THE DEBUGGING STATEMENT
#include <bits/stdc++.h>
#define _rep(i_,a_,b_) for(int i_ = a_;i_ <= b_;++i_)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
using namespace std;
const int kN = 100005;
vector<pair<int,int> > e;
vector<int> g[kN];
int is_bridge[kN],dfn[kN],low[kN],dfs_clock,dep[kN],up_link[kN],fat[kN];

void Tarjan(int u,int fa) {
	dfn[u] = low[u] = ++dfs_clock; dep[u] = dep[fa] + 1;
	fat[u] = fa;
	for(auto &v : g[u]) {
		pair<int,int> &f = e[v];
		if(!dfn[f.second]) {
			Tarjan(f.second,u);
			up_link[f.second] = v;
			low[u] = min(low[u],low[f.second]); 
			if(low[f.second] > dfn[u]) is_bridge[v] = 1;
		} else if(f.second != fa) low[u] = min(low[u],dfn[f.second]);
	}
} 

int n,m,cas;
bool solve(void) {
	n = in(),m = in();
	if(!n && !m) return false;
	printf("Case %d:\n",++cas);
	
	e.clear();
	_rep(i,1,n) g[i].clear();
	memset(is_bridge,0,sizeof(is_bridge));
	memset(up_link,0,sizeof(up_link));
	memset(low,0,sizeof(low));
	memset(dfn,0,sizeof(dfn));
	memset(dep,0,sizeof(dep));
	memset(fat,0,sizeof(fat));
	dfs_clock = 0;
	
	_rep(i,1,m) {
		int a = in(),b = in();
		e.push_back({a,b});
		g[a].push_back(e.size() - 1);
		e.push_back({b,a});
		g[b].push_back(e.size() - 1);
	}
	
	_rep(i,1,n) if(!dfn[i]) Tarjan(i,0);
	//find all the bridges
	
	int q = in(),cnt_b = 0;
	_rep(i,0,(int)(e.size()) - 1) cnt_b += is_bridge[i];
	while(q--) {
		int a = in(),b = in();
		if(dep[a] < dep[b]) swap(a,b);
		while(dep[a] > dep[b]) {
			if(is_bridge[up_link[a]]) --cnt_b;
			is_bridge[up_link[a]] = 0;
			a = fat[a];
		}
		while(a != b) {
			if(is_bridge[up_link[a]]) --cnt_b;
			is_bridge[up_link[a]] = 0;
			a = fat[a]; 
			
			if(is_bridge[up_link[b]]) --cnt_b;
			is_bridge[up_link[b]] = 0;
			b = fat[b]; 
		}
		printf("%d\n",cnt_b);
	}
	puts("");
	return true;
}

int main() {
	while(solve());
	return 0;
}

