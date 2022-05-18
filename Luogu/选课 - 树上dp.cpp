#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
const int kN = 305;
vector<int> g[kN];
int w[kN],f[kN][kN],siz[kN];
int n = in(),m = in() + 1;
void dfs(int u) {
	siz[u] = 1;
	f[u][1] = w[u];
	for(auto &v : g[u]) {
		dfs(v); siz[u] += siz[v];
		//f[v][k] 代表当给 v　的子树里选 k 门课的学分,k <= siz[v]
		for(int i = min(m,siz[u]); ~i; --i) 
			for(int j = min(i - 1,siz[v]); ~j; --j)
				f[u][i] = max(f[u][i],f[u][i - j] + f[v][j]);
	}
}

int main() {
	_rep(i,1,n) {
		g[in()].push_back(i);
		w[i] = in();
	}
	dfs(0);
	printf("%d\n",f[0][min(m,siz[0])]);
	return 0;
}
