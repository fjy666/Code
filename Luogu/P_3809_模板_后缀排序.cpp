#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;

int in(void) { int x; scanf("%d", &x); return x; }
ll inl(void) { ll x; scanf("%lld", &x); return x; }
const int kN = 1005000;
char s[kN];
int n;

int x[kN], y[kN], cnt[kN], sa[kN], rk[kN];	
void suffixSort(void) {
	int m = 200;
	_rep(i,1,n) ++cnt[x[i] = s[i]];
	_rep(i,1,m) cnt[i] += cnt[i - 1];
	for(int i = n; i >= 1; --i) sa[cnt[x[i]]--] = i;

	for(int k = 1; k <= n; k <<= 1) {
		int num = 0;
		_rep(i,n-k+1,n) y[++num] = i;
		_rep(i,1,n) if(sa[i] > k) y[++num] = sa[i] - k;
		
		memset(cnt, 0, sizeof(cnt));
		_rep(i,1,n) ++cnt[x[i]]; 
		_rep(i,1,m) cnt[i] += cnt[i - 1];
		for(int i = n;i >= 1; --i) sa[cnt[x[y[i]]]--] = y[i], y[i] = 0;
		
		swap(x, y);
		num = 1, x[sa[1]] = 1;
		_rep(i,2,n) 
			if(y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) x[sa[i]] = num;
			else x[sa[i]] = ++num;
		if(num == n) break;
		m = num;
	}

	_rep(i,1,n) printf("%d ", sa[i]);
}

int main() { 
	scanf("%s", s + 1);
	n = strlen(s + 1);
	suffixSort();
	return 0;
}