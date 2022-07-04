#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
// #define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;

int in(void) { int x; scanf("%d", &x); return x; }
ll inl(void) { ll x; scanf("%lld", &x); return x; }
const int kN = 2006000;
int s[kN]; int sa[kN], x[kN], y[kN], c[kN], n, bel[kN];
void suffixSort(void) {
	int m = 1145;
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

int stringcnt,kase = 0;
bool calculate(int L, int R) { //min{h[L], h[L+1], h[L+2], ......, h[R]} 
	if((R - L + 2) <= (stringcnt / 2)) return false;
	static int flag[105];
	memset(flag, 0, sizeof(flag));
	int cnt = 0;
	_rep(i,L,R) {
		if(!flag[bel[sa[i]]]) {
			++cnt;
			flag[bel[sa[i]]] = 1;
		}
		if(!flag[bel[sa[i - 1]]]) {
			++cnt;
			flag[bel[sa[i - 1]]] = 1;
		}
	}
	return cnt > (stringcnt / 2);
}
string add(int L, int R) {
	int len = *min_element(h + L, h + R + 1);
	string ans = "";
	_rep(i, sa[L], sa[L] + len - 1) ans += (char) s[i];
	return ans;
}
int getAns(int mid, vector<string> &rtn) { //返回所有长度为mid且满足条件的东西
	vector<string> ans; ans.clear();
	int L = 2;
	while(L <= n) {
		while(L <= n && h[L] < mid) ++L;
		if(L > n) break;
		int R = L;
		while(R < n && h[R + 1] >= mid) ++R;
		if(calculate(L,R)) ans.push_back(add(L,R));
		// printf("L = %d, R = %d\n",L,R);
		L = R + 1;
	}
	if(ans.size()) rtn = ans;
	return ans.size();
}

char tmp[kN];
int main() { 
	while(stringcnt = in()) {
		if(++kase > 1) puts("");
		int sep = 300, cnt = 0, R = 0;
		_rep(i,1,stringcnt) {
			scanf("%s", tmp + 1);
			int len = strlen(tmp + 1);
			_rep(j,1,len) s[++cnt] = tmp[j], bel[cnt] = i;
			s[++cnt] = sep++; bel[cnt] = 0;
			R = max(R, len);
		}
		n = cnt;
		suffixSort(), getHeight();
		int L = 1; vector<string> ans;
		while(L <= R) {
			int mid = (L + R) >> 1;
			// printf("%d\n", mid);
			if(getAns(mid, ans)) {
				L = mid + 1;
			}
			else R = mid - 1;
		}
		if(!ans.size()) puts("?");
		else for(auto &s : ans) printf("%s\n", s.c_str());
	}
	return 0;
}