#include <bits/stdc++.h>
using namespace std;
#undef INT_MIN
#define INT_MIN -2147483647
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
typedef long long ll;
//mt19937 generator(19491001);
//int in(void) { int x; scanf("%d",&x); return x; }
int in(void) {
	int x = 0,f = 1; char c = getchar();
	while(!isdigit(c)) { if(c == '-') f = -1; c = getchar(); }
	while(isdigit(c)) { x = x * 10 + c - '0'; c = getchar(); }
	return x * f;
}
ll inl(void) { ll x; scanf("%lld",&x); return x; }
const int kN = 2000000; //空间 n log n
int ch[kN][2],val[kN],siz[kN],rp[kN],ncnt;
int n = in(),m = in();
inline void pushup(int x) { siz[x] = siz[ch[x][0]] + siz[ch[x][1]] + 1; }
void rotate(int &x,int d) {
	int tmp = ch[x][d ^ 1]; ch[x][d ^ 1] = ch[tmp][d]; ch[tmp][d] = x; pushup(x); pushup(tmp); x = tmp;
}
void insert(int &rt,int v) {
	if(!rt) rt = ++ncnt,val[rt] = v,siz[rt] = 1,ch[rt][0] = ch[rt][1] = 0,rp[rt] = rand();
	else {
		int d = v > val[rt];
		insert(ch[rt][d],v);
		if(rp[ch[rt][d]] < rp[rt]) rotate(rt,d ^ 1);
		pushup(rt);
	}	
}
void remove(int &rt,int v) {
	if(val[rt] == v) {
		if(ch[rt][0] && ch[rt][1]) {
			int d = rp[ch[rt][0]] < rp[ch[rt][1]] ? 1 : 0;
			rotate(rt,d); remove(ch[rt][d],v);
		} else rt = ch[rt][0] + ch[rt][1];
	} else remove(ch[rt][v > val[rt]],v);
	if(rt) pushup(rt);
}
int pre(int &rt,int v) {
	if(!rt) return INT_MIN;
	if(val[rt] < v) return max(val[rt],pre(ch[rt][1],v));
	return pre(ch[rt][0],v);
}
int nxt(int &rt,int v) {
	if(!rt) return INT_MAX;
	if(val[rt] > v) return min(val[rt],nxt(ch[rt][0],v));
	return nxt(ch[rt][1],v);
}
int rnk(int &rt,int v) {
	if(!rt) return 0;
	if(v <= val[rt]) return rnk(ch[rt][0],v);
	return rnk(ch[rt][1],v) + siz[ch[rt][0]] + 1;
}

int rt[kN],a[kN];

#define mid ((L+R) >> 1)
void build(int x,int L,int R) {
	_rep(i,L,R) insert(rt[x],a[i]);
	if(L == R) return;
	build(x << 1,L,mid); build(x << 1 | 1,mid + 1,R);
} 
void modify(int x,int L,int R,int pos,int k) {
	remove(rt[x], a[pos]); insert(rt[x], k);
	if(L == R) return;
	if(pos <= mid) modify(x << 1,L,mid,pos,k); else modify(x << 1 | 1,mid + 1,R,pos,k);
}
int query_pre(int x,int L,int R,int l,int r,int v) {
	if(l <= L && R <= r) return pre(rt[x],v);
	int ans = INT_MIN;
	if(l <= mid) ans = max(query_pre(x << 1,L,mid,l,r,v),ans);
	if(mid < r) ans = max(query_pre(x << 1 | 1,mid + 1,R,l,r,v),ans);
	return ans;
} 
int query_nxt(int x,int L,int R,int l,int r,int v) {
	if(l <= L && R <= r) return nxt(rt[x],v);
	int ans = INT_MAX;
	if(l <= mid) ans = min(query_nxt(x << 1,L,mid,l,r,v),ans);
	if(mid < r) ans = min(query_nxt(x << 1 | 1,mid + 1,R,l,r,v),ans);
	return ans;
}
int query_rnk(int x,int L,int R,int l,int r,int v) {
	if(l <= L && R <= r) return rnk(rt[x],v);
	int ans = 0;
	if(l <= mid) ans += query_rnk(x << 1,L,mid,l,r,v);
	if(mid < r) ans += query_rnk(x << 1 | 1,mid + 1,R,l,r,v);
	return ans;
}
int query_kth(int L,int R,int v) {
	int l = 0,r = 100000000,ans = -1;
	while(l <= r) {
		int m = (l + r) >> 1,rkm = query_rnk(1,1,n,L,R,m) + 1;
		if(rkm <= v) ans = m, l = m + 1;
		else r = m - 1;
	}
	return ans;
}
int main() {
	_rep(i,1,n) a[i] = in();
	build(1,1,n);
	_rep(i,1,m) {
		int opt = in(),l = in(),r = in();
		if(opt == 1) printf("%d\n",query_rnk(1,1,n,l,r,in()) + 1);
		if(opt == 2) printf("%d\n",query_kth(l,r,in()));
		if(opt == 3) modify(1,1,n,l,r),a[l] = r;
		if(opt == 4) printf("%d\n",query_pre(1,1,n,l,r,in()));
		if(opt == 5) printf("%d\n",query_nxt(1,1,n,l,r,in()));
	}
	return 0;
}
