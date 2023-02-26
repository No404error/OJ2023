#include<iostream>
#include<cstdio>
using namespace std;

#define _for(i,j,k) for(int i=(j);i<=(k);i++)


const int maxn=10;
char a[maxn][maxn];
int use[maxn];
int n,k,ans;

void dfs(int c,int p){
    if(p==0){
        ans++;
        return;
    }
    else if(c==n+1)
        return;
    
    _for(l,1,n){
        if(a[c][l]=='#'&&!use[l]){
            use[l]=1;
            dfs(c+1,p-1);
            use[l]=0;
        }
    }
    dfs(c+1,p);
}

int main(){
    while(1){
        ans=0;
        cin>>n>>k;
        if(n==-1)
            break;
        
        _for(i,1,n)
            _for(j,1,n){
                cin>>a[i][j];
            }   
        dfs(1,k);
        printf("%d\n",ans);
    }
    return 0;
}