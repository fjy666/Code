#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
const int P = 131,mod = 19260817;
ll hsh[3005],pw[3005],hsh2[3005];
ll hs1(int l,int r) { return (hsh[r] - hsh[l - 1] * pw[r - l + 1] % mod + mod) % mod; }
ll hs2(int l,int r) { return (hsh2[l] - hsh2[r + 1] * pw[r - l + 1] % mod + mod) % mod;  }
bool ispalin(int l,int r) { return hs1(l,r) == hs2(l,r); }
char s[3005];
int main() {
	int n = in();
	scanf("%s",s + 1);
	_rep(i,1,n) hsh[i] = (hsh[i - 1] * P + s[i] - 'A') % mod;
	for(int i = n;i >= 1; --i) hsh2[i] = (hsh2[i + 1] * P + s[i] - 'A') % mod;
	pw[0] = 1; _rep(i,1,n) pw[i] = pw[i - 1] * P % mod;
	int ans = 0;
//	printf("%d\n",ispalin(1,n));
	_rep(l,1,n) {
		int cnt = 0;
		for(int r = l + 2;r <= n;++r) {	
			if(s[r - 2] == 'C' && s[r - 1] == 'S' && s[r] == 'P') {
				++cnt;
			}
			if(ispalin(l,r)) ans = max(ans,cnt);
		}
	}
	printf("%d\n",ans);
	return 0;
}
