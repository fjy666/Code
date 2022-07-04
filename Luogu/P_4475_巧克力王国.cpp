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
const int kN = 50005;
struct Point { int x, y, z; } a[kN];
auto cmp1 = [](const Point &lhs, const Point &rhs) -> bool { return lhs.x < rhs.x; };
auto cmp2 = [](const Point &lhs, const Point &rhs) -> bool { return lhs.y < rhs.y; };
int rt;
namespace KDTree {
	int ch[kN][2], x[kN], y[kN], l[kN], r[kN], u[kN], d[kN], v[kN], s[kN], nc;
	void pushup(int o) {
		#define upd(_) chkmin(l[o], l[_]), chkmin(d[o], d[_]), chkmax(r[o], r[_]), chkmax(u[o], u[_])
		l[o] = r[o] = x[o], u[o] = d[o] = y[o];
		if(ch[o][0]) upd(ch[o][0]); if(ch[o][1]) upd(ch[o][1]);
		s[o] = s[ch[o][0]] + s[ch[o][1]] + v[o]; 
	}
	int build(int L, int R, int d) {
		if(L > R) return 0;
		if(d) nth_element(a + L, a + mid, a + R + 1, cmp2);
		else nth_element(a + L, a + mid, a + R + 1, cmp1);
		int cur = ++nc; x[cur] = a[mid].x, y[cur] = a[mid].y, v[cur] = a[mid].z;
		ch[cur][0] = build(L, mid - 1, d ^ 1), ch[cur][1] = build(mid + 1, R, d ^ 1);
		pushup(cur); return cur;
	}
	int query(int o, int ax, int by, int c) {
		// printf("Debug#1\n");
		if(!o) return 0;
		// printf("Chocolate (%d,%d,%d) = root\n", x[o], y[o], v[o]);
		// printf("Min = %d, sx = %d, sy = %d\n", (ax > 0 ? ax * l[o] : ax * r[o]) + (by > 0 ? by * d[o] : by * u[o]), l[o], d[o]);
		if((ax > 0 ? ax * r[o] : ax * l[o]) + (by > 0 ? by * u[o] : by * d[o]) < c) return s[o];
		if((ax > 0 ? ax * l[o] : ax * r[o]) + (by > 0 ? by * d[o] : by * u[o]) >= c) return 0;
		return (ax * x[o] + by * y[o] < c ? v[o] : 0) + query(ch[o][0], ax, by, c) + query(ch[o][1], ax, by, c);
	}
}

int main() { 
	int n = in(), m = in();
	_rep(i,1,n) a[i].x = in(), a[i].y = in(), a[i].z = in();
	rt = KDTree::build(1, n, 0);
	_rep(i,1,m) {
		int a = in(), b = in(), c = in();
		printf("%d\n", KDTree::query(rt, a, b, c));
	}
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