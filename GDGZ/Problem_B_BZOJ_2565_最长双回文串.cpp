#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;

int in(void) { int x; scanf("%d", &x); return x; }
ll inl(void) { ll x; scanf("%lld", &x); return x; }
const int kN = 100500;
char s[kN], t[kN<<1];
int rev[kN<<1],lft[kN<<1],rgt[kN<<1];
int main() { 
	scanf("%s", s + 1);
	int n = strlen(s + 1);

	_rep(i,1,n) t[i*2-1] = '|', t[i*2] = s[i];
	t[n*2+1] = '|'; t[0] = '@';
	// printf("t = %s\n", t + 1);

	for(int i = 1, l = 0, r = 0; i <= 2 * n + 1; ++i) {
		if(i <= r) rev[i] = min(r - i + 1, rev[l * 2 - i]);
		while(t[i - rev[i]] == t[i + rev[i]]) ++rev[i];
		if(i + rev[i] - 1 > r) l = i, r = i + rev[i] - 1;
		lft[i - rev[i] + 1] = max(lft[i - rev[i] + 1], rev[i] - 1);
		rgt[i + rev[i] - 1] = max(rgt[i + rev[i] - 1], rev[i] - 1);
		// printf("i = %d, lft[3] = %d\n", i, lft[3]);
	}

	for(int i = 3; i <= 2 * n + 1; i += 2) lft[i] = max(lft[i], lft[i - 2] - 2);
	for(int i = 2 * n - 1; i > 0; i -= 2) rgt[i] = max(rgt[i], rgt[i + 2] - 2);
	int ans = 0;
	for(int i = 3;i < 2 * n + 1; i += 2) if(lft[i] && rgt[i]) {
		// printf("i = %d, lft = %d, rgt = %d\n", i, lft[i], rgt[i]);
		ans = max(ans, lft[i] + rgt[i]);
	}
	printf("%d\n", ans);
	return 0;
}