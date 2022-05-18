// created time : 2022-04-06 15:56:50
// writer : fjy
#include <bits/stdc++.h>
#define _rep(i_,a_,b_) for(int i_ = a_;i_ <= b_;++i_)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
using namespace std;
const int kN = 30005;
char s[kN];
int tr[kN][2], fail[kN], ncnt, tag[kN];
void insert(char *s) {
	int cur = 0;
	for(int i = 0; s[i]; ++i) {
		if(!tr[cur][s[i] - '0']) tr[cur][s[i] - '0'] = ++ncnt;
		cur = tr[cur][s[i] - '0'];
	}
	tag[cur] = 1;
}
void build(void) {
	queue<int> q;
	_rep(i,0,1) if(tr[0][i]) q.push(tr[0][i]);
	while(!q.empty()) {
		int u = q.front(); q.pop();
		_rep(i,0,1) 
			if(tr[u][i]) fail[tr[u][i]] = tr[fail[u]][i], tag[tr[u][i]] |= tag[fail[tr[u][i]]], q.push(tr[u][i]);
			else tr[u][i] = tr[fail[u]][i];
	} 
}
int in_stk[kN],dfsed[kN];
bool dfs(int x) {
	if(tag[x]) return false;
	if(in_stk[x]) return true;
	if(dfsed[x]) return false;
	dfsed[x] = 1;
	in_stk[x] = 1;
	if(dfs(tr[x][0]) || dfs(tr[x][1])) return true;
	in_stk[x] = 0;
	return false;
}
int main() {
	int n = in();
	_rep(i,1,n) {
		scanf("%s",s);
		insert(s);
	}
	build();
	puts(dfs(0) ? "TAK" : "NIE");
	return 0;
}