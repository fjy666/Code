#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;

int in(void) { int x; scanf("%d", &x); return x; }
ll inl(void) { ll x; scanf("%lld", &x); return x; }
const int kN = 1006000;
char s[kN]; int sa[kN], x[kN], y[kN], c[kN], n;
void suffixSort(void) {
	int m = 257;
	_rep(i,1,m) c[i] = 0;
	_rep(i,1,n) ++c[x[i] = s[i]]; _rep(i,1,m) c[i] += c[i - 1];
	_rep(i,1,n) sa[c[x[i]]--] = i;
	x[n + 1] = y[n + 1] = 0;
	for(int k = 1; k <= n; k <<= 1) {
		int num = 0;
		_rep(i,n - k + 1,n) y[++num] = i;
		_rep(i,1,n) if(sa[i] > k) y[++num] = sa[i] - k;
		_rep(i,1,m) c[i] = 0; _rep(i,1,n) ++c[x[i]]; _rep(i,1,m) c[i] += c[i - 1];
		for(int i = n;i;--i) sa[c[x[y[i]]]--] = y[i], y[i] = 0;
		swap(x,y); x[sa[1]] = num = 1;
		_rep(i,2,n) x[sa[i]] = (y[sa[i]] == y[sa[i-1]] && y[sa[i]+k] == y[sa[i-1]+k]) ? num : ++num;
		m = num; if(m == n) break;	
	}
} 
int rk[kN], h[kN];
void getHeight(void) {
	_rep(i,1,n) rk[sa[i]] = i;
	int k = 0;
	_rep(i,1,n) {
		if(k) --k;
		int j = sa[rk[i] - 1];
		while(j + k <= n && i + k <= n && s[j + k] == s[i + k]) ++k;
		h[rk[i]] = k;
	}
}

int m; 
int exist(int x) { //是否存在长度为 x 的出现至少 m 次的字符串
	deque<int> dq, saq; saq.push_back(1); 
	const int Len = m - 1;
	int res = 0;
	_rep(i,2,n) {
		while(!dq.empty() && dq.front() <= i - Len) dq.pop_front();
		while(!dq.empty() && h[dq.back()] >= h[i]) dq.pop_back();
		while(!saq.empty() && saq.front() <= i - m) saq.pop_front();
		while(!saq.empty() && sa[saq.back()] <= sa[i]) saq.pop_back();
		dq.push_back(i); saq.push_back(i);
		if(i - 1 >= Len && h[dq.front()] >= x) res = max(res, sa[saq.front()]);
	}
	return res;
}

int main() {
	while(m = in()) {
		scanf("%s", s + 1);
		n = strlen(s + 1);
		if(m == 1) {
			printf("%d %d\n", n, 0);
			continue;
		}
		suffixSort();
		getHeight();
		// _rep(i,1,n) printf("h[%d] = %d\n", i, h[i]);
		int L = 1, R = n, res = -1, res2 = -1;
		while(L <= R) {
			int tmp = exist(mid);
			if(tmp) res2 = tmp, res = mid, L = mid + 1;
			else R = mid - 1;
		}
		if(res == -1) {
			puts("none");
		} else {
			printf("%d %d\n", res, res2 - 1);
		}
	}
	return 0;
}


/* 
a list of keywords
clear empty push_back pop_back push pop top front back
emplace_back emplace push_front pop_front insert erase
find count set reset bitset map vector string multiset
*/