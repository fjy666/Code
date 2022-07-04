//Code by fjy666
//luogu-judger-enable-O2
#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
#define multiCase() int testCnt = in(); _rep(curCase,1,testCnt)
typedef long long ll;
typedef unsigned long long ull;

namespace FastIO {
    char OBuf[1 << 23], *p = OBuf;
    inline void pc(char c) { *p++=c; }
    inline void out(int x) { if(x < 0) pc('-'), x = -x; if(x > 9) out(x / 10); pc(x % 10 + '0'); }
    inline void out(const char *s) { if(*s) pc(*s),out(s+1); }      
    inline void flush(void) { fwrite(OBuf,p - OBuf,1,stdout); }
    struct _Flusher{ ~_Flusher(){ flush(); } } flusher;
    
	char IBuf[1 << 25], *i1 = IBuf;
    void rd(void) { fread(IBuf, 1, 1 << 25, stdin); }  
    inline char gc(void) { return *i1++; }
    inline int in(void) {
        char c = gc(); int x = 0,f = 1; while(!isdigit(c)) { if(c == '-') f = -1; c = gc(); }
        while(isdigit(c)) { x = x * 10 + c - '0', c = gc(); } return x * f;
    }
} using namespace FastIO;
 
// int in(void) { int x; scanf("%d", &x); return x; }
// ll inl(void) { ll x; scanf("%lld", &x); return x; }
template<typename T> void chkmax(T &a, const T &b) { a = max(a, b); } 
template<typename T> void chkmin(T &a, const T &b) { a = min(a, b); } 
const int kN = 300500;
vector<int> station[kN];
struct Option { int l, r, a; } q[kN];
struct Nation { int id, expect; } a[kN], q1[kN], q2[kN];
int n , m, k, ans[kN];
ull c[kN];
void add(int p, int k) { for(;p < kN; p += p & -p) c[p] += k; }
ull qry(int p) { ull a=0; for(;p; p-=p&-p) a+= c[p]; return a; }

void solve(int L, int R, int l, int r) {
	// printf("Calling solve(%d,%d, %d,%d)\n", L, R, l, r);
	if(L > R || l > r) return;
	if(L == R) { _rep(i, l, r) ans[a[i].id] = L; return; }
	_rep(i, L, mid) {
		if(q[i].l <= q[i].r) add(q[i].l, q[i].a), add(q[i].r + 1, -q[i].a);
		else add(1, q[i].a), add(q[i].r + 1, -q[i].a), add(q[i].l, q[i].a);
	}
	int p1 = 0, p2 = 0;
	_rep(i, l, r) {
		ull ans_i = 0;
		for(auto &st : station[a[i].id]) { ans_i += qry(st); if(ans_i >= a[i].expect) break; }
		// printf("id = %d, hav %lld expect %lld\n", a[i].id, ans_i, a[i].expect);
		if(ans_i < a[i].expect) 
			q2[++p2] = a[i], q2[p2].expect -= ans_i;
		else 
			q1[++p1] = a[i]; 
	}
	_rep(i, L, mid) {
		if(q[i].l <= q[i].r) add(q[i].l, -q[i].a), add(q[i].r + 1, q[i].a);
		else add(1, -q[i].a), add(q[i].r + 1, q[i].a), add(q[i].l, -q[i].a);
	}
	_rep(i,1,p1) a[l+i-1] = q1[i]; _rep(i,1,p2) a[l+p1+i-1] = q2[i];
	solve(L, mid, l, l + p1 - 1), solve(mid + 1, R, l + p1, r);
}

int main() { 
    FastIO::rd(), n = in(), m = in();
	_rep(i,1,m) station[in()].push_back(i);
	_rep(i,1,n) a[i].id = i, a[i].expect = in();
	k = in();
	_rep(i,1,k) q[i].l = in(), q[i].r = in(), q[i].a = in();
	q[++k] = Option{1, m, 1000000500}; //1e9+k
	solve(1, k, 1, n);
	_rep(i,1,n) if(ans[i] < k) out(ans[i]),pc('\n'); else out("NIE\n");
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