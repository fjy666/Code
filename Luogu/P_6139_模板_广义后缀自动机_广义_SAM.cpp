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
const int kN = 1000400;

namespace GeneralSAM {

	struct node {
		int len, link, ch[26];
		node& operator = (const node& rhs) {
			len = rhs.len, link = rhs.link;
			memcpy(ch, rhs.ch, sizeof(ch));
			return *this;
		}
	} sam[kN << 1]; int nc;

	void init(void) {
		nc = 0, sam[0].link = -1, sam[0].len = 0;
	}

	int extend(int nod, int c) {
		if(sam[nod].ch[c]) {
			int p = sam[nod].ch[c];
			if(sam[nod].len + 1 == sam[p].len) return p;

			int clone = ++nc; sam[clone] = sam[p]; sam[clone].len = sam[nod].len + 1;
			while(~nod && sam[nod].ch[c] == p) sam[nod].ch[c] = clone, nod = sam[nod].link;
			sam[p].link = clone; return clone;
		}

		int cur = ++nc; sam[cur].len = sam[nod].len + 1;
		while(~nod && !sam[nod].ch[c]) sam[nod].ch[c] = cur, nod = sam[nod].link;
		if(nod == -1) sam[cur].link = 0;
		else {
			int q = sam[nod].ch[c];
			if(sam[q].len == sam[nod].len + 1) sam[cur].link = q;
			else {
				int clone = ++nc; sam[clone] = sam[q]; sam[clone].len = sam[nod].len + 1;
				while(~nod && sam[nod].ch[c] == q) sam[nod].ch[c] = clone, nod = sam[nod].link;
				sam[q].link = sam[cur].link = clone;
			}
		}
		return cur;
	}

	void extend(char *s) {
		int last = 0;
		while(*s) {
			last = extend(last, *s - 'a');
			++s;
		}
	}

	void solve(void) {
		ll res = 0;
		_rep(i, 1, nc) {
			// printf("sam[i].len = %d\n, link = %d\n", sam[i].len, sam[i].link);
			// printf("delta = %d\n", sam[i].len - sam[sam[i].link].len);
			res += sam[i].len - sam[sam[i].link].len;
		}
		printf("%lld\n", res);
	}

} // namespace General SAM
char buf[1005000];
int main() { 
	GeneralSAM::init();
	multiCase() {
		scanf("%s", buf);
		GeneralSAM::extend(buf);
	}
	GeneralSAM::solve();
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