// created time : 2022-04-06 21:07:37
// writer : fjy
#include <bits/stdc++.h>
#define _rep(i_,a_,b_) for(int i_ = a_;i_ <= b_;++i_)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
using namespace std;
const int kN = 100500;
vector<int> g[kN];
int fat[kN]; int find(int x) { return fat[x] == x ? x : fat[x] = find(fat[x]); }
int p[kN],f[kN][2];

void dp(int u,int fa) {
	f[u][1] = p[u];
	for(auto &v : g[u]) if(v != fa) {
		dp(v,u);
		f[u][0] += max(f[v][0],f[v][1]);
		f[u][1] += f[v][0];
	}
}

void calc(int rt) {
	memset(f,0,sizeof(f));
	dp(rt,-1);
}

int main() {
	int n = in();
	_rep(i,1,n) fat[i] = i,p[i] = in();
	int s,t;
	_rep(i,1,n) {
		int u = in() + 1,v = in() + 1;
		if(find(u) != find(v))
			fat[find(u)] = find(v);
		else {
			s = u,t = v;
			continue;
		}
		g[u].push_back(v);
		g[v].push_back(u);
	}
	calc(s);
	int anss = f[s][0];
	calc(t);
	double k;
	scanf("%lf",&k);
	printf("%.1f\n",k * max(anss,f[t][0]));
	return 0;
}