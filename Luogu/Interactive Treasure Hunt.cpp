#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
int SCAN(int r,int c) {
	printf("SCAN %d %d\n",r,c); fflush(stdout);
	return in();
}
int main() {
	int t = in();
	while(t--) {
		int n = in(),m = in();
		int A1 = SCAN(1,1) + 4;
		int A2 = SCAN(1,m) + 2 - 2 * m;
		int B1 = (A1 + A2) / 2,B2 = (A1 - A2) / 2;
		int C1 = SCAN(B1 / 2,1) + 2,C2 = SCAN(1,B2 / 2) + 2;
		int x2 = (A1 - C1) / 2, x1 = B1 - x2;
		int y2 = (A1 - C2) / 2, y1 = B2 - y2;
		printf("DIG %d %d\n",x1,y1);
		fflush(stdout);
		int res = in();
		if(res == 1)
			printf("DIG %d %d\n",x2,y2), fflush(stdout), in();
		else printf("DIG %d %d\nDIG %d %d\n",x1,y2,x2,y1),fflush(stdout), in(),in();
	}
	return 0;
}
