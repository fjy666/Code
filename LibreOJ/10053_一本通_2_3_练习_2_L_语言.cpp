#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;

int in(void) { int x; scanf("%d", &x); return x; }
ll inl(void) { ll x; scanf("%lld", &x); return x; }
const int kM = 2145149;
int ch[500][26], nc, tag[505];
char s[505], t[kM];

void insert(char *s) {
	int cur = 0; char *o = s;
	for(;*s; ++s) {
		if(!ch[cur][*s - 'a']) ch[cur][*s - 'a'] = ++nc;
		cur = ch[cur][*s - 'a'];
	}
	tag[cur] = s - o;
}

bitset<kM> bits;

int main() { 
	int n = in(), m = in();
	int max_Len = 0;
	_rep(i,1,n) {
		scanf("%s",s);
		int n = strlen(s);
		reverse(s, s + n);
		insert(s);
		max_Len = max(max_Len, n);
	}
	_rep(i,1,m) {
		bits.reset();
		bits[0] = 1;
		scanf("%s", t + 1); int l = strlen(t + 1);
		int upperbound = l;
		int last_one = 0;
		_rep(i,1,l) {
			int cur = 0;
			for(int j = i; j; --j) {
				if(!ch[cur][t[j] - 'a']) break;
				cur = ch[cur][t[j] - 'a'];
				if(tag[cur] && bits[i - tag[cur]]) {
					bits[i] = 1;
					break;
				}
			}
			if(bits[i]) last_one = i;
			if(i - last_one == max_Len) {
				upperbound = i;
				break;
			}
		}
		for(int i = upperbound; ~i; --i) if(bits[i]) {
			printf("%d\n", i);
			break;
		}
	}
	return 0;
}