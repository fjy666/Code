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
ll in(void) { ll x; scanf("%lld",&x); return x; }
#endif
const int kN = 20055;

struct Edge { int from, to, cap, flow, unit; };
vector<Edge> E; vector<int> g[kN];
void add_flow(int u, int v, int cap, int cost) {
	E.push_back({u, v, cap, 0, cost});
	g[u].push_back(E.size() - 1);
	E.push_back({v, u, 0, 0, -cost});
	g[v].push_back(E.size() - 1);
}
char s[6][kN];
#define get_id(row, col) ((row - 1) * n + col)
#define IN(row, col) get_id(row, col)
#define OUT(row, col) (get_id(row, col) + 5 * n)
#define get_cost(row, col) (isdigit(s[row][col]) ? (s[row][col] - '0') : 0)
const int d[][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}};
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

int main() {
	int n;
	while(~scanf("%d", &n)) {
		_rep(i,1,5) scanf("%s", s[i] + 1);
		_rep(i,1,5) _rep(j,1,n) g[IN(i,j)].clear(), g[OUT(i,j)].clear(); 
		_rep(i,1,5) _rep(j,1,n) _rep(k,0,3) {
			int di = i + d[k][0], dj = j + d[k][1];
			if(in_range(di, 1, 5) && in_range(dj, 1, n))
				add_flow(OUT(i, j), IN(di, dj), 5, 0);
		}
		_rep(i,1,5) _rep(j,1,n) add_flow(IN(i, j), OUT(i, j), 1, get_cost(i, j));
		S = 0, T = 10 * n + 1;
		g[S].clear(), g[T].clear();
		_rep(i,1,5) _rep(j,1,n) if(s[i][j] == '@') add_flow(S, IN(i, j), 1, 0);
		_rep(i,1,5) add_flow(OUT(i, n), T, 5, 0);
		// puts("Add Edge Complete."); fflush(stdout);
		printf("%d\n", minCostMaxFlow().second);
	}
	return 0;
}