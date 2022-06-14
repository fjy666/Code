#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
#define muticase() for(int curCase = 1, casecnt = in(); curCase <= casecnt; ++curCase)
typedef long long ll;

int in(void) { int x; scanf("%d", &x); return x; }
ll inl(void) { ll x; scanf("%lld", &x); return x; }
char gc(void) { char c = getchar(); while(!isgraph(c)) c = getchar(); return c; }
const int kN = 2500000<<1;
char s[kN], t[kN];
int rev[kN],can[kN];

int main() { 
	muticase() {
		memset(rev, 0, sizeof(rev));
		memset(can, 0, sizeof(can));
		scanf("%s", s + 1); int n = strlen(s + 1);
		_rep(i,1,n) t[2 * i - 1] = '|', t[2 * i] = s[i]; t[2 * n + 1] = '|', t[2 * n + 2] = '#' t[0] = '@';
		for(int i = 1, l = 0, r = 0; i <= 2 * n + 1; ++i) {
			if(i <= r) rev[i] = min(r - i + 1, rev[2 * l - i]);
			while(t[i + rev[i]] == t[i - rev[i]]) ++rev[i];
			if(i + rev[i] - 1 > r) l = i, r = i + rev[i] - 1;
		}

		for(int i = n; i; --i) {
			int Half = (rev[i * 2] - 2) / 2; 
			if(i + Half == n || (i - Half == 1 && can[i + Half])) 
				can[i] = 1;
		}
		_rep(i,1,n) if(can[i]) printf("%d ", i); puts("");
	}
	return 0;
}