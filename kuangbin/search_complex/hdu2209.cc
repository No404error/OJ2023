#include<cstdio>
#include<cmath>
#include<cstring>

#define FOR(i,A,s) for(int i=A[s];i!=s;i=A[i])

const double eps=1e-8;
const int maxn=3500;
const int maxr=55;
const int maxc=55;

int U[maxn],D[maxn],L[maxn],R[maxn];
int col[maxn];
//int vnode[maxc];
int S[maxc];
bool vis[maxc];
int H[maxr];
//node节点数,n列数
int sz;
int n,m,k;

void init(){
    for(int i=0;i<=n;i++){
        L[i]=i-1;
        R[i]=i+1;
        U[i]=D[i]=i;
        S[i]=0;
        //vnode[i]=0;
    }
    L[0]=n;R[n]=0;
    sz=n+1;
    for(int i=1;i<=m;i++) H[i]=-1;
}

void addNode(int r,int c){
    S[c]++;
    col[sz]=c;
    U[sz]=U[c];D[U[c]]=sz;
    D[sz]=c;U[c]=sz;
    if(H[r]==-1)
        H[r]=L[sz]=R[sz]=sz;
    else{
        L[sz]=L[H[r]];R[L[H[r]]]=sz;
        R[sz]=H[r];L[H[r]]=sz;
    }
    sz++;
}

void remove(int c){
    /*
    if(!vnode[c]){
        vnode[c]=1;
        R[L[c]]=R[c],L[R[c]]=L[c];
    }
    */
    FOR(i,D,c)
        R[L[i]]=R[i],L[R[i]]=L[i];
}

void resume(int c){
    /*
    if(vnode[c]){
        vnode[c]=0;
        R[L[c]]=L[R[c]]=c;
    }
    */
    FOR(i,D,c)
        R[L[i]]=L[R[i]]=i;
}
bool v[maxr];
int aStar(){
    int ret=0;
    FOR(c,R,0)
        v[c]=true; 
    FOR(c,R,0)
        if(v[c]){
            v[c]=false;
            ret++;
            FOR(i,D,c)
                FOR(j,R,i)
                    v[col[j]]=false;
        }
    return ret;
}

bool dfs(int floor){
    if(floor+aStar()>k)
        return false;
    if(!R[0]){
        if(floor<=k)
            return true;
        return false;
    }
    int c=R[0];
    FOR(i,R,0)
        if(S[c]>S[i])
            c=i;
    //remove(c);
    FOR(i,D,c){
        remove(i);
        FOR(j,R,i) 
            remove(j);
        if(dfs(floor+1))
            return true;
        FOR(j,R,i) 
            resume(j);
        resume(i);
   }
   //resume(c);
   return false;
}
int ctx[55],cty[55];
int rdx[55],rdy[55];

double dist(int a,int b){
	return (double)(rdx[a]-ctx[b])*(rdx[a]-ctx[b])+(double)(rdy[a]-cty[b])*(rdy[a]-cty[b]);
}

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        scanf("%d%d%d",&n,&m,&k);
        for(int i=1;i<=n;i++) scanf("%d%d",&ctx[i],&cty[i]);
        for(int i=1;i<=m;i++) scanf("%d%d",&rdx[i],&rdy[i]);
        double l=0,r=2000,mid;
        while(r-l>eps){
            mid=(r+l)/2;
            init();
            int num=0;
            memset(vis,0,sizeof(vis));
            for(int i=1;i<=m;i++){
                for(int j=1;j<=n;j++){
                    double dis=dist(i,j);
                    if(dis<=mid*mid){
                        addNode(i,j);
                        if(!vis[j]){
                            vis[j]=1;
                            num++;
                        }
                    }
                }
            }
            if(num<n)
                l=mid;
            else if(dfs(0))
                r=mid;
            else
                l=mid;
        }
        printf("%.6lf\n",l);
    }
    return 0;
}