#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;

int in(void) { int x; scanf("%d", &x); return x; }
ll inl(void) { ll x; scanf("%lld", &x); return x; }

int ch[100005][2], nc, tag[100005];
void clear(void) {
	memset(ch, 0, sizeof(ch));
	memset(tag, 0, sizeof(tag));
	nc = 0;
}
bool insert(const string &s) {
	int cur = 0; bool flag = true;
	for(const char &c : s) {
		if(!ch[cur][c - '0']) flag = false, ch[cur][c - '0'] = ++nc;
		cur = ch[cur][c - '0'];
		if(tag[cur]) return true;
	}
	tag[cur] = true;
	return flag;
}

int main() { 
	string s; int kase = 0;
	while(cin >> s) { ++kase;
		bool flag = false;
		while(s != "9") {
			if(insert(s)) flag = true;
			cin >> s;
		}
		printf("Set %d ", kase);
		puts(flag ? "is not immediately decodable" : "is immediately decodable");
		clear();
	}
	return 0;
}