// created time : 2022-04-05 14:15:58
// writer : fjy
#include <bits/stdc++.h>
#define _rep(i_,a_,b_) for(int i_ = a_;i_ <= b_;++i_)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
using namespace std;
const int kN = 100005;
int tr[kN][26], ncnt, fail[kN], len[kN];
void insert(char *s) {
	int i = 0, cur = 0;
	for(; s[i]; ++i) {
		if(!tr[cur][s[i] - 'a']) tr[cur][s[i] - 'a'] = ++ncnt;
		cur = tr[cur][s[i] - 'a'];
	} 
	len[cur] = i;
}
void build(void) {
	queue<int> q;
	_rep(i,0,25) if(tr[0][i]) q.push(tr[0][i]);
	while(!q.empty()) {
		int u = q.front(); q.pop();
		_rep(i,0,25) {
			if(tr[u][i]) fail[tr[u][i]] = tr[fail[u]][i],q.push(tr[u][i]);
			else tr[u][i] = tr[fail[u]][i];
		}
	}
}
char s[kN],t[kN];
char stk[kN];
int top = 0,ccur[kN];
int main() {
	scanf("%s",t);
	int n = in();
	_rep(i,1,n) {
		scanf("%s",s);
		insert(s);
	}
	build();
	int cur = 0;
	for(int i = 0; t[i]; ++i) {
		cur = tr[cur][t[i] - 'a'];
		stk[++top] = t[i];
		ccur[top] = cur;

		if(len[cur]) {
			top -= len[cur];
			cur = ccur[top];
		}
	}
	stk[top + 1] = '\0';
	puts(stk + 1);
	return 0;
}