#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;

int in(void) { int x; scanf("%d", &x); return x; }
ll inl(void) { ll x; scanf("%lld", &x); return x; }
const int kN = 2 * 500500;
char s[kN], t[kN];
int rev[kN];

int main() { 
	int n = in();
	scanf("%s", s + 1);
	t[0] = '$';
	_rep(i,1,n) t[2 * i - 1] = '@', t[2 * i] = s[i];
	t[2 * n + 1] = '@'; n = n * 2 + 1;
	int ans = 0;
	for(int i = 1, l = 0, r = 0; i <= n; ++i) {
		if(i <= r) rev[i] = min(r - i + 1, rev[2 * l - i]);
		while(t[i - rev[i]] == t[i + rev[i]]) {
			++rev[i];
			if((rev[i] - 1) % 4 == 0 && t[i] == '@' && rev[(i + (i - rev[i] + 1)) / 2] * 2 - 1 >= rev[i])
				ans = max(ans, rev[i] - 1);
		}
		if(i + rev[i] - 1 > r) l = i, r = i + rev[i] - 1;
	}
	printf("%d\n", ans);
	return 0;
}