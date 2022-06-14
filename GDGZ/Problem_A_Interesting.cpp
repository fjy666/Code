#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;

#define int long long
int in(void) { int x; scanf("%lld", &x); return x; }
ll inl(void) { ll x; scanf("%lld", &x); return x; }
const int kN = 1005000, p = 1000000007;
int ch[kN][26], fail[kN], len[kN], nc, cnt[kN], sum[kN], last , n;
char s[kN];
void build(void) { len[1] = -1, fail[0] = fail[1] = nc = 1; last = 0; }
int get_fail(int x, int i) { while(s[i - len[x] - 1] != s[i]) x = fail[x]; return x; }
void insert(int i) {
	int x = get_fail(last, i);
	if(!ch[x][s[i] - 'a']) {
		++nc, fail[nc] = ch[get_fail(fail[x], i)][s[i] - 'a'], 
		ch[x][s[i] - 'a'] = nc, len[nc] = len[x] + 2,
		cnt[nc] = cnt[fail[nc]] + 1, sum[nc] = (sum[fail[nc]] + len[nc]) % p;
	}
	last = ch[x][s[i] - 'a'];
}
void clear(void) {  
	memset(ch, 0, sizeof(ch));
	memset(fail, 0, sizeof(fail));
	memset(cnt, 0, sizeof(cnt));
	memset(len, 0, sizeof(len));
	memset(sum , 0, sizeof(sum));
	build();
}

int Sum[kN], Cnt[kN];
ll convert(ll x) {
	return (x % p + p) % p;
}
signed main() { 
	build();
	scanf("%s", s + 1);
	n = strlen(s + 1);
	_rep(i,1,n) insert(i), Cnt[i] = cnt[last], Sum[i] = sum[last];
	clear();
	reverse(s + 1, s + 1 + n);
	ll res = 0;
	_rep(i, 1, n - 1) {
		insert(i); 
		int j = n - i;
		int ca = Cnt[j], sa = convert(Sum[j] - Cnt[j]);
		int cb = cnt[last], sb = sum[last];
		res = 
		 ((ll) res +
			(ll) j * j % p * ca % p * cb % p -
			(ll) cb * sa % p * j % p +
			(ll) ca * sb % p * j % p -
			(ll) sa * sb % p
		 ) % p;
		res = convert(res);
	}
	printf("%lld\n", res);
	return 0;
}