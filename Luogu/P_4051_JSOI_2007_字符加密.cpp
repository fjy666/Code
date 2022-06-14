#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;

int in(void) { int x; scanf("%d", &x); return x; }
ll inl(void) { ll x; scanf("%lld", &x); return x; }
const int kN = 105000 << 1;
char s[kN];
int n, x[kN], c[kN], sa[kN], y[kN];

void suffixSort(void) {
	int m = 200;
	_rep(i,1,n) ++c[x[i] = s[i]];
	_rep(i,1,m) c[i] += c[i - 1];
	_rep(i,1,n) sa[c[x[i]]--] = i;
	for(int k = 1; k <= n; k <<= 1) {
		int num = 0;
		_rep(i,n - k + 1,n) y[++num] = i;
		_rep(i,1,n) if(sa[i] > k) y[++num] = sa[i] - k;

		_rep(i,1,m) c[i] = 0;
		_rep(i,1,n) ++c[x[i]];
		_rep(i,1,m) c[i] += c[i - 1];
		for(int i = n;i >= 1; --i) sa[c[x[y[i]]]--] = y[i], y[i] = 0;

		swap(x,y), num = x[sa[1]] = 1;
		_rep(i,2,n) x[sa[i]] = (y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k]) ? num : ++num;
		if(num == n) break;
		m = num;
	}
}

int main() { 
	scanf("%s", s + 1);
	n = strlen(s + 1);
	_rep(i,n + 1,2 * n) s[i] = s[i - n];
	n <<= 1;
	suffixSort();
	_rep(i,1,n) if(sa[i] <= n / 2) putchar(s[sa[i] + n / 2 - 1]);
	return 0;
}