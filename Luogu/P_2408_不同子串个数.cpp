//Code by fjy666
#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;

int in(void) { int x; scanf("%d", &x); return x; }
ll inl(void) { ll x; scanf("%lld", &x); return x; }
const int kN = 100500;
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

char s[kN];
int main() { 
	init();
	int n = in();
	scanf("%s", s + 1);
	ll cnt = 0;
	_rep(i,1,n) {
		extend(s[i] - 'a');
		cnt += sam[last].len - sam[sam[last].link].len;
	}
	printf("%lld\n", cnt);
	return 0;
}

/* 
a list of keywords 
clear empty push_back pop_back push pop top front back
emplace_back emplace push_front pop_front insert erase
find count set reset bitset map vector string multiset
first second iterator prev next deque multimap reverse
*/