#include <bits/stdc++.h>
#define _rep(i_,a_,b_) for(int i_ = a_;i_ <= b_;++i_)
typedef int ll;
//int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
int in(void){
    int x(0),c(getchar()),f(0);
    while(c<'0'||c>'9'){if(c == '-')f = 1;c = getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c = getchar();}
    return f?-x:x;
}
using namespace std;
const int kN = 250000;
struct Triple {
	int x,y,id;
} p[kN];
vector<pair<int,int> > g[kN];
void add_edge(int u,int v,int w) {
	g[u].push_back({v,w});
	g[v].push_back({u,w});
}

ll d[kN];
int n = in(),m = in(),inq[kN];
queue<int> q;
void SPFA(void) {
	memset(d,0x3f,sizeof(d));
	d[m - 1] = 0;
	q.push(m - 1);
	inq[m - 1] = 1;
	while(!q.empty()) {
		int u = q.front(); q.pop(); inq[u] = 0;
		for(auto &v : g[u]) {
			if(d[v.first] > d[u] + v.second) {
				d[v.first] = d[u] + v.second;
				if(!inq[v.first]) {
					inq[v.first] = 1;
					q.push(v.first);
				}
			}
		}
	}
}

int main() {
	_rep(i,1,m + 2) p[i].x = in(),p[i].y = in(),p[i].id = i;
	m += 2;
	sort(p + 1,p + 1 + m,[](const Triple &a,const Triple &b) -> bool {
		return a.x == b.x ? a.y < b.y : a.x < b.x;
	});
	_rep(i,2,m) if(p[i - 1].x == p[i].x) 
		add_edge(p[i - 1].id,p[i].id,2 * (p[i].y - p[i - 1].y));
	sort(p + 1,p + 1 + m,[](const Triple &a,const Triple &b) -> bool{
		return a.y == b.y ? a.x < b.x : a.y < b.y;
	});
	_rep(i,2,m) if(p[i - 1].y == p[i].y) 
		add_edge(p[i - 1].id + m,p[i].id + m,2 * (p[i].x - p[i - 1].x));
	_rep(i,1,m - 2) add_edge(i,i + m,1);
	add_edge(m,m + m,0);
	add_edge(m - 1,m - 1 + m,0);
	SPFA();
	printf("%d\n",d[m] == 0x3f3f3f3f ? -1 : d[m]);
	return 0;
}
