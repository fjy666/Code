#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;
//int in(void) { int x; scanf("%d",&x); return x; }
//ll inl(void) { ll x; scanf("%lld",&x); return x; }

namespace FastIO { //by fjy666
	char OBuf[1 << 23], *p = OBuf;
	inline void pc(char c) { *p++=c; }
	inline void out(ll x) { if(x < 0) pc('-'), x = -x; if(x > 9) out(x / 10); pc(x % 10 + '0'); }
	inline void out(int x) { if(x < 0) pc('-'), x = -x; if(x > 9) out(x / 10); pc(x % 10 + '0'); }
	inline void out(char *s) { if(*s) pc(*s),out(s+1); }
	inline void flush(void) { fwrite(OBuf,p - OBuf,1,stdout); }
	struct _Flusher{ ~_Flusher(){ flush(); } } flusher;
	
	char IBuf[1 << 23], *i1 = IBuf,*i2 = IBuf;
	inline char gc(void) { return (i1 == i2 && (i2 = (i1 = IBuf) + fread(IBuf,1,1 << 23,stdin),i1 == i2)) ? EOF : *i1++; }
	inline int in(void) {
		char c = gc(); int x = 0,f = 1; while(!isdigit(c)) { if(c == '-') f = -1; c = gc(); }
		while(isdigit(c)) { x = x * 10 + c - '0', c = gc(); } return x * f;
	}
	inline ll inl(void) {
		char c = gc(); ll x = 0,f = 1; while(!isdigit(c)) { if(c == '-') f = -1; c = gc(); }
		while(isdigit(c)) { x = x * 10 + c - '0', c = gc(); } return x * f;
	}
} using FastIO::pc; using FastIO::out; using FastIO::gc; using FastIO::in; using FastIO::inl;


const int kN = 100500,kb = 1030;
struct Block {
	vector<int> l;
	int c1[kN],c2[kN / kb + 5];
	int h[kN + kN / 2],rh[kN + kN / 2],pool;
	Block() : pool(kN) {} 
};
vector<Block> l;
using It = vector<Block>::iterator;
int a[kN],n = in(),m = in(),cx = 0;
void Modify_bf(It& blk,int L,int R,int x,int y) { //对于块 blk [L,R] 使用暴力
	Block &b = *blk;
	if(!b.rh[x]) return; //b中不存在x这个值
	
	for(int i = L - 1; i < R; ++i) if(b.h[b.l[i]] == x)  {
		if(!b.rh[y]) { //如果b中不存在y，就新建一个表示y的值
			++b.pool;
			b.h[b.pool] = y;
			b.rh[y] = b.pool;
		}
		b.l[i] = b.rh[y]; ++cx;
		++b.c1[y], --b.c1[x], ++b.c2[get(y)], --b.c2[get(x)];
	}
	for(int i = 0;i < b.l.size(); ++i) if(b.h[b.l[i]] == x) return;
	//如果这个块里已经没有x了，就把x删了
	b.h[b.rh[x]] = 0;
	b.rh[x] = 0;
}
It get_block(int &k) {
	It tmp = l.begin();
	while(k > tmp->l.size()) {
		k -= tmp->l.size();
		++tmp;
	}
	return tmp;
}
void Modify(int L,int R,int x,int y) {
	It l = get_block(L),r = get_block(R);
	if(l == r) { 
		cx = 0;
		Modify_bf(l,L,R,x,y); 
		for(It i = next(l); i != ::l.end(); ++i) {
			i->c1[y] += cx;
			i->c1[x] -= cx;
			i->c2[get(y)] += cx;
			i->c2[get(x)] -= cx;
		}
		return; 
	}
	cx = 0;
	Modify_bf(l,L,l->l.size(),x,y); 
	for(It B = next(l); B != r; ++B) { //整块修改
		Block &b = *B;
		if(b.rh[x] && b.rh[y]) {
			int fuck = cx;
			Modify_bf(B,1,b.l.size(),x,y);
			b.c1[y] += fuck;
			b.c1[x] -= fuck;
			b.c2[get(y)] += fuck;
			b.c2[get(x)] -= fuck;
			continue;
		}
		cx += b.c1[x] - (prev(B)->c1[x] + cx);
		b.c1[y] += cx;
		b.c1[x] -= cx;
		b.c2[get(y)] += cx; 
		b.c2[get(x)] -= cx;
		
		if(!b.rh[x]) continue;
		b.h[b.rh[x]] = y;
		b.rh[y] = b.rh[x];
		b.rh[x] = 0;
	}
	int fuck = cx;
	Modify_bf(r,1,R,x,y); //散块直接暴力艹他
	r->c1[y] += fuck;
	r->c1[x] -= fuck;
	r->c2[get(y)] += fuck;
	r->c2[get(x)] -= fuck;
	for(It i = next(r); i != ::l.end(); ++i) {
		i->c1[y] += cx;
		i->c1[x] -= cx;
		i->c2[get(y)] += cx;
		i->c2[get(x)] -= cx;
	}
}
int Query_kth(int L,int R,int k) {
	static int c1[kN],c2[kN / kb + 5];
	It l = get_block(L),r = get_block(R);
	if(l == r) {
		for(int i = L - 1; i < R; ++i) {
			int v = l->h[l->l[i]];
			++c1[v],++c2[get(v)];
		}
		
		int ans = -1,b = 1;
		while(k > c2[b]) k -= c2[b],++b;
		for(int i = (b - 1) * kb + 1; i <= b * kb; ++i) {
			k -= c1[i];
			if(k <= 0) {
				ans = i;
				break;
			}
		}
		
		for(int i = L - 1; i < R; ++i) {
			int v = l->h[l->l[i]];
			--c1[v],--c2[get(v)];
		}
		return ans;
	}
	for(int i = L - 1; i < l->l.size(); ++i) {
		int v = l->h[l->l[i]];
		++c1[v],++c2[get(v)];
	}
	for(int i = 0; i < R; ++i) {
		int v = r->h[r->l[i]];
		++c1[v],++c2[get(v)];
	}
	
	int ans = -1,b = 1; It tmp = prev(r);
	while(k > c2[b] + tmp->c2[b] - l->c2[b]) 
		k -= c2[b] + tmp->c2[b] - l->c2[b],++b;
	for(int i = (b - 1) * kb + 1; i <= b * kb; ++i) {
		k -= c1[i] + tmp->c1[i] - l->c1[i];
		if(k <= 0) {
			ans = i;
			break;
		}
	}
	
	for(int i = L - 1; i < l->l.size(); ++i) {
		int v = l->h[l->l[i]];
		--c1[v],--c2[get(v)];
	}
	for(int i = 0; i < R; ++i) {
		int v = r->h[r->l[i]];
		--c1[v],--c2[get(v)];
	}
	return ans;
}
int main() {
	_rep(i,1,n) a[i] = in();
	l.emplace_back();
	_rep(i,1,n) {
		if(i % kb == 1) {
			l.emplace_back();
			It x = prev(l.end()), y = prev(x);
			memcpy(x->c1,y->c1,sizeof(x->c1));
			memcpy(x->c2,y->c2,sizeof(x->c2));
		}
		It x = prev(l.end());
		x->l.push_back(a[i]);
		++x->c1[a[i]], ++x->c2[get(a[i])];
	}
	for(Block &b : l) for(auto &ele : b.l) b.h[ele] = ele, b.rh[ele] = ele;
	_rep(i,1,m) {
		int op = in(),l = in(),r = in(),a = in(),b;
		if(op == 1) { b = in(); if(a != b) Modify(l,r,a,b); }
		else out(Query_kth(l,r,a)),pc('\n');
	}
	return 0;
}
