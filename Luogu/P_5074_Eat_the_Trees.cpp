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
const int kN = 13, kM = 300000, p = 2999987; //<-- 真的不是质数！
int a[2][], nxt[1<<kN], head[kM], tot[2], mp[kN][kN], n, m, now;
ll f[2][1<<kN];
void ins(int s, ll d) {
	int h = s % p + 1;
	for(int i = head[h]; i; i = nxt[i]) if(a[now][i] == d) { f[now][i] += d; return; }
	++tot[now], nxt[tot[now]] = head[h], head[h] = tot[now];
	f[now][tot[now]] = d, a[now][tot[now]] = s;
}
#define shift(i) (2 * (i - 1))
#define bit(i) (1 << shift(i))
#define gets(i,k) ((i >> shift(k)) & 3)

int main() { 
	multiCase() {
		n = in(), m = in();
		memset(mp, 0, sizeof(mp));
		_rep(i,1,n) _rep(j,1,m) mp[i][j] = in();
		int ei = 0, ej = 0;
		_rep(i,1,n) _rep(j,1,m) if(mp[i][j]) ei = i, ej = j;
		if(!ei && !ej) {
			puts("1");
			continue;
		}
		ll ans = 0;
		now = 0, tot[0] = 1, f[0][1] = 1, a[0][1] = 0;
		memset(head, 0, sizeof(head));
		_rep(i,1,n) {
			_rep(j, 1, tot[now]) a[now][j] <<= 2;
			_rep(j, 1, m) {
				int lst = now; now ^= 1;
				tot[now] = 0, memset(head, 0, sizeof(head));
				_rep(k, 1, tot[lst]) {
					ll cnt = f[lst][k]; int s = a[lst][k], b1 = gets(s, j), b2 = gets(s, j + 1);
					if(cnt) {
						// printf("(%d,%d) %lld\n", i, j, cnt);
						if(!mp[i][j]) { if(!b1 && !b2) ins(s, cnt); }
						else if(!b1 && !b2) {
							if(mp[i][j + 1] && mp[i + 1][j]) ins(s + bit(j) + 2 * bit(j + 1), cnt);
						} else if(!b1 && b2) {
							if(mp[i][j + 1]) ins(s, cnt);
							if(mp[i + 1][j]) ins(s - b2 * bit(j + 1) + b2 * bit(j), cnt);
						} else if(b1 && !b2) {
							if(mp[i][j + 1]) ins(s - b1 * bit(j) + b1 * bit(j + 1), cnt);
							if(mp[i + 1][j]) ins(s, cnt);
						} else {
							if(b1 == 1 && b2 == 1) {
								int q = 1;
								_rep(k, j + 2, m + 1) {
									if(gets(s, k) == 1) ++q;
									if(gets(s, k) == 2) --q;
									if(!q) {
										ins(s - b1 * bit(j) - b2 * bit(j + 1) - bit(k), cnt);
										break;
									}
								}
							} else if(b1 == 2 && b2 == 2) {
								int q = 1;
								for(int k = j - 1; k; --k) {
									if(gets(s, k) == 1) --q;
									if(gets(s, k) == 2) ++q;
									if(!q) {
										ins(s - b1 * bit(j) - b2 * bit(j + 1) + bit(k), cnt);
										break;
									}
								}
							} else if(b1 == 1 && b2 == 2) {
								if(i == ei && j == ej) ans += cnt;
								else ins(s - b1 * bit(j) - b2 * bit(j + 1), cnt);
							} else 
								ins(s - b1 * bit(j) - b2 * bit(j + 1), cnt);
						}
					}
				}
			}
		}
		printf("%lld\n", ans);
	}
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