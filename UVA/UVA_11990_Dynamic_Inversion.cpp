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
const int kN = 200500;
struct Elem {
	int del, id, val;
} a[kN];
int BIT[kN];
void add(int a, int b) { for(;a < kN; a += a & -a) BIT[a] += b; }
int qry(int a) { int r = 0; for(;a; a -= a & -a) r += BIT[a]; return r; }
int n,m;

ll ans[kN];
void CDQ(int L, int R) {
	if(L == R) return;
	CDQ(L, mid); CDQ(mid + 1, R);
	auto cmp = [](const Elem &a, const Elem &b) -> bool {
		return a.val < b.val;
	};
	sort(a + L, a + mid + 1, cmp); sort(a + mid + 1, a + R + 1, cmp);
	int lp = mid;
	for(int rp = R; rp > mid; --rp) { //double ptr scan
		while(lp >= L && a[lp].val > a[rp].val) add(a[lp].del, 1), --lp;
		// if(a[rp].val == 4) 
		// 	printf("(%d, %d) rp = %d ADD %d 1\n", L, R, rp, qry(n + 1) - qry(a[rp].del - 1));
		ans[a[rp].val] += qry(n + 1) - qry(a[rp].del - 1);
	} 
	_rep(i, lp + 1, mid) add(a[i].del, -1);
	lp = mid + 1;
	_rep(rp, L, mid) {
		while(lp <= R && a[lp].val < a[rp].val) add(a[lp].del, 1), ++lp;
		// if(a[rp].val == 4) 
		// 	printf("(%d, %d) rp = %d ADD %d 2\n", L, R, rp, qry(n + 1) - qry(a[rp].del - 1));
		ans[a[rp].val] += qry(n + 1) - qry(a[rp].del - 1);
	}
	_rep(i, mid + 1, lp - 1) add(a[i].del, -1);
}

int q[kN], idx[kN];
int main() {
	while(~scanf("%d%d", &n, &m)) {
		_rep(i,1,n) a[i].del = 0, ans[i] = 0;
		_rep(i,1,n) a[i].val = in(), a[i].id = i, idx[a[i].val] = i;
		ll res = 0, res2 = 0;
		_rep(i,1,m) {
			q[i] = in();
			a[idx[q[i]]].del = i;
		}
		_rep(i,1,n) if(!a[i].del) a[i].del = n + 1;
		CDQ(1, n);
		_rep(i,1,n) if(a[i].del <= n) res += ans[a[i].val]; else res2 += ans[a[i].val];
		res += res2 / 2;
		printf("%lld\n", res);
		_rep(i,1,m - 1) {
			res -= ans[q[i]];
			printf("%lld\n", res);
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