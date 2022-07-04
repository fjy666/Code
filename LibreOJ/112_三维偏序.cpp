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
struct Elem {
	int a, b, c, cnt, val;
} a[kN];
bool operator == (const Elem &a, const Elem &b) {
	return a.a == b.a && a.b == b.b && a.c == b.c;
}
int n = in();

int BIT[kN]; 
void add(int a, int v) { for(;a < kN; a += a & -a) BIT[a] += v; }  
int qry(int a) { int r = 0; for(;a;a -= a & -a) r += BIT[a]; return r; }
void CDQ(int L, int R) {
	if(L == R) return;
	CDQ(L, mid); CDQ(mid + 1, R);
	sort(a + L, a + mid + 1, [](const Elem &a, const Elem &b) -> bool {
		return a.b != b.b ? a.b < b.b : a.c < b.c;
	});
	sort(a + mid + 1, a + R + 1, [](const Elem &a, const Elem &b) -> bool {
		return a.b != b.b ? a.b < b.b : a.c < b.c;
	});
	int pl = L;
	_rep(i, mid + 1, R) {
		while(pl <= mid && a[pl].b <= a[i].b) add(a[pl].c, a[pl].cnt), ++pl;
		a[i].val += qry(a[i].c);
	}
	_rep(i,L,pl - 1) add(a[i].c, -a[i].cnt);
}

int res[kN];
int main() { in();
	_rep(i,1,n) a[i].a = in(), a[i].b = in(), a[i].c = in();
	sort(a + 1, a + 1 + n, [](const Elem &a, const Elem &b) -> bool {
		return a.a != b.a ? a.a < b.a : (a.b != b.b ? a.b < b.b : a.c < b.c);
	});
	int m = 0;
	_rep(i,1,n) a[i].cnt = 1;
	_rep(i,1,n) if(a[i] == a[m]) ++a[m].cnt; else a[++m] = a[i]; 
	CDQ(1, m);
	_rep(i,1,m) res[a[i].val + a[i].cnt - 1] += a[i].cnt;
	_rep(i,0,n - 1) printf("%d\n", res[i]); 
	return 0;
}

/* 
a list of keywords 
clear empty push_back pop_back push pop top front back
emplace_back emplace push_front pop_front insert erase
find count set reset bitset map vector string multiset
first second iterator prev next deque multimap reverse
*/