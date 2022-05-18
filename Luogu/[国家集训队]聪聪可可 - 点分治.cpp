#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
const int kN = 20500;
vector<pair<int,int> > g[kN];

int siz[kN], mx[kN], ansx, ansy, n, _s[kN];
void dfs(int u,int fa) {
	siz[u] = 1, mx[u] = INT_MIN;
	for(int no_c17 = 0; no_c17 < g[u].size(); ++no_c17) {
		int v = g[u][no_c17].first, w = g[u][no_c17].second;	
		if(v != fa) {
			dfs(v,u);
			siz[u] += siz[v];
			mx[u] = max(mx[u],siz[v]);
		}
	}
	_s[u] = siz[u];
	mx[u] = max(mx[u], n - siz[u]);
	if(mx[u] < ansx || (mx[u] == ansx && u < ansy)) ansx = mx[u], ansy = u;
}

inline int calc_focus(int u,int f,bool flag = true) {
	ansx = INT_MAX; if(flag) n = _s[u];
	dfs(u,f);
	return ansy;
}
ll gcd(ll a,ll b) { return !b ? a : gcd(b,a % b); }

ll ans = 0,cnt[3],cur[3];
void calc(int u,int f,int len) {
	++cur[len % 3]; ans += cnt[(3 - len + 3 + 3 + 3) % 3];
	for(int no_cpp17 = 0; no_cpp17 < g[u].size(); ++no_cpp17) {
		int v = g[u][no_cpp17].first, w = g[u][no_cpp17].second;	
		if(v != f) calc(v,u,(len + w) % 3);
	} 
}

int vis[kN];
void Divid(int u,int f) {
	vis[u] = 1;
	ll tmp[3] = {cnt[0], cnt[1], cnt[2]};
	cnt[0] = cnt[1] = cnt[2] = 0;
	for(int no_c = 0;no_c < g[u].size(); ++no_c) {
		int v = g[u][no_c].first, w = g[u][no_c].second;
		if(v != f && !vis[v]) {
			cur[0] = cur[1] = cur[2] = 0;
			calc(v,u,w);
			cnt[0] += cur[0], cnt[1] += cur[1], cnt[2] += cur[2];
			Divid(calc_focus(v,u),u);
		}
	}
	ans += cnt[0]; //从一个点到u的路径
	cnt[0] = tmp[0], cnt[1] = tmp[1], cnt[2] = tmp[2];
}

int main() {
	n = in();
	int tmpn = n;
	_rep(i,2,n) {
		int u = in(), v = in(), w = in();
		g[u].push_back({v,w});
		g[v].push_back({u,w});
	}
	Divid(calc_focus(1,0,false),0);
	ll res1 = ans * 2 + tmpn, res2 = tmpn * tmpn;
//	printf("res1 = %lld\n",res1);
	ll d = gcd(res1,res2);
	res1 /= d, res2 /= d;
	printf("%lld/%lld\n",res1,res2);
	return 0;
}
