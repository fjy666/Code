#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;

int in(void) { int x; scanf("%d", &x); return x; }
ll inl(void) { ll x; scanf("%lld", &x); return x; }
const int kN = 400400, kM = 100400;
int ch[kM][2], nc;

void insert(int nx) {
	int cur = 0;
	for(int i = 30; ~i; --i) {
		int v = (nx >> i) & 1;
		if(!ch[cur][v]) ch[cur][v] = ++nc;
		cur = ch[cur][v];
	}
}
int query(int x) {
	int cur = 0, res = 0;
	for(int i = 30; ~i; --i) {
		int v = (x >> i) & 1;
		if(ch[cur][v ^ 1]) cur = ch[cur][v ^ 1], res |= 1 << i;
		else cur = ch[cur][v];
	}
	return res;
}
void clear(void) {
	memset(ch, 0, sizeof(ch));
	nc = 0;
}

int lft[kN], rgt[kN], a[kN];

int main() { 
	int n = in();
	_rep(i,1,n) a[i] = in();
	insert(0);
	int xor_sum = 0;
	_rep(i,1,n) {
		lft[i] = query(xor_sum ^= a[i]); //查询 0~i-1中和 a[i] xor 起来最大的
		insert(xor_sum);
	}
	clear();
	xor_sum = 0; insert(0);
	for(int i = n; i; --i) {
		rgt[i] = query(xor_sum ^= a[i]);
		insert(xor_sum);
	}
	_rep(i, 2, n) lft[i] = max(lft[i], lft[i - 1]);
	for(int i = n - 1; i; --i) rgt[i] = max(rgt[i], rgt[i + 1]);
	int res = 0;
	_rep(i, 1, n - 1) res = max(res, lft[i] + rgt[i + 1]);
	printf("%d\n", res);
	return 0;
}