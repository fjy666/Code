#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L + R) >> 1)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
const int kN = 300500;
int siz[kN * 30],ch[kN * 30][2],nc,rt[kN];
int clone(int x) { return ++nc,siz[nc] = siz[x],ch[nc][0] = ch[x][0],ch[nc][1] = ch[x][1],nc; }
void pushup(int x) { siz[x] = siz[ch[x][0]] + siz[ch[x][1]]; }
void insert(int &rt,int L,int R,int v) { rt = clone(rt);
	if(L == R) { ++siz[rt]; return; }
	if(v <= mid) insert(ch[rt][0],L,mid,v); else insert(ch[rt][1],mid + 1,R,v);
	pushup(rt);
}
int query(int qwq,int qaq,int L,int R,int k) {
	if(L == R) return L;
	if(siz[ch[qwq][0]] - siz[ch[qaq][0]] >= k) return query(ch[qwq][0],ch[qaq][0],L,mid,k);
	else return query(ch[qwq][1],ch[qaq][1],mid + 1,R,k - (siz[ch[qwq][0]] - siz[ch[qaq][0]]));
}
int a[kN],d[kN];
int main() {
	int n = in(),m = in();
	_rep(i,1,n) d[i] = a[i] = in();
	sort(d + 1,d + 1 + n);
	_rep(i,1,n) a[i] = lower_bound(d + 1,d + 1 + n,a[i]) - d;
	
	_rep(i,1,n) {
		rt[i] = rt[i - 1];
		insert(rt[i],1,n,a[i]);
	}
	_rep(i,1,m) {
		int l = in(),r = in(),k = in();
		printf("%d\n",d[query(rt[r],rt[l - 1],1,n,k)]);
	}
	return 0;
}
