#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
// #define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;

int in(void) { int x; scanf("%d", &x); return x; }
ll inl(void) { ll x; scanf("%lld", &x); return x; }
const int kN = 3000000;
char s[kN], ts[kN];
int l[kN];

int main() { 
	scanf("%s",s + 1);
	int n = 0;
	ts[0] = '@'; for(char *p = s + 1; *p; ++p) ts[++n] = '|', ts[++n] = *p; ts[++n] = '|';
	for(int i = 1, mid = 0,r = 0; i <= n; ++i) {
		if(i <= r) l[i] = min(l[2 * mid - i], r - i + 1);
		while(ts[i - l[i]] == ts[i + l[i]]) ++l[i];
		if(i + l[i] - 1 > r) mid = i, r = i + l[i] - 1;
	}
	printf("%d\n", *max_element(l + 1, l + 1 + n) - 1);
	return 0;
}