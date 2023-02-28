#include<iostream>
#include<string>
#include<map>
#include<queue>
using namespace std;

typedef pair<int,string> pis;

void bfs(int n){
    bool f[202]={false};
    queue<pis> q;
    q.push(pis(1%n,"1"));
    f[1%n]=true;

    pis fir,sec;
    while(!q.empty()){
        fir=q.front();
        q.pop();

        if(!fir.first){
            cout<<fir.second<<endl;
            return;
        }

        sec.first=(fir.first*10)%n;
        sec.second=fir.second+"0";
        if(!f[sec.first]){
            f[sec.first]=true;
            q.push(sec);
        }

        sec.first=(fir.first*10+1)%n;
        sec.second=fir.second+"1";
        if(!f[sec.first]){
            f[sec.first]=true;
            q.push(sec);
        }
    }
    
}

int main(){
    int n;
    while(true){
        cin>>n;
        if(!n)
            break;
        bfs(n);
    }
    return 0;
}