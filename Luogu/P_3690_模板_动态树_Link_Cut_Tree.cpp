//Code by fjy666
#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
#define multiCase() int testCnt = in(); _rep(curCase,1,testCnt)
typedef long long ll;

int in(void) { int x; scanf("%d", &x); return x; }
ll inl(void) { ll x; scanf("%lld", &x); return x; }
const int kN = 100500;
int ch[kN][2], fa[kN], v[kN], s[kN], tag[kN];
void pushup(int x) { s[x] = v[x] ^ s[ch[x][0]] ^ s[ch[x][1]]; }
void pushdown(int x) {
	if(tag[x]) {
		swap(ch[x][0], ch[x][1]);
		tag[ch[x][0]] ^= 1, tag[ch[x][1]] ^= 1;
		tag[x] = 0;
	}
}
int identify(int x) { return ch[fa[x]][0] == x ? 0 : (ch[fa[x]][1] == x ? 1 : -1); }
void pushall(int x) { if(identify(x) != -1) pushall(fa[x]); pushdown(x); }
void connect(int x, int y, int d) { fa[x] = y, ch[y][d] = x; }
void rotate(int x) {
	int y = fa[x], z = fa[y], d = identify(x);
	connect(ch[x][d ^ 1], y, d);
	if(identify(y) != -1) connect(x, z, identify(y)); else fa[x] = z;
	connect(y, x, d ^ 1);
	pushup(y), pushup(x);
}
void splay(int x) { pushall(x);
	while(identify(x) != -1) {
		int y = fa[x], z = fa[y];
		if(identify(y) != -1) rotate(identify(y) == identify(x) ? y : x);
		rotate(x);
	}
}
void access(int x) { for(int y = 0; x; y = x, x = fa[x]) splay(x), ch[x][1] = y, pushup(x); }
void makeroot(int x) { access(x); splay(x); tag[x] ^= 1; }
int getroot(int x) { access(x), splay(x), pushdown(x); while(ch[x][0]) pushdown(x = ch[x][0]); return x; }
void split(int x, int y) { makeroot(x), access(y), splay(y); }
void link(int x, int y) { makeroot(x); if(getroot(y) == x) return; fa[x] = y; }	
void cut(int x, int y) { 
	if(getroot(x) != getroot(y)) return; 
	split(x,y);
	if(fa[x] != y || ch[x][1]) return;
	fa[x] = ch[y][0] = 0;
}

int n = in(), m = in();
int main() { 
	_rep(i,1,n) v[i] = in();
	_rep(i,1,m) {
		int op = in(), x = in(), y = in();
		if(op == 0) split(x,y), printf("%d\n", s[y]);
		if(op == 1) link(x,y);
		if(op == 2) cut(x,y);
		if(op == 3) splay(x), v[x] = y;		
	}
	return 0;
}

/* 
a list of keywords 
clear empty push_back pop_back push pop top front back
emplace_back emplace push_front pop_front insert erase
find count set reset bitset map vector string multiset
first second iterator prev next deque multimap reverse
*/