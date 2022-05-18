#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
const int kN = 100500;
int val[kN],ch[kN][2],siz[kN],rp[kN],ncnt,rt;
void pushup(int x) { siz[x] = siz[ch[x][0]] + siz[ch[x][1]] + 1; }
void split(int rt,int v,int &x,int &y) {
	if(!rt) x = y = 0;
	else if(val[rt] <= v) x = rt,split(ch[rt][1],v,ch[x][1],y),pushup(rt);
	else y = rt,split(ch[rt][0],v,x,ch[y][0]),pushup(rt);
}
int merge(int x,int y) {
	if(x && y) {
		if(rp[x] > rp[y]) return ch[x][1] = merge(ch[x][1],y),pushup(x),x;
		else return ch[y][0] = merge(x,ch[y][0]),pushup(y),y;
	} else return x + y;
}
int new_node(int x) { return ++ncnt,val[ncnt] = x,siz[ncnt] = 1,rp[ncnt] = rand(),ncnt; }
void insert(int &rt,int v) { int x,y; split(rt,v,x,y); rt = merge(merge(x,new_node(v)),y); }
void remove(int &rt,int v) { 
	int x,y; split(rt,v,x,y); int z; split(x,v - 1,x,z); z = merge(ch[z][0],ch[z][1]); rt = merge(merge(x,z),y);
}
int kth(int &rt,int k) {
	if(siz[ch[rt][0]] + 1 == k) return val[rt];
	else if(siz[ch[rt][0]] >= k) return kth(ch[rt][0],k);
	else return kth(ch[rt][1],k - siz[ch[rt][0]] - 1);
}

int rk(int &rt,int k) {	int x,y,ans; split(rt,k - 1,x,y); return ans = siz[x] + 1,rt = merge(x,y),ans;}
int pre(int &rt,int k) { int x,y; split(rt,k - 1,x,y); int ans = kth(x,siz[x]); rt = merge(x,y); return ans; }
int nxt(int &rt,int k) { int x,y; split(rt,k,x,y); int ans = kth(y,1); rt = merge(x,y); return ans; }
int main() {
	int n = in();
	while(n--) {
		int opt = in(),x = in();
		if(opt == 1) insert(rt,x);
		else if(opt == 2) remove(rt,x);
		else if(opt == 3) printf("%d\n",rk(rt,x));
		else if(opt == 4) printf("%d\n",kth(rt,x));
		else if(opt == 5) printf("%d\n",pre(rt,x));
		else printf("%d\n",nxt(rt,x));
	}
	return 0;
}
