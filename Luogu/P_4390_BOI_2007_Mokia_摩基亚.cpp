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
const int kN = 2000400<<2;

struct Option { int op, x, y, z, id1, id2; } q[kN]; 
ll res[kN][4], n;

ll c[kN];
void add(int x, int y) { for(;x < kN; x += x & -x) c[x] += y; }
ll qry(int x) { ll a = 0; for(;x;x -= x & -x) a += c[x]; return a; }

void CDQ(int L, int R) {
	if(L == R) return;
	CDQ(L, mid); CDQ(mid + 1, R);
	// printf("mid=%d\n",mid);
	sort(q + L, q + mid + 1, [](const Option &a, const Option &b) -> bool { return a.x < b.x; });
	sort(q + mid + 1, q + R + 1, [](const Option &a, const Option &b) -> bool { return a.x < b.x; });
	int pl = L;
	_rep(i, mid + 1, R) if(q[i].op == 2) {
		while(pl <= mid && (q[pl].op == 2 || q[pl].x <= q[i].x)) {
			if(q[pl].op == 1) add(q[pl].y, q[pl].z);
			// printf("pl = %d(x=%d) ADD pos %d val %d\n",pl,q[pl].x,  q[pl].y, q[pl].z);
			++pl;
		}
		// printf("i=%d, QRY %d\n",i,  q[i].y);
		res[q[i].id1][q[i].id2] += qry(q[i].y);
 	}
	// memset(c, 0, sizeof(c));
	_rep(i, L, pl - 1) if(q[i].op == 1) add(q[i].y, -q[i].z);
}

int main() { 
	in(), in();
	int op = in();
	while(op != 3) {
		if(op == 1) ++n, q[n].op = 1, q[n].x = in() + 2, q[n].y = in() + 2, q[n].z = in(), q[n].id1 = n;
		else {
			int x1 = in() + 1, y1 = in() + 1, x2 = in() + 2, y2 = in() + 2;
			++n, q[n].x = x2, q[n].y = y2, q[n].id1 = n,     q[n].id2 = 0, q[n].op = 2;
			++n, q[n].x = x1, q[n].y = y2, q[n].id1 = n - 1, q[n].id2 = 1, q[n].op = 2;
			++n, q[n].x = x2, q[n].y = y1, q[n].id1 = n - 2, q[n].id2 = 2, q[n].op = 2;
			++n, q[n].x = x1, q[n].y = y1, q[n].id1 = n - 3, q[n].id2 = 3, q[n].op = 2;
		}
		op = in();
	}
	CDQ(1, n);
	sort(q + 1, q + 1 + n, [](const Option &lhs, const Option &rhs) -> bool { return lhs.id1 < rhs.id1; });
	_rep(i,1,n) if(q[i].op == 2) {
		// printf("r0 = %lld, r1 = %lld, r2 = %lld, r3 = %lld\n", res[q[i].id1][0], res[q[i].id1][1], res[q[i].id1][2], res[q[i].id1][3]);
		printf("%lld\n", res[q[i].id1][0] - res[q[i].id1][1] - res[q[i].id1][2] + res[q[i].id1][3]);
		i += 3;
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