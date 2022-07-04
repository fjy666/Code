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
const int kN = 500500, p = 499989, kM = 127;
int n, m, mp[kM][kM], now, tot[2], e1, e2;
int head[kN], nxt[kN], a[2][kN];
ll f[2][kN]; 

void ins(int sta, ll dp) {
	int hsh = sta % p + 1;
	for(int i = head[hsh]; i; i = nxt[i]) 
		if(a[now][i] == sta) { f[now][i] = max(f[now][i], dp); return; }
	nxt[++tot[now]] = head[hsh], head[hsh] = tot[now];
	a[now][tot[now]] = sta, f[now][tot[now]] = dp;
}
#define bit(i) (1 << (2 * (i - 1)))
#define shift(i) (2 * (i - 1))
void calc(void) {
	tot[now] = 1, a[now][1] = 0, f[now][1] = 0;
	ll ans = LLONG_MIN;
	_rep(i,1,n) {
		_rep(j,1,tot[now]) a[now][j] <<= 2;
		_rep(j,1,m) {
			int last = now; now ^= 1;
			memset(head, 0, sizeof(head)), tot[now] = 0;
			_rep(k,1,tot[last]) {
				int st = a[last][k], b1 = (st >> shift(j)) & 3, b2 = (st >> shift(j + 1)) & 3;
				ll cnt = f[last][k] + mp[i][j]; 
				if(!b1 && !b2) {
					ins(st, cnt - mp[i][j]); 
					if(i < n && j < m) ins(st + bit(j) + 2 * bit(j + 1), cnt); 
				} else if(!b1 && b2) {
					if(j < m) ins(st, cnt);
					if(i < n) ins(st + b2 * bit(j) - bit(j + 1) * b2, cnt);
				} 
				else if(b1 && !b2) {
					if(i < n) ins(st, cnt);
					if(j < m) ins(st - b1 * bit(j) + b1 * bit(j + 1), cnt);
				} 
				else if(b1 && b2) {
					if(b1 == 1 && b2 == 1) {
						int fuck = 1;
						for(int b = j + 2; b <= m + 1; ++b) {
							if(((st >> shift(b)) & 3) == 1) ++fuck;
							if(((st >> shift(b)) & 3) == 2) --fuck;
							if(!fuck) {
								ins(st - b1 * bit(j) - b2 * bit(j + 1) - bit(b), cnt);
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
								ins(st - b1 * bit(j) - b2 * bit(j + 1) + bit(b), cnt);
								break;
							}
						}
					} else if(b1 == 2 && b2 == 1) ins(st - b1 * bit(j) - b2 * bit(j + 1), cnt);
					else {
						if(st == b1 * bit(j) + b2 * bit(j + 1))
							chkmax(ans, cnt);
					}
				}
			}
		}
	}
	printf("%lld\n", ans);
}

int main() { 
	n = in(), m = in();
	_rep(i,1,n) _rep(j,1,m) mp[i][j] = in();
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