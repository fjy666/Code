// created time : 2022-04-08 19:17:16
// writer : fjy
#include <bits/stdc++.h>
#define int long long
#define _rep(i_,a_,b_) for(int i_ = a_;i_ <= b_;++i_)
typedef long long ll;
int in(void) { int x; scanf("%lld",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
using namespace std;
const int kN = 500500;
int ch[kN][2], fa[kN], ncnt, root, siz[kN];
int val[kN], rev[kN], mx[kN], add[kN];

void pushup(int x) { mx[x] = max({mx[ch[x][0]],mx[ch[x][1]],val[x]});
					 siz[x] = siz[ch[x][0]] + siz[ch[x][1]] + 1; }

int build(int *a,int l,int r,int f) {
    if(l > r) return 0;
    int id = ++ncnt,mid = (l + r) >> 1;
    val[id] = a[mid], fa[id] = f;
    ch[id][0] = build(a,l,mid - 1,id);
    ch[id][1] = build(a,mid + 1,r,id);
    pushup(id);
    return id;
}

void pushdown(int x) {
	if(rev[x]) {
		swap(ch[x][0],ch[x][1]);
		rev[ch[x][0]] ^= 1;
		rev[ch[x][1]] ^= 1;
		rev[x] = 0;
	}
	if(add[x]) {
		if(ch[x][0]) {
			add[ch[x][0]] += add[x];
			val[ch[x][0]] += add[x];
			mx[ch[x][0]] += add[x];
		}
		if(ch[x][1]) {
			add[ch[x][1]] += add[x];
			val[ch[x][1]] += add[x];
			mx[ch[x][1]] += add[x];
		} 
		add[x] = 0;
	}
}

int get(int x) { return ch[fa[x]][1] == x; }
void rotate(int x) {
    int y = fa[x],z = fa[y],d = get(x);
    ch[y][d] = ch[x][d ^ 1]; fa[ch[x][d ^ 1]] = y;
    ch[z][get(y)] = x; fa[x] = z;
    ch[x][d ^ 1] = y; fa[y] = x;
    pushup(y); pushup(x);
}

void splay(int x,int goal = 0) {
    while(fa[x] != goal) {
        int y = fa[x],z = fa[y];
        if(z != goal) rotate(get(x) == get(y) ? y : x);
        rotate(x);
    }
    if(!goal) root = x;
}

int kth(int k) {
    int cur = root;
    while(true) {
        pushdown(cur);
        if(siz[ch[cur][0]] >= k) cur = ch[cur][0];
        else if(siz[ch[cur][0]] + 1 < k) k -= siz[ch[cur][0]] + 1,cur = ch[cur][1];
        else {
            splay(cur);
            return cur;
        }
    }
}

int get_sum(int l,int r) {
	int a = kth(l),b = kth(r + 2);
	splay(a); splay(b,a);
	return mx[ch[b][0]];
}
void addd(int l,int r,int delta) {
	int a = kth(l), b = kth(r + 2);
	splay(a); splay(b,a);
	mx[ch[b][0]] += delta;
	val[ch[b][0]] += delta;
	add[ch[b][0]] += delta;
	pushup(b); pushup(a);
}
void reverse(int l,int r) {
	int a = kth(l), b = kth(r + 2);
	splay(a); splay(b,a);
	rev[ch[b][0]] ^= 1;
}

int a[kN];

char command[150];
signed main() {
    int n = in(),m = in();
    _rep(i,1,n) a[i] = 0;
    mx[0] = LLONG_MIN;
    root = build(a,0,n + 1,0);
    _rep(i,1,m) {
    	int k = in(),l = in(),r = in();
    	if(k == 1) addd(l,r,in());
    	if(k == 2) reverse(l,r);
    	if(k == 3) printf("%lld\n",get_sum(l,r));
	}
    return 0;
}
