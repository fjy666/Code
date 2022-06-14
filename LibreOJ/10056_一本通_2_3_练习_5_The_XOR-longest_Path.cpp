#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;

int in(void) { int x; scanf("%d", &x); return x; }
ll inl(void) { ll x; scanf("%lld", &x); return x; }
const int kN = 105000;
vector<pair<int,int> > g[kN];
int dep[kN];
void dfs(int u, int f) {
	for(auto &e : g[u]) if(e.first != f) {
		dep[e.first] = dep[u] ^ e.second;
		dfs(e.first, u);
	}
}
int ch[kN * 35][2],nc;
void insert(int u) {
	int cur = 0;
	for(int i = 30; ~i; --i) {
		int v = (u >> i) & 1;
		if(!ch[cur][v]) ch[cur][v] = ++nc;
		cur = ch[cur][v];
	}
}
int query(int u) {
	int cur = 0, res = 0;
	for(int i = 30; ~i; --i) {
		int v = (u >> i) & 1;
		if(ch[cur][v ^ 1]) res |= 1 << i, cur = ch[cur][v ^ 1];
		else cur = ch[cur][v];
	}
	return res;
}
int main() { 
	int n = in();
	_rep(i,1,n - 1) {
		int u = in(), v = in(), w = in();
		g[u].emplace_back(v,w);
		g[v].emplace_back(u,w);
	} 
	dfs(1, 0);
	insert(dep[1]);
	int ans = 0;
	_rep(i,2,n) {
		ans = max(ans, query(dep[i]));
		insert(dep[i]);
	}
	printf("%d\n", ans);
	return 0;
}