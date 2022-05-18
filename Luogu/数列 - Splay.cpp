// created time : 2022-04-08 19:17:16
// writer : fjy
#include <bits/stdc++.h>
#define _rep(i_,a_,b_) for(int i_ = a_;i_ <= b_;++i_)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
using namespace std;
const int kN = 500500;
int ch[kN][2], fa[kN], ncnt, root, siz[kN]; //Splay 主体
int val[kN], lsum[kN], rsum[kN], sum[kN], dat[kN]; //维护的数据
int rev[kN], tag[kN], rubbish[kN], top; //标记

void pushup(int x) {
	if(x == 0)
		puts("fucking error appeared. :(");
    sum[x] = sum[ch[x][0]] + sum[ch[x][1]] + val[x];
    siz[x] = siz[ch[x][0]] + siz[ch[x][1]] + 1;

    // lsum[x] = max(lsum[ch[x][0]], sum[ch[x][0]] + val[x] + max(lsum[ch[x][1]],0));
    lsum[x] = sum[ch[x][0]] + val[x] + max(lsum[ch[x][1]],0);
    if(ch[x][0]) lsum[x] = max(lsum[x],lsum[ch[x][0]]);

    // rsum[x] = max(rsum[ch[x][1]], sum[ch[x][1]] + val[x] + max(rsum[ch[x][0]],0));
    rsum[x] = sum[ch[x][1]] + val[x] + max(rsum[ch[x][0]],0);
    if(ch[x][1]) rsum[x] = max(rsum[x],rsum[ch[x][1]]);

    // dat[x] = max({dat[ch[x][0]], dat[ch[x][1]], max(rsum[ch[x][0]],0) + val[x] + max(lsum[ch[x][1]],0)});
    dat[x] = max(rsum[ch[x][0]],0) + val[x] + max(lsum[ch[x][1]],0);
    if(ch[x][0]) dat[x] = max(dat[x], dat[ch[x][0]]);
    if(ch[x][1]) dat[x] = max(dat[x], dat[ch[x][1]]);

}

int build(int *a,int l,int r,int f) {
    if(l > r) return 0;
    int id = top ? rubbish[top--] : ++ncnt,mid = (l + r) >> 1;
    val[id] = a[mid], fa[id] = f, rev[id] = 0, tag[id] = INT_MIN;
    ch[id][0] = build(a,l,mid - 1,id);
    ch[id][1] = build(a,mid + 1,r,id);
    pushup(id);
    return id;
}

void pushdown(int x) {
    if(rev[x] != 0) {
        rev[x] = 0;
        swap(ch[x][0],ch[x][1]);
        rev[ch[x][0]] ^= 1;
        rev[ch[x][1]] ^= 1;
        swap(lsum[ch[x][0]],rsum[ch[x][0]]);
        swap(lsum[ch[x][1]],rsum[ch[x][1]]);
    }
    if(tag[x] != INT_MIN) {
#define set_interval(node, to)\
    tag[(node)] = val[(node)] = to;\
    lsum[(node)] = rsum[(node)] = dat[(node)] = max(to,to * siz[(node)]);\
    sum[(node)] = siz[(node)] * to;
        if(ch[x][0]) { set_interval(ch[x][0],tag[x]); }
        if(ch[x][1]) { set_interval(ch[x][1],tag[x]); }
        tag[x] = INT_MIN;
    } 
}

int get(int x) { return ch[fa[x]][1] == x; }
void rotate(int x) {
    int y = fa[x],z = fa[y],d = get(x);
    ch[y][d] = ch[x][d ^ 1]; fa[ch[x][d ^ 1]] = y;
    ch[z][get(y)] = x; fa[x] = z;
    ch[x][d ^ 1] = y; fa[y] = x;
    pushup(y);
	pushup(x);
}

void splay(int x,int goal = 0) {
    while(fa[x] != goal) {
        int y = fa[x],z = fa[y];
        if(z != goal) rotate(get(x) == get(y) ? y : x);
        rotate(x);
    }
    if(!goal) root = x;
}

void recycle(int node) {
	if(!node) return;
	recycle(ch[node][0]);
	recycle(ch[node][1]);
	dat[node] = fa[node] = ch[node][0] = ch[node][1] = rev[node] = sum[node]
			  = lsum[node] = rsum[node] = tag[node] = val[node] = 0;
	rubbish[++top] = node;
}

int kth(int k) {
    int cur = root;
    while(true) {
        pushdown(cur);
        if(siz[ch[cur][0]] >= k) cur = ch[cur][0];
        else if(siz[ch[cur][0]] + 1 < k) k -= siz[ch[cur][0]] + 1,cur = ch[cur][1];
        else {
            splay(cur);
            return cur;
        }
    }
}

int a[kN],b[kN];

#define no_tag(node) (rev[node] == 0 && tag[node] == INT_MIN)

inline void insert(int x,int rt) { //在 x 后面插入树 rt
    int a = kth(x + 1),b = kth(x + 2); 
    splay(a); splay(b,a); assert(no_tag(a) && no_tag(b));
    ch[b][0] = rt; fa[rt] = b;
    pushup(b); pushup(a);
}

inline void remove(int x,int tot) { //删除从 x 开始的连续 tot 个数字
    int a = kth(x),
		b = kth(x + tot + 1);
    splay(a); splay(b,a); assert(no_tag(a) && no_tag(b));
    recycle(ch[b][0]);
    ch[b][0] = 0;
    pushup(b); pushup(a);
}

inline void make_same(int x,int tot,int y) {
    int a = kth(x), b = kth(x + tot + 1);
    splay(a); splay(b,a); assert(no_tag(a) && no_tag(b));
    set_interval(ch[b][0],y); 
    pushup(b); pushup(a);
} 

inline void reverse(int x,int tot) {
    int a = kth(x), b = kth(x + tot + 1);
    splay(a); splay(b,a); assert(no_tag(a) && no_tag(b));
    rev[ch[b][0]] ^= 1;
    swap(lsum[ch[b][0]],rsum[ch[b][0]]);
    pushup(b); pushup(a);
}

inline int get_sum(int x,int tot) {
    int a = kth(x), b = kth(x + tot + 1);
    splay(a); splay(b,a); assert(no_tag(a) && no_tag(b));
    return sum[ch[b][0]];
}

inline int max_sum(int pos,int tot) {
	int a = kth(pos), b = kth(pos + tot + 1);
	splay(a); splay(b,a);
	return dat[ch[b][0]];
}

char command[150];
int main() {
    int n = in(),m = in();
    _rep(i,1,n) a[i] = in();
    a[0] = -1030, a[n + 1] = -1030;
    root = build(a,0,n + 1,0);

    _rep(i,1,m) {
        scanf("%s",command);
        if(strcmp(command,"GET") == 0) {
        	int pos = in();
        	printf("%d\n",get_sum(pos,1));
			continue;
		}
        int pos = in(),tot = in();
        if(strcmp(command,"INSERT") == 0) {
            _rep(i,1,tot) b[i] = in();
            insert(pos,build(b,1,tot,0));
        }
        if(strcmp(command,"DELETE") == 0)
            remove(pos,tot);
        if(strcmp(command,"MAKE-SAME") == 0)
            make_same(pos,tot,in());
        if(strcmp(command,"REVERSE") == 0)
            reverse(pos,tot);
        if(strcmp(command,"GET-SUM") == 0)
            printf("%d\n",get_sum(pos,tot));
        if(strcmp(command,"MAX-SUM") == 0)
			printf("%d\n",max_sum(pos,tot));
	}
    return 0;
}
