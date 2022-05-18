#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
const int kN = 205000;
int ch[kN * 24][2],siz[kN * 24],ncnt,a[kN],d[kN],rt[kN];
void pushup(int rt) { siz[rt] = siz[ch[rt][0]] + siz[ch[rt][1]]; } 
int clone(int rt) { 
	++ncnt; ch[ncnt][0] = ch[rt][0],ch[ncnt][1] = ch[rt][1],siz[ncnt] = siz[rt]; return ncnt; 
}

void insert(int &rt,int L,int R,int pos) {
	rt = clone(rt);
	if(L == R) ++siz[rt];
	else {
		if(pos <= mid) insert(ch[rt][0],L,mid,pos);
		else insert(ch[rt][1],mid + 1,R,pos);
		pushup(rt);
	}
}

int query(int rtr,int rtl,int L,int R,int k) {
	if(L == R) return L; int sizl = siz[ch[rtr][0]] - siz[ch[rtl][0]];
	if(k <= sizl) return query(ch[rtr][0],ch[rtl][0],L,mid,k);
	else return query(ch[rtr][1],ch[rtl][1],mid + 1,R,k - sizl);
}

int main() {
	int n = in(),m = in();
	_rep(i,1,n) a[i] = d[i] = in();
	sort(d + 1,d + 1 + n);
	_rep(i,1,n) a[i] = lower_bound(d + 1,d + 1 + n,a[i]) - d; //离散化
	_rep(i,1,n) {
		rt[i] = rt[i - 1];
		insert(rt[i],1,n,a[i]);
	}
	_rep(i,1,m) {
		int L = in(),R = in(),k = in(); //[L,R] k 小
		printf("%d\n",d[query(rt[R],rt[L-1],1,n,k)]);
	}
	return 0;
}
