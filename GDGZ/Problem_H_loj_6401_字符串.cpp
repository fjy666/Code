//Code by fjy666
#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;

int in(void) { int x; scanf("%d", &x); return x; }
ll inl(void) { ll x; scanf("%lld", &x); return x; }
const int kN = 200500;
struct state { int ch[26], link, len; } sam[kN];
int last, nc, match[kN];
void init(void) {
	nc = last = 0;
	sam[0].link = -1, sam[0].len = 0;
}
void extend(int c, int mat) {
	int cur = ++nc; sam[cur].len = sam[last].len + 1, match[cur] = mat;
	while(~last && !sam[last].ch[c]) sam[last].ch[c] = cur, last = sam[last].link;
	if(last == -1) sam[cur].link = 0;
	else {
		int p = last, q = sam[last].ch[c];
		if(sam[p].len + 1 == sam[q].len) sam[cur].link = q;
		else {
			int clone = ++nc; sam[clone] = sam[q]; sam[clone].len = sam[p].len + 1; //match[clone] = match[q];
			sam[q].link = sam[cur].link = clone;
			for(; sam[last].ch[c] == q; last = sam[last].link) sam[last].ch[c] = clone;
		}
	}
	last = cur;
}

char s[kN];
int bad[kN], c_[kN], ord[kN];
int main() { 
	init();
	scanf("%s", s + 1);
	int n = strlen(s + 1);
	_rep(i,1,n) scanf("%1d", &bad[i]), bad[i] ^= 1;
	int k = in();
	int j = 1, cnt = 0;
	_rep(i,1,n) {
		cnt += bad[i];
		while(cnt > k) cnt -= bad[j++];
		extend(s[i] - 'a', i - j + 1);
	}
	_rep(i,1,nc) ++c_[sam[i].len];
	_rep(i,1,n) c_[i] += c_[i - 1];
	_rep(i,1,nc) ord[c_[sam[i].len]--] = i;
	ll res = 0;
	for(int i = nc; i; --i) {
		int u = ord[i];
		res += max(min(match[u], sam[u].len) - sam[sam[u].link].len, 0);
		match[sam[u].link] = max(match[sam[u].link], match[u]); 
	}
	printf("%lld\n", res);
	return 0;
}

/* 
a list of keywords 
clear empty push_back pop_back push pop top front back
emplace_back emplace push_front pop_front insert erase
find count set reset bitset map vector string multiset
first second iterator prev next deque multimap reverse
*/