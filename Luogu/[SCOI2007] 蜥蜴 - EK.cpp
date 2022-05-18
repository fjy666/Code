// -< fjy666 >-
//ALWAYS TO REMAMBER DELETE THE DEBUGGING STATEMENT
#include <bits/stdc++.h>
#define _rep(i_,a_,b_) for(int i_ = a_;i_ <= b_;++i_)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
using namespace std;

/*
This is the Edmonds-Karp Algorithm template.
It`s time complexity is O(nm^2),can deal with problems that satisfiyed with n <= 100
Good Luck:)
*/
const int kN = 114514;
struct edge {  
	int u,v;
	ll f,c;
};
vector<edge> e;
vector<int> g[kN];
void add_edge(int u,int v,ll f) {
//  	printf("add edge between vertex %d and %d,flow = %lld\n",u,v,f);
	e.push_back({u,v,f,0});
	g[u].push_back(e.size() - 1);
	e.push_back({v,u,0,0});
	g[v].push_back(e.size() - 1);
}
ll a[kN]; int pre[kN];
ll max_flow(int s,int t) {
	ll ans = 0;
	while(true) {
		memset(a,0,sizeof(a));	
		memset(pre,0,sizeof(pre));
		a[s] = LLONG_MAX;
		queue<int> q;
		q.push(s);
		while(!q.empty()) {
			int u = q.front(); q.pop();
			for(auto &id : g[u]) {
				edge p = e[id];
				if(!a[p.v] && p.f > p.c) {
					a[p.v] = min(a[u],p.f - p.c);
					pre[p.v] = id;
					q.push(p.v);
				}
			}
		}
		if(!a[t]) break;
		ans += a[t];
		for(int i = t; i != s; i = e[pre[i]].u) {
			e[pre[i]].c += a[t];
			e[pre[i] ^ 1].c -= a[t];
		}
//		puts("Augument completed.");
	}
	return ans;
} 

int r = in(),c = in(),d = in(),S = 0,T = 10000;
int encode_in(int x,int y) {
	if(x < 1 || x > r || y < 1 || y > c) return T;
	return (x - 1) * c + y;	
}
int encode_out(int x,int y) {
	return r * c + (x - 1) * c + y;
}

double dis(int x1,int y1,int x2,int y2) {
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int mp[25][25];
char buf[25]; 
int main() {
	_rep(i,1,r) _rep(j,1,c) {
		scanf("%1d",&mp[i][j]);
		add_edge(encode_in(i,j),encode_out(i,j),mp[i][j]);
		_rep(k,0,r + 1)
			_rep(l,0,c + 1)
				if((dis(i,j,k,l) <= d) && (k != i || l != j))
					add_edge(encode_out(i,j),encode_in(k,l),LLONG_MAX);
	}
	int cnt = 0;
	_rep(i,1,r) {
		scanf("%s",buf + 1);
		_rep(j,1,c) if(buf[j] == 'L') add_edge(S,encode_in(i,j),1),++cnt;
	}
	printf("%lld\n",cnt - max_flow(S,T));
	return 0;
}

