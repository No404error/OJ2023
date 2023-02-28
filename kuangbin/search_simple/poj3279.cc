#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

const int maxn=18;
int grid[maxn][maxn];
int ans[maxn][maxn];
int temp[maxn][maxn];
int M,N;
int len=INT_MAX;
const int dx[]={0,-1,1,0,0};
const int dy[]={0,0,0,1,-1};

//第一个想法是在dfs一层时将要修改的节点反转,最后再反转回来,这样的效率太低
//第二个想法是不在原棋盘上进行翻转,转而记录节点及其周围的节点的翻转次数，综合得出当前的节点状态

//得到
int getColor(int r,int c){
    int cnt=grid[r][c];
    for(int i=0;i<5;i++){
        cnt+=temp[r+dx[i]][c+dy[i]];
    }
    return cnt%2;
}

int solve(){
    //上一层的黑块只能由这一层下方的黑块来补黑
    for(int i=2;i<=M;i++)
        for(int j=1;j<=N;j++)
            if(getColor(i-1,j))
                temp[i][j]=1;

    //查看最后一行的颜色
    for(int i=1;i<=N;i++){
         if(getColor(M,i))
            return INT_MAX;
    }

    int cnt=0;
    for(int i=1;i<=M;i++)
        for(int j=1;j<=N;j++)
            if(temp[i][j])
                cnt++;

    return cnt;
}

int main(){
    //scanf("%d %d",&M,&N);
    cin>>M>>N;
    for(int i=1;i<=M;i++)
        for(int j=1;j<=N;j++)
            cin>>grid[i][j];

    for(int i=0;i<(1<<(N+1));i++){
        memset(temp,0,sizeof(temp));
        for(int j=1;j<=N;j++)
            if((i>>(N-j))&1)
                temp[1][j]=1;
        int cnt=solve();
        if(cnt<len){
            len=cnt;
            memcpy(ans,temp,sizeof(ans));
        }
    }
    if(len==INT_MAX)
        printf("IMPOSSIBLE\n");
    else{
        for(int i=1;i<=M;i++){
            for(int j=1;j<=N;j++)
                printf("%d ",ans[i][j]);
        printf("\n");
        }
    }
    return 0;
}
