// -< fjy666 >-
//ALWAYS TO REMAMBER DELETE THE DEBUGGING STATEMENT
#include <bits/stdc++.h>
#define _rep(i_,a_,b_) for(int i_ = a_;i_ <= b_;++i_)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
using namespace std;
const int kN = 10000 * 50 + 114;
int tr[kN][26], ncnt, fail[kN], flg[kN], a[kN];
void insert(char *s,int fc) { int cur = 0;
	for(; *s; ++s) {
		if(!tr[cur][*s - 'a']) tr[cur][*s - 'a'] = ++ncnt;
		cur = tr[cur][*s - 'a'];
	}
	++flg[cur];
}
void build(void) {
	queue<int> q;
	_rep(i,'a','z') if(tr[0][i - 'a']) q.push(tr[0][i - 'a']),fail[tr[0][i - 'a']] = 0;
	while(!q.empty()) {
		int u = q.front(); q.pop();
		_rep(i,0,25) 
			if(tr[u][i]) fail[tr[u][i]] = tr[fail[u]][i],q.push(tr[u][i]);
			else tr[u][i] = tr[fail[u]][i];
	}
}
char buf[1145140];
int main() {
	int T = in();
	while(T--) {
		ncnt = 0;
		memset(a,0,sizeof(a));
		memset(tr,0,sizeof(tr));
		memset(fail,0,sizeof(fail));
		memset(flg,0,sizeof(flg)); 
		int n = in();
		_rep(i,1,n) {
			scanf("%s",buf);
			insert(buf,i); 
		}
		build();
		scanf("%s",buf);
		int nod = 0,res = 0;
		for(int i = 0; buf[i]; ++i) {
			nod = tr[nod][buf[i] - 'a'];
			int tmp = nod;
			while(tmp) res += flg[tmp],flg[tmp] = 0,tmp = fail[tmp];
		}
		_rep(i,1,n) if(a[i]) ++res;
		printf("%d\n",res);
	}
	return 0;
}	

