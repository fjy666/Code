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
int n = in(), m = in() << 1; 
namespace KDTree {
	int ch[kN][2], x[kN], y[kN], l[kN], r[kN], u[kN], d[kN], nc;
	void pushup(int o) {
		#define upd(_) chkmin(l[o], l[_]), chkmin(d[o], d[_]), chkmax(r[o], r[_]), chkmax(u[o], u[_])
		l[o] = r[o] = x[o], u[o] = d[o] = y[o];
		if(ch[o][0]) upd(ch[o][0]); if(ch[o][1]) upd(ch[o][1]);
	}
	int build(int L, int R, int d) {
		if(L > R) return 0;
		if(d) nth_element(a + L, a + mid, a + R + 1, cmp2);
		else nth_element(a + L, a + mid, a + R + 1, cmp1);
		int cur = ++nc; x[cur] = a[mid].x, y[cur] = a[mid].y;
		ch[cur][0] = build(L, mid - 1, d ^ 1), ch[cur][1] = build(mid + 1, R, d ^ 1);
		pushup(cur); return cur;
	}
	priority_queue<ll, vector<ll>, greater<ll> > q;
	void ins(ll s) {
		if(q.size() < m) q.push(s);
		else if(q.top() < s) q.pop(), q.push(s);
	}
	ll sqr(ll x) { return x * x; }
	ll f(int o, int x, int y) { //估价函数
		return max(sqr(x - l[o]), sqr(x - r[o])) + max(sqr(y - u[o]),sqr(y - d[o])); 
	}
	void query(int o, int qx, int qy) {
		if(!o) return;
		ins(sqr(qx - x[o]) + sqr(qy - y[o]));
		ll f1 = f(ch[o][0], qx, qy), f2 = f(ch[o][1], qx, qy);
		if(f1 > q.top() && f2 >q.top()) {
			if(f1 > f2) {
				query(ch[o][0], qx, qy);
				if(f2 > q.top()) query(ch[o][1], qx ,qy);
			} else {
				query(ch[o][1], qx, qy);
				if(f1 > q.top()) query(ch[o][0], qx, qy);
			} 
		} else {
			if(f1 > q.top()) query(ch[o][0], qx, qy);
			if(f2 > q.top()) query(ch[o][1], qx, qy);
		}
	}
} //namespace KDTree

int main() { 
	_rep(i,1,n) a[i].x = in(), a[i].y = in();
	rt = KDTree::build(1, n, 0);
	_rep(i,1,n) KDTree::query(rt, a[i].x, a[i].y);
	printf("%lld\n", KDTree::q.top());
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