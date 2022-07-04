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
vector<int> g[kN];
int n = in();
int siz[kN], dep[kN]; ll ans[kN];

void dfs1(int u, int f) {
	siz[u] = 1, dep[u] = dep[f] + 1;
	for(auto &v : g[u]) if(v != f) dfs1(v, u), siz[u] += siz[v];
}
void dfs2(int u, int f) {
	for(auto &v : g[u]) if(v != f) {
		ans[v] = ans[u] - siz[v] + (siz[1] - siz[v]);
		dfs2(v, u);
	}
}

int main() { 
	_rep(i,2,n) {
		int u = in(), v = in();
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dep[0] = -1; dfs1(1, 0);
	ans[1] = accumulate(dep + 1, dep + 1 + n, 1ll);
	dfs2(1, 0);
	int res = 0;
	_rep(i,1,n) {  if(ans[i] > ans[res]) res = i; }
	printf("%d\n", res);
	return 0;
}

/* 
a list of keywords 
clear empty push_back pop_back push pop top front back
emplace_back emplace push_front pop_front insert erase
find count set reset bitset map vector string multiset
first second iterator prev next deque multimap reverse
*/