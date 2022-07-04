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

char t[kN];
int main() { 
	scanf("%s", s + 1), n = strlen(s + 1);
	suffixSort();
	int m = in();
	while(m--) {
		scanf("%s", t);
		if(strncmp(t,s + sa[1],strlen(t)) < 0 || strncmp(t, s + sa[n],strlen(t)) > 0) puts("-1");
		else {
			int L = 1, R = n;
			while(L <= R) {
				int cmp = strncmp(t, s + sa[mid],strlen(t));
				// printf("sa[mid] = %d, cmp = %d\n", sa[mid], cmp);
				if(cmp == 0) {
					printf("%d ", sa[mid] - 1);
					goto endloop;
				}
				if(cmp < 0) R = mid - 1;
				else L = mid + 1;
			}
			printf("-1 ");
			endloop:;
		}
	}
	return 0;
}