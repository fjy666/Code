#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
const int kN = 100500;
#define get(x) ((x - 1) / 400 + 1)
int n = in(),m = in();
struct query {
	int l,r,id;
	bool operator < (const query &x) const {
		return get(l) == get(x.l) ? (get(l) & 1 ? r < x.r : r > x.r) : get(l) < get(x.l);
	}
} q[kN];

int a[kN],pre[kN],nxt[kN],st[18][kN],lg[kN];
ll ans[kN],f[kN],g[kN],res;
int getmin(int l,int r) {
	int k = lg[r - l + 1];
	if(a[st[k][l]] < a[st[k][r - (1 << k) + 1]]) return st[k][l];
	else return st[k][r - (1 << k) + 1];
}
void add_l(int l,int r,int w) {
	int pos = getmin(l,r); 
	res += a[pos] * (r - pos + 1) * w;
	res += (g[l] - g[pos]) * w;
}
void add_r(int l,int r,int w) {
	int pos = getmin(l,r); 
	res += a[pos] * (pos - l + 1) * w;
	res += (f[r] - f[pos]) * w;
}

int main() {
//	_rep(i,2,n) lg[i] = lg[i >> 1] + 1;
	_rep(i,1,n) a[i] = in(),st[0][i] = i;
//	_rep(i,1,17) for(int j = 1; j + (1 << i) - 1 <= n; ++j) 
//		if(a[st[i - 1][j]] < a[st[i - 1][j + (1 << (i - 1))]]) st[i][j] = st[i - 1][j];
//	else st[i][j] = st[i - 1][j + (1 << (i - 1))];
//	_rep(i,1,m) {
//		int l = in(),r = in();
//		q[i] = {l,r,i};
//	}
	a[0] = INT_MIN; _rep(i,1,n) {
		pre[i] = i - 1;
		while(a[pre[i]] >= a[i]) pre[i] = pre[pre[i]];
	}
	_rep(i,1,n) f[i] = f[pre[i]] + (ll)(i - pre[i]) * a[i];
	
	a[n + 1] = INT_MIN; for(int i = n; i; --i) {
		nxt[i] = i + 1;
		while(a[nxt[i]] >= a[i]) nxt[i] = nxt[nxt[i]];
	}
	for(int i = n;i; --i) g[i] = g[nxt[i]] + (ll)(nxt[i] - i) * a[i];
	
//	sort(q + 1,q + 1 + m);
//	int l = 1,r = 0;
//	_rep(i,1,m) {
//		while(l > q[i].l) add_l(--l,r,1);
//		while(r < q[i].r) add_r(l,++r,1);
//		while(l < q[i].l) add_l(l++,r,-1);
//		while(r > q[i].r) add_r(l,r++,-1);
//		ans[q[i].id] = res;
//	}
//	
//	_rep(i,1,m) printf("%lld\n",ans[i]);
	return 0; 
}
