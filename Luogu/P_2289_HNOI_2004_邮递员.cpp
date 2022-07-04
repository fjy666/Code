//Code by fjy666
//luogu-judger-enable-O2
#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
#define multiCase() int testCnt = in(); _rep(curCase,1,testCnt)
typedef __int128 ll;

int in(void) { int x; scanf("%d", &x); return x; }
ll inl(void) { ll x; scanf("%lld", &x); return x; }
template<typename T> void chkmax(T &a, const T &b) { a = max(a, b); } 
template<typename T> void chkmin(T &a, const T &b) { a = min(a, b); } 
const int kN = 305000, p = 299989;
int now, tot[2], a[2][kN], nxt[kN], head[kN];
ll f[2][kN];
void ins(int x, ll d) {
	int hsh = x % p + 1;
	for(int i = head[hsh]; i; i = nxt[i]) if(a[now][i] == x) { f[now][i] += d; return; }
	nxt[++tot[now]] = head[hsh], head[hsh] = tot[now];
	f[now][tot[now]] = d, a[now][tot[now]] = x;
}

int m = in(), n = in();
#define shift(j) (2 * (j - 1))
#define getb(a,b) ((a >> shift(b)) & 3)
#define bit(b) (1 << shift(b))

void out(ll x) { if(x > 9) out(x / 10); putchar(x % 10 + '0'); }
void work(void) {
    if(n == 1 && m == 1) {
        puts("1");
        return;
    }
	ll ans = 0;
	tot[now] = 1, a[now][1] = 0, f[now][1] = 1;
	_rep(i,1,n) {
		_rep(j,1,tot[now]) a[now][j] <<= 2;
		_rep(j,1,m) {
			int lst = now; now ^= 1;
			tot[now] = 0, memset(head, 0, sizeof(head));
			_rep(k,1,tot[lst]) {
				int s = a[lst][k], b1 = getb(s, j), b2 = getb(s, j + 1); ll cnt = f[lst][k];
				if(!b1 && !b2) { if(i < n && j < m) ins(s + bit(j) + 2 * bit(j + 1), cnt); }
				else if(b1 && !b2) {
					if(i < n) ins(s, cnt);
					if(j < m) ins(s - b1 * bit(j) + b1 * bit(j + 1), cnt);
				} else if(!b1 && b2) {
					if(i < n) ins(s - b2 * bit(j + 1) + b2 * bit(j), cnt);
					if(j < m) ins(s, cnt);
				} else {
					if(b1 == 1 && b2 == 1) {
						int tmp = 1;
						_rep(b, j + 2, m + 1) {
							if(getb(s, b) == 1) ++tmp;
							if(getb(s, b) == 2) --tmp;
							if(!tmp) {
								ins(s - b1 * bit(j) - b2 * bit(j + 1) - bit(b), cnt);
								break;
							}
						}
					} else if(b1 == 2 && b2 == 2) {
						int tmp = 1;
						for(int b = j - 1; b; --b) {
							if(getb(s, b) == 1) --tmp;
							if(getb(s, b) == 2) ++tmp;
							if(!tmp) {
								ins(s - b1 * bit(j) - b2 * bit(j + 1) + bit(b), cnt);
								break;
							}
						}
					} else if(b1 == 2 && b2 == 1) {
						ins(s - b1 * bit(j) - b2 * bit(j + 1), cnt);
					} else {
						if(i == n && j == m) ans += cnt;
					}
				}
			}
		}
	}
	out(ans << 1);
}

int main() { 
	work();
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