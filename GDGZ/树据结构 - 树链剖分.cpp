//created time: 2022-05-28 15:01:36
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

const int kN = 100500,kM = kN << 2;
ll a[kM], b[kM], area[kM]; 

void pushdown(int x) {
	area[x << 1] += area[x] + b[x] * a[x << 1]; a[x << 1] += a[x]; b[x << 1] += b[x]; //b[x] 表示放大倍数, a[x] 表示要放大的宽(?)
	area[x << 1|1] += area[x] + b[x] * a[x << 1 | 1]; a[x << 1 | 1] += a[x]; b[x << 1 | 1] += b[x];
	area[x] = a[x] = b[x] = 0;
}

void add(int x,int L,int R,int l,int r,int d) {
	if(l <= L && R <= r) {
		a[x] += d;
		return;
	}
	pushdown(x);
	if(l <= mid) add(x << 1,L,mid,l,r,d);
	if(mid < r) add(x << 1 | 1,mid + 1,R,l,r,d);
}

void mul(int x,int L,int R,int l,int r,int d) {
	if(l <= L && R <= r) {
		b[x] += d; area[x] += d * a[x];
		return;
	}
	pushdown(x);
	if(l <= mid) mul(x << 1,L,mid,l,r,d);
	if(mid < r) mul(x << 1 | 1,mid + 1,R,l,r,d);
}

ll query(int x,int L,int R,int pos) {
	if(L == R) return area[x];
	pushdown(x);
	return pos <= mid ? query(x << 1,L,mid,pos) : query(x << 1 | 1,mid + 1,R,pos);
}

vector<int> g[kN];
int n = in();
int f[kN],siz[kN],son[kN],dep[kN];

void dfs1(int u,int fa) {
	siz[u] = 1,f[u] = fa,dep[u] = dep[fa] + 1;
	for(auto &v : g[u]) if(v != fa) {
		dfs1(v,u); siz[u] += siz[v]; if(siz[v] > siz[son[u]]) son[u] = v;
	}
}

int top[kN],dfn[kN],dfs_clock;
void dfs2(int u,int t) {
	top[u] = t,dfn[u] = ++dfs_clock;
	if(son[u]) dfs2(son[u],t);
	for(auto &v :g[u]) if(v != f[u] && v != son[u]) dfs2(v,v);
}

void add(int u,int k) {
	while(u) {
		add(1,1,n,dfn[top[u]],dfn[u],k);
		u = f[top[u]];
	}
}

void mul(int u,int k) {
	while(u) {
		mul(1,1,n,dfn[top[u]],dfn[u],k);
		u = f[top[u]];
	}
}

int main() {
	_rep(i,2,n) {
		int u = in(),v = in();
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs1(1,0);
	dfs2(1,0);
	int m = in();
	while(m--) {
		int opt = in(),x = in();
		if(opt == 1) add(x,in());
		if(opt == 2) mul(x,in());
		if(opt == 3) printf("%lld\n",query(1,1,n,dfn[x]));
	}
	return 0;
}
