//created time: 2022-05-25 12:07:37
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

const int kM = 100500 * 40;
int ch[kM][2], cnt[kM], nc, res[kM];
inline void pushup(int rt) { 
	if(cnt[ch[rt][0]] >= cnt[ch[rt][1]]) cnt[rt] = cnt[ch[rt][0]], res[rt] = res[ch[rt][0]];
	else cnt[rt] = cnt[ch[rt][1]], res[rt] = res[ch[rt][1]];
}
void insert(int &rt,int L,int R,int pos,int v) {
	if(!rt) rt = ++nc;
	if(L == R) { cnt[rt] += v, res[rt] = L; return; }
	if(pos <= mid) insert(ch[rt][0],L,mid,pos,v); else insert(ch[rt][1],mid + 1,R,pos,v);
	pushup(rt);
}
int merge(int x,int y,int L,int R) {
	if(!x || !y) return x + y;
	if(L == R) { cnt[x] += cnt[y]; res[x] = L; return x; }
	ch[x][0] = merge(ch[x][0], ch[y][0], L, mid); ch[x][1] = merge(ch[x][1], ch[y][1], mid+1, R);
	pushup(x); return x;
}

const int kN = 100500;
vector<int> g[kN];
int f[20][kN],lg[kN],rt[kN],dep[kN];
void dfs(int u,int fa) {
	dep[u] = dep[fa] + 1; f[0][u] = fa; for(int i = 1;i < 20;++i) f[i][u] = f[i - 1][f[i - 1][u]];
	for(auto &v : g[u]) if(v != fa) dfs(v,u);
}
int LCA(int u,int v) {
	if(dep[u] < dep[v]) swap(u,v);
	while(dep[u] != dep[v]) u = f[lg[dep[u] - dep[v]]][u];
	if(u == v) return u;
	for(int i = 19;~i;--i) if(f[i][u] != f[i][v]) u = f[i][u], v = f[i][v];
	return f[0][u];	
}

int ans[kN];
void dfs2(int u) {
  	for(auto &v : g[u]) if(v != f[0][u]) {
		dfs2(v);
		rt[u] = merge(rt[u],rt[v],1,1e5);
	}
	ans[u] = cnt[rt[u]] == 0 ? 0 : res[rt[u]];
}

int main() {
	int n = in(),q = in();
	_rep(i,1,n - 1) {
		int a = in(),b = in();
		g[a].push_back(b); g[b].push_back(a);
	}
	_rep(i,2,n) lg[i] = lg[i >> 1] + 1;
	dfs(1,0);
	while(q--) {
		int u = in(),v = in(),k = in();
		int lc = LCA(u,v);
		insert(rt[u],1,1e5,k,1);
		insert(rt[v],1,1e5,k,1);
		insert(rt[lc],1,1e5,k,-1);
		insert(rt[f[0][lc]],1,1e5,k,-1);
	}
	dfs2(1);
	_rep(i,1,n) out(ans[i]),pc('\n');
	return 0;
}
