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
const int kN = 505, kM = 60500; 
struct MatrixElement {
	int x, y, z;
	bool operator < (const MatrixElement &rhs) const {
		return z < rhs.z;
	}
} a[kN * kN];

struct Query {
	int x1, y1, x2, y2, k, id;
} q[kM], q1[kM], q2[kM];
int res[kM];

struct FenwickTree {
	int c[kN][kN];
	void add(int x, int y, int z) { for(;x<kN;x+=x&-x)for(int q=y;q<kN;q+=q&-q)c[x][q]+=z; }
	int qry(int x, int y) { int a=0;for(;x;x-=x&-x)for(int q=y;q;q-=q&-q)a+=c[x][q];return a; }
	int qry(int x1,int y1,int x2,int y2) { return qry(x2,y2)-qry(x1-1,y2)-qry(x2,y1-1)+qry(x1-1,y1-1); }
} t;

void solve(int L, int R, int l, int r) {
	if(L > R || l > r) return;
	if(L == R) { _rep(i, l, r) res[q[i].id] = a[L].z; return; }
	int cnt1 = 0, cnt2 = 0;
	_rep(i, L, mid) t.add(a[i].x, a[i].y, 1);
	_rep(i,l,r) {
		int ans = t.qry(q[i].x1, q[i].y1, q[i].x2, q[i].y2);
		if(ans >= q[i].k) q1[++cnt1] = q[i];
		else q2[++cnt2] = q[i], q2[cnt2].k -=
	}
	_rep(i, L, mid) t.add(a[i].x, a[i].y, -1);
	_rep(i,1,cnt1) q[l+i-1] = q1[i]; _rep(i,1,cnt2) q[l+cnt1+i-1] = q2[i];
	solve(L, mid, l, l + cnt1 - 1); solve(mid + 1, R, l + cnt1, r);
}

int main() { 
	int n = in(), m = in();
	_rep(i,1,n) _rep(j,1,n) {
		int id = (i - 1) * n + j;
		a[id].x = i, a[id].y = j, a[id].z = in();
	}
	sort(a + 1, a + 1 + n * n);
	_rep(i,1,m) q[i].x1 = in(), q[i].y1 = in(), q[i].x2 = in(), q[i].y2 = in(), q[i].k = in();
	_rep(i,1,m) q[i].id = i;
	solve(1, n * n, 1, m);
	_rep(i,1,m) printf("%d\n", res[i]);
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