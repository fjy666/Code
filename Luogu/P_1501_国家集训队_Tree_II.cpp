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
const unsigned int p = 51061;
unsigned sum[kN], mul[kN], tag[kN], ch[kN][2], siz[kN], fa[kN], add[kN], val[kN];
int identify(int x) { return ch[fa[x]][0] == x ? 0 : (ch[fa[x]][1] == x ? 1 : 2); }
void pushr(int x) {
	if(tag[x]) {
		swap(ch[x][0], ch[x][1]);
		tag[ch[x][0]] ^= 1;
		tag[ch[x][1]] ^= 1;
		tag[x] = 0;
	}
}
void pusha(int x) {
	if(add[x]) {
		if(ch[x][0]) {
			sum[ch[x][0]] = (sum[ch[x][0]] + add[x] * siz[ch[x][0]] % p) % p;
			add[ch[x][0]] = (add[ch[x][0]] + add[x]) % p;
			val[ch[x][0]] = (val[ch[x][0]] + add[x]) % p;
		}
		if(ch[x][1]) {
			sum[ch[x][1]] = (sum[ch[x][1]] + add[x] * siz[ch[x][1]] % p) % p;
			add[ch[x][1]] = (add[ch[x][1]] + add[x]) % p;
			val[ch[x][1]] = (val[ch[x][1]] + add[x]) % p;
		}
		add[x] = 0;
	}
}
void pushm(int x) {
	if(mul[x] != 1) {
		if(ch[x][0]) {
			sum[ch[x][0]] = (sum[ch[x][0]] * mul[x]) % p;
			add[ch[x][0]] = (add[ch[x][0]] * mul[x]) % p;
			val[ch[x][0]] = (val[ch[x][0]] * mul[x]) % p;
			mul[ch[x][0]] = (mul[ch[x][0]] * mul[x]) % p;
		}
		if(ch[x][1]) {
			sum[ch[x][1]] = (sum[ch[x][1]] * mul[x]) % p;
			add[ch[x][1]] = (add[ch[x][1]] * mul[x]) % p;
			val[ch[x][1]] = (val[ch[x][1]] * mul[x]) % p;
			mul[ch[x][1]] = (mul[ch[x][1]] * mul[x]) % p;
		}
		mul[x] = 1;
	}
}
void pushdown(int x) { pushr(x); pushm(x); pusha(x); }
void pushall(int x) { if(2 != identify(x)) pushall(fa[x]); pushdown(x); }
void pushup(int x) { 
	sum[x] = (sum[ch[x][0]] + sum[ch[x][1]] + val[x]) % p; 
	siz[x] = siz[ch[x][0]] + siz[ch[x][1]] + 1; 
}
void rotate(int x) {
	int y = fa[x], z = fa[y], d = identify(x);
	fa[ch[x][d ^ 1]] = y, ch[y][d] = ch[x][d ^ 1];
	if(identify(y) != 2) ch[z][identify(y)] = x; fa[x] = z;
	ch[x][d ^ 1] = y; fa[y] = x;
	pushup(y); pushup(x);	
}
void splay(int x) {
	pushall(x);
	while(2 != identify(x)) {
		int y = fa[x], z = fa[y];
		if(2 != identify(y)) rotate(identify(x) == identify(y) ? y : x);
		rotate(x);
	}
}
void access(int x) { for(int y = 0; x; y = x, x = fa[x]) splay(x), ch[x][1] = y, pushup(x); }
void makeroot(int x) { access(x), splay(x), tag[x] ^= 1; }
int findroot(int x) {
	access(x), splay(x), pushdown(x);
	while(ch[x][0]) pushdown(x = ch[x][0]);
	return x;
}
void split(int x, int y) { makeroot(x), access(y), splay(y); }
void link(int x, int y) {
	if(findroot(x) == findroot(y)) return;
	makeroot(x), splay(x), fa[x] = y;
}
void cut(int x, int y) {
	if(findroot(x) != findroot(y)) return;
	split(x,y);
	if(ch[y][0] == x && fa[x] == y && !ch[x][1])
		fa[x] = ch[y][0] = 0;
}
int main() { 
	int n = in(), m = in();
	_rep(i,1,n) mul[i] = 1, tag[i] = add[i] = 0, sum[i] = val[i] = siz[i] = 1;
	_rep(i,1,n - 1) {
		int u = in(), v = in();
		link(u,v);
	}
	_rep(i,1,m) {
		char opt[5]; int u, v;
		scanf("%s%d%d", opt, &u, &v);
		if(opt[0] == '+') {
			split(u,v); unsigned c = in() % p;
			add[v] = (add[v] + c) % p;
			sum[v] = (sum[v] + siz[v] * c % p) % p;
			val[v] = (val[v] + c) % p;
		}
		if(opt[0] == '-') {
			int u1 = in(), u2 = in();
			cut(u, v); link(u1, u2);
		}
		if(opt[0] == '*') {
			split(u,v); unsigned c = in() % p;
			add[v] = add[v] * c % p;
			sum[v] = sum[v] * c % p;
			val[v] = val[v] * c % p;
			mul[v] = mul[v] * c % p;
		}
		if(opt[0] == '/') {
			split(u,v);
			printf("%u\n", sum[v]);
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
*/
