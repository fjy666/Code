#include <bits/stdc++.h>
#define _rep(i_,a_,b_) for(int i_ = a_;i_ <= b_;++i_)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
using namespace std;
const int kN = 5000005;
char s[kN],t[kN];
int n,m;
int border[kN];
void prefix_function(void) {
	border[1] = 0;
	_rep(i,2,m) {
		int j = border[i - 1];
		while(j > 0 && t[j + 1] != t[i]) j = border[j];
		if(t[j + 1] == t[i]) ++j;
		border[i] = j;
	}
}
char ans[kN];
int match[kN];
int main() {
	scanf("%s%s",t + 1,s + 1);
	n = strlen(s + 1),m = strlen(t + 1);
	prefix_function();
	int mat = 0,cnt = 0,resault=0;
	_rep(i,1,n) {
		while(mat > 0 && s[i] != t[mat + 1]) mat = border[mat];
		if(s[i] == t[mat + 1]) ++mat;
		match[++cnt] = mat;
		ans[cnt] = s[i];
		if(mat == m) {
//			printf("Orz,find match on %d\n",i);
			cnt -= m;
			mat = match[cnt];
			++resault;
		}		
	}
	printf("%d\n" ,resault);
	return 0;
}