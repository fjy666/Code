//created time: 2022-05-29 12:30:39
//基环树上直径
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
int v[kN], w[kN], n = in(), on_ring[kN];
vector<pair<int,ll> > g[kN];
ll res = 0, dep[kN];

int mx_d;
void dp(int u,int f) {
	for(auto &[v,w] : g[u]) if(!on_ring[v] && v != f) {
		dep[v] = dep[u] + w;
		dp(v,u);
	}
	if(dep[u] > dep[mx_d]) mx_d = u;
}

ll d2[kN]; int mx_d2,rt;
void dfs(int u,int f) {
	for(auto &[v,w] : g[u]) if(v != f && (v == rt || !on_ring[v])) {
		d2[v] = d2[u] + w;
		dfs(v,u);
	}
	if(d2[u] > d2[mx_d2]) mx_d2 = u;
}

ll f1[kN], f2[kN];
void calc(int x,int id) { 
	static int vis[kN], fro[kN];
	while(true) {
		if(vis[x] != 0 && vis[x] != id) return;
		if(vis[x] == id) break;
		vis[x] = id;
		fro[v[x]] = x;
		x = v[x];
	}
	int ox = x; vector<int> ring;
	do ring.push_back(x), on_ring[x] = 1, x = fro[x]; while(x != ox);
	
	ll ans = 0;
	vector<ll> d;
	for(auto &ele : ring) {
		mx_d = 0;
		dp(ele,0); d.push_back(dep[mx_d]);
		rt = ele, mx_d2 = 0; dfs(mx_d,0);
		ans = max(ans, d2[mx_d2]);
	}
	//复制二倍
	int RING_LEN = ring.size(); ring.resize(2 * RING_LEN);
	for(int i = RING_LEN; i < 2 *RING_LEN; ++i) ring[i] = ring[i - RING_LEN];
	d.resize(2 * RING_LEN); for(int i = RING_LEN; i <2 * RING_LEN; ++i) d[i] = d[i - RING_LEN];
	vector<ll> f1; f1.resize(ring.size());
	for(int i = 1;i < ring.size();++i) {
		ll dis = -1;
		for(auto &[v,w] : g[ring[i - 1]]) if(v == ring[i]) { dis = max(dis,w); }
		if(dis == -1) {
			puts("fucking error appeared");
			abort();
		}
		f1[i] = f1[i - 1] + dis;
	}
#define get_dis(i,j) (f1[j] - f1[i])
	deque<int> q;
	for(int i = 0;i < ring.size();++i) {
		while(!q.empty() && q.front() <= i - RING_LEN) q.pop_front();
		if(!q.empty()) ans = max(ans, d[q.front()] + d[i] + get_dis(q.front(),i));
		while(!q.empty() && d[q.back()] + get_dis(q.back(),i) <= d[i]) q.pop_back();
		q.push_back(i);
	}
	res += ans;
}

int main() {
	_rep(i,1,n) v[i] = in(), w[i] = in(), g[v[i]].push_back({i,w[i]}), g[i].push_back({v[i], w[i]});
	_rep(i,1,n) calc(i,i);
	printf("%lld\n",res);
	return 0;
}
