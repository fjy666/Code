#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
const int kN = 100500,kb = 320;
int a[kN],n = in(),d[kN];
int cnt[kb][kN],sum[kb][kN],res[kb][kb];
#define get(x) ((x - 1) / kb + 1)
#define occur(i,j,x) (sum[j][x] - sum[i - 1][x])
void init(void) {
	_rep(i,1,get(n)) 
		_rep(j,(i - 1) * kb + 1,min(n,i * kb))
			++cnt[i][a[j]];
	_rep(i,1,get(n)) _rep(j,1,n) sum[i][j] = sum[i - 1][j] + cnt[i][j];
	
	_rep(i,1,get(n)) {
		res[i][i] = a[(i - 1) * kb + 1];
		_rep(j,(i - 1) * kb + 2,min(n,i * kb))
			if(cnt[i][a[j]] > cnt[i][res[i][i]] || (cnt[i][a[j]] == cnt[i][res[i][i]] && a[j] < res[i][i]))
				res[i][i] = a[j];
		_rep(j,i + 1,get(n)) {
			res[i][j] = res[i][j - 1];
			_rep(k,(j - 1) * kb + 1,min(n,j * kb))
				if (occur(i,j,a[k]) > occur(i,j,res[i][j]) 
			     ||(occur(i,j,a[k]) == occur(i,j,res[i][j]) && a[k] < res[i][j]))
					res[i][j] = a[k];
		}
	}
} 
int tmp[kN];
int query(int l,int r) {
	if(get(l) == get(r)) {
		int ans = a[l];
		_rep(i,l,r) ++tmp[a[i]];
		_rep(i,l + 1,r) if(tmp[a[i]] > tmp[ans] || (tmp[a[i]] == tmp[ans] && a[i] < ans)) ans = a[i];
		_rep(i,l,r) --tmp[a[i]];
		return ans;
	}
	
	int ans = res[get(l) + 1][get(r) - 1];
	_rep(i,l,get(l) * kb) ++tmp[a[i]];
	_rep(i,(get(r) - 1) * kb + 1,r) ++tmp[a[i]];
	
	_rep(i,l,get(l) * kb) {
		int oc = occur(get(l) + 1,get(r) - 1,a[i]) + tmp[a[i]],od = occur(get(l) + 1,get(r) - 1,ans) + tmp[ans];
		if(oc > od || (oc == od && a[i] < ans)) ans = a[i];
	}
	_rep(i,(get(r) - 1) * kb + 1,r) {
		int oc = occur(get(l) + 1,get(r) - 1,a[i]) + tmp[a[i]],od = occur(get(l) + 1,get(r) - 1,ans) + tmp[ans];
		if(oc > od || (oc == od && a[i] < ans)) ans = a[i];
	}
	
	_rep(i,l,get(l) * kb) --tmp[a[i]];
	_rep(i,(get(r) - 1) * kb + 1,r) --tmp[a[i]];
	return ans;
}
int main() {
	_rep(i,1,n) d[i] = a[i] = in();
	sort(d + 1,d + 1 + n);
	_rep(i,1,n) a[i] = lower_bound(d + 1,d + 1 + n,a[i]) - d; //离散化
	init();
	_rep(i,1,n) {
		int l = in(),r = in();
		printf("%d\n",d[query(l,r)]);
	}
	return 0;
}
