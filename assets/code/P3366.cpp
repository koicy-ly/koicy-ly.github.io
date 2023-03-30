#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int MAX=100010;
struct node
{
  int u,v;
  LL w;
};
struct node1
{
  int to,next;
  LL val;
};
node edge[MAX*3];

int head[MAX];
node1 tree[MAX];

int n,m,k,cnt;
int k1,k2;
int father[MAX];
int book[MAX];
LL ans;
int fa[MAX][20];
int deep[MAX];
LL chafen[MAX*3];
int treemax[MAX][18];

void add(int come,int to,LL val)
{
  k2++;
  tree[k2]=(node1){to,head[come],val};
  head[come]=k2;
}

bool cmp(node x,node y) {  return x.w<y.w;  }

int find(int x)
{
  while(x!=father[x]) x=father[x]=father[father[x]];
  return x;
}

void kru()
{
  for(int i=1;i<=m;i++)
  {
    int u=find(edge[i].u),v=find(edge[i].v);
    if(v==u) continue;
    add(edge[i].u,edge[i].v,edge[i].w);
    add(edge[i].v,edge[i].u,edge[i].w);
    book[i]=true;
    father[u]=v;
    cnt++;
    ans+=edge[i].w;
    if(cnt==n)  break;
  }
}

void dfs(int u)
{
  for(int i=head[u];i;i=tree[i].next)
  {
    int v=tree[i].to;
    if(deep[v]==0)
    {
      deep[v]=deep[u]+1;
      fa[v][0]=u;
      treemax[v][0]=edge[i].w;
      dfs(v);
    }
  }
}

int lca(int x,int y)
{
  if(deep[x]<deep[y])  swap(x,y);
  for(int i=18;i>=0;i--)
  {
    if(deep[fa[x][i]]>=deep[y])
    x=deep[fa[x][i]];
  }
  if(x==y) return x;
  for(int i=18;i>=0;i--)
  {
    if(fa[x][i]!=fa[y][i])
    {
      x=fa[x][i];
      y=fa[y][i];
    }
  }
  return fa[x][0];
}

int check(int x,int root,int val)
{
  for(int i=18;i>=0;i--)
  {
    if(deep[fa[x][i]]<=deep[root] && fa[x][i]<val)
    {
      x=fa[x][i];
    }
  }
}

void solve()
{
  int x,y,f;
  long long maxn,max1,max2;
  LL val;
  for(int i=1;i<=m;i++)
  {
    if(book[i]==0)
    {
      x=edge[i].u,y=edge[i].v;
      val=edge[i].w;
      f=lca(x,y);
      max1=check(x,f,val);
      max2=check(y,f,val);
      maxn=max(max1,max2);
      chafen[i]=maxn;
    }
  }
}

int main()
{
  int x,y;
  LL z;
  scanf("%d%d",&n,&m);
  for(int i=1;i<=m;i++)
  {
    scanf("%d%d%lld",&edge[i].u,&edge[i].v,&edge[i].w);
  }
  for(int i=1;i<=n;i++)
  father[i]=i;
  sort(edge+1,edge+m+1,cmp);
  kru();  //\u6700\u5c0f\u751f\u6210\u6811 
  deep[1]=1;
  dfs(1);
  for(int i=1;i<=18;i++)
  {
    for(int j=1;j<=n;j++)
    fa[j][i]=fa[fa[j][i-1]][i-1];
  }
  for(int i=1;i<=18;i++)
  {
    for(int j=1;j<=n;j++)
    treemax[j][i]=max(treemax[j][i-1],treemax[treemax[j][i-1]][i-1]);
  }
  memset(chafen,-1,sizeof(chafen));
  solve();
  LL minx=(1<<25);
  for(int i=1;i<=m;i++)
  {
    if(chafen[i]!=-1)
    minx=min(minx,chafen[i]);
  }
  printf("%d",ans/*+minx*/);
  return 0;
}