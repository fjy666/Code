//created time: 2022-05-28 09:27:57
#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;

namespace FastIO { //by fjy666
	char OBuf[1 << 23], *p = OBuf;
	inline void pc(char c) { *p++=c; }
	inline void out(ll x) { if(x < 0) pc('-'), x = -x; if(x > 9) out(x / 10); pc(x % 10 + '0'); }
	inline void out(int x) { if(x < 0) pc('-'), x = -x; if(x > 9) out(x / 10); pc(x % 10 + '0'); }
	inline void out(char *s) { if(*s) pc(*s),out(s+1); }
	inline void flush(void) { fwrite(OBuf,p - OBuf,1,stdout); }
	struct _Flusher{ ~_Flusher(){ flush(); } } flusher;
	
	char IBuf[1 << 23], *i1 = IBuf,*i2 = IBuf;
	inline char gc(void) { return (i1 == i2 && (i2 = (i1 = IBuf) + fread(IBuf,1,1 << 23,stdin),i1 == i2)) ? EOF : *i1++; }
	inline int in(void) {
		char c = gc(); int x = 0,f = 1; while(!isdigit(c)) { if(c == '-') f = -1; c = gc(); }
		while(isdigit(c)) { x = x * 10 + c - '0', c = gc(); } return x * f;
	}
	inline ll inl(void) {
		char c = gc(); ll x = 0,f = 1; while(!isdigit(c)) { if(c == '-') f = -1; c = gc(); }
		while(isdigit(c)) { x = x * 10 + c - '0', c = gc(); } return x * f;
		}
} using FastIO::pc; using FastIO::out; using FastIO::gc; using FastIO::in; using FastIO::inl;
const int kN = 1000500;
vector<int> g[kN];
ll fight[kN],f[kN][2],ff[kN][2][2];
//ff[i][j][k] 表示dp到i，i的取/不取情况为j, 1号节点的取/不取情况为k
int deg[kN],ring[kN],top;
//f[i][0] 代表没有 i，f[i][1] 代表有 i

void dp(int u,int fa) {
	f[u][0] = 0,f[u][1] = fight[u];
	for(auto &v : g[u]) if(!deg[v] && v != fa) {
		dp(v,u);
		f[u][0] += max(f[v][1], f[v][0]);
		f[u][1] += f[v][0];
	}
} 


void dfs(int u) {
	ring[++top] = u;
	deg[u] = 0;
	for(auto &v : g[u]) if(deg[v]) dfs(v);
}

int main() {
	int n = in();
	_rep(i,1,n) {
		fight[i] = inl();
		int u = in();
		g[u].push_back(i);
		g[i].push_back(u);
		++deg[u], ++deg[i];
	}
	
	queue<int> q;
	_rep(i,1,n) if(deg[i] == 1) q.push(i);
	while(!q.empty()) {
		int u = q.front(); q.pop();
		for(auto &v : g[u]) {
			--deg[v];
			if(deg[v] == 1) q.push(v);
		}
	}
	_rep(i,1,n) if(deg[i] != 2) deg[i] = 0;
	_rep(i,1,n) if(deg[i]) dp(i,0);
	
	ll res = 0;
	_rep(i,1,n) if(deg[i]) {
		//搞一个环
		top = 0;
		dfs(i);
		
		printf("FIND RING:");
		_rep(i,1,top) printf("%d ",ring[i]);
		puts("");
		//环上最大独立集OvO
		
//		if(top == 1) {
//			res += max(f[ring[1]][0], f[ring[1]][1]);
//			continue;
//		}
		
		ff[1][0][0] = f[ring[1]][0];
		ff[1][1][1] = f[ring[1]][1];
		_rep(i,2,top) _rep(j,0,1) {
			ff[i][0][j] = f[ring[i]][0]  
					    + max(ff[i - 1][0][j], ff[i - 1][1][j]);
			ff[i][1][j] = f[ring[i]][1] + ff[i - 1][0][j];
		}
		res += max({ff[top][0][1], ff[top][0][0], ff[top][1][0]});
		
		_rep(i,1,top) ff[i][0][0] = ff[i][0][1] = ff[i][1][0] = ff[i][1][1] = 0; 
	}
	printf("%lld\n",res);
	return 0;
}
