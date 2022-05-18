#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
const int kN = 20000 * 30;

mt19937 generator(20100325);
int ch[kN][2],val[kN],siz[kN],rp[kN],ncnt;
void pushup(int x) { siz[x] = siz[ch[x][0]] + siz[ch[x][1]] + 1; }
void rotate(int &x,int d) {
	int tmp = ch[x][d ^ 1]; ch[x][d ^ 1] = ch[tmp][d]; ch[tmp][d] = x; pushup(x); pushup(tmp); x = tmp;
}
void insert(int &rt,int v) {
	if(!rt) rt = ++ncnt, val[rt] = v,siz[rt] = 1,rp[rt] = (int) generator();
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
int rnk(int &rt,int v) {
	if(!rt) return 0;
	else if(v > val[rt]) return siz[ch[rt][0]] + 1 + rnk(ch[rt][1],v);
	else return rnk(ch[rt][0],v);
}
int yukai(int &rt,int v) {
	if(!rt) return 0;
	else if(v >= val[rt]) return siz[ch[rt][0]] + 1 + yukai(ch[rt][1],v);
	else return yukai(ch[rt][0],v);
}

// Treap part ends
int a[kN];

#define mid ((L+R) >> 1)
int rt[kN];
void build(int x,int L,int R) {
	_rep(i,L,R) insert(rt[x],a[i]);
	if(L == R) return; build(x << 1,L,mid); build(x << 1 | 1,mid + 1,R);	
}
void modify(int x,int L,int R,int pos,int delta) {
	remove(rt[x], a[pos]); insert(rt[x], delta);
	if(L == R) return; if(pos <= mid) modify(x << 1,L,mid,pos,delta); else modify(x << 1 | 1,mid + 1,R,pos,delta);
}
//查询[l,r]中有多少个数比v小
int query(int x,int L,int R,int l,int r,int v) { if(l > r) return 0; 
	if(l <= L && R <= r) return rnk(rt[x],v); int ans = 0;
	if(l <= mid) ans += query(x << 1,L,mid,l,r,v); if(mid < r) ans += query(x << 1 | 1,mid + 1,R,l,r,v); return ans;
}
//查询[l,r]中有多少个数 <= x
int query1(int x,int L,int R,int l,int r,int v) { if(l > r) return 0; 
	if(l <= L && R <= r) return yukai(rt[x],v); int ans = 0;
	if(l <= mid) ans += query1(x << 1,L,mid,l,r,v);if(mid < r) ans += query1(x << 1 | 1,mid + 1,R,l,r,v); return ans;
}

//Seg part ends

int c[kN],d[kN]; 
void add(int x,int d) { for(;x < kN; x += x & -x) c[x] += d; }
int qry(int x) { int a = 0; for(;x;x -= x & -x) a += c[x]; return a; }

int main() {
	int n = in();
	_rep(i,1,n) a[i] = in(),d[i] = a[i];
	sort(d + 1,d + 1 + n);
	build(1,1,n);
	int init = 0;
	_rep(i,1,n) a[i] = lower_bound(d + 1,d + 1 + n,a[i]) - d;
	_rep(i,1,n) init += i - 1 - qry(a[i]), add(a[i],1);
	_rep(i,1,n) a[i] = d[a[i]];
	printf("%d\n", init);
	
	int m = in();
	_rep(i,1,m) {
		int j = in(),k = in(); //swap(a[j],a[k])
		if(j > k) swap(j,k);
		if(a[j] < a[k]) init++;
		if(a[j] > a[k]) init--;
		
		init -= query(1,1,n,j + 1,k - 1,a[j]);
		init += query(1,1,n,j + 1,k - 1,a[k]);
		init -= (k - 1 - (j + 1) + 1) - query1(1,1,n,j + 1,k - 1,a[k]);
		init += (k - 1 - (j + 1) + 1) - query1(1,1,n,j + 1,k - 1,a[j]);
		
		int aj = a[j],ak = a[k];
		modify(1,1,n,j,ak); modify(1,1,n,k,aj);
		swap(a[j],a[k]);
		printf("%d\n",init);
	}
	return 0;
}
