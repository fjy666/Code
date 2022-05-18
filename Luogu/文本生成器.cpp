// created time : 2022-04-05 15:52:32
// writer : fjy
#include <bits/stdc++.h>
#define _rep(i_,a_,b_) for(int i_ = a_;i_ <= b_;++i_)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
using namespace std;
const int p = 10007,kN = 10050;
int tr[kN][26], ncnt, fail[kN], tag[kN], f[105][kN];
void insert(char *s) {
	int cur = 0;
	for(int i = 0; s[i]; ++i) {
		if(!tr[cur][s[i] - 'A']) tr[cur][s[i] - 'A'] = ++ncnt;
		cur = tr[cur][s[i] - 'A'];
	}
	tag[cur] = 1;
}
void build(void) {
	queue<int> q;
	_rep(i,0,25) if(tr[0][i]) q.push(tr[0][i]);
	while(!q.empty()) {
		int u = q.front(); q.pop();
		_rep(i,0,25) 
			if(tr[u][i]) fail[tr[u][i]] = tr[fail[u]][i], tag[tr[u][i]] |= tag[fail[tr[u][i]]], 
						 q.push(tr[u][i]);
			else tr[u][i] = tr[fail[u]][i];
	}
}

int n = in(), m = in();
void dp(void) {
	f[0][0] = 1;
	_rep(cnt,0,m - 1)
		_rep(i,0,ncnt)
			_rep(j,0,25)
				if(!tag[tr[i][j]])
					f[cnt + 1][tr[i][j]] = (f[cnt + 1][tr[i][j]] + f[cnt][i]) % p;
}

char s[65][150];
int main() {
	_rep(i,1,n) {
		scanf("%s",s[i]);
		insert(s[i]);
	}
	build();
	dp();
	int ans = 0;
	_rep(i,0,ncnt) ans = (ans + f[m][i]) % p;
	int ans1 = 1;
	_rep(i,1,m) ans1 = (ans1 * 26) % p;
	printf("%d\n",(ans1 - ans + p) % p);
	return 0;
}