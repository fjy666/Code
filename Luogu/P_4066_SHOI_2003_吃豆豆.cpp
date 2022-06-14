#include <bits/stdc++.h>
using namespace std;
#define _USE_FAST_IO
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
#define debug(variable, excepted) \
	if(variable != excepted) \
		printf("[Line %d] The expression %s should be %d, but now it is %d\n", __LINE__, #variable, excepted, variable);
#define muticase for(int curCase = 1, casecnt = in(); curCase <= casecnt; ++curCase)
#define in_range(i, j, k) (j <= i && i <= k)
typedef long long ll;

#ifdef _USE_FAST_IO
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
#else 
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
#endif
namespace MCMF{
	const int kN = 105000;
	struct Edge { int from, to, cap, flow, unit; };
	vector<Edge> E; vector<int> g[kN];
	void add_flow(int u, int v, int cap, int cost) {
		E.push_back({u, v, cap, 0, cost});
		g[u].push_back(E.size() - 1);
		E.push_back({v, u, 0, 0, -cost});
		g[v].push_back(E.size() - 1);
	}
	int S,T;
	pair<int,int> SPFA(void) {
		static int d[kN], inq[kN], pre[kN];
		memset(d, 0x3f, sizeof(d));
		memset(inq, 0, sizeof(inq));
		memset(pre, 0, sizeof(pre));
		queue<int> q;
		q.push(S), d[S] = 0, inq[S] = 1;
		while(!q.empty()) {
			int u = q.front(); q.pop(); inq[u] = 0;
			for(auto &id : g[u]) { Edge &e = E[id];
				if(e.cap > e.flow && d[e.to] > d[u] + e.unit) {
					d[e.to] = d[u] + e.unit;
					pre[e.to] = id;
					if(!inq[e.to]) {
						inq[e.to] = 1;
						q.push(e.to);
					}
				}
			}
		}
		if(d[T] == 0x3f3f3f3f) return {-1, -1};
		int flow = INT_MAX, tmp = T;
		while(tmp != S) {
			flow = min(flow, E[pre[tmp]].cap - E[pre[tmp]].flow);
			tmp = E[pre[tmp]].from;
		}
		tmp = T; 
		while(tmp != S) {
			E[pre[tmp]].flow += flow;
			E[pre[tmp] ^ 1].flow -= flow;
			tmp = E[pre[tmp]].from;
		}
		return {flow, flow * d[T]};
	}
	pair<int,int> minCostMaxFlow(void) {
		pair<int,int> tmp, ans = {0,0};
		while((tmp = SPFA()) != pair<int,int> {-1, -1}) ans.first += tmp.first, ans.second += tmp.second;
		return ans;
	}
} using namespace MCMF;
struct Point {
	int x,y;
	bool operator < (const Point &rhs) const {
		return x != rhs.x ? x < rhs.x : y < rhs.y;
	}
} a[kN];
#define IN(x) (x)
#define OUT(x) (x + n)

int main() {
	int n = in();
	_rep(i,1,n) a[i].x = in(), a[i].y = in();
	sort(a + 1, a + 1 + n);
	int S1 = kN - 3, S2 = kN - 2; T = kN - 1;
	add_flow(S1, S2, 2, 0);
	S = S1;
	_rep(i,1,n) {
		add_flow(S2, IN(i), INT_MAX, 0);
		add_flow(IN(i), OUT(i), INT_MAX, 0); 
		add_flow(IN(i), OUT(i), 1, -1);
		add_flow(OUT(i), T, INT_MAX, 0);
	}
	_rep(i,1,n) {
		int j;
		for(j = i + 1; j <= n; ++j)  if(a[j].y >= a[i].y) break;
		if(j > n) continue;
		add_flow(OUT(i), IN(j), INT_MAX, 0);
		_rep(k, j + 1, n) if(a[k].y < a[j].y && a[k].y >= a[i].y) {
			add_flow(OUT(i), IN(k), INT_MAX, 0);
			j = k;
		}  
	}
	printf("%d\n", -minCostMaxFlow().second);
	return 0;
}