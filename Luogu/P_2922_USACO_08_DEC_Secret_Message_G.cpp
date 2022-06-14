#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;

int in(void) { int x; scanf("%d", &x); return x; }
ll inl(void) { ll x; scanf("%lld", &x); return x; }
const int kN = 500500;
int ch[kN][2], nc, cnt[kN], tag[kN];
int b[kN];

void insert(void) {
	int cur = 0;
	_rep(i, 1, b[0]) {
		if(!ch[cur][b[i]]) ch[cur][b[i]] = ++nc;
		cur = ch[cur][b[i]];
	}
	++cnt[cur]; ++tag[cur];
}

void build(int x) {
	_rep(i, 0, 1) if(ch[x][i]) {
		build(ch[x][i]);
		cnt[x] += cnt[ch[x][i]]; 
	}
}

int main() { 
	int n = in();
	int m = in();
	_rep(i,1,n) {
		b[0] = in();
		_rep(j,1,b[0]) b[j] = in();
		insert();
	}
	build(0);
	_rep(i,1,m) {
		b[0] = in();
		_rep(j,1,b[0]) b[j] = in();
		int cur = 0, res = 0;
		_rep(j,1,b[0]) {
			res += tag[cur];
			if(!ch[cur][b[j]]) {
				cur = -1;
				break;
			}
			cur = ch[cur][b[j]];
		}
		if(cur != -1) res += cnt[cur];
		printf("%d\n", res);
	}
	return 0;
}