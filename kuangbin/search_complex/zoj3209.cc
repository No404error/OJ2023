#include<cstdio>
#include<cstring>

const int maxc=1000;
const int maxr=1000;
const int maxn=451000;
const int resf=0x3f3f3f;
//列数,节点数
int n,sz;
//上下左右
int U[maxn],D[maxn],L[maxn],R[maxn];

int H[maxr];
//列节点数
int S[maxc];
//行列位置
int col[maxn];

void init(int Ncol){
    n=Ncol;
    sz=Ncol+1;
    for(int i=0;i<=n;i++){
        L[i]=i-1,R[i]=i+1,U[i]=D[i]=i;
        S[i]=0;
    }
    L[0]=n,R[n]=0;
    memset(H,-1,sizeof(H));
}

void addNode(int r,int c){
    //左右
    U[sz]=U[c];D[sz]=c;
    D[U[c]]=sz;U[c]=sz;

    //上下
    if(H[r]==-1) H[r]=L[sz]=R[sz]=sz;
    else{
        L[sz]=L[H[r]];R[L[H[r]]]=sz;
        R[sz]=H[r];L[H[r]]=sz;
    }

    //其他
    col[sz]=c;
    S[c]++;
    sz++;
}

#define FOR(i,A,s) for(int i = A[s] ; i != s; i = A[i])

void remove(int c){
    L[R[c]]=L[c];R[L[c]]=R[c];
    FOR(i,D,c)
        FOR(j,R,i){
            U[D[j]]=U[j];D[U[j]]=D[j];S[col[j]]--;
        }
            
}

void recover(int c){
    FOR(i,U,c)
        FOR(j,L,i){
            U[D[j]]=D[U[j]]=j;S[col[j]]++;
        }
            
    L[R[c]]=R[L[c]]=c;
}

int res;

void dfs(int floor){
    if(floor>=res)
        return;

    if(!R[0]){
        res=res>floor?floor:res;
        return;
    }

    int c=R[0];
    FOR(i,R,0) 
        if(S[i]<S[c]) c=i;

    remove(c);
    FOR(i,D,c){
        FOR(j,R,i) remove(col[j]);
        dfs(floor+1);
        FOR(j,L,i) recover(col[j]);
    }
    recover(c);
}

int main(){
    int cases,n,m,p;
    int x1,x2,y1,y2;
    //cin>>cases;
    scanf("%d",&cases);
    while(cases--){
        //cin>>n>>m>>p;
        scanf("%d%d%d",&n,&m,&p);
        //展开
        init(n*m);
        for(int i=1;i<=p;i++){
            //cin>>x1>>y1>>x2>>y2;
            scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
            for(int j=y1;j<y2;j++)
                for(int k=x1;k<x2;k++){
                    addNode(i,j*n+k+1);
                }
        }
        res=resf;
        dfs(0);
        printf("%d\n",res==resf?-1:res);
    }
    return 0;
}