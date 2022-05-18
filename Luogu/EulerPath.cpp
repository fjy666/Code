// -< fjy666 >-
//ALWAYS TO REMAMBER DELETE THE DEBUGGING STATEMENT
#include <bits/stdc++.h>
#define _rep(i_,a_,b_) for(int i_ = a_;i_ <= b_;++i_)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
using namespace std;
const int kN = 100005;
vector<int> g[kN];
stack<int> stk;
int nxt[kN];
void dfs(int x) {
	for(int i = nxt[x]; i < g[x].size(); i = nxt[x]) {
		nxt[x] = i + 1;
		dfs(g[x][i]);
	}
	stk.push(x);
}
int ind[kN],oud[kN];
int main() {
	int n = in(),m = in();
	_rep(i,1,m) {
		int u = in(),v = in();
		++oud[u],++ind[v];
		g[u].push_back(v);
	}
	int cnt_diffrence = 0,flag = true;
	_rep(i,1,n) {
		if(ind[i] != oud[i]) {
			if(abs(ind[i] - oud[i]) > 1) flag = false;
			++cnt_diffrence;
		}
	}
	if(!flag || cnt_diffrence > 2) {
		puts("No");
		return 0;
	}
	_rep(i,1,n) sort(g[i].begin(),g[i].end());
	int S = 1;
	_rep(i,1,n) if(oud[i] - ind[i] == 1) S = i;
	dfs(S);
	while(!stk.empty()) printf("%d ",stk.top()),stk.pop(); 
	return 0;
}

