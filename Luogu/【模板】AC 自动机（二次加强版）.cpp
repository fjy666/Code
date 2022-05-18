// -< fjy666 >-
//ALWAYS TO REMAMBER DELETE THE DEBUGGING STATEMENT
#include <bits/stdc++.h>
#define _rep(i_,a_,b_) for(int i_ = a_;i_ <= b_;++i_)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
using namespace std;
const int kN = 1000005;
int tr[kN][26], ncnt, val[kN], fail[kN], bel[kN], occur[kN], add[kN], ind[kN];
int insert(char *s,int id) {
	int cur = 0;
	for(int i = 0; s[i]; ++i) {
		if(!tr[cur][s[i] - 'a']) tr[cur][s[i] - 'a'] = ++ncnt;
		cur = tr[cur][s[i] - 'a'];
	}
	if(!val[cur]) val[cur] = id;
	return val[cur];
}
void build(void) {
	queue<int> q;
	_rep(i,0,25) if(tr[0][i]) q.push(tr[0][i]),fail[tr[0][i]] = 0;
	while(!q.empty()) {
		int u = q.front(); q.pop();
		_rep(i,0,25) 
			if(tr[u][i]) fail[tr[u][i]] = tr[fail[u]][i],q.push(tr[u][i]);
			else tr[u][i] = tr[fail[u]][i];
	}
}
void toposort(void) {
	queue<int> q;
	_rep(i,1,ncnt) ++ind[fail[i]];
	_rep(i,1,ncnt) if(ind[i] == 0) q.push(i);
	while(!q.empty()) {
		int u = q.front(); q.pop();
		if(u == 0) break;
		occur[val[u]] = add[u];
		--ind[fail[u]]; add[fail[u]] += add[u];
		if(!ind[fail[u]]) q.push(fail[u]);
	}
}
char s[kN],t[kN];
int main() {
	int n = in();
	_rep(i,1,n) {
		scanf("%s",s);
		bel[i] = insert(s,i);
	}
	build();
	scanf("%s",t);
	int cur = 0;
	for(int i = 0; t[i]; ++i) {
		cur = tr[cur][t[i] - 'a'];
		++add[cur];
	}
	toposort();
	_rep(i,1,n) printf("%d\n",occur[bel[i]]);
	return 0;
}
