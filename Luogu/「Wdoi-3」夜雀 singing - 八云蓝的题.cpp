#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
const int kN = 5005000;
int n = in(),m = in(),t = in();
//n棵树，m只鸟
int h[kN];
struct bird{
	int p,l,r;
	bool flag;
}a[kN];
int L[kN],R[kN];
int main() {
	_rep(i,1,n) h[i] = in();
	_rep(i,1,m) a[i].p = in();
	sort(a + 1,a + 1 + m,[](const bird &a,const bird &b)->bool{ return a.p < b.p; });
	a[m + 1].l = a[m].p + 1;
	for(int i = m;i;--i) {
		a[i].l = min(a[i + 1].l,a[i].p + 1);
		while(a[i].l > 1 && (a[i].p - (a[i].l - 1)) < h[a[i].l - 1]) --a[i].l;
	}
	sort(a + 1,a + 1 + m,[](const bird &a,const bird &b)->bool{ return a.p > b.p; });
	a[m + 1].r = a[m].r - 1;
	for(int i = m;i;--i) {
		a[i].r = max(a[i + 1].r,a[i].p - 1);
		while(a[i].r < n && ((a[i].r + 1) - a[i].p) < h[a[i].r + 1]) ++a[i].r;
	}
	_rep(i,1,m) a[i].l = max(a[i].l,a[i].p - t),a[i].r = min(a[i].r,a[i].p + t);
	L[0] = INT_MIN;     
	_rep(i,1,n) if(h[i] > t) L[i] = i; else L[i] = L[i - 1];
	R[n + 1] = INT_MAX;
	for(int i = n;i;--i) if(h[i] > t) R[i] = i; else R[i] = R[i + 1];
	_rep(i,1,m) a[i].flag = (a[i].l <= L[a[i].p]) || (R[a[i].p] <= a[i].r);
	sort(a + 1,a + 1 + m,[](const bird &a,const bird &b)->bool{ return a.flag != b.flag ? a.flag < b.flag : a.r < b.r; });
	if(a[1].flag == 1) {
		puts("0");
		return 0;
	}
	a[m + 1].flag = 1;
	int res = 0;
	for(int i = 1;!a[i].flag; ) {
		++res;
		int j = i + 1;
		while(!a[j].flag && a[j].l <= a[i].r) ++j;
		i = j;
	}
	printf("%d\n",res + 1);
	return 0;
}
