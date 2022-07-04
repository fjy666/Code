#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;

int in(void) { int x; scanf("%d", &x); return x; }
ll inl(void) { ll x; scanf("%lld", &x); return x; }
const int kN = 1006000;
char s[kN]; int sa[kN], x[kN], y[kN], c[kN], n;
void suffixSort(void) {
	int m = 257;
	_rep(i,1,m) c[i] = 0;
	_rep(i,1,n) ++c[x[i] = s[i]];
	_rep(i,1,m) c[i] += c[i - 1];
	_rep(i,1,n) sa[c[x[i]]--] = i;
	x[n + 1] = y[n + 1] = 0;
	for(int k = 1; k <= n; k <<= 1) {
		int num = 0;
		_rep(i,n - k + 1,n) y[++num] = i;
		_rep(i,1,n) if(sa[i] > k) y[++num] = sa[i] - k;
		_rep(i,1,m) c[i] = 0; _rep(i,1,n) ++c[x[i]]; _rep(i,1,m) c[i] += c[i - 1];
		for(int i = n;i;--i) sa[c[x[y[i]]]--] = y[i], y[i] = 0;
		swap(x,y); x[sa[1]] = num = 1;
		_rep(i,2,n) x[sa[i]] = (y[sa[i]] == y[sa[i-1]] && y[sa[i]+k] == y[sa[i-1]+k]) ? num : ++num;
		m = num; if(m == n) break;	
	}
} 
int rk[kN], h[kN];
void getHeight(void) {
	_rep(i,1,n) rk[sa[i]] = i;
	int k = 0;
	_rep(i,1,n) {
		if(k) --k;
		int j = sa[rk[i] - 1];
		while(j + k <= n && i + k <= n && s[j + k] == s[i + k]) ++k;
		h[rk[i]] = k;
	}
}

int stk[kN], top;
int gx[kN];
ll solve(void) { //return sum of LCP(suffix[i], suffix[j]) (i < j)
	suffixSort(), getHeight();
	ll tot1 = top = 0, tot = 0;
	_rep(j,2,n) {
		int cur = 1;
		while(top && h[stk[top]] >= h[j]) 
			tot -= (ll) gx[top] * h[stk[top]],
			cur += gx[top],
			--top;
		++top, stk[top] = j, gx[top] = cur, tot += (ll) h[j] * cur;
		tot1 += tot;
	}
	return tot1;
}
char t1[kN], t2[kN];
int main() { 
	scanf("%s%s", t1 + 1, t2 + 1);
	int m1 = strlen(t1 + 1), m2 = strlen(t2 + 1);
	memcpy(s + 1, t1 + 1,sizeof(char) * m1);
	n = m1;
	ll fs1 = solve();

	memcpy(s + 1, t2 + 1, sizeof(char) * m2);
	n = m2;
	ll fs2 = solve();

	memcpy(s + 1, t1 + 1, sizeof(char) * m1);
	s[m1 + 1] = '*';
	memcpy(s + m1 + 2, t2 + 1, sizeof(char) * m2);
	n = m1 + m2 + 1;
	ll fS = solve();
	printf("%lld\n", fS - fs1 - fs2);
	return 0;
}