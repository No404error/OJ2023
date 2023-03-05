#include<iostream>
#include<cstring>
#include<string>
#include<queue>
using namespace std;

typedef long long ll;

typedef struct node{
    int a[9];
    int hash;
    int pos;
    int len;
    int right;
    ll path;
    node(){};
    node(int *as,int hash,int pos,int right,int len,ll path):hash(hash),pos(pos),right(right),len(len),path(path){
        memcpy(a,as,sizeof(a));
    }
} node;

int fn[]={1,1,2,6,24,120,720,5040,40320,362880};
const int maxn=362885;
int vis[2][maxn];
ll path[2][maxn];

ll power4[30];

void init(){
    power4[0]=1;
    for(int i=1;i<30;i++)
        power4[i]=power4[i-1]*4;
}

int cantor(int *a){
    int res=1;
    for(int i=0;i<9;i++){
        int tmp=0;
        for(int j=i+1;j<9;j++)
            if(a[i]>a[j]) tmp++;
        res+=fn[8-i]*tmp;
    }
    return res;
}

const int op[]={1,0,0,-1,0,1,-1,0};
const char ops[]="dlru";
const char dops[]="urld";

string getstr(ll path,int right,int hash){
    int str[35];
    int cnt=0;

    for(int i=1;i<=vis[right][hash];i++){
        str[i]=path%4;
        path/=4;
        cnt++;
    }
    string ans="";
    for(int i=cnt;i>0;i--){
        ans+=ops[str[i]];
    }
    return ans;
}

node getStrNode(string s,int right){
    int a[9];
    int pos;
    for(int i=0;i<9;i++){
        if(s[i]=='X'){
            a[i]=9;
            pos=i;
        }    
        else
            a[i]=s[i]-'0';
    }
    return node(a,cantor(a),pos,right,0,0);
}

void bfs(string b,string e){
    if(b==e){
        cout<<"0\n\n";
        return;
    }
    memset(vis,-1,sizeof(vis));
    queue<node> q;
    node bb=getStrNode(b,0),ee=getStrNode(e,1);
    q.push(bb);
    vis[0][bb.hash]=0;
    q.push(ee);
    vis[1][ee.hash]=0;
    
    int len=INT_MAX;
    string ans="";

    while(!q.empty()){
        node now=q.front();
        q.pop();
            
        int a[9];
        int right=now.right;
        int y=now.pos/3,x=now.pos%3,nx,ny;
        for(int i=0;i<8;i+=2){
            ny=y+op[i];
            nx=x+op[i+1];
            if(ny>=0&&ny<3&&nx>=0&&nx<3){
                int nPos=ny*3+nx;
                memcpy(a,now.a,sizeof(a));
                swap(a[now.pos],a[nPos]);
                int hash=cantor(a);
                //未被访问
                if(vis[right][hash]==-1){
                    vis[right][hash]=now.len+1;
                    ll pa=right?(3-i/2)*power4[now.len]+now.path:(now.path*4+i/2);
                    path[right][hash]=pa;
                }else{
                    if(now.len+1>vis[right][hash]) continue;
                    ll pa=right?(3-i/2)*power4[now.len]+now.path:(now.path*4+i/2);
                    if(path[right][hash]>pa)
                        path[right][hash]=pa;
                }

                if(vis[right^1][hash]!=-1){
                    string tmp=getstr(path[0][hash],0,hash)+getstr(path[1][hash],1,hash);
                    //设正n,反m层相遇,要保证仅在解(n,m)解决,(n-1,m-1)之类是不可能的,所以当tmp的len大于len时结束
                    if(tmp.length()>len){
                        cout<<ans.length()<<endl;
                        cout<<ans<<endl;
                        return;
                    }else if(tmp.length()<len){
                        len=tmp.length();
                        ans=tmp;
                    }else if(tmp<ans)
                        ans=tmp;
                }
                //由于要确保答案仅在(n,m),索性把经历过点的都存进来
                q.push(node(a,hash,nPos,now.right,now.len+1,path[right][hash]));
            }
        } 
    }
}

int main(){
    init();
    int times;
    string b,e;
    cin>>times;
    for(int time=1;time<=times;time++){
        cin>>b>>e;
        printf("Case %d: ",time);
        bfs(b,e);
    }
    return 0;
}