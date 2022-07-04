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
const int kN = 100500;
vector<pair<int,ll> > g[kN];
void addedge(int u, int v, ll w) {
	g[u].push_back({v, w});
	g[v].push_back({u, w});
}
int n = in(), m = in();
int dfn[kN], dfs_clock, dfm[kN], dep[kN], fa[kN], siz[kN], son[kN];
ll dis[kN];
void dfs1(int u, int f) {
	siz[u] = 1, fa[u] = f, dep[u] = dep[f] + 1;
	for(auto &e : g[u]) if(e.first != f) { int v = e.first; ll w = e.second;
		dis[v] = dis[u] + w;
		dfs1(v, u), siz[u] += siz[v]; if(siz[v] > siz[son[u]]) son[u] = v;
	}
}
int top[kN];
void dfs2(int u, int t) {
	top[u] = t, dfn[u] = ++dfs_clock, dfm[dfs_clock] = u;
	if(son[u]) dfs2(son[u], t);
	for(auto &e : g[u]) if(e.first != fa[u] && e.first != son[u]) dfs2(e.first, e.first);
}
int LCA(int u, int v) {
	while(top[u] != top[v]) {
		if(dep[top[u]] < dep[top[v]]) swap(u, v);
		u = fa[top[u]];
	}
	return dep[u] < dep[v] ? u : v;
} 

struct Line {
	ll k, b;
	ll calc(ll x) { return k * dis[dfm[x]] + b; }
} t[kN << 2]; ll mn[kN << 2];
void pushup(int x, int L, int R) { mn[x] = min({mn[x], t[x].calc(L), t[x].calc(R), mn[x << 1], mn[x << 1 | 1]}); }
void insert(int x, int L, int R, int l, int r, Line s) {
	if(r < L || R < l) return;
	if(l <= L && R <= r) {
		if(L == R) { if(t[x].calc(L) > s.calc(L)) t[x] = s; mn[x] = t[x].calc(L); }
		else {
			if(t[x].k < s.k) {
				if(t[x].calc(mid) > s.calc(mid)) insert(x << 1 | 1, mid + 1, R, l, r, t[x]), t[x] = s;
				else insert(x << 1, L, mid, l, r, s);			
			} else if(t[x].k > s.k) {
				if(t[x].calc(mid) > s.calc(mid)) insert(x << 1, L, mid, l, r, t[x]), t[x] = s;
				else insert(x << 1 | 1, mid + 1, R, l, r, s);
			} else {
				if(t[x].calc(mid) > s.calc(mid)) t[x] = s;
			}
			pushup(x, L, R);
		}
	} else {
		insert(x << 1, L, mid, l, r, s);
		insert(x << 1 | 1, mid + 1, R, l, r, s);
		pushup(x, L, R);
	}
}
ll query(int x, int L, int R, int l, int r) {
	if(l <= L && R <= r) return mn[x];
	ll ans = min(t[x].calc(max(l, L)), t[x].calc(min(r, R)));	
	if(l <= mid) ans = min(ans, query(x << 1, L, mid, l, r));
	if(mid < r) ans = min(ans, query(x << 1 | 1, mid + 1, R, l, r));
	return ans;
}

void modify(int s, int t, ll a, ll b) { int l = LCA(s, t);
	Line s1, s2;
	//(dis[s] - dis[i])a + b
	//a * dis[s] - a * dis[i] + b
	s1.k = -a, s1.b = b + a * dis[s];
	s2.k = a, s2.b = b + a * (dis[s] - 2 * dis[l]);
	while(top[s] != top[t]) {
		if(dep[top[s]] > dep[top[t]]) insert(1, 1, n, dfn[top[s]], dfn[s], s1), s = fa[top[s]];
		else insert(1, 1, n, dfn[top[t]], dfn[t], s2), t = fa[top[t]];
	}
	if(dfn[s] < dfn[t]) insert(1, 1, n, dfn[s], dfn[t], s2);
	else insert(1, 1, n, dfn[t], dfn[s], s1);
}

ll query(int s, int t) {
	ll res = LLONG_MAX;
	while(top[s] != top[t]) {
		if(dep[top[s]] < dep[top[t]]) swap(s, t);
		res = min(res, query(1, 1, n, dfn[top[s]], dfn[s])), s = fa[top[s]]; 
	}
	if(dfn[s] > dfn[t]) swap(s, t); res = min(res, query(1, 1, n, dfn[s], dfn[t]));
	return res;
}

int main() { 
	_rep(i,2,n) {
		int u = in(), v = in(); ll w = inl();
		addedge(u, v, w);
	}
	dfs1(1, 0); dfs2(1, 1);
	fill(t, t + (kN << 2), Line{0, LLONG_MAX});
	fill(mn, mn + (kN << 2), LLONG_MAX);
	insert(1, 1, n, 1, n, Line{0ll, 123456789123456789ll});
	_rep(i,1,m) {
		int op = in(), a, b;
		if(op == 1) {
			a = in(), b = in(); ll c = in(), d = in();
			modify(a, b, c, d);
		} else {
			a = in(), b = in();
			printf("%lld\n", query(a, b));
		}
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