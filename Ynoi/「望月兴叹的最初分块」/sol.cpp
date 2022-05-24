
#include<bits/stdc++.h>
using namespace std;
#define N 100100
#define BLK 320
#define LK(x) ((x)*kuai)
#define RK(x) min(((x)+1)*kuai,n)
inline char nc()
{
	static char buf[100000],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
inline int read()
{
	char ch=nc();int sum=0,w=1;
	while(!(ch>='0'&&ch<='9')) {if(ch=='-') w=-1;ch=nc();}
	while(ch>='0'&&ch<='9')sum=sum*10+ch-48,ch=nc();
	return sum*w;
}
int n,m,b[BLK][1000],h[BLK][N],fh[BLK][1000],ls[N],ls2[2000],c[N],kuai,a[N],mkuai,cnt[BLK][N];
int Q,_m;
inline void pd(int id)
{
	int l=LK(id),r=RK(id);
	for(int i=l;i<r;i++)
	{
		a[i]=fh[id][c[i]];
	}
}
inline void change(int bl,int x,int y)
{
	int id=h[bl][x];
	h[bl][y]=id;
	fh[bl][id]=y;
	h[bl][x]=0;
}
inline void build(int id)
{
	int tp=0;
	int l=LK(id),r=RK(id);
	for(int i=1;i<=kuai;i++)
	{
		h[id][fh[id][i]]=0;
	}
	for(int i=l;i<r;i++)
	{
		if(!h[id][a[i]])
		{
			h[id][a[i]]=++tp;
			fh[id][tp]=a[i];
		}
	}
	for(int i=l;i<r;i++)
	{
		c[i]=h[id][a[i]];
	}
}
int main()
{
	int MAXN=100100;
	n=read(),Q=read();
	kuai=mkuai=500;
	m=n/kuai+1,_m=MAXN/mkuai+1;
	for(int i=0;i<n;i++)
	{
		a[i]=read();
	}
	for(int i=0;i<m;i++)
	{
		for(int j=LK(i),tp=0;j<RK(i);j++)
		{
			if(!h[i][a[j]])
			{
				h[i][a[j]]=++tp;
				fh[i][tp]=a[j];
			}
		}
		for(int j=LK(i);j<RK(i);j++)
		{
			c[j]=h[i][a[j]];
		}
	}
	for(int i=0;i<m;i++)
	{
		if(i)
		{
			for(int j=0;j<MAXN;j++)
			{
				cnt[i][j]=cnt[i-1][j];
			}
		}
		if(i)
		{
			for(int j=0;j<_m;j++)
			{
				b[i][j]=b[i-1][j];
			}
		}
		for(int j=LK(i);j<RK(i);j++)
		{
			cnt[i][a[j]]++;
			b[i][a[j]/mkuai]++;
		}
	}
	for(int ni=1,op,l,r,x,y;ni<=Q;++ni)
	{
		op=read(),l=read(),r=read();
		l--,r--;
		if(op==1)
		{
			x=read(),y=read();
			int bl=l/kuai,br=r/kuai;
			int bx=x/mkuai,by=y/mkuai;
			if(cnt[br][x]-(bl?cnt[bl-1][x]:0)==0)
			{
				continue;
			}
			for(int i=m-1;i>=1&&i>=bl;--i)
			{
				cnt[i][x]-=cnt[i-1][x],
				cnt[i][y]-=cnt[i-1][y],
				b[i][bx]-=b[i-1][bx],
				b[i][by]-=b[i-1][by];
			}
			if(bl==br)
			{
				pd(bl);
				for(int i=l;i<=r;++i)
				{
					if(a[i]==x)
					{
						a[i]=y,
						cnt[bl][x]--,
						cnt[bl][y]++,
						b[bl][bx]--,
						b[bl][by]++;
					}
				}
				build(bl);
			}
			else
			{
				pd(bl),pd(br);
				for(int i=l;i<RK(bl);++i)
				{
					if(a[i]==x)
					{
						a[i]=y,
						cnt[bl][x]--,
						cnt[bl][y]++,
						b[bl][bx]--,
						b[bl][by]++;
					}
				}
				for(int i=LK(br);i<=r;++i)
				{
					if(a[i]==x)
					{
						a[i]=y,
						cnt[br][x]--,
						cnt[br][y]++,
						b[br][bx]--,
						b[br][by]++;
					}
				}
				build(bl),build(br);
				for(int i=bl+1;i<br;++i)if(cnt[i][x])
				{
					if(cnt[i][y])
					{
						pd(i);
						for(int j=LK(i);j<RK(i);++j)
						{
							if(a[j]==x)
							{
								a[j]=y,
								cnt[i][x]--,
								cnt[i][y]++,
								b[i][bx]--,
								b[i][by]++;
							}
						}
						build(i);
					}
					else
					{
						b[i][by]+=cnt[i][x];
						b[i][bx]-=cnt[i][x];
						cnt[i][y]+=cnt[i][x],cnt[i][x]=0;
						change(i,x,y);
					}
				}
			}
			for(int i=max(1,bl);i<m;++i)
			{
				cnt[i][x]+=cnt[i-1][x],
				cnt[i][y]+=cnt[i-1][y],
				b[i][bx]+=b[i-1][bx],
				b[i][by]+=b[i-1][by];
			}
		}
		else
		{
			x=read();
			int bl=l/kuai,br=r/kuai;
			if(bl==br)
			{
				pd(bl);
				for(int i=l;i<=r;++i)
				{
					ls[i]=a[i];
				}
				nth_element(ls+l,ls+l+x-1,ls+r+1);
				printf("%d\n",ls[l+x-1]);
				for(int i=l;i<=r;++i)
				{
					ls[i]=0;
				}
			}
			else
			{
				pd(bl),pd(br);
				for(int i=l;i<RK(bl);++i)
				{
					ls[a[i]]++,
					ls2[a[i]/mkuai]++;
				}
				for(int i=LK(br);i<=r;++i)
				{
					ls[a[i]]++,
					ls2[a[i]/mkuai]++;
				}
				for(int i=0,sum=0;i<_m;++i)
				{
					if(ls2[i]+b[br-1][i]-b[bl][i]+sum>=x)
					{
						for(int j=i*mkuai;j<(i+1)*mkuai;++j)
						{
							if(ls[j]+cnt[br-1][j]-cnt[bl][j]+sum>=x)
							{
								printf("%d\n",j);
								goto lxldl;
							}
							else
							{
								sum+=ls[j]+cnt[br-1][j]-cnt[bl][j];
							}
						}
					}
					else
					{
						sum+=ls2[i]+b[br-1][i]-b[bl][i];
					}
				}
				lxldl:
					for(int i=l;i<RK(bl);++i)
					{
						ls[a[i]]--,
						ls2[a[i]/mkuai]--;
					}
					for(int i=LK(br);i<=r;++i)
					{
						ls[a[i]]--,
						ls2[a[i]/mkuai]--;
					}
			}
		}
	}
	return 0;
}



