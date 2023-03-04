#include<iostream>
#include<queue>
#include<cstdio>
#include<string>
#include<cstring>
using namespace std;

int f[10];
void fact(int n){
    f[0]=f[1]=1;
    for(int i=2;i<=n;i++)
        f[i]=f[i-1]*i;
}

int kangtuo(int *s){
    int num=1;
    for(int i=0;i<9;i++){
        int tmp=0;
        for(int j=i+1;j<9;j++){
            if(s[i]>s[j])
                tmp++;
        }
        num+=tmp*f[8-i];
    }
    return num;
}

const int maxn=362880+5;
//记录到vis的方向
int vis[9][maxn];
//记录父节点的canton value
int pre[9][maxn];

void init(){
    fact(8);
    memset(vis,-1,sizeof(vis));
    memset(pre,-1,sizeof(pre));
}

typedef struct node{
    int a[9];
    int pos;
    int hash;
    node(){};
    node(int* as,int p,int h):pos(p),hash(h){
        memcpy(a,as,sizeof(a));
    };
} node;

//udlr
int op[]={1,0,0,-1,0,1,-1,0};
char ops[]="dlru";

void bfs(int sta){
    int a[10];
    node now,tmp;
    for(int i=0,v=1;i<9;i++){
        if(i==sta)
            now.a[i]=9;
        else
            now.a[i]=v++;
    }
    now.pos=sta;
    now.hash=kangtuo(now.a);

    queue<node> q;

    q.push(now);
    vis[sta][now.hash]=0;

    while(!q.empty()){
        tmp=q.front();
        q.pop();

        int y=tmp.pos/3;
        int x=tmp.pos%3;
        int nx,ny;
        for(int i=0;i<8;i+=2){
            ny=y+op[i];
            nx=x+op[i+1];
            if(nx>=0&&nx<3&&ny>=0&&ny<3){
                memcpy(a,tmp.a,sizeof(a));
                swap(a[tmp.pos],a[ny*3+nx]);
                int p=kangtuo(a);
                if(vis[sta][p]==-1){
                    vis[sta][p]=i/2;
                    pre[sta][p]=tmp.hash;
                    q.push(node(a,ny*3+nx,p));
                }
            }
        }
    }
}

int main(){
    init();
    for(int i=0;i<9;i++)
        bfs(i);
    int num;
    int sta;
    //begin,end
    char b[10],e[10];
    int map[10],ee[10];
    scanf("%d",&num);
    for(int times=1;times<=num;times++){
        scanf("%s %s",b,e);
        for(int i=0,j=1;i<9;i++){
            if(b[i]=='X')
                sta=i;
            else
                map[b[i]-'0']=j++;
        }
        for(int i=0;i<9;i++){
            if(e[i]=='X')
                ee[i]=9;
            else
                ee[i]=map[e[i]-'0'];
        }

        int hash=kangtuo(ee);
        string s="";
        while(hash!=-1){
            s+=ops[vis[sta][hash]];
            hash=pre[sta][hash];
        }
        cout<<"Case "<<times<<": "<<s.length()-1<<endl;
        for(int i=s.length()-2;i>=0;i--)
            printf("%c",s[i]);
        cout<<endl;
    }
    return 0;
}