#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
const int kN = 50050;
#define get(x) ((x - 1) / 200 + 1)
struct query {
	int l,r,x,id;
	bool operator < (const query &x) const {
		return get(l) == get(x.l) ? (get(l) & 1 ? r < x.r : r > x.r) : get(l) < get(x.l);
	}
} q[kN];
int a[kN], cnt[kN];

struct Linklist {
	int L[kN],R[kN],c[kN];
	int head,tail;
	Linklist() : head(0),tail(0) {}
	void add(int pos) {
		if(!c[pos]) {
			c[pos] = 1;
			L[pos] = tail;
			R[pos] = head;
			R[tail] = pos;
			tail = pos;
		} else ++c[pos];
	}
	void del(int pos) {
		--c[pos];
		if(!c[pos]) {
			if(pos == tail) {
				tail = L[pos];
				R[tail] = head;
			} else {
				L[R[pos]] = L[pos];
				R[L[pos]] = R[pos];
			}
		}
	}
}link;

void add(int x) {
	if(cnt[a[x]]) link.del(cnt[a[x]]);
	++cnt[a[x]];
	link.add(cnt[a[x]]);
}
void del(int x) {
	link.del(cnt[a[x]]);
	--cnt[a[x]];
	if(cnt[a[x]]) link.add(cnt[a[x]]);
}

int gcd(int a,int b) {
	return !b ? a : gcd(b,a % b);
}

int ans[kN];
int main() {
	int n = in(),m = in();
	_rep(i,1,n) a[i] = in();
	_rep(i,1,m) {
		int l = in(),r = in(),x = in();
		q[i] = {l,r,x,i};
	}
	sort(q + 1,q + 1 + m);
	int l = 1,r = 0;
	
	_rep(i,1,m) {
		while(l > q[i].l) add(--l);
		while(r < q[i].r) add(++r);
		while(l < q[i].l) del(l++);
		while(r > q[i].r) del(r--);
		for(int j = link.R[link.head]; j != link.head; j = link.R[j]) 
			if(gcd(j,q[i].x) == 1)
				ans[q[i].id] += link.c[j];
	}
	_rep(i,1,m) printf("%d\n",ans[i]);
	return 0;
}
