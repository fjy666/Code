#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
const int kN = 10050;
vector<int> g[kN];
int color[kN],inq[kN];
bool check(int x) { int cnt = 0;
	for(auto &v : g[x]) if(color[v] == color[x]) ++cnt;
	return cnt <= 1;
}
int main(void) {
	int n = in(),m = in();
	_rep(i,1,m) {
		int a = in(),b = in();
		g[a].push_back(b);
		g[b].push_back(a);
	}
	_rep(i,1,n) color[i] = rand() % 3;
	queue<int> q;
	_rep(i,1,n) if(!check(i)) q.push(i),inq[i] = 1;
	while(!q.empty()) {
		int u = q.front(); q.pop(); inq[u] = 0; if(check(u)) continue;
		int c[3] = {0,0,0};
		for(auto &v : g[u]) ++c[color[v]];
		if(c[0] == *min_element(c,c + 3)) color[u] = 0;
		else if(c[1] == *min_element(c,c + 3)) color[u] = 1;
		else color[u] = 2;
		for(auto &v : g[u]) if(!check(v) && !inq[v])
			q.push(v),inq[v] = 1;
	}
	_rep(i,1,n) putchar("CSP"[color[i]]);
	return 0;
}
