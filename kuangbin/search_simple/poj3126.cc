#include<iostream>
#include<cstring>
#include<queue>
using namespace std;

const int maxn=10001;
bool isPrime[maxn];
bool vis[maxn];
void Eratosthenes(int n){
    isPrime[0]=isPrime[1]=false;
    for(int i=2;i*i<=n;i++){
        if(isPrime[i]){
            for(int j=i*i;j<=n;j+=i)
                isPrime[j]=false;
        }
    }
}

typedef pair<int,int> pii;

void bfs(int st,int en){

    queue<pii> q;
    q.push(pii(st,0));
    vis[st]=true;
    while (!q.empty()){
        pii node=q.front();
        q.pop();
        if(node.first==en){
            cout<<node.second<<endl;
            return;
        }
        int last=node.first;
        int arr[5];
        int prr[5]={0,1,10,100,1000};
        for(int i=1;i<=4;i++){
            arr[i]=last%10;
            last/=10;
        }

        for(int i=1;i<=4;i++){
            int proto=node.first-arr[i]*prr[i];
            for(int j=0;j<10;j++){
                int val=proto+j*prr[i];
                if(val>=1000&&isPrime[val]&&!vis[val]){
                    vis[val]=true;
                    q.push(pii(val,node.second+1));
                }
            }
        }
    }
    
}

int main(){
    memset(isPrime,true,sizeof(isPrime));
    Eratosthenes(10000);
    int n,st,en;
    cin>>n;
    while(n--){
        memset(vis,false,sizeof(vis));
        cin>>st>>en;
        bfs(st,en);
    }
    return 0;
}