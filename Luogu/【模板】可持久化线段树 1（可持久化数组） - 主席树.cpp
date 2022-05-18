#include <bits/stdc++.h>
using namespace std;
#define mid ((L+R) >> 1)
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
const int kN = 1005000;
int ch[kN * 24][2], val[kN * 24];
int rt[kN],ncnt,a[kN];

void build(int &rt,int L,int R) {
	rt = ++ncnt, ch[rt][0] = ch[rt][1] = 0;
	if(L == R) val[rt] = a[L];
	else build(ch[rt][0],L,mid),build(ch[rt][1],mid + 1,R);
}
int query(int &rt,int L,int R,int pos) {
	if(L == R) return val[rt];
	if(pos <= mid) return query(ch[rt][0],L,mid,pos); else return query(ch[rt][1],mid + 1,R,pos);
}
int clone(int rt) {
	++ncnt; ch[ncnt][0] = ch[rt][0], ch[ncnt][1] = ch[rt][1], val[ncnt] = val[rt];
	return ncnt;
}
void modify(int &rt,int L,int R,int pos,int d) {
	rt = clone(rt);
	if(L == R) val[rt] = d;
	else {
		if(pos <= mid) modify(ch[rt][0],L,mid,pos,d);
		else modify(ch[rt][1],mid + 1,R,pos,d);
	}
}

int main() {
	int n = in(),m = in();
	_rep(i,1,n) a[i] = in();
	build(rt[0],1,n);
	_rep(i,1,m) {
		int v = in(); rt[i] = rt[v];
		int opt = in(),loc = in();
		if(opt == 1) modify(rt[i],1,n,loc,in());
		else printf("%d\n",query(rt[i],1,n,loc));
	}
	return 0;
}
