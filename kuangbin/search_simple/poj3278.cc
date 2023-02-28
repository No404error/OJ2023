#include<iostream>
#include<queue>
#include<map>
#include<cstring>
using namespace std;

const int maxn=100005;
const int field=100000;
int times[maxn];
int n,k;

queue<int> q;

bool searchNode(int pos,int cnt){
    if(pos==k){
        printf("%d\n",cnt);
        return true;
    }
    if(pos>=0&&pos<=field&&times[pos]==-1){
        times[pos]=cnt;
        q.push(pos);
    }
    return false;
}

int main(){
    memset(times,-1,sizeof(times));

    scanf("%d %d",&n,&k);
    
    q.push(n); 
    times[n]=0;

    if(n==k){
        printf("0");
        return 0;
    }

    while(!q.empty()){
        int pos=q.front();
        q.pop();
        int cnt=times[pos]+1;

        if(searchNode(pos-1,cnt))
            break;
        if(searchNode(pos+1,cnt))
            break;
        if(searchNode(pos*2,cnt))
            break;
    }
    return 0;
}