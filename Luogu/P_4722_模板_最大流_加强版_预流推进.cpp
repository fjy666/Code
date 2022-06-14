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
const int kN = 1205;
struct Edge { 
	int from, to, cap, flow; 
	Edge(int f, int t, int c, int fl) : from(f), to(t), cap(c), flow(fl) {}
};
vector<Edge> E; vector<int> g[kN];

void add_edge(int u, int v, int w) {
	E.emplace_back(u, v, w, 0);
	g[u].emplace_back(E.size() - 1);
	E.emplace_back(v, u, 0, 0);
	g[v].emplace_back(E.size() - 1); 
}
int n = in(), m = in(), S = in(), T = in();
int h[kN], e[kN]; //高度，流量

int bfs(void) {
	memset(h, 0x3f, sizeof(h));
	queue<int> q; q.push(T); h[T] = 0;
	while(!q.empty()) {
		int u = q.front(); q.pop();
		for(auto &id : g[u]) {
			Edge &cur = E[id];
			if(cur.cap == 0 && h[cur.to] > h[u] + 1) { //cap==0确保是反向边
				h[cur.to] = h[u] + 1; 
				q.push(cur.to);
			}
		}
	}
	return h[S] == 0x3f3f3f3f ? -1 : 1;
}
void relabel(int u) {
	h[u] = 0x3f3f3f3f;
	for(auto &id : g[u]) {
		Edge &cur = E[id]; 
		if(cur.cap > cur.flow) h[u] = min(h[u], h[cur.to] + 1);
	}
}
struct cmp {
	bool operator () (const int &a, const int &b) const {
		return h[a] < h[b];
	}
};
priority_queue<int, vector<int>, cmp> q;
bool inq[kN];
void push(int u) {
	for(auto &id : g[u]) {
		Edge &cur = E[id];
		if(h[cur.to] + 1 != h[u]) continue;
		int flow = min(cur.cap - cur.flow, e[u]);
		e[cur.to] += flow, e[u] -= flow, E[id].flow += flow, E[id ^ 1].flow -= flow;
		if(cur.to != S && cur.to != T && !inq[cur.to]) q.push(cur.to), inq[cur.to] = 1;
		if(e[u] == 0) break;
	}
}
int gap[kN];
int HLPP(void) {
	if(bfs() == -1) return -1; h[S] = n;
	_rep(i,1,n) if(h[i] != 0x3f3f3f3f) ++gap[h[i]];
	for(auto &id : g[S]) {
		Edge &cur = E[id];
		int f = cur.cap;
		cur.flow += f, E[id ^ 1].flow -= f, e[S] -= f, e[cur.to] += f;
		if(cur.to != T) q.push(cur.to), inq[cur.to] = 1; 
	}
	while(!q.empty()) {
		int u = q.top(); q.pop(); inq[u] = 0;
		push(u); if(e[u]) { //还有剩余流量
			if(!--gap[h[u]]) _rep(i,1,n) if(i != S && i != T && h[i] > h[u]) h[i] = n + 1;
			relabel(u); ++gap[h[u]];
			q.push(u), inq[u] = 1;		
		}
	} 
	return e[T];
}
int main() {
	_rep(i,1,m) {
		int a = in(), b = in(), c = in();
		add_edge(a, b, c);
	}
	printf("%d\n", HLPP());
	return 0;
}