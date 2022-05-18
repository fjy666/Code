#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
const int kN = 3500,p = 1000000007;
char s[kN];
int f[kN][kN],d[kN][kN],sum[kN][kN];

int main() {
	int n = in();
	scanf("%s",s + 1);
	for(int i = n;i >= 1;--i) 
		for(int j = i - 1;j >= 1;--j) {
		
			if(s[i] == s[j]) d[j][i] = d[j + 1][i + 1] + 1;
			else d[j][i] = 0;
		}
	f[n][n] = 1;
	for(int i = n;i >= 1;--i) sum[n][i] = sum[n][i + 1] + f[n][i];
	for(int i = n - 1;i >= 1;--i) {
		f[i][n] = 1;
		for(int j = i; j < n; ++j) {
			int tmp = d[i][j + 1];
//			printf("tmp = %d\n",tmp);
			printf("tmp = %d\n",tmp);
			tmpfile()
			if(i + tmp <= j) f[i][j] = s[i + tmp] > s[j + 1 + tmp] ? 0 : sum[j + 1][j + 1 + tmp + 1];
			else f[i][j] = j + 1 + (j - i + 1) + 1 <= n ? sum[j + 1][j + 1 + (j - i + 1) + 1] : 0;
		}
		for(int j = n;j >= 1;--j) sum[i][j] = (sum[i][j + 1] + f[i][j]) % p;
	}
	printf("%d\n",sum[1][1]);
	return 0;
}

