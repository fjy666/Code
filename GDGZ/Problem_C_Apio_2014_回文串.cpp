#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;

int in(void) { int x; scanf("%d", &x); return x; }
ll inl(void) { ll x; scanf("%lld", &x); return x; }
const int kN = 300500;
char s[kN];
int ch[kN][26], fail[kN], len[kN], nc, last, cnt[kN];
void build(void) { nc = 1, fail[0] = fail[1] = 1, len[1] = -1; }
int get_fail(int x, int i) { while(s[i - len[x] - 1] != s[i]) x = fail[x]; return x; }
void insert(int i) {
	int x = get_fail(last, i);
	if(!ch[x][s[i] - 'a']) 
		++nc, len[nc] = len[x] + 2, fail[nc] = ch[get_fail(fail[x], i)][s[i] - 'a'], ch[x][s[i] - 'a'] = nc;
	last = ch[x][s[i] - 'a'];
	++cnt[last];
}
int main() { 
	build();
	scanf("%s", s + 1);
	int n = strlen(s + 1);
	_rep(i, 1, n) insert(i);
	int ans = 0;
	for(int i = nc; i > 1; --i) ans = max(ans, cnt[i] * len[i]), cnt[fail[i]] += cnt[i];
	printf("%d\n", ans);
	return 0;
}