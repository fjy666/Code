#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
const int kN = 100500;
int val[kN * 500],ch[kN * 500][2],nc,siz[kN * 500];
void pushup(int x) { siz[x] = siz[ch[x][0]] + siz[ch[x][1]]; } 
void insert(int &rt,int L,int R,int v) { if(!rt) rt = ++nc;
	if(L == R) { ++siz[rt]; return; }
	if(v <= mid) insert(ch[rt][0],L,mid,v); else insert(ch[rt][1],mid + 1,R,v);
	pushup(rt);
}
void remove(int &rt,int L,int R,int v) {
	if(L == R) { --siz[rt]; return; }
	if(v <= mid) remove(ch[rt][0],L,mid,v); else remove(ch[rt][1],mid + 1,R,v);
	pushup(rt);
}
int rt[kN],a[kN],d[kN * 2];
struct Query {
	char op;
	int x,y,z;
} q[kN];
int rt1[kN],rt2[kN];
int query(int L,int R,int k) { if(L == R) return L; 
	int lsiz = 0;
	_rep(i,1,rt1[0]) lsiz -= siz[ch[rt1[i]][0]]; _rep(i,1,rt2[0]) lsiz += siz[ch[rt2[i]][0]];
	if(lsiz >= k) {
		_rep(i,1,rt1[0]) rt1[i] = ch[rt1[i]][0]; _rep(i,1,rt2[0]) rt2[i] = ch[rt2[i]][0];
		return query(L,mid,k);
	} else {
		_rep(i,1,rt1[0]) rt1[i] = ch[rt1[i]][1]; _rep(i,1,rt2[0]) rt2[i] = ch[rt2[i]][1];
		return query(mid + 1,R,k - lsiz);
	}
}
int main() {
	int n = in(),m = in(),top = 0;
	_rep(i,1,n) a[i] = in(),d[++top] = a[i];
	_rep(i,1,m) {
		char o[5]; int x,y; scanf("%s%d%d",o,&x,&y);
		q[i].op = o[0],q[i].x = x,q[i].y = y;
		if(q[i].op == 'Q') q[i].z = in();
		else d[++top] = q[i].y;
	}
	sort(d + 1,d + 1 + top);
	_rep(i,1,n) a[i] = lower_bound(d + 1,d + 1 + top,a[i]) - d;
	_rep(i,1,n) _rep(j,i - (i & -i) + 1,i) insert(rt[i],1,top,a[j]);
	//建树
	_rep(i,1,m) {
		if(q[i].op == 'Q') {
			//query [q[i].x,q[i].y]`s q[i].z th
			rt1[0] = rt2[0] = 0;
			int tmp = q[i].x - 1;
			for(;tmp;tmp -= tmp & -tmp) rt1[++rt1[0]] = rt[tmp];
			tmp = q[i].y;
			for(;tmp;tmp -= tmp & -tmp) rt2[++rt2[0]] = rt[tmp];
			printf("%d\n",d[query(1,top,q[i].z)]);
		} else {
			int tmp = q[i].x; q[i].y = lower_bound(d + 1,d + 1 + top,q[i].y) - d;
			for(;tmp <= n;tmp += tmp & -tmp) 
				remove(rt[tmp],1,top,a[q[i].x]),insert(rt[tmp],1,top,q[i].y);
			a[q[i].x] = q[i].y;
		}
	}
	return 0;
}
