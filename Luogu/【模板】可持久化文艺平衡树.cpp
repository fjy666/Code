#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
typedef long long ll;
#define int long long
//int in(void) { int x; scanf("%d",&x); return x; }
ll in(void) { ll x; scanf("%lld",&x); return x; }
const int kN = 200500 * 100;
int val[kN],ch[kN][2],tag[kN],siz[kN],rp[kN],nc,sum[kN];
mt19937 eng(223);
int new_node(int x) { return ++nc,val[nc] = x,rp[nc] = eng(),siz[nc] = 1,nc; }
int clone(int x) { return ++nc,val[nc] = val[x],siz[nc] = siz[x],rp[nc] = rp[x],ch[nc][0] = ch[x][0]
							  ,ch[nc][1] = ch[x][1],tag[nc] = tag[x],sum[nc] = sum[x],nc; }
void pushup(int x) {
	sum[x] = val[x] + sum[ch[x][0]] + sum[ch[x][1]];
	siz[x] = siz[ch[x][0]] + siz[ch[x][1]] + 1;
}
void pushdown(int x) {
	if(tag[x]) {
		if(ch[x][0]) ch[x][0] = clone(ch[x][0]),tag[ch[x][0]] ^= 1;
		if(ch[x][1]) ch[x][1] = clone(ch[x][1]),tag[ch[x][1]] ^= 1;
		swap(ch[x][0],ch[x][1]);
		tag[x] = 0;
	}
}
//split by size
void split(int rt,int k,int &x,int &y) {
	if(!rt) x = y = 0;
	else { pushdown(rt);
		if(siz[ch[rt][0]] < k) x = clone(rt),split(ch[x][1],k - siz[ch[x][0]] - 1,ch[x][1],y),pushup(x);
		else y = clone(rt),split(ch[y][0],k,x,ch[y][0]),pushup(y);
	}
}
int merge(int x,int y) { 
	if(!x || !y) return x + y;
	if(rp[x] > rp[y]) return x = clone(x),pushdown(x),ch[x][1] = merge(ch[x][1],y),pushup(x),x;
	else return y = clone(y),pushdown(y),ch[y][0] = merge(x,ch[y][0]),pushup(y),y;
}

int rt[kN];

//void flatten(int x) {
//	if(!x) return; pushdown(x);
//	flatten(ch[x][0]),printf("%d ",val[x]),flatten(ch[x][1]);
//}

signed main() {
	int n = in(),lastans = 0;
	_rep(i,1,n) {
		int v = in(),opt = in(),l = in() ^ lastans;
//		printf("Real l: %d\n",l);
		rt[i] = rt[v];
		if(opt == 1) {
			int r = in() ^ lastans;
//			printf("Real r: %d\n",r);
			int x,y; split(rt[i],l,x,y);
			rt[i] = merge(merge(x,new_node(r)),y);
		} else if(opt == 2) {
			int x,y,z; split(rt[i],l,x,z);
			split(x,l - 1,x,y);
			rt[i] = merge(x,z);
		} else if(opt == 3) { int r = in() ^ lastans;
//			printf("Real r: %d\n",r);
			int x,y,z; split(rt[i],r,x,z);
			split(x,l - 1,x,y); //y is the goal
			tag[y] ^= 1;
			rt[i] = merge(merge(x,y),z);
		} else { int r = in() ^ lastans;
//			printf("Real r: %d\n",r);
			int x,y,z; split(rt[i],r,x,z);
			split(x,l - 1,x,y); //y is the goal
			printf("%lld\n",lastans = sum[y]);
			rt[i] = merge(merge(x,y),z);
		}
//		printf("版本 %d:[",i);
//		flatten(rt[i]);
//		printf("]\n");
	}
	return 0;
}
