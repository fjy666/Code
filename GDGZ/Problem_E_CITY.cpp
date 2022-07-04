//Code by fjy666
//luogu-judger-enable-O2
#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
#define multiCase() int testCnt = in(); _rep(curCase,1,testCnt)
typedef long long ll;

int in(void) { int x; scanf("%lld", &x); return x; }
ll inl(void) { ll x; scanf("%lld", &x); return x; }
template<typename T> void chkmax(T &a, const T &b) { a = max(a, b); } 
template<typename T> void chkmin(T &a, const T &b) { a = min(a, b); } 
const int kN = 1000500, p = 299989, kM = 17;
int n, m, mp[kM][kM], now, tot[2], ei, ej;
int head[p], nxt[kN], a[2][kN];
ll f[2][kN]; 

void insert(int sta, ll dp) {
	int hsh = sta % p;
	for(int i = head[hsh]; i; i = nxt[i]) 
		if(a[now][i] == sta) { f[now][i] += dp; return; }
	nxt[++tot[now]] = head[hsh], head[hsh] = tot[now];
	a[now][tot[now]] = sta, f[now][tot[now]] = dp;
}
#define bit(i) (1 << (2 * (i - 1)))
#define shift(i) (2 * (i - 1))
bool valid(int s) {
	int c = 0;
	_rep(i,1,m + 1) {
		if(((s >> shift(i)) & 3) == 1) ++c;
		if(((s >> shift(i)) & 3) == 2) --c;
		if(c < 0) return false;
	}
	return c == 0;
}
void calc(void) {
	tot[now] = 1, a[now][1] = 0, f[now][1] = 1;
	ll ans = 0;
	_rep(i,1,n) {
		_rep(j,1,tot[now]) a[now][j] <<= 2;
		_rep(j,1,m) {
			int last = now; now ^= 1;
			memset(head, 0, sizeof(head)), tot[now] = 0;
			_rep(k,1,tot[last]) {
				int st = a[last][k], b1 = (st >> shift(j)) & 3, b2 = (st >> shift(j + 1)) & 3;
				ll cnt = f[last][k];

				if(!valid(st)) continue;
				if((mp[i][j] == 2 || mp[i][j] == 0) && b2) continue;
				if((mp[i][j] == 3 || mp[i][j] == 0) && b1) continue;

				if(!mp[i][j]) { if(!b1 && !b2) insert(st, cnt); }
				else if(!b1 && !b2) {
					if(mp[i][j] == 1) insert(st + bit(j) + 2 * bit(j + 1), cnt);
				} else if(b1 && !b2) {
					if(j < m) insert(st - b1 * bit(j) + b1 * bit(j + 1), cnt);
					if(mp[i][j] == 1) insert(st, cnt);
				} else if(!b1 && b2) {
					if(i < n) insert(st - b2 * bit(j + 1) + b2 * bit(j), cnt);
					if(mp[i][j] == 1) insert(st, cnt);
				} else if(mp[i][j] == 1) {
					if(b1 == 1 && b2 == 1) {
						int fuck = 1;
						for(int b = j + 2; b <= m + 1; ++b) {
							if(((st >> shift(b)) & 3) == 1) ++fuck;
							if(((st >> shift(b)) & 3) == 2) --fuck;
							if(!fuck) {
								insert(st - b1 * bit(j) - b2 * bit(j + 1) - bit(b), cnt);
								break;
							}
						}
					}	
					else if(b1 == 2 && b2 == 2) {
						int fuck = 1;
						for(int b = j - 1; b; --b) {
							if(((st >> shift(b)) & 3) == 1) --fuck;
							if(((st >> shift(b)) & 3) == 2) ++fuck;
							if(!fuck) {
								insert(st - b1 * bit(j) - b2 * bit(j + 1) + bit(b), cnt);
								break;
							}
						}
					} else if(b1 == 2 && b2 == 1) insert(st - b1 * bit(j) - b2 * bit(j + 1), cnt);
					else if(i == ei && j == ej) ans += cnt * (st == b1 * bit(j) + b2 * bit(j + 1));
				}
			}
		}
	}
	printf("%lld\n", ans);
}

int main() { 
	n = in(), m = in();
    char buf[18];
	_rep(i,1,n) {
		scanf("%s", buf + 1);
		_rep(j,1,m) {
		    char c = buf[j];
			if(c == '#') mp[i][j] = 0;
			if(c == '.') mp[i][j] = 1;
			if(c == '-') mp[i][j] = 2;
			if(c == '|') mp[i][j] = 3;
			if(mp[i][j]) ei = i, ej = j;
		}
	}
	calc();
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