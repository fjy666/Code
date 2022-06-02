//created time: 2022-06-02 12:11:11
#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;

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

struct Point { double x,y; };
struct Circle {	Point O; double r; } c[105];
int Black[105];

double dist(Point x, Point y) {	return hypot(x.x - y.x, x.y - y.y); }
const double pi = 3.1415926;
int main() {
	int n; scanf("%d", &n);
	_rep(i,1,n) 
		scanf("%lf%lf%lf", &c[i].O.x, &c[i].O.y, &c[i].r);
	sort(c + 1, c + 1 + n, [](const Circle &a, const Circle &b) -> bool { return a.r > b.r; });
	c[0] = Circle{{0.0, 0.0}, 114514.1919810}; Black[0] = 1;
	double total_area = 0.0;
	_rep(i,1,n) {
		for(int j = i - 1; ~j; --j) 
			if(dist(c[i].O, c[j].O) + c[i].r <= c[j].r) {
				Black[i] = Black[j] ^ 1;
				total_area += c[i].r * c[i].r * pi * (Black[i] ? -1 : 1);
				break;
			}
	}
	printf("%.2lf\n", total_area);
	return 0;
}
