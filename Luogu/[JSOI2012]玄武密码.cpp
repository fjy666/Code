// created time : 2022-04-05 14:48:39
// writer : fjy
#include <bits/stdc++.h>
#define _rep(i_,a_,b_) for(int i_ = a_;i_ <= b_;++i_)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
using namespace std;
const int kN = 15005005;
int tr[kN][4], ncnt, fail[kN], tag[kN];
int c2i(char x) {
	if(x == 'E') return 0;
	if(x == 'N') return 1;
	if(x == 'W') return 2;
	if(x == 'S') return 3;
	assert(false);
}
void insert(char *s) {
	int cur = 0;
	for(int i = 0; s[i]; ++i) {
		if(!tr[cur][c2i(s[i])]) tr[cur][c2i(s[i])] = ++ncnt;
		cur = tr[cur][c2i(s[i])];
	}
}
void build(void) {
	queue<int> q;
	_rep(i,0,3) if(tr[0][i]) q.push(tr[0][i]);
	while(!q.empty()) {
		int u = q.front(); q.pop();
		_rep(i,0,3)
			if(tr[u][i]) fail[tr[u][i]] = tr[fail[u]][i], q.push(tr[u][i]);
			else tr[u][i] = tr[fail[u]][i];
	}
}
char s[kN],t[100005][105];
int query(char *t) {
	int cur = 0,res = 0;
	for(int i = 0; t[i]; ++i) {
		cur = tr[cur][c2i(t[i])];
		if(tag[cur]) res = i + 1;
	}
	return res;
}
int main() {
	int n = in(),m = in();
	scanf("%s",s);
	_rep(i,1,m) {
		scanf("%s",t[i]);
		insert(t[i]);
	}
	build();
	int cur = 0;
	for(int i = 0; s[i]; ++i) {
		cur = tr[cur][c2i(s[i])];
		// printf("cur = %d\n",cur);
		int tmp = cur;
		while(tmp) {
			tag[tmp] = 1;
			tmp = fail[tmp];
		}
	}
	_rep(i,1,m)
		printf("%d\n",query(t[i]));
	return 0;
}