#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;

const int maxn=102;
const int maxtime=1002;
//1:炮台,2:子弹,3:走过的痕迹
char condition[maxn][maxn][maxtime];
int m,n,k,d;

const int dx[]={-1,1,0,0,0};
const int dy[]={0,0,-1,1,0};

void addBattery(int x,int y){
    for(int i=0;i<=d;i++)
        condition[x][y][i]=1;
}

bool moveBullet(int c,int t,int v,int& x,int& y){
    for(int i=1;i<=v;i++){
        x+=dx[c];
        y+=dy[c];
        if(x<0||x>n||y<0||y>m||condition[x][y][t]==1)
            return false;
    }
    condition[x][y][t]=2;
    return true;
}

void addBullet(int c,int t,int v,int x,int y){
    for(int i=0;i<=d;i+=t){
        int tx=x,ty=y;
        for(int j=i+1;j<=d;j++){
            if(!moveBullet(c,j,v,tx,ty))
                break;
        }
    }
}

struct node{
    int c,t,v,x,y;
    node(int c,int t,int v,int x,int y):c(c),t(t),v(v),x(x),y(y){};
};

struct nodec{
    int x,y,t;
    nodec(int x,int y,int t):x(x),y(y),t(t){};
};

void bfs(){
    queue<nodec> q;
    condition[0][0][0]=3;
    q.push(nodec(0,0,0));
    while(!q.empty()){
        nodec node=q.front();
        q.pop();
        int x=node.x,y=node.y,t=node.t;
        //return ok
        if(x==n&&y==m){
            cout<<t<<endl;
            return;
        }else if(t==d+1){
            cout<<"Bad luck!"<<endl;
            return;
        }
        for(int i=0;i<5;i++){
            int nt=t+1,nx=x+dx[i],ny=y+dy[i];
            if(nx<0||nx>n||ny<0||ny>m)
                continue;
            if(!condition[nx][ny][nt]){
                condition[nx][ny][nt]=3;
                q.push(nodec(nx,ny,nt));
            }
        }
    }
}

int main(){
    while(cin>>n>>m>>k>>d){
        memset(condition,0,sizeof(condition));

        vector<node> vec;
        int c,t,v,x,y;
        char ch;
        for(int i=0;i<k;i++){
            cin>>ch>>t>>v>>x>>y;
            switch (ch){
                case 'N': c=0;break;
                case 'S': c=1;break;
                case 'W': c=2;break;
                case 'E': c=3;break;
            }
            addBattery(x,y);
            vec.push_back(node(c,t,v,x,y));
        }
        for(int i=0;i<vec.size();i++)
            addBullet(vec[i].c,vec[i].t,vec[i].v,vec[i].x,vec[i].y);
        bfs();
    }
    return 0;
}