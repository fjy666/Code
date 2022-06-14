#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;

int in(void) { int x; scanf("%d", &x); return x; }
ll inl(void) { ll x; scanf("%lld", &x); return x; }
const int kN = 20005; 
int s[kN], x[kN], y[kN], sa[kN], c[kN], n = in(), k = in();

void suffixSort(void) {
	int m = n;
	_rep(i,1,n) ++c[x[i] = s[i]]; _rep(i,1,m) c[i] += c[i - 1];
	_rep(i,1,n) sa[c[x[i]]--] = i;
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


int main() { 
	_rep(i,1,n) s[i] = in();
	suffixSort(), getHeight();
	int res = 0;
	deque<int> q; --k;
	_rep(i,2,n) {
		while(!q.empty() && q.front() <= i - k) q.pop_front();
		while(!q.empty() && h[q.back()] >= h[i]) q.pop_back();
		q.push_back(i);
		if(i > k) res = max(res, h[q.front()]);
	}	
	printf("%d\n", res);
	return 0;
}