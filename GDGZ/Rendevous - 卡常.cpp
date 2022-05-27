#include <bits/stdc++.h>
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;
using std::pair; using std::swap; using std::max; using std::min; using std::vector;

char inBuff[1 << 23],*in1=inBuff,*in2=inBuff;
#define getChar() (in1==in2&&(in2=(in1=inBuff)+fread(inBuff,1,1<<23,stdin),in1==in2)?EOF:*in1++)
int in(void){
	int x(0),c(getChar()),f(0);
	while(c<'0'||c>'9'){if(c == '-')f = 1;c = getChar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c = getChar();}
	return f?-x:x;
}
char outBuff[1 << 23],*p = outBuff;
void out(int x) {
	if(x > 9) out(x / 10);
	*p++ = x%10 + '0';
}
//int in(void) {
//	char c = getchar(); int x = 0;
//	while(!isdigit(c)) c = getchar();
//	while(isdigit(c)) x = x * 10 + c - '0',c = getchar();
//	return x;
//}
//int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
const int kN = 500500;
int a[kN],n = in(),q = in();
int siz[kN],dis[kN],ring_cnt,bel[kN],root[kN];
vector<int> G[kN];
inline void get_ring(int x,int id) {
	static int vis[kN], fro[kN];
	while(true) {
		if(vis[x] != id && vis[x]) return;
		if(vis[x] == id) break;
		vis[x] = id,fro[a[x]] = x,x = a[x];
	}
	++ring_cnt;
	int en = x;
	do {
		siz[ring_cnt]++,dis[x] = siz[ring_cnt],bel[x] = ring_cnt,x = fro[x];
	} while(x != en);
}
int _rt,fa[20][kN],dep[kN];
void dfs(int x,int f) {
	root[x] = _rt; dep[x] = dep[f] + 1; fa[0][x] = f;
	for(int i = 1;i <= 19; ++i) fa[i][x] = fa[i - 1][fa[i - 1][x]];
	for(auto &v : G[x]) if(!bel[v]) dfs(v,x);
}
int lg[kN];
inline int LCA(int u,int v) {
	while(dep[u] != dep[v]) {
		if(dep[u] < dep[v]) swap(u,v);
		u = fa[lg[dep[u] - dep[v]]][u];
	}
	if(u == v) return u;
	for(int i = 19;~i;--i) if(fa[i][u] != fa[i][v]) u = fa[i][u],v = fa[i][v];
	return fa[0][u];
}
inline pair<int,int> better(pair<int,int> a,pair<int,int> b) {
	int Ma = max(a.first,a.second), Mb = max(b.first,b.second);
	if(Ma != Mb) return Ma < Mb ? a : b;
	Ma = min(a.first,a.second); Mb = min(b.first,b.second);
	if(Ma != Mb) return Ma < Mb ? a : b;
	return a.first > b.first ? a : b;
}
int main() {
	_rep(i,1,n) a[i] = in(),G[a[i]].push_back(i);
	_rep(i,2,n) lg[i] = lg[i >> 1] + 1;
	_rep(i,1,n) get_ring(i,i);
	_rep(i,1,n) if(bel[i]) _rt = i, dfs(i,i);
	_rep(i,1,q) {
		int a = in(),b = in();
		if(bel[root[a]] != bel[root[b]]) {
			*p++='-'; *p++='1'; *p++=' '; *p++='-'; *p++='1'; *p++='\n';
			continue;
		}
		if(root[a] == root[b]) {
			int _lca = LCA(a,b);
			out(dep[a] - dep[_lca]); *p++=' '; out(dep[b] - dep[_lca]); *p++='\n';
		} else {
			int ra = root[a], rb = root[b];
			int d1 = (dis[rb] - dis[ra] + siz[bel[ra]]) % siz[bel[ra]], d2 = (dis[ra] - dis[rb] + siz[bel[ra]]) % siz[bel[ra]];
			pair<int,int> a1 = {dep[a], dep[b] + d1},a2 = {dep[a] + d2,dep[b]};
			pair<int,int> ans = better(a1,a2);
			out(ans.first - 1); *p++=' '; out(ans.second - 1); *p++='\n';
		}
	}
	fwrite(outBuff,p - outBuff,1,stdout);
	return 0;
}
