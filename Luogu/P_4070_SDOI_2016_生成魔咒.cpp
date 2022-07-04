//Code by fjy666
#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;

int in(void) { int x; scanf("%d", &x); return x; }
ll inl(void) { ll x; scanf("%lld", &x); return x; }
const int kN = 2000600;
struct state {
	int len, link;
	map<int,int> trans;
} sam[kN];
int nc, last;

void init(void) {
	sam[0].link = -1, sam[0].len = 0;
	nc = 0, last = 0;
}
void extend(int c) {
	int cur = ++nc; sam[cur].len = sam[last].len + 1;
	while(~last && !sam[last].trans.count(c)) sam[last].trans[c] = cur, last = sam[last].link;
	if(last == -1) sam[cur].link = 0;
	else {
		int q = sam[last].trans[c];
		if(sam[q].len == sam[last].len + 1) sam[cur].link = q;
		else {
			int clone = ++nc; sam[clone] = sam[q];
			sam[clone].len = sam[last].len + 1;
			sam[q].link = sam[cur].link = clone;
			while(~last && sam[last].trans[c] == q) sam[last].trans[c] = clone, last = sam[last].link;
		}
	}
	last = cur;
}

ll res;
int main() { 
	int n = in();
	init();
	_rep(i,1,n) {
		extend(in());
		res += sam[last].len - sam[sam[last].link].len;
		printf("%lld\n", res);
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