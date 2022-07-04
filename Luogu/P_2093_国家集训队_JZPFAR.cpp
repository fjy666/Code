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
struct Point { int x, y, id; } a[kN];
auto cmp1 = [](const Point &lhs, const Point &rhs) -> bool { return lhs.x < rhs.x; };
auto cmp2 = [](const Point &lhs, const Point &rhs) -> bool { return lhs.y < rhs.y; };
//麻了这两玩意每次都打这次直接从上一题贺/kx
ll sqr(ll x) { return x * x; }

namespace KDTree {
	int x[kN], y[kN], u[kN], d[kN], l[kN], r[kN], ch[kN][2], nc, id[kN];
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
		int cur = ++nc; x[cur] = a[mid].x, y[cur] = a[mid].y, id[cur] = a[mid].id;
		ch[cur][0] = build(L, mid - 1, d ^ 1); ch[cur][1] = build(mid + 1, R, d ^ 1);
		return pushup(cur), cur;
	}

	int qx, qy, k;	
	ll dist(int x, int y, int dx, int dy) { return sqr(x-dx)+sqr(y-dy); }
	struct cmp {
		bool operator ()(const int &a, const int &b) {
			ll da = dist(x[a], y[a], qx, qy), db = dist(x[b], y[b], qx, qy);
			return da != db ? da > db : id[a] < id[b];
		} 
	}compare;
	priority_queue<int, vector<int>, cmp> pq;
	void ins(int o) {
		// printf("Try to insert %d(%d,%d,id%d)\n", o, x[o], y[o], id[o]);
		if(pq.size() < k) pq.push(o); //, printf("IN(%d,%d)%d\n", x[o], y[o], id[o]);
		else {
			// printf("Cmp %d(%d,%d,id%d) %d(%d,%d,id%d)\n", o, x[o], y[o], id[o], pq.top(), x[pq.top()], y[pq.top()], id[pq.top()]);	
			if(compare(o, pq.top())) {
				pq.pop(), pq.push(o); //, printf("IN(%d,%d)%d\n", x[o], y[o], id[o]);
			}
		}
	}
	ll f(int o) {
		return sqr(max(abs(l[o] - qx), abs(r[o] - qx))) + sqr(max(abs(u[o] - qy), abs(d[o] - qy)));
	}
	void query(int o) {
		if(!o) return;
		ins(o);
		ll f1 = f(ch[o][0]), f2 = f(ch[o][1]);
		if(pq.size() < k) {
			if(f1 >= f2) {
				query(ch[o][0]);
				if(pq.size() < k || f2 >= dist(qx, qy, x[pq.top()], y[pq.top()])) query(ch[o][1]);
			} else {
				query(ch[o][1]);
				if(pq.size() < k || f1 >= dist(qx, qy, x[pq.top()], y[pq.top()])) query(ch[o][0]);
			}
			return;
		}
		if(f1 >= dist(qx, qy, x[pq.top()], y[pq.top()]) && f2 >= dist(qx, qy, x[pq.top()], y[pq.top()])) {
			if(f1 >= f2) {
				query(ch[o][0]);
				if(f2 >= dist(qx, qy, x[pq.top()], y[pq.top()])) query(ch[o][1]);
			} else {
				query(ch[o][1]);
				if(f1 >= dist(qx, qy, x[pq.top()], y[pq.top()])) query(ch[o][0]);
			}
		} else {
			if(f1 >= dist(qx, qy, x[pq.top()], y[pq.top()])) query(ch[o][0]);
			if(f2 >= dist(qx, qy, x[pq.top()], y[pq.top()])) query(ch[o][1]);
		}
	}
}

int n = in();
int main() { 
	_rep(i,1,n) a[i].x = in(), a[i].y = in(), a[i].id = i;
	KDTree::build(1, n, 0);
	multiCase() {
		KDTree::qx = in(), KDTree::qy = in(), KDTree::k = in();
		while(!KDTree::pq.empty()) KDTree::pq.pop();
		// KDTree::x[0] = KDTree::qx, KDTree::y[0] = KDTree::qy,KDTree::id[0] = n + 1;
		// _rep(i,1,KDTree::k) KDTree::pq.push(0);
		KDTree::query(1);
		printf("%d\n", KDTree::id[KDTree::pq.top()]);
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