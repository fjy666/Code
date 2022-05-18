#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
const int kN = 200500;
map<int,int> mp; //没看题面，打个补丁/xk
mt19937 generator((unsigned) time(nullptr));
int f[kN];
int find(int x) { return f[x] == x ? x : f[x] = find(f[x]); }

int ch[kN][2],siz[kN],v[kN],ncnt,rp[kN];
int rubbish[kN],top;
void pushup(int x) { siz[x] = siz[ch[x][0]] + siz[ch[x][1]] + 1; }
void rotate(int &x,int d) {
	int tmp = ch[x][d ^ 1]; ch[x][d ^ 1] = ch[tmp][d]; ch[tmp][d] = x; pushup(x); pushup(tmp); x = tmp;
}

void insert(int &x,int va) {
	if(!x) x = (top ? rubbish[top--] : ++ncnt),
		ch[x][0] = ch[x][1] = 0,siz[x] = 1,v[x] = va,rp[x] = (int) generator();
	else {
		int d = va > v[x];
		insert(ch[x][d],va);
		if(rp[ch[x][d]] < rp[x]) rotate(x,d ^ 1);
		pushup(x);
	}
}

int get(int rt,int k) {
	if(siz[rt] < k) return -1;
	if(siz[ch[rt][0]] + 1 == k) return v[rt];
	else if(siz[ch[rt][0]] >= k) return get(ch[rt][0],k);
	else return get(ch[rt][1],k - siz[ch[rt][0]] - 1);
}

int rt[kN];
void merge(int rt1,int id) {
	if(!rt1) return;
	insert(rt[id], v[rt1]);
	merge(ch[rt1][0],id); merge(ch[rt1][1],id);
	rubbish[++top] = rt1;
}

void link(int a,int b) {
	int fa = find(a), fb = find(b);
	if(siz[rt[fa]] > siz[rt[fb]]) swap(fa,fb);
	f[fa] = fb;
	merge(rt[fa],fb);
	
}

void debug(int rt) { if(rt) debug(ch[rt][0]), printf("%d ",v[rt]), debug(ch[rt][1]); }

int main() {
	int n = in(),m = in();
	_rep(i,1,n) f[i] = i;
	_rep(i,1,n) {
		int qwq = in();
		insert(rt[i],qwq);
		mp[qwq] = i;
	}
	mp[-1] = -1;
	_rep(i,1,m) {
		int a = in(),b = in();
		if(find(a) == find(b)) continue;
		link(a,b);
	}
	int q = in();
	while(q--) {
		char opt[5]; int x,y;
		scanf("%s%d%d",opt,&x,&y);
		if(opt[0] == 'B') {
			if(find(x) == find(y)) continue;
			link(x,y);
		} else {
			int f = find(x);
//			printf("["); debug(rt[f]); puts("]");
			printf("%d\n",mp[get(rt[f],y)]);
		}
	}
	return 0;
}
