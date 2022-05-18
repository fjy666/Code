#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
int m, n; unsigned int seed,last = 7;
unsigned randNum(void){ 
	seed = seed * 17 + last;
	return seed % m + 1; 
}
const int kN = 1000500;
mt19937 rng(114514);
pair<int,int> val[kN]; int ncnt; int rnd[kN], ch[kN][2], siz[kN], root;
void pushup(int x) { siz[x] = siz[ch[x][0]] + siz[ch[x][1]] + 1; }
void rotate(int &id,int d) {
	int tmp = ch[id][d ^ 1]; ch[id][d ^ 1] = ch[tmp][d]; ch[tmp][d] = id;
	pushup(id); pushup(tmp); id = tmp;
}
void insert(pair<int,int> v,int &t) { 
	if(!t) {
		val[++ncnt] = v, rnd[ncnt] = (int) rng(), siz[ncnt] = 1;
		ch[ncnt][0] = ch[ncnt][1] = 0; 
		t = ncnt;
		return;
	}
	int subt = v > val[t];
	insert(v,ch[t][subt]);
	if(rnd[ch[t][subt]] < rnd[t]) rotate(t,subt ^ 1);
	pushup(t);
}

void remove(pair<int,int> t,int &id) {
	if(val[id] == t) {
		if(!ch[id][0]) id = ch[id][1];
		else if(!ch[id][1]) id = ch[id][0];
		else {
			int dir = rnd[ch[id][0]] > rnd[ch[id][1]] ? 0 : 1;
			rotate(id,dir); remove(t,ch[id][dir]);
		}
	} else remove(t,ch[id][t > val[id]]);
	if(id) pushup(id);
}

int kth(pair<int,int> t,int &id) {
	if(!id) return 0;
	if(val[id] <= t) return kth(t,ch[id][1]);
	return siz[ch[id][1]] + 1 + kth(t,ch[id][0]);
}

void debug(int id) {
	if(!id) return;
	if(!( (ch[id][0] == 0 || val[ch[id][0]] < val[id]) && (ch[id][1] == 0 || val[ch[id][1]] > val[id]))) {
		puts("fucking shit error:/");
		exit(3);
	}
	debug(ch[id][0]);
	printf(" (%d,%d)",val[id].first,val[id].second);
	debug(ch[id][1]);
}

int fs[kN],cnt[kN];
int main() {
	int T = in();
	while(T--) {
		cin >> m >> n >> seed;
		root = ncnt = 0;
		_rep(i,1,m) fs[i] = cnt[i] = 0;
		_rep(i,1,n) {
			int Ria = randNum(); int Rib = randNum(); //第Ria个人AC,罚时为Rib
//			if(Ria == 27 && Rib == 80) {
//				puts("Fucking Error Appeared");
//			}
//			printf("Ria = %d,Rib = %d\n",Ria,Rib);
			if(cnt[Ria]) remove(make_pair(cnt[Ria],-fs[Ria]),root);
			fs[Ria] += Rib, cnt[Ria]++;
			printf("%u\n",last = kth(make_pair(cnt[Ria],-fs[Ria]),root));
			insert(make_pair(cnt[Ria],-fs[Ria]),root);
			debug(root);
		}
	}
	return 0;
}
