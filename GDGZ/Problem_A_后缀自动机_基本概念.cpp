//Code by fjy666
#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;

int in(void) { int x; scanf("%d", &x); return x; }
ll inl(void) { ll x; scanf("%lld", &x); return x; }
const int kN = 55;
char s[kN], t[kN];
int n;

int main() { 
	scanf("%s", s + 1);
	n = strlen(s + 1);
	int fjy = in();
	while(fjy--) {
		scanf("%s", t + 1);
		int m = strlen(t + 1);
		vector<int> endpos = vector<int>();
		map<int,int> hash = map<int,int>();
		_rep(i,1,n - m + 1) {
			bool flag = false;
			_rep(j,1,m) if(s[i + j - 1] != t[j]) flag = true;
			if(!flag) endpos.push_back(i + m - 1), hash[i + m - 1] = 1;
		} 
		vector<int> sets = vector<int>();
		_rep(st, 1, endpos[0]) { //try every length possiable
			int len = endpos[0] - st + 1;
			_rep(i,1,len) t[i] = s[st + i - 1]; //baka, you should copy string s first!
			bool available = true;
			_rep(i,1,n - len + 1) {
				bool match = true;
				_rep(j,i,i + len - 1) if(s[j] != t[j - i + 1]) match = false;
				if(match != hash[i + len - 1]) available = false;
			}
			if(available) sets.push_back(st);
		}
		_rep(i,sets[sets.size() - 1],endpos[0]) putchar(s[i]);
		putchar(' ');
		_rep(i,sets[0],endpos[0]) putchar(s[i]); 
		putchar(' ');
		for(auto &element : endpos) printf("%d ", element);
		puts("");
	}
	return 0;
}

/* 
a list of keywords 
clear empty push_back pop_back push pop top front back
emplace_back emplace push_front pop_front insert erase
find count set reset bitset map vector string multiset
first second iterator prev next deque multimap reverse
*/