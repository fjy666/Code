#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
const int kN = 300500;
mt19937 generator((unsigned) time(0));
int delta = 0;
int ch[kN][2], v[kN], s[kN], rp[kN], ncnt, rt;
void pushup(int x) { s[x] = s[ch[x][0]] + s[ch[x][1]] + 1; }
void rotate(int &x,int d) {
	int tmp = ch[x][d ^ 1]; ch[x][d ^ 1] = ch[tmp][d]; ch[tmp][d] = x; 
	pushup(x); pushup(tmp); x = tmp;
}
void insert(int &r,int va) {
	if(!r) r = ++ncnt, v[r] = va, s[r] = 1, rp[r] = (int) generator();
	else {
		int d = va > v[r];
		insert(ch[r][d], va);
		if(rp[ch[r][d]] < rp[r]) rotate(r,d ^ 1);
		pushup(r);
	}
}
void remove(int &r,int va) {
	if(v[r] == va) {
		if(ch[r][0] && ch[r][1]) {
			int d = rp[ch[r][0]] > rp[ch[r][1]] ? 0 : 1;
			rotate(r,d); remove(ch[r][d],va);
		} else r = ch[r][0] + ch[r][1];
	} else remove(ch[r][va > v[r]],va);
	if(r) pushup(r);
}
int nxt(int r,int va) {
	if(!r) return INT_MAX;
	if(v[r] > va) return min(v[r],nxt(ch[r][0],va));
	else return nxt(ch[r][1],va);
}
int kth(int r,int k) {
	if(s[ch[r][0]] + 1 == k) return v[r];
	else if(s[ch[r][0]] >= k) return kth(ch[r][0],k);
	else return kth(ch[r][1],k - s[ch[r][0]] - 1);
}
int main() {
	int n = in(),lb = in(),cnt = 0;
	_rep(i,1,n) {
		char opt[5]; int k;
		scanf("%s%d",opt,&k);
		if(opt[0] == 'I') {
			if(k < lb) continue;
			int nx = k - delta;
			insert(rt,nx);
		} 
		if(opt[0] == 'A') delta += k;
		if(opt[0] == 'S') delta -= k;
		if(opt[0] == 'F') {
			if(k > s[rt]) puts("-1");
			else printf("%d\n",kth(rt,s[rt] - k + 1) + delta);
		}
		while(true) {
			if(s[rt] == 0) break;
			int a = kth(rt,1); if(a + delta >= lb) break;
			remove(rt,a); ++cnt;
		}
	}
	printf("%d\n",cnt);
	return 0;
}
