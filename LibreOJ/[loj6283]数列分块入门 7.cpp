#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
const int kN = 100500,kb = 350,p = 10007;
#define get(x) ((x - 1) / kb + 1)
int a[kN],mul[kb],add[kb];
void free(int id) {
	//让块id的标记免费
	_rep(i,(id - 1) * kb + 1,id * kb) {
		a[i] = (a[i] * mul[id]) % p;
		a[i] = (a[i] + add[id]) % p;
	}
	mul[id] = 1,add[id] = 0;
}
void Add(int l,int r,int c) {
	for(int i = get(l) + 1; i < get(r); ++i) add[i] = (add[i] + c) % p;
	free(get(l));
	for(int i = l; i <= min(r,get(l) * kb); ++i) a[i] = (a[i] + c) % p;
	if(get(l) != get(r)) {
		free(get(r));
		for(int i = (get(r) - 1) * kb + 1; i <= r; ++i)
			a[i] = (a[i] + c) % p;
	}
} 
void Mul(int l,int r,int c) {
	for(int i = get(l) + 1; i < get(r); ++i) add[i] = (add[i] * c) % p,mul[i] = (mul[i] * c) % p;
	free(get(l));
	for(int i = l; i <= min(r,get(l) * kb); ++i) a[i] = (a[i] * c) % p;
	if(get(l) != get(r)) {
		free(get(r));
		for(int i = (get(r) - 1) * kb + 1; i <= r; ++i)
			a[i] = (a[i] * c) % p;
	}
}
int main() {
	int n = in();
	_rep(i,1,n) a[i] = in() % p;
	_rep(i,1,get(n)) mul[i] = 1,add[i] = 0;
	_rep(i,1,n) {
		int opt = in(),l = in(),r = in(),c = in();
		if(opt == 0) Add(l,r,c % p);
		if(opt == 1) Mul(l,r,c % p);
		if(opt == 2) printf("%d\n",(a[r] * mul[get(r)] + add[get(r)]) % p);
	}
	return 0;
}
