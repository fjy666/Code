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
template<typename T> void updmax(T &a, const T &b) { a = max(a, b); } 
template<typename T> void updmin(T &a, const T &b) { a = min(a, b); } 
const int kN = 100500;
int n = in(), m = in();
struct Elem {
	int id, val, mx, mn;
} a[kN];

int c[kN];
void add(int p, int d) { for(;p < kN; p += p & -p) updmax(c[p], d); }
int qry(int p) { int a = 0; for(;p; p -= p & -p) updmax(a, c[p]); return a; }
void clr(int a) { for(;a < kN;a += a & -a) c[a] = 0; }

auto cmp = [](const Elem &a, const Elem &b) -> bool { return a.val < b.val; };
auto cup = [](const Elem &a, const Elem &b) -> bool { return a.mx < b.mx; };
auto cnp = [](const Elem &a, const Elem &b) -> bool { return a.id < b.id; };
int f[kN];
void CDQ(int L, int R) {
	if(L == R) { updmax(f[L], 1); return; }
	CDQ(L, mid); int lp = L;
	sort(a + L, a + mid + 1, cup);
	sort(a + mid + 1, a + R + 1, cmp);
	_rep(i, mid + 1, R) {
		while(lp <= mid && a[lp].mx <= a[i].val) add(a[lp].val, f[a[lp].id]), ++lp;
		updmax(f[a[i].id], qry(a[i].mn) + 1);
	}
	_rep(i, L, lp - 1) clr(a[i].val);
	sort(a + mid + 1, a + R + 1, cnp);
	CDQ(mid + 1, R);
}

int main() { 
	_rep(i,1,n) a[i].id = i, a[i].val = a[i].mx = a[i].mn = in();
	_rep(i,1,m) {
		int j = in(), to = in();
		updmax(a[j].mx, to), updmin(a[j].mn, to);
	}
	CDQ(1, n);
	//fi = max{fj} + 1
	int res = 0; _rep(i,1,n) updmax(res, f[i]);
	printf("%d\n", res);
	return 0;
}

/* 
a list of keywords 
clear empty push_back pop_back push pop top front back
emplace_back emplace push_front pop_front insert erase
find count set reset bitset map vector string multiset
first second iterator prev next deque multimap reverse
*/