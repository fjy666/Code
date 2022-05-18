#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
const int kN = 100500,kM = kN * 30;
int ch[kM][2],siz[kM],fa[kM],ncnt;
int clone(int rt) { 
	++ncnt; ch[ncnt][0] = ch[rt][0]; ch[ncnt][1] = ch[rt][1]; fa[ncnt] = fa[rt]; siz[ncnt] = siz[rt];
	return ncnt;
}
void update_s(int &rt,int L,int R,int pos,int s) {
	rt = clone(rt);
	if(L == R) siz[rt] = s;
	else {
		if(pos <= mid) update_s(ch[rt][0],L,mid,pos,s);
		else update_s(ch[rt][1],mid + 1,R,pos,s);
	}
}
void update_f(int &rt,int L,int R,int pos,int s) {
	rt = clone(rt);
	if(L == R) fa[rt] = s;
	else {
		if(pos <= mid) update_f(ch[rt][0],L,mid,pos,s);
		else update_f(ch[rt][1],mid + 1,R,pos,s);
	}
}
int query_f(int rt,int L,int R,int pos) {
	if(L == R) return fa[rt];
	if(pos <= mid) return query_f(ch[rt][0],L,mid,pos);
	else return query_f(ch[rt][1],mid + 1,R,pos);
}
int query_s(int rt,int L,int R,int pos) {
	if(L == R) return siz[rt];
	if(pos <= mid) return query_s(ch[rt][0],L,mid,pos);
	else return query_s(ch[rt][1],mid + 1,R,pos);
}
void build(int &rt,int L,int R) { rt = ++ncnt;
	if(L == R) siz[rt] = 1,fa[rt] = L;
	else build(ch[rt][0],L,mid),build(ch[rt][1],mid + 1,R);
}
int rt[kN << 1];
int n = in(),m = in(),i;

int find(int a) { int tmp;
	if((tmp = query_f(rt[i],1,n,a)) == a) return a;
	return find(tmp);
}

int main() {
	build(rt[0],1,n);
	for(::i = 1; ::i <= m; ++::i) {
		int opt = in(),a = in();
		if(opt == 2) {
			rt[i] = rt[a];
			continue;
		}
		rt[i] = rt[i - 1];
		int b = in(),fa = find(a), fb = find(b);
		if(opt == 3) {
			puts(fa == fb ? "1" : "0");
			continue;
		}
		int sfa = query_s(rt[i],1,n,fa), sfb = query_s(rt[i],1,n,fb);
		if(sfa > sfb) swap(sfa,sfb), swap(fa,fb);
		//merge fa into fb
		update_s(rt[i],1,n,fb,sfb + sfa);
		update_f(rt[i],1,n,fa,fb);
	}
	return 0;
}
