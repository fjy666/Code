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
int x = in(), y = in(), k = in(), b = in();

int f[45][45][2];
int num[45], top; 
int dp(int pos, int cnt, int lim) {
	if(!pos) return cnt == k;
	if(cnt > k) return 0;
	if(f[pos][cnt][lim]) return f[pos][cnt][lim];
	int &res = f[pos][cnt][lim];
	res += dp(pos - 1, cnt, lim && (num[pos] == 0));
	if(!lim || num[pos] == 1) res += dp(pos - 1, cnt + 1, lim && (num[pos] == 1));
	return res;
}

int solve(int x) {
	memset(f, 0, sizeof(f));
	if(!x) return 0;
	top = 0;
	while(x) num[++top] = x % b, x /= b;
	for(int i = top; i >= 1; --i) if(num[i] > 1) {
		for(int j = i; j; --j) num[j] = 1;
		break;
	}
	return dp(top, 0, 1);
}

int main() { 
	printf("%d\n", solve(y) - solve(x - 1));
	return 0;
}

/* 
a list of keywords 
clear empty push_back pop_back push pop top front back
emplace_back emplace push_front pop_front insert erase
find count set reset bitset map vector string multiset
first second iterator prev next deque multimap reverse
*/