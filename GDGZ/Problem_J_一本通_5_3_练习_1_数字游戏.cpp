//Code by fjy666
#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
#define multiCase() int testCnt = in(); _rep(curCase,1,testCnt)
typedef long long ll;

int in(void) { int x; scanf("%d", &x); return x; }
ll inl(void) { ll x; scanf("%lld", &x); return x; }

int l, r, b;
int f[12][105];
int num[12], top;
int dp(int pos,int sum,int lim) {
	// printf("Call (%d,%d,%d)\n", pos, sum, lim);
	if(!pos) return sum == 0;
	if(!lim && ~f[pos][sum]) return f[pos][sum];
	if(!lim) {
		int &ref = f[pos][sum]; ref = 0;
		_rep(i,0,(lim ? num[pos] : 9)) {
			ref += dp(pos - 1,(sum + i) % b, lim && (i == num[pos]));
		}
		return ref;
	} else {
		int ref = 0;
		_rep(i,0,(lim ? num[pos] : 9)) {
			ref += dp(pos - 1,(sum + i) % b, lim && (i == num[pos]));
		}
		return ref;
	}
}
int solve(int x) { if(!x) return 1;
	top = 0;
	while(x) num[++top] = x % 10, x /= 10;
	return dp(top, 0, 1);
}

int main() { 
	while(~scanf("%d%d%d", &l, &r, &b)) {
		memset(f, -1, sizeof(f));
		printf("%d\n", solve(r) - solve(l - 1));
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