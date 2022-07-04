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
const int p = 20110520, P = 299989, kN = 500000;
int n, m, mp[150][150], baka[150][150];
char buf[150];
int head[P], nxt[kN], tot[2], f[2][kN], a[2][kN], now;
void insert(int st, int d) { d %= p;
	for(int i = head[st % P]; i; i = nxt[i]) if(a[now][i] == st) { f[now][i] = (f[now][i] + d) % p; return; }
	nxt[++tot[now]] = head[st % P]; head[st % P] = tot[now];
	a[now][tot[now]] = st, f[now][tot[now]] = d;
}
#define shift(i) (2 * (i - 1))
#define gb(i, j) ((i >> shift(j)) & 3) //getbit
#define bit(i) (1 << shift(i))
/*
0 --> 没有插头
1 --> 已经转弯了
2 --> 还没有转弯
*/
void work(void) {
	tot[now] = 1, f[now][tot[now]] = 1;
	int ans = 0, ei, ej;
	_rep(i,1,n) _rep(j,1,m) if(mp[i][j]) ei = i, ej = j;
	// printf("ei = %d, ej = %d\n", ei, ej);
	_rep(i,1,n) {
		_rep(j,1,tot[now]) a[now][j] <<= 2;
		_rep(j,1,m) {
			int lst = now; now ^= 1;	
			memset(head, 0, sizeof(head)); tot[now] = 0;
			_rep(k,1,tot[lst]) {
				int st = a[lst][k], cnt = f[lst][k], b1 = gb(st, j), b2 = gb(st, j + 1);
				// printf("(%d,%d) %d\n", i, j, cnt);
				if(!mp[i][j]) { if(b1 || b2) assert(false); insert(st, cnt); }
				else if(!b1 && !b2) { 
					if(mp[i][j + 1] && mp[i + 1][j]) insert(st + bit(j) + bit(j + 1), cnt);
					if(mp[i][j + 1]) insert(st + 2 * bit(j + 1), cnt);
					if(mp[i + 1][j]) insert(st + 2 * bit(j), cnt);
				} else if(b1 && !b2) {
					if(b1 == 1) {
						insert(st - bit(j), cnt);
						if(mp[i][j + 1]) insert(st - bit(j) + bit(j + 1), cnt);
						if(i == ei && j == ej) ans = (ans + cnt) % p;
					} else {
						if(mp[i][j + 1]) insert(st - 2 * bit(j) + 2 * bit(j + 1), cnt);
						if(mp[i + 1][j]) insert(st - bit(j), cnt);
					}
				} else if(!b1 && b2) {
					if(b2 == 1) {
						insert(st - bit(j + 1), cnt);
						if(mp[i + 1][j]) insert(st - bit(j + 1) + bit(j), cnt);
						if(i == ei && j == ej) ans = (ans + cnt) % p;
					} else {
						if(mp[i][j + 1]) insert(st - bit(j + 1), cnt);
						if(mp[i + 1][j]) insert(st - 2 * bit(j + 1) + 2 * bit(j), cnt);
					}
				} else if(b1 == 2 && b2 == 2) {
					insert(st - 2 * bit(j) - 2 * bit(j + 1), cnt);
					if(i == ei && j == ej) ans = (ans + cnt) % p;
				}
			}
		}
	}
	printf("%d\n", ans);
}	

int main() { 
	n = in(), m = in();
	_rep(i,1,n) {
		scanf("%s", buf + 1);
		_rep(j,1,m) mp[i][j] = buf[j] == '_';
	}
	if(n < m) {
		_rep(i,1,n) _rep(j,1,m) baka[j][i] = mp[i][j];
		memcpy(mp, baka, sizeof(mp));
		swap(n, m);
	}
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