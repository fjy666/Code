#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
const int kN = 500500 * 50;
mt19937 engine(20100325);
int val[kN],ch[kN][2],siz[kN],rp[kN],nc,rt[kN];
void pushup(int x) { siz[x] = siz[ch[x][0]] + siz[ch[x][1]] + 1; }
int new_node(int x) { ++nc,siz[nc] = 1,rp[nc] = engine(),val[nc] = x,ch[nc][0] = ch[nc][1] = 0; return nc; }
int clone(int x) { ++nc,val[nc] = val[x],siz[nc] = siz[x],ch[nc][0] = ch[x][0],ch[nc][1] = ch[x][1],rp[nc] = rp[x]; return nc; }
void split(int rt,int v,int &x,int &y) {
	if(!rt) x = y = 0;
	else {
		if(val[rt] <= v) { x = clone(rt); split(ch[x][1],v,ch[x][1],y); pushup(x);}
		else { y = clone(rt); split(ch[y][0],v,x,ch[y][0]); pushup(y); }
	}
}
int merge(int x,int y) {
	if(!x || !y) return x + y;
	if(rp[x] > rp[y]) {	x = clone(x); ch[x][1] = merge(ch[x][1],y); pushup(x); return x; }
	else { y = clone(y); ch[y][0] = merge(x,ch[y][0]); pushup(y); return y; }
}
int kth(int rt,int k) {
	if(siz[ch[rt][0]] >= k) return kth(ch[rt][0],k);
	else if(siz[ch[rt][0]] + 1 == k) return val[rt];
	else return kth(ch[rt][1],k - siz[ch[rt][0]] - 1);
}

int main() {
	int n = in();
	_rep(i,1,n) {
		int v = in(),opt = in(),a = in();
		rt[i] = rt[v];
		if(opt == 1) { int x,y; split(rt[i],a,x,y); rt[i] = merge(merge(x,new_node(a)),y);  }
		else if(opt == 2) { int x,y,z; split(rt[i],a,x,z); split(x,a - 1,x,y); y = merge(ch[y][0],ch[y][1]);
			rt[i] = merge(merge(x,y),z);
		} else if(opt == 3) {
			int x,y; split(rt[i],a - 1,x,y);
			printf("%d\n",siz[x] + 1);
			rt[i] = merge(x,y);
		} else if(opt == 4) printf("%d\n",kth(rt[i],a));
		else if(opt == 5) {
			int x,y; split(rt[i],a - 1,x,y); printf("%d\n",x ? kth(x,siz[x]) : -2147483647); rt[i] = merge(x,y); 
		} else {
			int x,y; split(rt[i],a,x,y); printf("%d\n",y ? kth(y,1) : 2147483647); rt[i] = merge(x,y); 
		}
	}
	return 0;
}
