#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
int main() {
	int ca = 0;
	while(true) {
		system("\"谈笑风生 - generator\" > data.txt");
		system("谈笑风生 < data.txt > Sol.txt");
		system("\"谈笑风生 - O(qn)\" < data.txt > Ac.txt");
		if(!system("fc Sol.txt Ac.txt > nul"))
			printf("Case %d:Accepted\n",++ca);
		else { puts("WA"); return 0; }
	} 
	return 0;
}
