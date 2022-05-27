//基环树是啥？能吃吗？？？
#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
const int kN = 300500;
vector<int> g[kN];
int dfn[kN],dfs_clock,siz[kN],dep[kN];
void dfs(int u,int f) {
	siz[u] = 1,dfn[u] = ++dfs_clock,dep[u] = dep[f] + 1;
	for(auto &v : g[u]) if(v != f) dfs(v,u),siz[u] += siz[v];
}
ll sum[kN * 30];
int ch[kN * 30][2],nc;
int clone(int x) { return ++nc,sum[nc] = sum[x],ch[nc][0] = ch[x][0],ch[nc][1] = ch[x][1],nc; }
void insert(int &rt,int L,int R,int pos,int value) { rt = clone(rt);
	sum[rt] += value;
	if(L == R) return;
	if(pos <= mid) insert(ch[rt][0],L,mid,pos,value); else insert(ch[rt][1],mid + 1,R,pos,value);
}
ll query(int rt,int L,int R,int l,int r) {
	if(l <= L && R <= r) return sum[rt];
	if(l > r) return 0;
	ll ans = 0;
	if(l <= mid) ans += query(ch[rt][0],L,mid,l,r);
	if(mid < r) ans += query(ch[rt][1],mid + 1,R,l,r);
	return ans;
}
int a[kN],rt[kN];
int main() {
	int n = in(),q = in();
	_rep(i,1,n - 1) {
		int u = in(),v = in();
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1,0);
	_rep(i,1,n) a[i] = i;
	sort(a + 1,a + 1 + n,[](const int &a,const int &b)->bool{ return dep[a] < dep[b]; });
	
	_rep(i,1,n) {
		if(dep[a[i]] != dep[a[i - 1]]) rt[dep[a[i]]] = rt[dep[a[i - 1]]];
		insert(rt[dep[a[i]]],1,n,dfn[a[i]],siz[a[i]] - 1);
 	}
	int MAX_DEP = dep[a[n]];
	while(q--) {
		int p = in(),k = in();
		ll ans1 = 0; //统计 b 在 p 上面的方案数
		ans1 = (ll) min(dep[p] - 1,k) * (siz[p] - 1);
		ll ans2 = 0; //统计 b 在 p 下面的方案数
		ans2 = query(rt[min(MAX_DEP,dep[p] + k)],1,n,dfn[p] + 1,dfn[p] + siz[p] - 1);
		printf("%lld\n",ans1 + ans2);
	}
	return 0;
}
