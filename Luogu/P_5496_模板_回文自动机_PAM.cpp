#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;

int in(void) { int x; scanf("%d", &x); return x; }
ll inl(void) { ll x; scanf("%lld", &x); return x; }
const int kN = 505000;
int ch[kN][26], cnt[kN], fail[kN], nc, len[kN], last;
char s[kN];
void build(void) { fail[1] = 1, fail[0] = 1, len[1]	= -1, nc = 1; }
int get_fail(int x, int i) { 
	while(s[i - len[x] - 1] != s[i]) {
		x = fail[x];
	}
	return x;
}
void insert(int i) {
	int x = get_fail(last, i);
	if(!ch[x][s[i] - 'a']) 
		++nc, len[nc] = len[x] + 2, fail[nc] = ch[get_fail(fail[x], i)][s[i] - 'a'], 
		cnt[nc] = cnt[fail[nc]] + 1, ch[x][s[i] - 'a'] = nc;
	last = ch[x][s[i] - 'a'];
}

int main() { 
	build();
	scanf("%s", s + 1);
	int n = strlen(s + 1), lastans;
	_rep(i,1,n) {
		if(i >= 2) s[i] = (s[i] + lastans - 97) % 26 + 97;
		insert(i);
		printf("%d ", lastans = cnt[last]);
	}
	return 0;
}