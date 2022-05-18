#include <bits/stdc++.h>
#define _rep(i_,a_,b_) for(int i_ = a_;i_ <= b_;++i_)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
using namespace std;
const int kN = 3005000;
int ch[kN][2], fa[kN], ncnt, root, rev[kN], siz[kN];
char val[kN];
void pushup(int x) { siz[x] = siz[ch[x][0]] + siz[ch[x][1]] + 1; }
int build(char *s, int l, int r, int f) {
	if(l > r) return 0;
	int id = ++ncnt,mid = (l + r) >> 1; 
	val[id] = s[mid]; rev[id] = 0; fa[id] = f;
	ch[id][0] = build(s,l,mid - 1,id);
	ch[id][1] = build(s,mid + 1,r,id);
	pushup(id); return id;
} 
void pushdown(int x) {
	if(rev[x]) {
		swap(ch[x][0], ch[x][1]);
		rev[ch[x][0]] ^= 1;
		rev[ch[x][1]] ^= 1;	
		rev[x] = 0;
	}
}
int get(int x) { return ch[fa[x]][1] == x; }
void rotate(int x) {
	int y = fa[x], z = fa[y], d = get(x);
	ch[y][d] = ch[x][d ^ 1]; fa[ch[x][d ^ 1]] = y;
	ch[z][get(y)] = x; fa[x] = z;
	ch[x][d ^ 1] = y; fa[y] = x;
	pushup(y); pushup(x);
}
void splay(int x,int goal = 0) {
	while(fa[x] != goal) {
		int y = fa[x], z = fa[y];
		if(z != goal) rotate(get(x) == get(y) ? y : x);
		rotate(x);
	}
	if(!goal) root = x;
}
int kth(int k) { int cur = root;
	while(true) {
		pushdown(cur);
		if(siz[ch[cur][0]] >= k) cur = ch[cur][0];
		else if(siz[ch[cur][0]] + 1 < k) k -= siz[ch[cur][0]] + 1,cur = ch[cur][1];
		else { splay(cur);  return cur; }
	}
}
int cursor;
void move(int k) { cursor = k; }
void insert(int id) {
	int a = kth(cursor + 1), b = kth(cursor + 2);
	splay(a); splay(b,a);
	ch[b][0] = id; fa[id] = b; pushup(b); pushup(a);
}
void de1ete(int n) {
	int a = kth(cursor + 1), b = kth(cursor + n + 2);
	splay(a); splay(b,a);
	ch[b][0] = 0; pushup(b); pushup(a);
}
void reverse(int n) {
	int a = kth(cursor + 1), b = kth(cursor + n + 2);
	splay(a); splay(b,a);
	rev[ch[b][0]] ^= 1; pushup(b); pushup(a);
}
//char get(void) { int a = kth(cursor + 2); return val[a]; }
void g3t(int d) {
	if(!d) return;
	pushdown(d);
	g3t(ch[d][0]);
	putchar(val[d]);
	g3t(ch[d][1]);
}
void prev(void) { --cursor; }
void n3xt(void) { ++cursor; }
char cmd[15],a[kN];
int main() {
	int n = in();
	a[0] = a[1] = '&';
	root = build(a,0,1,0);
	_rep(i,1,n) {
		scanf("%s",cmd);
		if(strcmp(cmd,"Move") == 0) move(in());
		if(strcmp(cmd,"Insert") == 0) {
			int n = in(); getchar();
			_rep(i,1,n) {
				a[i] = getchar();
				if(a[i] == '\n' || a[i] == '\r') --i;
			}
			insert(build(a,1,n,0));
		}
		if(strcmp(cmd,"Delete") == 0) de1ete(in());
		if(strcmp(cmd,"Rotate") == 0) reverse(in());
		if(strcmp(cmd,"Get") == 0) {
			int n = in();
			int a = kth(cursor + 1), b = kth(cursor + n + 2);
			splay(a); splay(b,a);
			g3t(ch[b][0]); putchar('\n');
		}
		if(strcmp(cmd,"Prev") == 0) prev();
		if(strcmp(cmd,"Next") == 0) n3xt();
		//		flat(root); putchar('\n');
	}
	return 0;
}

