#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
const int kN = 105,p = 10000000; //压7位
int a[kN][kN],n = in();
int f[kN][kN][25];
void add(int i,int j,int k,int l) { //f[k][l] += f[i][j]
	f[k][l][0] = max(f[k][l][0],f[i][j][0]);
	_rep(_,1,f[k][l][0]) {
		f[k][l][_] += f[i][j][_];
		if(f[k][l][_] >= p) {
			f[k][l][_] -= p;
			++f[k][l][_ + 1];
		} 
	}
	if(f[k][l][f[k][l][0] + 1]) ++f[k][l][0];
}
void pr(int x,int y) {
	if(f[x][y][0] == 0) {
		printf("0");
		return;
	}
	printf("%d",f[x][y][f[x][y][0]]);
	for(int i = f[x][y][0] - 1;i;--i) printf("%07d",f[x][y][i]);
}
int main() {
	_rep(i,1,n) _rep(j,1,n) a[i][j] = in();
	f[1][1][0] = 1,f[1][1][1] = 1;
	_rep(i,1,n) _rep(j,1,n) if(a[i][j] != 0) {
//		if((i + a[i][j] == n && j == n) || (i == n && j + a[i][j] == n))
//			puts("Error");
		if(i + a[i][j] <= n) add(i,j,i + a[i][j],j);
		if(j + a[i][j] <= n) add(i,j,i,j + a[i][j]);
//		printf("(%d,%d) ",i,j);
//		pr(i,j),putchar('\n');
	}
	pr(n,n);
	return 0;
}
