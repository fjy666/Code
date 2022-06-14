#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;

int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }

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
	int S = 0,T = kN - 1;
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

int main() {
	return 0;
}