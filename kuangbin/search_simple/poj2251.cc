#include<iostream>
#include<queue>
#include<cstring>
using namespace std;

#define _for(i,j,k) for(int i=(j);i<=k;i++)

int l,r,c;
const int maxn=32;
char a[maxn][maxn][maxn];
int vis[maxn][maxn][maxn];

typedef struct cell{
    int l,r,c;
    cell(){}
    cell(int l,int r,int c){
        this->l=l;
        this->r=r;
        this->c=c;
    }
} cell;

cell st;
int dis;

const int dir[][3]={{1,0,0},{-1,0,0},{0,1,0},{0,-1,0},{0,0,1},{0,0,-1}};

int main(){
    while (true){
        memset(vis,-1,sizeof(vis));
        cin>>l>>r>>c;

        if(l==0)
            break;
        
        _for(i,1,l)
            _for(j,1,r)
                _for(k,1,c){
                    cin>>a[i][j][k];
                    if(a[i][j][k]=='S'){
                        st=cell(i,j,k);
                        vis[i][j][k]=0;
                    }
                }

        queue<cell> q;
        q.push(st);

        bool find=false;

        while(!q.empty()&&!find){
            cell cel=q.front();

            for(int i=0;i<6;i++){
                cell t=cel;
                t.l+=dir[i][0];
                t.r+=dir[i][1];
                t.c+=dir[i][2];

                if(vis[t.l][t.r][t.c]!=-1)
                    continue;

                if(t.l>=1&&t.l<=l&&t.r>=1&&t.r<=r&&t.c>=1&&t.c<=c){
                    if(a[t.l][t.r][t.c]=='.'){
                        q.push(t);
                        vis[t.l][t.r][t.c]=vis[cel.l][cel.r][cel.c]+1;
                    }
                        
                    else if(a[t.l][t.r][t.c]=='E'){
                        find=true;
                        dis=vis[cel.l][cel.r][cel.c]+1;
                        break;
                    }
                }
            }

            q.pop();
        }

        if(find)
            cout<<"Escaped in "<<dis<<" minute(s)."<<endl;
        else
            cout<<"Trapped!"<<endl;
    }
    
    return 0;
}