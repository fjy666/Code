//Code by fjy666
//luogu-judger-enable-O2
/*
Things to checkout:
Do you run your init() in main?
Do you open 2*kN space in SAM, manacher, etc?
*/
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
const int kN = 105000 * 20;
int n = in();
int ability[kN], d[kN];
vector<int> g[kN];
int ch[kN][2], sum[kN], nc, rt[kN];
void pushup(int x) { sum[x] = sum[ch[x][0]] + sum[ch[x][1]]; }
int merge(int x, int y, int L, int R) {
	if(!x || !y) return x + y;
	if(L == R) { return sum[x] += sum[y], x; }
	ch[x][0] = merge(ch[x][0], ch[y][0], L, mid), ch[x][1] = merge(ch[x][1], ch[y][1], mid + 1, R);
	return pushup(x), x;
}
void insert(int &o, int L, int R, int pos) {
	if(!o) o = ++nc, sum[o] = 1;
	if(L == R) return;
	pos <= mid ? insert(ch[o][0], L, mid, pos) : insert(ch[o][1], mid + 1, R, pos);
}
int query(int x, int L, int R, int l, int r) {
	if(l > r || !x) return 0;
	if(l <= L && R <= r) return sum[x];
	int res = 0;
	if(l <= mid) res += query(ch[x][0], L, mid, l, r);
	if(mid < r) res += query(ch[x][1], mid + 1, R, l, r);
	return res;
}
int res[kN];
void dfs(int x) {
	// printf("Root %d\n", x);
	for(auto &v : g[x]) {
		dfs(v); 
		// printf("Mergeing Tree %d and %d\n", x, v);
		rt[x] = merge(rt[x], rt[v], 1, n);
	}
	res[x] = query(rt[x], 1, n, ability[x] + 1, n);
	// if(x == 4) {
	// 	printf("s[rt[4]] = %d, res[4]=%d\n", sum[rt[x]], res[4]);
	// } 	
	// printf("End %d\n", x);
}

int main() { 
	_rep(i,1,n) d[i] = ability[i] = in();
	sort(d + 1, d + 1 + n);
	_rep(i,1,n) 
		ability[i] = lower_bound(d + 1, d + 1 + n, ability[i]) - d, 
		insert(rt[i], 1, n, ability[i]);
	_rep(i,2,n) g[in()].push_back(i);
	dfs(1);
	_rep(i,1,n) printf("%d\n", res[i]);
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