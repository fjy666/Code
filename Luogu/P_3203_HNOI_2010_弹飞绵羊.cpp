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
const int kN = 200500;
int n = in();
namespace LCT {
	int ch[kN][2], fa[kN], siz[kN], rev[kN];
	int identify(int x) { return ch[fa[x]][0] == x ? 0 : (ch[fa[x]][1] == x ? 1 : -1); }
	void pushup(int x) { siz[x] = siz[ch[x][0]] + siz[ch[x][1]] + 1; }
	void pushdown(int x) { 
		if(rev[x]) {
			swap(ch[x][0], ch[x][1]);
			rev[ch[x][0]] ^= 1, rev[ch[x][1]] ^= 1;
			rev[x] = 0;
		}
	}
	void pushall(int x) { if(identify(x) != -1) pushall(fa[x]); pushdown(x); }
	void rotate(int x) {
		int y = fa[x], z = fa[y], d = identify(x);
		fa[ch[x][d ^ 1]] = y, ch[y][d] = ch[x][d ^ 1];
		if(identify(y) != -1) ch[z][identify(y)] = x; fa[x] = z;
		ch[x][d ^ 1] = y, fa[y] = x;
		pushup(y), pushup(x);
	}
	void splay(int x) {
		pushall(x);
		while(identify(x) != -1) {
			int y = fa[x], z = fa[y];
			if(identify(y) != -1) rotate(identify(x) == identify(y) ? y : x);
			rotate(x);
		}
	}
	void access(int x) {
		for(int y = 0; x; y = x, x = fa[x]) 
			splay(x), ch[x][1] = y, pushup(x);
	}
	void makeroot(int x) {
		access(x), splay(x), rev[x] ^= 1; 
	}
	int findroot(int x) {
		access(x), splay(x), pushdown(x);
		while(ch[x][0]) pushdown(x = ch[x][0]);
		return x;
	}
	void link(int x, int y) {
		// printf("link %d %d\n", x, y);
		if(findroot(x) == findroot(y)) return;
		makeroot(x), fa[x] = y;
	}
	void split(int x, int y) {
		// printf("Split %d and %d\n", x, y);
		assert(findroot(x) == findroot(y));
		makeroot(x), access(y), splay(y); 
	}
	void cut(int x, int y) {
		if(findroot(x) != findroot(y)) return;
		split(x, y); 
		if(ch[y][0] == x && fa[x] == y && !ch[x][1])
			ch[y][0] = fa[x] = 0;
	}
} //namespace LCT

int b[kN];
int main() { 
	_rep(i,1,n) {
		int bounce = (b[i] = in());
		if(i + bounce <= n) LCT::link(i, i + bounce);
		else LCT::link(i, n + 1);
	}
	multiCase() {
		int op = in();
		if(op == 1) {
			int i = in() + 1;
			LCT::split(i, n + 1);
			printf("%d\n", LCT::siz[n + 1] - 1);
		} else {
			int i = in() + 1, j = in();
			if(i + b[i] <= n) LCT::cut(i, i + b[i]);
			else LCT::cut(i, n + 1);
			b[i] = j;
			if(i + b[i] <= n) LCT::link(i, i + b[i]);
			else LCT::link(i, n + 1); 
		}
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