//Code by fjy666
#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;

int in(void) { int x; scanf("%d", &x); return x; }
ll inl(void) { ll x; scanf("%lld", &x); return x; }
const int kN = 1000500;
struct state { int ch[26], link, len; } sam[kN];
int last, nc;
void init(void) {
	nc = last = 0;
	sam[0].link = -1, sam[0].len = 0;
}
void extend(int c) {
	int cur = ++nc; sam[cur].len = sam[last].len + 1;
	while(~last && !sam[last].ch[c]) sam[last].ch[c] = cur, last = sam[last].link;
	if(last == -1) sam[cur].link = 0;
	else {
		int p = last, q = sam[last].ch[c];
		if(sam[p].len + 1 == sam[q].len) sam[cur].link = q;
		else {
			int clone = ++nc; sam[clone] = sam[q]; sam[clone].len = sam[p].len + 1; 
			sam[q].link = sam[cur].link = clone;
			for(; sam[last].ch[c] == q; last = sam[last].link) sam[last].ch[c] = clone;
		}
	}
	last = cur;
}
void clear(void) {
	memset(sam, 0, sizeof(sam));
}

string a[15];
int mn[kN], mx[kN], c[kN], ord[kN];

int main() { 
	int t = in();
	while(t--) {
		init();
		int n = in();
		_rep(i,1,n) cin >> a[i];
		for(auto &c : a[1]) extend(c - 'a');
		memset(c,0,sizeof(c));
		_rep(i,1,nc) ++c[sam[i].len];
		_rep(i,1,a[1].length()) c[i] += c[i - 1];
		_rep(i,1,nc) ord[c[sam[i].len]--] = i;
		memset(mn, 0x3f, sizeof(mn));
		_rep(i,2,n) {
			int cur = 0, cnt = 0;
			_rep(j,1,nc) mx[j] = 0;
			// memset(mx, 0, sizeof(mx));
			for(auto &c : a[i]) {
				if(sam[cur].ch[c - 'a']) 
					++cnt, cur = sam[cur].ch[c - 'a'];
				else {
					while(~cur && !sam[cur].ch[c - 'a']) 
						cur = sam[cur].link;
					if(cur == -1) cur = cnt = 0;
					else cnt = min(cnt + 1,sam[cur].len + 1), cur = sam[cur].ch[c - 'a'];
				}
				// printf("cnt = %d\n", cnt);
				mx[cur] = max(mx[cur], cnt);	
			}
			for(int j = nc; j; --j) {
				int u = ord[j];
				mn[u] = min(mn[u], mx[u]);
				int fa = sam[u].link;
				mx[fa] = max(mx[fa], min(sam[fa].len, mx[u])); 
			}
		}
		int res = 0;
		_rep(i,1,nc) res = max(res, mn[i]);
		printf("%d\n", res);
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