//Code by fjy666
#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
#define multiCase() int testCnt = in(); _rep(curCase,1,testCnt)
typedef long long ll;

int in(void) { int x; scanf("%d", &x); return x; }
ll inl(void) { ll x; scanf("%lld", &x); return x; }
const int kN = 1000500;
int n = in();
vector<int> g[kN], g2[kN];
int fa[20][kN], dep[kN], dfn[kN], dfs_clock, lg[kN];

void dfs(int u, int f) {
	fa[0][u] = f; _rep(i,1,19) fa[i][u] = fa[i - 1][fa[i - 1][u]];
	dep[u] = dep[f] + 1, dfn[u] = ++dfs_clock;
	for(auto &v : g[u]) if(v != f) dfs(v, u);
}
int LCA(int u, int v) {
	while(dep[u] != dep[v]) {
		if(dep[u] < dep[v]) swap(u, v);
		u = fa[lg[dep[u] - dep[v]]][u];
	}
	if(u == v) return u;
	for(int i = 19; ~i; --i) if(fa[i][u] != fa[i][v]) u = fa[i][u], v = fa[i][v];
	return fa[0][u];
}

vector<int> queries;
int isQuery[kN], stk[kN], top;
void add_edge(int u, int v) {
	// printf("Add (%d,%d)\n", u, v);
	g2[u].push_back(v);
	g2[v].push_back(u);
}
int siz[kN], mx[kN], mn[kN], res1, res2;
ll res; //总和
const int inf = 0x3f3f3f3f;
void dfs2(int u, int f) {
	siz[u] = isQuery[u]; mn[u] = isQuery[u] ? 0 : inf, mx[u] = isQuery[u] ? 0 : -inf;
	for(auto &v : g2[u]) if(v != f) {
		dfs2(v, u);
		siz[u] += siz[v];
		int weight = abs(dep[u] - dep[v]);
		res1 = min(res1, mn[u] + mn[v] + weight);
		res2 = max(res2, mx[u] + mx[v] + weight);
		mn[u] = min(mn[u], mn[v] + weight);
		mx[u] = max(mx[u], mx[v] + weight);
	}
	// printf("u = %d, mx = %d, mn = %d\n", u, mx[u], mn[u]);
	for(auto &v : g2[u]) if(v != f) 
		res += 1ll * siz[v] * ((int) queries.size() - siz[v]) * abs(dep[u] - dep[v]);
} 
int main() { 
	_rep(i,2,n) {
		int u = in(), v = in();
		g[u].push_back(v), g[v].push_back(u);
	}
	dfs(1, 0);
	_rep(i,2,n) lg[i] = lg[i >> 1] + 1;
	multiCase() {
		queries.clear();
		int k = in(); _rep(i,1,k) queries.push_back(in()), isQuery[queries.back()] = 1;
		sort(queries.begin(), queries.end(), 
			[](const int &a, const int &b) -> bool { return dfn[a] < dfn[b]; });
		stk[top = 1] = 1; g2[1].clear();
		for(auto &u : queries) if(u != 1) {
			int l = LCA(u, stk[top]);
			if(l != stk[top]) {
				while(dfn[stk[top - 1]] > dfn[l]) {
					add_edge(stk[top], stk[top - 1]);
					--top;
				}
				if(dfn[stk[top - 1]] == dfn[l]) {
					add_edge(stk[top], l);
					--top;
				} else g2[l].clear(), add_edge(l, stk[top]), stk[top] = l;
			}
			stk[++top] = u; g2[u].clear();
		}
		_rep(i,1,top - 1) add_edge(stk[i], stk[i + 1]);
		res = res2 = 0; res1 = inf;
		dfs2(1, 0);
		printf("%lld %d %d\n", res, res1, res2);
		for(auto &q : queries) isQuery[q] = 0;
	}
	return 0;
}

/* 
a list of keywords 
clear empty push_back pop_back push pop top front back
emplace_back emplace push_front pop_front insert erase
find count set reset bitset map vector string multiset
first second iterator prev next deque multimap reverse
*/