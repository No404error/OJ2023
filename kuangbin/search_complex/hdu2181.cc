#include<iostream>
#include<algorithm>
using namespace std;

const int N=22;
const int M=4;

int num[N][M];
bool vis[N];
int out[N];

int order;
int start;

void dfs(int pos,int total){
    for(int i=1;i<=3;i++){
        int n=num[pos][i];
        if(total==19&&num[pos][i]==start){
            cout<<order++<<":  ";
            for(int i=0;i<20;i++)
                cout<<out[i]<<" ";
            cout<<start<<endl;
            return;
        }
        if(vis[n])
            continue;
        vis[n]=1;
        out[total+1]=n;
        dfs(n,total+1);
        vis[n]=0;
    }
}

void run(int pos){
    order=1;
    vis[pos]=1;
    out[0]=pos;
    dfs(pos,0);
}

int main(){
    for(int i=1;i<=20;i++){
        int a[5];
        for(int j=1;j<=3;j++)
            cin>>a[j];
        sort(a+1,a+4);
        for(int j=1;j<=3;j++)
            num[i][j]=a[j];
    }
        
    int res;
    while(cin>>res&&res){
        run(res);
    }
    return 0;
}