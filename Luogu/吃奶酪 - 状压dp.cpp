#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
const int kN = 16;
double x[kN],y[kN];
inline double dis(int i,int j) { return sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j])); }
double f[kN][1 << kN];
int pw[1 << kN];
int main() {
	int n = in(); 
	_rep(i,1,n) scanf("%lf%lf",&x[i],&y[i]);
	_rep(i,1,n) f[i][1 << (i - 1)] = dis(0,i);
	_rep(i,0,n - 1) pw[1 << i] = i + 1;
	for(int i = 0;i < (1 << n);++i) if(__builtin_popcount(i) > 1) _rep(j,1,n) if(i & (1 << (j - 1))) {
		f[j][i] = 1e114;
		for(int k = 1;k <= n;++k) if((i & (1 << (k - 1))) && (k != j)) f[j][i] = min(f[j][i],f[k][i ^ (1 << (j - 1))] + dis(j,k));
//		printf("f[%d][%d] = %.3f\n",j,i,f[j][i]);
	}
	double res = 1e114;
	_rep(i,1,n) res = min(res,f[i][(1 << n) - 1]);
	printf("%.3f\n",res);
	return 0;
}
