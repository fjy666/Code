//Code by fjy666
#include <bits/stdc++.h>
// using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
#define multiCase() int testCnt = in(); _rep(curCase,1,testCnt)
typedef long long ll;

int in(void) { int x; scanf("%d", &x); return x; }
ll inl(void) { ll x; scanf("%lld", &x); return x; }
const int kN = 300500,kM = 1005000;
int n = in(), m = in();
struct Option {
	int op, x, y, id;
} a[kN << 1], baka[kN << 1], cirno;
int res[kN << 1];
int bit[kM];
void set(int x, int y) { for(;x < kM;x += x & -x) if(y > bit[x]) bit[x] = y; }
void clr(int x) { for(;x < kM;x += x & -x) bit[x] = 0; }
int qry(int x) { int a = 0; for(;x;x -= x & -x) a = std::max(a, bit[x]); return a; }

auto cmp = [](const Option &a, const Option &b) -> bool {
	return a.x < b.x;
};
void CDQ(int L, int R) {
	// printf("Calling cdq(%d,%d)\n", L, R);
	if(L == R) return;
	CDQ(L, mid); CDQ(mid + 1, R);
	std::sort(a + L, a + mid + 1, cmp); std::sort(a + mid + 1, a + R + 1, cmp);
	int pl = L;
	_rep(i, mid + 1, R) {
		while(!a[i].op && i <= R) ++i; if(i > R) break;
		while(pl <= mid && a[pl].x <= a[i].x) { if(!a[pl].op) set(a[pl].y, a[pl].x + a[pl].y); ++pl; }
		// printf("Update %d to %d\n", a[i].id, a[i].x + a[i].y - qry(a[i].y));
		if(qry(a[i].y) > 0) res[a[i].id] = std::min(res[a[i].id], a[i].x + a[i].y - qry(a[i].y));
	}
	_rep(i, L, pl - 1) if(!a[i].op) clr(a[i].y);
}

int query[kN << 1];
int main() { 
	_rep(i,1,n) a[i].x = in() + 1, a[i].y = in() + 1, a[i].op = 0, a[i].id = i; //0表示加点, 1表示查询
	int greatest = 0;
	_rep(i,1,m) a[i + n].op = in() - 1, a[i + n].x = in() + 1, a[i + n].y = in() + 1, a[i + n].id = i + n;
	n += m;
	_rep(i,1,n) if(a[i].op) query[i] = 1;
	_rep(i,1,n) baka[i] = a[i], greatest = std::max({greatest, a[i].x, a[i].y}); ++greatest;
	memset(res, 0x3f, sizeof(res));
	CDQ(1, n);
	_rep(i,1,n) a[i] = baka[i], a[i].x = greatest - a[i].x;
	CDQ(1, n);
	_rep(i,1,n) a[i] = baka[i], a[i].y = greatest - a[i].y;
	CDQ(1, n);
	_rep(i,1,n) a[i] = baka[i], a[i].x = greatest - a[i].x, a[i].y = greatest - a[i].y;
	CDQ(1, n);
	_rep(i,1,n) if(query[i]) printf("%d\n", res[i]);
	return 0;
}

/* 
a list of keywords 
clear empty push_back pop_back push pop top front back
emplace_back emplace push_front pop_front insert erase
find count set reset bitset map vector string multiset
first second iterator prev next deque multimap reverse
*/