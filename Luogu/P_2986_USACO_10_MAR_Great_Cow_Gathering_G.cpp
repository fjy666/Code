//Code by fjy666
#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
#define multiCase() int testCnt = in(); _rep(curCase,1,testCnt)
typedef long long ll;

#define int long long
int in(void) { int x; scanf("%lld", &x); return x; }
ll inl(void) { ll x; scanf("%lld", &x); return x; }
const int kN = 100500;
int C[kN], n = in(), siz[kN], dep[kN], ans[kN], tot;
vector<pair<int,int> > g[kN];
void dfs1(int u, int f) {
	siz[u] = C[u]; ans[1] += 1ll * C[u] * dep[u];
	for(auto &[v,w] : g[u]) if(v != f) {
		dep[v] = dep[u] + w;
		dfs1(v, u);
		siz[u] += siz[v];
	}
}
void dfs2(int u, int f) {
	for(auto &[v, w] : g[u]) if(v != f) {
		ans[v] = ans[u] + w * (tot - siz[v]) - w * siz[v];
		dfs2(v, u);
	}
}
signed main() { 
	_rep(i,1,n) C[i] = in(), tot += C[i];
	_rep(i,2,n) {
		int u = in(), v = in(), w = in();
		g[u].emplace_back(v,w);
		g[v].emplace_back(u,w);
	}
	dfs1(1, 0);
	dfs2(1, 0);
	printf("%lld\n", *min_element(ans + 1, ans + 1 + n));
	printf("%d", a);
	return 0;
}

/* 
a list of keywords 
clear empty push_back pop_back push pop top front back
emplace_back emplace push_front pop_front insert erase
find count set reset bitset map vector string multiset
first second iterator prev next deque multimap reverse
*/