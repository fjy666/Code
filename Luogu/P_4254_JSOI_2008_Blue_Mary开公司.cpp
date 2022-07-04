//Code by fjy666
#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
#define multiCase() int testCnt; cin >> testCnt; _rep(curCase,1,testCnt)
typedef long long ll;

int in(void) { int x; scanf("%d", &x); return x; }
ll inl(void) { ll x; scanf("%lld", &x); return x; }
const int kN = 100500;
struct Line {
	double k, b; 
	double calc(int x) { return k * x + b; }
} t[kN << 2];
void insert(int x, int L, int R, Line s) {
	if(L == R) {
		if(t[x].calc(L) < s.calc(L)) t[x] = s;
		return;
	}
	if(t[x].k < s.k) {
		if(t[x].calc(mid) < s.calc(mid)) insert(x << 1, L, mid, t[x]), t[x] = s;
		else insert(x << 1 | 1, mid + 1, R, s);
	} else if(t[x].k > s.k) {
		if(t[x].calc(mid) < s.calc(mid)) insert(x << 1 | 1, mid + 1, R, t[x]), t[x] = s;
		else insert(x << 1, L, mid, s);
	} else {
		if(t[x].calc(mid) < s.calc(mid)) t[x] = s;
	}
}
double query(int x, int L, int R, int p) {
	if(p < L || R < p) return 0.0;
	if(L == R) return t[x].calc(p);
	return max({t[x].calc(p), query(x << 1, L, mid, p), query(x << 1 | 1, mid + 1, R ,p)});
}

int main() { 
	ios::sync_with_stdio(false);
	multiCase() {
		string cmd; cin >> cmd;
		if(cmd[0] == 'Q') {
			int t; cin >> t;
			printf("%d\n", floor(query(1, 1, 50000, t) / 100));
		} else {
			double k, p; cin >> k >> p;
			insert(1, 1, 50000, Line{p, k});
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