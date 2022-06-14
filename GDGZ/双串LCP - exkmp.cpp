#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;

int in(void) { int x; scanf("%d", &x); return x; }
ll inl(void) { ll x; scanf("%lld", &x); return x; }
const int kN = 1005000;
char s[kN], t[kN];
int n,m;

int z[kN];
void Z_function(char *s,int n) {
	z[1] = n; for(int i = 2, l = 0, r = 0; i <= n; ++i) {
		if(i <= r) z[i] = min(z[i - l + 1], r - i + 1);
		while(i + z[i] <= n && s[z[i] + 1] == s[i + z[i]]) ++z[i];
		if(i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
	}
}
int ans[kN];
void exkmp(char *s, int n, char *t, int m) {
	Z_function(t, m); for(int i = 1, l = 0, r = 0; i <= n; ++i) {
		if(i <= r) ans[i] = min(z[i - l + 1], r - i + 1);
		while(i + ans[i] <= n && s[i + ans[i]] == t[ans[i] + 1]) ++ans[i];
		if(i + ans[i] - 1 > r) l = i, r = i + ans[i] - 1;
	}
}

int main() {
	scanf("%s%s", s + 1, t + 1);
	n = strlen(s + 1), m = strlen(t + 1);
	exkmp(s, n, t, m);
	int q = in();
	while(q--) {
		int st = in();
		printf("%d\n", ans[st]);
	}
	return 0;
}