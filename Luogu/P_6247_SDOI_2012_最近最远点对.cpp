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
double sqr(double x) { return x * x; }
struct Point { double x, y; } a[kN];
auto cmp1 = [](const Point &lhs, const Point &rhs) -> bool { return lhs.x < rhs.x; };
auto cmp2 = [](const Point &lhs, const Point &rhs) -> bool { return lhs.y < rhs.y; };
namespace KDTree {
	double x[kN], y[kN], l[kN], r[kN], u[kN], d[kN];
	int nc, ch[kN][2]; 
	void pushup(int o) {
		#define upd(ch) chkmax(r[o], r[ch]), chkmax(u[o], u[ch]), chkmin(l[o], l[ch]), chkmin(d[o], d[ch])
		l[o] = r[o] = x[o], u[o] = d[o] = y[o];
		if(ch[o][0]) upd(ch[o][0]); if(ch[o][1]) upd(ch[o][1]);
		#undef upd 
	}
	int build(int L, int R, int d) {
		if(L > R) return 0; 
		if(d) nth_element(a + L, a + mid, a + R + 1, cmp1); 
		else nth_element(a + L, a + mid, a + R + 1, cmp2);
		int cur = ++nc;   x[cur] = a[mid].x, y[cur] = a[mid].y;
		ch[cur][0] = build(L, mid - 1, d ^ 1); ch[cur][1] = build(mid + 1, R, d ^ 1);
		return pushup(cur), cur;
	}
	double fMin(int o, double qx, double qy) { //欧几里得距离估值最小值
		return sqr(max({l[o] - qx, qx - r[o], 0.0})) + sqr(max({d[o] - qy, qy - u[o], 0.0}));
	}
	double ansMin;
	void qMin(int o, double qx, double qy) {
		if(!o) return;
		if(qx != x[o] || qy != y[o]) chkmin(ansMin, sqr(qx - x[o]) + sqr(qy - y[o]));
		double f1 = fMin(ch[o][0], qx, qy), f2 = fMin(ch[o][1], qx, qy);
		if(f1 < ansMin && f2 < ansMin) {
			if(f1 < f2) {
				qMin(ch[o][0], qx, qy);
				if(f2 < ansMin) qMin(ch[o][1], qx, qy);
			} else {
				qMin(ch[o][1], qx, qy);
				if(f1 < ansMin) qMin(ch[o][0], qx, qy);
			}
		} else {
			if(f1 < ansMin) qMin(ch[o][0], qx, qy);
			if(f2 < ansMin) qMin(ch[o][1], qx, qy);
		}
	}
	double fMax(int o, double qx, double qy) {
		return max(sqr(l[o] - qx), sqr(r[o] - qx)) + max(sqr(d[o] - qy), sqr(u[o] - qy));
	}
	double ansMax;
	void qMax(int o, double qx, double qy) {
		if(!o) return;
		if(qx != x[o] || qy != y[o]) chkmax(ansMax, sqr(qx - x[o]) + sqr(qy - y[o]));
		double f1 = fMax(ch[o][0], qx, qy), f2 = fMax(ch[o][1], qx, qy);
		if(f1 > ansMax && f2 > ansMax) {
			if(f1 > f2) {
				qMax(ch[o][0], qx, qy);
				if(f2 > ansMax) qMax(ch[o][1], qx, qy);
			} else {
				qMax(ch[o][1], qx, qy);
				if(f1 > ansMax) qMax(ch[o][0], qx, qy);
			}
		} else {
			if(f1 > ansMax) qMax(ch[o][0], qx, qy);
			if(f2 > ansMax) qMax(ch[o][1], qx, qy);
		}
	}
}

int main() { 
	int n = in();
	_rep(i,1,n) scanf("%lf%lf", &a[i].x, &a[i].y);
	KDTree::build(1, n, 0);
	KDTree::ansMin = 1e45, KDTree::ansMax = 0;
	_rep(i,1,n) KDTree::qMin(1, a[i].x, a[i].y), KDTree::qMax(1, a[i].x, a[i].y);
	printf("%.6lf %.6lf\n", sqrt(KDTree::ansMin), sqrt(KDTree::ansMax));
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