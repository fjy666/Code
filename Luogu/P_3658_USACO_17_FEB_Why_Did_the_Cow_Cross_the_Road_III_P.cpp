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
const int kN = 100500;
struct Elem {
	int a, b, c, res;
} a[kN];
int n = in(), k = in();
auto cmp = [](const Elem &a, const Elem &b) { return a.b < b.b; };
auto cmp2 = [](const Elem &a, const Elem &b) { return a.c < b.c; };
int c[kN];
void add(int x, int d) { for(;x < kN; x += x & -x) c[x] += d; }
int qry(int x) { int a=0; for(;x;x -= x&-x)a+=c[x]; return a; }

void CDQ(int L, int R) {
	if(L == R) return;
	CDQ(L, mid); CDQ(mid + 1, R);
	sort(a + L, a + mid + 1, cmp2); sort(a + mid + 1, a + R + 1, cmp2);
	int pl = mid; for(int i = R; i > mid; --i) {
		while(pl >= L && a[pl].c > a[i].c) add(a[pl].a, 1), --pl;
		int R = min(n, a[i].a + k), L = max(1, a[i].a - k);
		a[i].res += qry(n) - (qry(R) - qry(L - 1));
	}
	_rep(i, pl + 1, mid) add(a[i].a, -1);
} 

int main() { 
	_rep(i, 1, n) a[i].a = i;
	_rep(i, 1, n) a[in()].b = i;
	_rep(i, 1, n) a[in()].c = i;
	sort(a + 1, a + 1 + n, cmp);
	CDQ(1, n);
	int ans = 0;
	_rep(i, 1, n) ans += a[i].res; //, printf("res[%d] = %d\n", a[i].a, a[i].res);
	printf("%d\n", ans);
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