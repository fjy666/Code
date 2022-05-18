// created time : 2022-04-06 13:16:05
// writer : fjy
#include <bits/stdc++.h>
#define _rep(i_,a_,b_) for(int i_ = a_;i_ <= b_;++i_)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
using namespace std;
const int kN = 15,kL = 55,kQ = (1 << kN) * kN * kL;
int tr[kN * kL][26], fail[kN * kL], ncnt, tag[kN * kL];
void insert(char *s,int tg) {
	int cur = 0;
	for(int i = 0; s[i]; ++i) {
		if(!tr[cur][s[i] - 'A']) tr[cur][s[i] - 'A'] = ++ncnt;
		cur = tr[cur][s[i] - 'A'];
	}
	tag[cur] |= tg;
}
void build(void) {
	queue<int> q;
	_rep(i,0,25) if(tr[0][i]) q.push(tr[0][i]);
	while(!q.empty()) {
		int u = q.front(); q.pop();
		_rep(i,0,25)
			if(tr[u][i]) fail[tr[u][i]] = tr[fail[u]][i],tag[tr[u][i]] |= tag[fail[tr[u][i]]], q.push(tr[u][i]);
			else tr[u][i] = tr[fail[u]][i];
	}
}

char s[kN][kL];
int sta[kQ],nod[kQ],fro[kQ];
//vis[i][j] 表示 节点i 状态j 所经过的字母
char vis[kN * kL][1 << kN];

int main() {
	int n = in();
	_rep(i,1,n) {
		scanf("%s",s[i]);
		insert(s[i],1 << (i - 1));
	}
	build();
	int FULL = (1 << n) - 1;
	fro[0] = 0,sta[0] = 0,nod[0] = 0;
	vis[0][0] = '-';

	int l = 0,r = 0;
	
	while(l <= r) {
		if(sta[l] == FULL) {
			stack<char> ans;
			int cur = l;
			while(cur) {
				ans.push(vis[nod[cur]][sta[cur]]);
				cur = fro[cur];
			}
			while(!ans.empty()) putchar(ans.top()),ans.pop();
			puts("");
			return 0;
		}
		_rep(i,0,25) {
			int nws = tr[nod[l]][i],st = sta[l] | tag[nws];
			if(!vis[nws][st]) {
				vis[nws][st] = i + 'A';
				++r,fro[r] = l,sta[r] = st,nod[r] = nws;
			}
		}
		++l;
	}

	return 0;
}