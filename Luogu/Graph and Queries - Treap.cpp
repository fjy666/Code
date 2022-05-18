#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
const int kN = 200050;

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

void remove(int &x,int va) {
	if(v[x] == va) {
		if(ch[x][0] && ch[x][1]) {
			int d = rp[ch[x][0]] > rp[ch[x][1]] ? 0 : 1;
			rotate(x,d);
			remove(ch[x][d], va);
		} else x = ch[x][0] + ch[x][1];
	} else remove(ch[x][va > v[x]],va);
	if(x) pushup(x);
}

int get(int rt,int k) {
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
	if(fa == fb) return;
	if(siz[rt[fa]] > siz[rt[fb]]) swap(fa,fb);
	f[fa] = fb;
	merge(rt[fa],fb);
}

void debug(int rt) { if(rt) debug(ch[rt][0]), printf("%d ",v[rt]), debug(ch[rt][1]); }

struct query {
	string cmd;
	int x,y;
} q[500000];

int kase = 0,p[kN],a[kN],b[kN],removed[kN],n,m;
bool solve(void) {
	n = in(), m = in();
	if(!n && !m) return false;
	_rep(i,1,n) p[i] = in(),f[i] = i;//,rt[i] = 0;
	_rep(i,1,m) a[i] = in(),b[i] = in();
	string cmd;
	int Q = 0;
	while(cin >> cmd) {
		if(cmd == "E") break;
		++Q; q[Q].cmd = cmd;
		if(cmd == "D") {
			int id = in();
			removed[id] = 1;
			q[Q].x = id;
		}
		if(cmd == "C") {
			int a = in(),b = in();
			q[Q].x = a, q[Q].y = p[a];
			p[a] = b;
		}
		if(cmd == "Q")
			q[Q].x = in(), q[Q].y = in();
	}
	_rep(i,1,n) insert(rt[i], p[i]);//,printf("p[%d] = %d\n",i,p[i]);
	_rep(i,1,m) if(!removed[i]) link(a[i],b[i]);
	double res = 0;
	int cnt = 0;
	for(int i = Q; i >= 1; --i) {
		if(q[i].cmd == "D") link(a[q[i].x],b[q[i].x]);
		if(q[i].cmd == "C") {
			int f = find(q[i].x);
			remove(rt[f], p[q[i].x]);
			insert(rt[f], p[q[i].x] = q[i].y);
		}
		if(q[i].cmd == "Q") {
			++cnt;
			int f = find(q[i].x);
			if(siz[rt[f]] < q[i].y) res += 0;
			else res += get(rt[f], siz[rt[f]] - q[i].y + 1);
		}
	}
	if(ncnt > 2 * n) {
		puts("fuck you uva.");
		while(true) {}
	}
	printf("Case %d: %.6f\n",++kase,res / cnt);
	return true;
}

void clear(void) {
	ncnt = top = 0;
	_rep(i,1,n) rt[i] = 0;
	_rep(i,1,m) removed[i] = 0;
}

int main() {
	while(solve()) clear();	
	return 0;
}
