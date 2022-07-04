//Code by fjy666
//luogu-judger-enable-O2
#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
#define multiCase() int testCnt = in(); _rep(curCase,1,testCnt)
typedef long long ll;

int in(void) { int x; scanf("%d", &x); return x; }
ll inl(void) { ll x; scanf("%lld", &x); return x; }
template<typename T> void chkmax(T &a, const T &b) { a = max(a, b); } 
template<typename T> void chkmin(T &a, const T &b) { a = min(a, b); } 
const int kN = 2005, p = 1000000007;
char s[kN][kN];
int n = in(), f[kN][kN][2], pw[kN * kN];

int main() { 
	_rep(i,1,n) scanf("%s", s[i] + 1);
	int cnt = 0;
	_rep(i,1,n) _rep(j,1,n) cnt += s[i][j] == '.';
	pw[0] = 1; _rep(i,1,n*n) pw[i] = pw[i - 1] * 2 % p;
	f[0][0][1] = f[0][0][0] = pw[cnt];
	_rep(i,0,n) _rep(j,0,n) if(i || j) {
		if(i) {
			f[i][j][0] = (f[i][j][0] + f[i - 1][j][0]) % p;
			if(s[i][j] == '.') f[i][j][0] = (f[i][j][0] + (ll) f[i - 1][j][1] * 500000004 % p) % p; 
 		} 
		if(j) {
			f[i][j][1] = (f[i][j][1] + f[i][j - 1][1]) % p;
			if(s[i][j] == '.') f[i][j][1] = (f[i][j][1] + (ll) f[i][j - 1][0] * 500000004 % p) % p;
		}
		// printf("     Going (%d,%d) from left: %d, from up: %d\n", i, j, f[i][j][1], f[i][j][0]);
	}
	printf("%d\n", (f[n][n][0] + f[n][n][1]) % p);
	return 0;
}

/* 
a list of keywords
clear empty push_back pop_back push pop top front back
emplace_back emplace push_front pop_front insert erase
find count set reset bitset map vector string multiset
first second iterator prev next deque multimap reverse
sort begin end list modify query init check calc prime 
*/