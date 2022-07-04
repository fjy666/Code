//Code by fjy666
//Luogu judger enable O2
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
const int kN = 500550;

struct Elem { int a, b, c, d, id; ll e; } a[kN], b[kN];
bool operator == (const Elem &a, const Elem &b) {
	return memcmp(&a, &b, sizeof(Elem)) == 0;
}
auto cmp = [](const Elem &a, const Elem &b) -> bool 
	{ return a.a != b.a ? a.a < b.a : (a.b != b.b ? a.b < b.b : (a.c != b.c ? a.c < b.c : a.d < b.d)); };
auto cmp2 = [](const Elem &a, const Elem &b) -> bool 
	{ return a.b != b.b ? a.b < b.b : (a.c != b.c ? a.c < b.c : a.d < b.d); };
auto cmp3 = [](const Elem &a, const Elem &b) -> bool 
	{ return a.c != b.c ? a.c < b.c : a.d < b.d; };

int n = in();
ll f[kN];

ll c[kN];
void add(int p, ll d) { for(;p < kN; p += p & -p) updmax(c[p], d); }
ll qry(int p) { ll a = 0; for(;p; p -= p & -p) updmax(a, c[p]); return a; }
void clr(int a) { for(;a < kN;a += a & -a) c[a] = 0; }

void CDQ2(int L, int R) {
	if(L == R) return;
	CDQ2(L, mid);
	stable_sort(b + L, b + 1 + mid, cmp3); stable_sort(b + mid + 1, b + R + 1, cmp3);
	int pl = L;
	_rep(i, mid + 1, R) {
		while(pl <= mid && b[pl].c <= b[i].c) { if(b[pl].a == 0) add(b[pl].d, f[b[pl].id]); ++pl; }
		if(b[i].a == 1) updmax(f[b[i].id], qry(b[i].d) + b[i].e);
	}
	_rep(i, L, pl - 1) if(b[i].a == 0) clr(b[i].d);
	stable_sort(b + L, b + 1 + R, cmp2);
	CDQ2(mid + 1, R);
}

void CDQ1(int L, int R) {
	if(L == R) { f[L] = max(f[L], a[L].e); return; }
	CDQ1(L, mid);
	
	_rep(i, L, R) b[i] = a[i];
	_rep(i, L, R) b[i].a = i > mid;
	stable_sort(b + L, b + R + 1, cmp2);

	CDQ2(L, R);
	CDQ1(mid + 1, R);
}

int fuck[kN]; 
int main() { 
	_rep(i,1,n) a[i].a = in(), a[i].b = in(), a[i].c = in(), a[i].d = in(), a[i].e = inl(), fuck[i] = a[i].d;
	stable_sort(fuck + 1, fuck + 1 + n);
	_rep(i,1,n) a[i].d = lower_bound(fuck + 1, fuck + 1 + n, a[i].d) - fuck;
	stable_sort(a + 1, a + 1 + n, cmp);
	int m = 0;
	_rep(i,1,n) if(a[i] == a[m]) a[m].e += max(a[i].e, 0ll); else a[++m] = a[i];
	n = m;
	_rep(i,1,n) a[i].id = i;
	CDQ1(1, n);
	ll res = 0;
	_rep(i,1,n) updmax(res, f[i]);
	printf("%lld\n", res);
	return 0;
}

/* 
a list of keywords 
clear empty push_back pop_back push pop top front back
emplace_back emplace push_front pop_front insert erase
find count set reset bitset map vector string multiset
first second iterator prev next deque multimap reverse
*/