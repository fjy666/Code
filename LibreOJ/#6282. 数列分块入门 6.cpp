#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
const int kN = 100050,kb = 350;
#define get(x) ((x - 1) / kb + 1)
int a[kN * 2],n = in();
vector<int> b[kb]; int b_cnt;
inline void rebuild(void) {
	int k = 0;
	_rep(i,1,b_cnt) for(auto element: b[i]) a[++k] = element;
	b_cnt = get(k); _rep(i,1,b_cnt) b[i].clear();
	_rep(i,1,k) b[get(i)].push_back(a[i]);
}
void insert(int pos,int num) {
	pos--; int i;
	for(i = 1;i <= b_cnt;++i) { 
		if(b[i].size() >= pos) break; 
		pos -= b[i].size(); 
	}
	//在第i块中pos位后插入num
	b[i].insert(b[i].begin() + pos,num);
}
int query(int pos) {
	int i;
	for(i = 1;i <= b_cnt;++i) {
		if(b[i].size() >= pos) break;
		pos -= b[i].size();
	}
	return b[i][pos - 1];
}
int main() {
	_rep(i,1,n) a[i] = in();
	_rep(i,1,n) b[get(i)].push_back(a[i]);
	b_cnt = get(n);
	
	int m = n;
	_rep(i,1,m) {
		int opt = in(),l = in(),r = in(),c = in();
		if(opt == 0) insert(l,r);
		else printf("%d\n",query(r));
		if(i % kb == 0) rebuild();
	}
	return 0;
}
