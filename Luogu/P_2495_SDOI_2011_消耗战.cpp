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
const int kN = 290000;
vector<pair<int,ll> > g[kN], g2[kN];
int n;
int fa[20][kN], lg[kN], dep[kN], dfn[kN], dfs_clock;
ll minx[kN];
void dfs1(int u, int f) { dfn[u] = ++dfs_clock;
	dep[u] = dep[f] + 1, fa[0][u] = f; _rep(i,1,19) fa[i][u] = fa[i - 1][fa[i - 1][u]];
	for(auto &[v, w] : g[u]) if(v != f) {
		minx[v] = min(minx[u], w); dfs1(v, u);
	}
}
int LCA(int u, int v) {
	while(dep[u] != dep[v]) {
		if(dep[u] < dep[v]) swap(u,v);
		u = fa[lg[dep[u] - dep[v]]][u];
	}
	if(u == v) return u;
	for(int i = 19; ~i; --i) if(fa[i][u] != fa[i][v]) u = fa[i][u], v = fa[i][v];
	return fa[0][u]; 
}

vector<int> query; int flag[kN];
int stk[kN], top;

ll dp(int u, int fat) {
	ll sum = 0, fu = 0;
	for(auto& [v, _] : g2[u]) if(v != fat) sum += dp(v, u);
	if(flag[u]) fu = minx[u]; else fu = min(minx[u], sum);
	return fu;
}

void dfs_vis(int u, int fat) {
	printf("NODE %d: ", u);
	for(auto &[v,w] : g2[u]) if(v != fat) printf("%d ",v); puts("");
	for(auto &[v,w] : g2[u]) if(v != fat) dfs_vis(v, u);
}

int main() { 
	freopen("5.in", "r", stdin);
	freopen("5.out", "w", stdout);
	n = in();
	_rep(i,1,n - 1) {
		int u = in(), v = in(), w = in();
		g[u].push_back({v,w});
		g[v].push_back({u,w});
	}
	minx[1] = LLONG_MAX;
	dfs1(1, 0);
	_rep(i,2,n) lg[i] = lg[i >> 1] + 1;
	// printf("LCA(3, 8) = %d\n", LCA(3,8));
	int q = in();
	while(q--) {
		query.clear();
		int k = in(); _rep(i,1,k) query.push_back(in()), flag[query.back()] = 1;
		sort(query.begin(), query.end(), [](const int &a, const int &b) -> bool { return dfn[a] < dfn[b]; });
		stk[top = 1] = 1; g2[1].clear();
		for(auto &u : query) { //建立虚树
			int l = LCA(u, stk[top]); 
			if(l != stk[top]) {
				// puts("going if condition");
				while(dfn[stk[top - 1]] > dfn[l]) {
					g2[stk[top]].push_back({stk[top - 1], -1});
					g2[stk[top - 1]].push_back({stk[top], -1});
					--top;
				} 
				if(dfn[stk[top - 1]] != dfn[l]) {
					// printf("for u = %d going case 1, stk[top] = %d\n", u, stk[top]);
					g2[l].clear(), g2[l].push_back({stk[top], -1}), g2[stk[top]].push_back({l, -1}), stk[top] = l;
				} else g2[stk[top]].push_back({l, -1}), g2[l].push_back({stk[top--], -1});
			}
			stk[++top] = u, g2[u].clear();
		}
		_rep(i,1,top - 1) g2[stk[i]].push_back({stk[i + 1], -1}), g2[stk[i + 1]].push_back({stk[i], -1});
		//build virtual tree in O(klogk)
		// dfs_vis(1, 0);
		printf("%lld\n", dp(1, 0));
		for(auto &p : query) flag[p] = 0;
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