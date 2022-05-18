#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
const int kN = 300500 * 50;
mt19937 eng(20100325);
int val[kN],ch[kN][2],siz[kN],nc,rp[kN];
void pushup(int x) { siz[x] = siz[ch[x][0]] + siz[ch[x][1]] + 1; }
int new_node(int x) { return ++nc,val[nc] = x,siz[nc] = 1,rp[nc] = eng(),nc; }
int clone(int x) { return ++nc,val[nc] = val[x],ch[nc][0] = ch[x][0],ch[nc][1] = ch[x][1],rp[nc] = rp[x],siz[nc] = siz[x],nc; }
void split(int rt,int k,int &x,int &y) {
	if(!rt) x = y = 0;
	else {
		if(siz[ch[rt][0]] < k) x = clone(rt),split(ch[x][1],k - siz[ch[x][0]] - 1,ch[x][1],y),pushup(x);
		else y = clone(rt),split(ch[y][0],k,x,ch[y][0]),pushup(y);
	}
} 
int merge(int x,int y) {
	if(!x || !y) return x + y;
	if(rp[x] > rp[y]) return (x = clone(x),ch[x][1] = merge(ch[x][1],y),pushup(x),x);
	else return (y = clone(y),ch[y][0] = merge(x,ch[y][0]),pushup(y),y);
}
void insert(int &rt,int pos,int k) {
	int x,y; split(rt,pos - 1,x,y);
	rt = merge(merge(x,new_node(k)),y);
}
void remove(int &rt,int pos) {
//	if(siz[rt] < pos - 1) 
//		cerr << "Error 2 appeared\n";
	int x,y,z; split(rt,pos,x,z);
//	if(siz[x] != pos) 
//		cerr << "Error 3 appeared\n";
	split(x,pos - 1,x,y);
//	if(siz[y] != 1) 
//		cerr << "Error 1 appeared\n";
	rt = merge(x,z);
}
int kth(int &rt,int p) {
	if(siz[ch[rt][0]] + 1 == p) return val[rt];
	else if(siz[ch[rt][0]] >= p) return kth(ch[rt][0],p);
	else return kth(ch[rt][1],p - siz[ch[rt][0]] - 1);
}
void flatten(int rt) {
	if(!rt) return;
	flatten(ch[rt][0]),printf("%d ",val[rt]),flatten(ch[rt][1]);
}
int rt[kN];
int main() {
	int n = in();
	int tot = 0;
	_rep(i,1,n) {
		int opt = in(),t = in(),k = in();
		if(opt != 3) rt[++tot] = rt[t];
		if(opt == 1) insert(rt[tot],k,in());
		else if(opt == 2) remove(rt[tot],k);
		else printf("%d\n",kth(rt[t],k)); //这不产生新版本
	}
	return 0;
}
