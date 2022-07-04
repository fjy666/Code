//Code by fjy666
//luogu-judger-enable-O2
#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
#define sqr(x) ((x) * (x))
#define multiCase() int testCnt = in(); _rep(curCase,1,testCnt)
typedef long long ll;

int in(void) { int x; scanf("%d", &x); return x; }
ll inl(void) { ll x; scanf("%lld", &x); return x; }
template<typename T> void chkmax(T &a, const T &b) { a = max(a, b); } 
template<typename T> void chkmin(T &a, const T &b) { a = min(a, b); } 
const int kN = 200500;
struct Point { double x, y; int fucking_flag; } a[kN];
bool operator != (const Point &lhs, const Point &rhs) { return !(lhs.x == rhs.x && lhs.y == rhs.y); }
auto cmp1 = [](const Point &lhs, const Point &rhs) -> bool { return lhs.x < rhs.x; };
auto cmp2 = [](const Point &lhs, const Point &rhs) -> bool { return lhs.y < rhs.y; };
double dist(const Point &a, const Point &b) { return hypot(a.x - b.x, a.y - b.y); }
int l[kN], r[kN], u[kN], d[kN], ch[kN][2], n = in();

void pushup(int x) {
	l[x] = r[x] = a[x].x, u[x] = d[x] = a[x].y;
#define update(child) l[x] = min(l[x], l[child]), r[x] = max(r[x], r[child]), u[x] = max(u[x], u[child]), d[x] = min(d[x], d[child])
	if(ch[x][0]) { update(ch[x][0]); }
	if(ch[x][1]) { update(ch[x][1]); }
#undef update
}

int build(int L, int R) {
	if(L > R) return 0;
	double avx = 0, avy = 0; 
	_rep(i, L, R) avx += a[i].x, avy += a[i].y; 
	avx /= (R - L + 1), avy /= (R - L + 1);
	double fcx = 0, fcy = 0; 
	_rep(i, L, R) fcx += sqr(a[i].x - avx), fcy += sqr(a[i].y - avy);
	if(fcx >= fcy) nth_element(a + L, a + mid, a + R + 1, cmp1);
	else nth_element(a + L, a + mid, a + R + 1, cmp2);
	ch[mid][0] = build(L, mid - 1), ch[mid][1] = build(mid + 1, R);
	pushup(mid); return mid;
}

double f(int x, Point p) {
	double ans = 0.0;
	if(p.x > r[x]) ans += sqr(p.x - r[x]);
	if(p.x < l[x]) ans += sqr(p.x - l[x]);
	if(p.y > u[x]) ans += sqr(p.y - u[x]);
	if(p.y < d[x]) ans += sqr(p.y - d[x]);
	return ans;
}

double ans = 1e45;
void query(int L, int R, Point x) {
	if(L > R) return;
	if(a[mid].fucking_flag != x.fucking_flag) ans = min(ans, dist(a[mid], x));
	if(L == R) return;
	double fl = sqrt(f(ch[mid][0], x)), fr = sqrt(f(ch[mid][1], x));
	if(fl < ans && fr < ans)  {
		if(fl < fr) {
			query(L, mid - 1, x);
			if(fr < ans) query(mid + 1, R, x);
		} else {
			query(mid + 1, R, x);
			if(fl < ans) query(L, mid - 1, x);
		}
	} else {
		if(fl < ans) query(L, mid - 1, x);
		if(fr < ans) query(mid + 1, R, x);
	}
}

int main() { 
	_rep(i,1,n) scanf("%lf%lf", &a[i].x, &a[i].y), a[i].fucking_flag = i;
	build(1, n);
	_rep(i,1,n) query(1, n, a[i]);
	printf("%.4lf\n", ans);
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