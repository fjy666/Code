//created time: 2022-05-30 14:16:54
#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;

//namespace FastIO { //by fjy666
//	char OBuf[1 << 23], *p = OBuf;
//	inline void pc(char c) { *p++=c; }
//	inline void out(ll x) { if(x < 0) pc('-'), x = -x; if(x > 9) out(x / 10); pc(x % 10 + '0'); }
//	inline void out(int x) { if(x < 0) pc('-'), x = -x; if(x > 9) out(x / 10); pc(x % 10 + '0'); }
//	inline void out(char *s) { if(*s) pc(*s),out(s+1); }
//	inline void flush(void) { fwrite(OBuf,p - OBuf,1,stdout); }
//	struct _Flusher{ ~_Flusher(){ flush(); } } flusher;
//	
//	char IBuf[1 << 23], *i1 = IBuf,*i2 = IBuf;
//	inline char gc(void) { return (i1 == i2 && (i2 = (i1 = IBuf) + fread(IBuf,1,1 << 23,stdin),i1 == i2)) ? EOF : *i1++; }
//	inline int in(void) {
//		char c = gc(); int x = 0,f = 1; while(!isdigit(c)) { if(c == '-') f = -1; c = gc(); }
//		while(isdigit(c)) { x = x * 10 + c - '0', c = gc(); } return x * f;
//	}
//	inline ll inl(void) {
//		char c = gc(); ll x = 0,f = 1; while(!isdigit(c)) { if(c == '-') f = -1; c = gc(); }
//		while(isdigit(c)) { x = x * 10 + c - '0', c = gc(); } return x * f;
//	}
//} using FastIO::pc; using FastIO::out; using FastIO::gc; using FastIO::in; using FastIO::inl;
int in(void) { int x; scanf("%d", &x); return x; }

const int kN = 200500;
int sm[kN * 4], mx[kN * 4], mn[kN * 4], rev[kN * 4];
void pushdown(int x) {
	if(rev[x]) {
		sm[x << 1] = -sm[x << 1]; sm[x << 1 | 1] = -sm[x << 1 | 1];
		int tmp = mx[x << 1]; mx[x << 1] = -mn[x << 1]; mn[x << 1] = -tmp;
		tmp = mx[x << 1 | 1]; mx[x << 1 | 1] = -mn[x << 1 | 1]; mn[x << 1 | 1] = -tmp;
		rev[x << 1] ^= 1; rev[x << 1 | 1] ^= 1;
		rev[x] = 0;
	}
}
void pushup(int x) {
	sm[x] = sm[x << 1] + sm[x << 1 | 1];
	mx[x] = max(mx[x << 1], mx[x << 1 | 1]);
	mn[x] = min(mn[x << 1], mn[x << 1 | 1]);
}
void modify(int x, int L, int R, int p, int w) {
	if(L == R) {
		sm[x] = mx[x] = mn[x] = w;
		return;
	}
	pushdown(x);
	if(p <= mid) modify(x << 1, L, mid, p, w); else modify(x << 1 | 1, mid + 1, R, p, w);
	pushup(x);	
}
void negetive(int x, int L, int R, int l, int r) {
	if(l <= L && R <= r) {
		rev[x] ^= 1; sm[x] = -sm[x];
		int t = mx[x]; mx[x] = -mn[x]; mn[x] = -t;
		return;
	}
	pushdown(x);
	if(l <= mid) negetive(x << 1, L, mid, l, r); 
	if(mid < r) negetive(x << 1 | 1, mid + 1, R, l, r);
	pushup(x);
}
int query_sum(int x, int L, int R, int l, int r) {
	if(l <= L && R <= r) return sm[x];
	pushdown(x);
	int res = 0;
	if(l <= mid) res += query_sum(x << 1, L, mid, l, r);
	if(mid < r) res += query_sum(x << 1 | 1, mid + 1, R, l, r);
	return res;
}
int query_max(int x, int L, int R, int l, int r) {
	if(l <= L && R <= r) return mx[x];
	pushdown(x);
	int res = INT_MIN;
	if(l <= mid) res = max(res, query_max(x << 1, L, mid, l, r));
	if(mid < r) res = max(res, query_max(x << 1 | 1, mid + 1, R, l, r));
	return res;
}
int query_min(int x, int L, int R, int l, int r) {
	if(l <= L && R <= r) return mn[x];
	pushdown(x);
	int res = INT_MAX;
	if(l <= mid) res = min(res, query_min(x << 1, L, mid, l, r));
	if(mid < r) res = min(res, query_min(x << 1 | 1, mid + 1, R, l, r));
	return res;
}

int n = in(), m;
vector<pair<int,int> > g[kN];
vector<pair<int,int> > e;
int dep[kN], fa[kN], siz[kN], son[kN], weight[kN], lg[kN];

void dfs1(int u,int f) {
	siz[u] = 1, fa[u] = f, dep[u] = dep[f] + 1;
	for(auto &[v,w] : g[u]) if(v != f) {
		weight[v] = w;
		dfs1(v, u);
		if(siz[v] > siz[son[u]]) son[u] = v;
	}
}

int top[kN], dfn[kN], dfs_clock;
void dfs2(int u,int t) {
	dfn[u] = ++dfs_clock, top[u] = t, modify(1, 1, n, dfn[u], weight[u]);
	if(son[u]) dfs2(son[u], t);
	for(auto &[v,w] : g[u]) if(v != fa[u] && v != son[u]) dfs2(v,v);
}

int main() {
	_rep(i,2,n) lg[i] = lg[i >> 1] + 1;
	_rep(i,2,n) {
		int u = in() + 1,v = in() + 1,w = in();
		g[u].push_back({v, w});
		g[v].push_back({u, w});
		e.push_back({u, v});
	}
	dfs1(1, 0); dfs2(1, 1);
	m = in();
	_rep(i,1,m) {
		char op[5]; int x,y;
		scanf("%s%d%d", op, &x, &y);
		if(op[0] == 'C') {
			auto &[u,v] = e[x - 1];
			if(dep[u] < dep[v]) swap(u,v); //u`s father is v
			modify(1, 1, n, dfn[u], y);
		} 
		if(op[0] == 'N') {
			++x, ++y;
			while(top[x] != top[y]) {
				if(dep[top[x]] < dep[top[y]]) swap(x,y);
				negetive(1, 1, n, dfn[top[x]], dfn[x]);
				x = fa[top[x]];
			}
			if(dep[x] < dep[y]) swap(x,y);
			negetive(1, 1, n, dfn[y] + 1, dfn[x]);
		}
		if(op[0] == 'S') {
			++x, ++y;
			int res = 0;
			while(top[x] != top[y]) {
				if(dep[top[x]] < dep[top[y]]) swap(x,y);
				res += query_sum(1, 1, n, dfn[top[x]], dfn[x]);
				x = fa[top[x]];
			}
			if(dep[x] < dep[y]) swap(x,y);
			res += query_sum(1, 1, n, dfn[y] + 1, dfn[x]);
			printf("%d\n", res);
		} 
		if(op[0] == 'M' && op[1] == 'A') {
			++x, ++y;
			int res = INT_MIN;
			while(top[x] != top[y]) {
				if(dep[top[x]] < dep[top[y]]) swap(x,y);
				res = max(res, query_max(1, 1, n, dfn[top[x]], dfn[x]));
				x = fa[top[x]];
			}
			if(dep[x] < dep[y]) swap(x,y);
			res = max(res, query_max(1, 1, n, dfn[y] + 1, dfn[x]));
			printf("%d\n", res);
		}
		if(op[0] == 'M' && op[1] == 'I') {
			++x, ++y;
			int res = INT_MAX;
			while(top[x] != top[y]) {
				if(dep[top[x]] < dep[top[y]]) swap(x,y);
				res = min(res, query_min(1, 1, n, dfn[top[x]], dfn[x]));
				x = fa[top[x]];
			}
			if(dep[x] < dep[y]) swap(x,y);
			res = min(res, query_min(1, 1, n, dfn[y] + 1, dfn[x]));
			printf("%d\n", res);
		}
	}
	return 0;
}
