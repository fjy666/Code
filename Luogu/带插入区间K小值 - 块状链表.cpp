//author: fjy666
//created time: 2022-05-17 12:10:05
#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
const int kb = 305;
struct Block {
	vector<int> v;
	int c1[305],c2[70005];
};
typedef list<Block>::iterator It;
list<Block> l;
It get_block(int &k) {
	It a = l.begin();
	while(k > a->v.size()) {
		k -= a->v.size();
		++a;
	}
	return a;
}
int query_kth(int L,int R,int k) {
	It l = get_block(L),r = get_block(R);
	static int c1[505],c2[70005];
	if(l == r) { //这个时候 R-L+1<=sqrt(n)，直接暴力
		for(int i = L - 1; i < R; ++i) ++c1[get(l->v[i])],++c2[l->v[i]];
		int b = 1;
		while(k > c1[b]) k -= c1[b],++b;
		int ans = -1;
		_rep(i,(b - 1) * kb + 1,b * kb) {
			k -= c2[i];
			if(k <= 0) { ans = i; break; }
		}
		for(int i = L - 1; i < R; ++i) --c1[get(l->v[i])],--c2[l->v[i]]; //Resume
		return ans;
	}
	for(int i = L - 1; i < l->v.size(); ++i) ++c1[get(l->v[i])],++c2[l->v[i]];
	for(int i = 0; i < R; ++i) ++c1[get(r->v[i])],++c2[r->v[i]];
	int b = 1,ans;
	while(k > c1[b] + prev(r)->c1[b] - l->c1[b]) k -= c1[b] + prev(r)->c1[b] - l->c1[b], ++b;
	_rep(i,(b - 1) * kb + 1,b * kb) {
		k -= c2[i] + prev(r)->c2[i] - l->c2[i];
		if(k <= 0) { ans = i; break; }
	}
	for(int i = L - 1; i < l->v.size(); ++i) --c1[get(l->v[i])],--c2[l->v[i]];
	for(int i = 0; i < R; ++i) --c1[get(r->v[i])],--c2[r->v[i]]; //Resume
	return ans;
}
void modify(int pos,int value) {
	It b = get_block(pos);
	int &ori = b->v[pos - 1];
	for(It i = b; i != l.end(); ++i) i->c1[get(ori)]--,i->c2[ori]--;
	ori = value;
	for(It i = b; i != l.end(); ++i) i->c1[get(ori)]++,i->c2[ori]++;
}
void insert(int pos,int value) {
	It b = get_block(pos);
	if(b == l.end()) {
		--b;
		pos = b->v.size() + 1;
	}
	b->v.insert(b->v.begin() + pos - 1,value);
	for(It i = b; i != l.end(); ++i) ++i->c1[get(value)],++i->c2[value];
	if(b->v.size() > 2 * kb) {
		//每sqrt(n)个操作会有一次，所以总复杂度为 O(nsqrt(n))
		l.emplace(next(b));
		next(b)->v = vector<int>(b->v.begin() + kb,b->v.end());
		b->v.erase(b->v.begin() + kb,b->v.end());
		memcpy(b->c1,prev(b)->c1,sizeof(b->c1));
		memcpy(b->c2,prev(b)->c2,sizeof(b->c2));
		for(auto &e : b->v) ++b->c1[get(e)],++b->c2[e];
		memcpy(next(b)->c1,b->c1,sizeof(next(b)->c1));
		memcpy(next(b)->c2,b->c2,sizeof(next(b)->c2));
		for(auto &e : next(b)->v) ++next(b)->c1[get(e)],++next(b)->c2[e];
	}
}
int a[70005];
int lastans = 0;
int main() {
	int n = in();
	_rep(i,1,n) a[i] = in() + 1;
	l.emplace_back();
	_rep(i,1,n) {
		if(i % kb == 1) {
			l.emplace_back();
			It x = prev(l.end()),y = prev(x);
			memcpy(x->c1,y->c1,sizeof(x->c1));
			memcpy(x->c2,y->c2,sizeof(x->c2));
		}
		It x = prev(l.end());
		x->v.push_back(a[i]);
		x->c1[get(a[i])]++;
		x->c2[a[i]]++;
	}
	//build
	int q = in();
	while(q--) {
		char op[5]; int x,y;
		scanf("%s%d%d",op,&x,&y);
		x ^= lastans; y ^= lastans;
//		printf("The true x = %d,y = %d\n",x,y);
		if(op[0] == 'Q') printf("%d\n", lastans = query_kth(x,y,in() ^ lastans) - 1);
		if(op[0] == 'M') modify(x,y + 1);
		if(op[0] == 'I') insert(x,y + 1);
		
//		printf("The Current List is: [");
//		for(It i = l.begin(); i != l.end(); ++i) for(auto &e : i->v) printf("%d ",e - 1);
//		printf("]\n");
	}
	return 0;
}
