//author: fjy666
//created time: 2022-05-18 12:09:33
#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
const int kN = 500000 * 30;
int siz[kN], ch[kN][2], nc; 
int clone(int x) { return ++nc,siz[nc] = siz[x],ch[nc][0] = ch[x][0],ch[nc][1] = ch[x][1],nc; }
void insert(int &rt,int L,int R,int p) { rt = clone(rt);
	if(L == R) ++siz[rt];
	else {
		if(p <= mid) insert(ch[rt][0],L,mid,p);
		else insert(ch[rt][1],mid + 1,R,p);
		siz[rt] = siz[ch[rt][0]] + siz[ch[rt][1]];
	}
}
int rt[500500];
int query(int rtr,int rtl,int L,int R,int s) {
	if((siz[rtr] - siz[rtl]) * 2 <= s) return 0;
	if(L == R) return L;
	if((siz[ch[rtr][0]] - siz[ch[rtl][0]]) * 2 > s) return query(ch[rtr][0],ch[rtl][0],L,mid,s);
	else return query(ch[rtr][1],ch[rtl][1],mid + 1,R,s);
}
int main() {
	int n = in(),m = in();
	_rep(i,1,n) {
		rt[i] = rt[i - 1];
		insert(rt[i],1,n,in());
	}
	_rep(i,1,m) {
		int L = in(),R = in();
		printf("%d\n",query(rt[R],rt[L - 1],1,n,R - L + 1));
	}
	return 0;
}
