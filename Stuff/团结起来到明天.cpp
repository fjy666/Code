#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;

int in(void) { int x; scanf("%d", &x); return x; }
ll inl(void) { ll x; scanf("%lld", &x); return x; }
const int kN = 150000, kb = 400;
int a[kN], n = in(), m = in();

struct Block { int order[kb + 10],tag[kb + 10],size,rev,nxt; } b[kb];
int freenode;
int get_block(int &k) {
	int cur = head;
	while(k > b[head].size) {
		k -= b[head].size;
		head = b[head].nxt;
	}
	return it;
}
void build(void) {
	int cur = 0;
	_rep(i,1,n) {
		if(i % kb == 1) {

		}
		list<Block>::iterator it = prev(l.end());
		++it->size; it->order[it->size] = a[i];
	}
	vector<pair<int,int> > tmp;
	for(list<Block>::iterator it = l.begin(); it != l.end(); ++it) {
		tmp.clear();
		_rep(i, 1, it->size) tmp.emplace_back(it->order[i], i);
		sort(tmp.begin(), tmp.end());
		_rep(i, 1, it->size) it->order[i] = tmp[i - 1].first, it->tag[i] = tmp[i - 1].second;
		it->rev = 0;
	}
}

void pushdown(list<Block>::iterator it) { if(it->rev) {
	_rep(i,1,it->size) it->tag[i] = it->size - it->tag[i] + 1;
	it->rev = 0;
} }

void reverse(int l,int r) {
	list<Block>::iterator L = get_block(l), R = get_block(r);\
	pushdown(L), pushdown(R);
	if(L == R) {
		static int a[kb];
		_rep(i, 1, L->size) a[L->tag[i]] = L->order[i];
		reverse(a + l, a + r + 1);
		vector<pair<int,int> > tmp;
		_rep(i, 1, L->size) tmp.emplace_back(a[i], i);
		sort(tmp.begin(), tmp.end());
		_rep(i, 1, it->size) it->order[i] = tmp[i - 1].first, it->tag[i] = tmp[i - 1].second;
		it->tag = 0;
		return;
	} 
	if(l != 1) { //split
		Block lb, nb; lb.size = nb.size = 0;
		_rep(i, 1, L->size) {
			if(L->tag[i] < l) {
				++lb.size;
				lb.order[lb.size] = L->order[i];
				lb.tag[lb.size] = L->tag[i];
			} else {
				++nb.size;
				nb.order[nb.size] = L->order[i];
				nb.tag[nb.size] = L->tag[i];
			}
		}
		_rep(i, 1, nb.size) nb.tag[i] -= lb.size;
		::l.emplace_back(next(L), nb);
		*L = lb; L = next(L);
	}
	if(r != R->size) { //split
		Block lb, nb; lb.size = nb.size = 0;
		_rep(i,1,R->size) {
			if(R->tag[i] > r) {
				++lb.size;
				lb.order[lb.size] = R->order[i];
				lb.tag[lb.size] = R->tag[i];
			} else {
				++nb.size;
				nb.order[nb.size] = R->order[i];
				nb.tag[nb.size] = R->tag[i];
			}
		}
		_rep(i, 1, lb.size) lb.tag[i] -= nb.size;
		::l.emplace_back(R, nb);
		*R = lb; R = prev(R);
	}
	::l.reverse
}

int query(int l, int r, int k) {
	list<Block>::iterator L = get_block(l), R = get_block(r);
	pushdown(L), pushdown(R);
	if(L == R) {
		int res = 0;
		_rep(i, 1, L->size) if(l <= L->tag[i] && L->tag[i] <= r && L->order[i] < k) ++res;
		return res;
	}
	int cnt = 0;
	_rep(i,1,L->size) if(L->tag[i] >= l && L->order[i] < k) ++res;
	_rep(i,1,R->size) if(R->tag[i] <= r && R->order[i] < k) ++res;
	for(auto it = next(L); it != R; ++it) {
		if(it->order[1] >= k) continue;
		if(it->order[it->size] < k) {
			res += it->size;
			continue;
		}
		res += it->lower_bound(it->order + 1, it->order + 1 + it->size, k) - it->order;
	} 
	return res;
}

int main() { 
	_rep(i,1,n) a[i] = in();
	build();
	_rep(i,1,m) {
		int op = in(), l = in(), r = in();
		if(op == 1) reverse(l,r);
		else {
			int L = 1, R = 100000, res = -1, k = in();
			while(L <= R) {
				int mans = query(l, r, mid);
				if(mans >= k) R = mid - 1;
				else L = mid + 1, res = mid;
			}
			printf("%d\n", res);
		}
	}
	return 0;
}